#include "networking.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <fstream>
#include <iostream>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ssl = boost::asio::ssl;
using tcp = asio::ip::tcp;

bool DownloadFile(const std::string& url, const std::string& outputFilename) {
    try {
        // Parse the URL
        std::string protocol, host, target;
        unsigned short port = 80; // Default HTTP port

        if (url.substr(0, 7) == "http://") {
            protocol = "http";
            host = url.substr(7);
            port = 80;
        }
        else if (url.substr(0, 8) == "https://") {
            protocol = "https";
            host = url.substr(8);
            port = 443; // Default HTTPS port
        }
        else {
            std::cerr << "Invalid URL format.\n";
            return false;
        }

        // Extract the host and target (path)
        size_t pos = host.find('/');
        if (pos != std::string::npos) {
            target = host.substr(pos);
            host = host.substr(0, pos);
        }
        else {
            target = "/";
        }

        // Set up Boost.Asio and SSL context
        asio::io_context ioc;
        ssl::context ctx(ssl::context::sslv23_client);
        tcp::resolver resolver(ioc);

        if (protocol == "https") {
            ctx.set_verify_mode(ssl::verify_peer);
            ctx.set_default_verify_paths();
        }

        // Resolve the host
        auto const results = resolver.resolve(host, std::to_string(port));

        if (protocol == "http") {
            // HTTP connection
            tcp::socket socket(ioc);
            asio::connect(socket, results.begin(), results.end());

            // Set up HTTP GET request
            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            // Send request
            http::write(socket, req);

            // Receive response
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(socket, buffer, res);

            // Check response status
            if (res.result() != http::status::ok) {
                std::cerr << "HTTP request failed with status: " << res.result_int() << "\n";
                return false;
            }

            // Write to file
            std::ofstream outputFile(outputFilename, std::ios::binary);
            if (!outputFile) {
                std::cerr << "Failed to open output file: " << outputFilename << "\n";
                return false;
            }
            outputFile << beast::buffers_to_string(res.body().data());
            outputFile.close();

            // Close connection
            beast::error_code ec;
            socket.shutdown(tcp::socket::shutdown_both, ec);
            return true;
        }
        else {
            // HTTPS connection
            beast::ssl_stream<beast::tcp_stream> sslStream(ioc, ctx);
            beast::get_lowest_layer(sslStream).connect(results);
            sslStream.handshake(ssl::stream_base::client);

            // Set up HTTPS GET request
            http::request<http::string_body> req{ http::verb::get, target, 11 };
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            // Send request
            http::write(sslStream, req);

            // Receive response
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(sslStream, buffer, res);

            // Check response status
            if (res.result() != http::status::ok) {
                std::cerr << "HTTPS request failed with status: " << res.result_int() << "\n";
                return false;
            }

            // Write to file
            std::ofstream outputFile(outputFilename, std::ios::binary);
            if (!outputFile) {
                std::cerr << "Failed to open output file: " << outputFilename << "\n";
                return false;
            }
            outputFile << beast::buffers_to_string(res.body().data());
            outputFile.close();

            // Close connection
            beast::error_code ec;
            sslStream.shutdown(ec);
            if (ec && ec != beast::errc::not_connected) {
                std::cerr << "Shutdown failed: " << ec.message() << "\n";
            }

            return true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Download failed: " << e.what() << "\n";
        return false;
    }
}
