#include "WorkerCore.h"

#include "networking.h"
#include "RestServer.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <nlohmann/json.hpp>

#include <iostream>
#include <sstream>
#include <thread>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

WorkerCore::WorkerCore(net::io_context& ioc, unsigned short port) : RestServer(ioc, port) {}

WorkerCore::~WorkerCore() {}

http::response<http::string_body> WorkerCore::HandleRequest(const http::request<http::string_body>& req)
{
    http::response<http::string_body> res;

    if (req.method() != http::verb::get && req.method() != http::verb::post) {
        res.result(http::status::bad_request);
        res.body() = "Unsupported HTTP method";
        res.prepare_payload();
        return res;
    }

    const std::string target = std::string(req.target());

    if (target == "/api/v1/get_urls") {
        DownloadFile("https://www.ynet.co.il/home/0,7340,L-8,00.html", "C:/Users/Gal/Downloads/myHtml.html");

        nlohmann::json json_response = {
            { "get_urls", "ok" }
        };

        http::response<http::string_body> res;

        res.version(req.version());                         
        res.keep_alive(req.keep_alive());                   
        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = json_response.dump();
        res.prepare_payload();                              
        return res;
    }
    else if (target == "/api/v1/stats") {
        nlohmann::json json_response = {
            { "totalRequests", 5432 }
        };

        res.result(http::status::ok);
        res.set(http::field::content_type, "application/json");
        res.body() = json_response.dump();
        res.prepare_payload();
        return res;
    }

    res.result(http::status::not_found);
    res.body() = "Not found";
    res.prepare_payload();
    return res;
}

void WorkerCore::NotifyMaster(const std::string& masterIP, unsigned short masterPort, unsigned short workerPort)
{
    try {
        boost::asio::io_context ioc;

        // Resolve the master IP and port
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(masterIP, std::to_string(masterPort));

        // Connect to the master
        tcp::socket socket(ioc);
        boost::asio::connect(socket, results.begin(), results.end());

        // Create JSON payload
        nlohmann::json json_payload = {
            { "ip", "worker_ip" },  // TODO: dynamically fetch worker IP
            { "port", workerPort }
        };
        std::string body = json_payload.dump();

        // Create HTTP POST request
        http::request<http::string_body> req{ http::verb::post, "/register_worker", 11 };
        req.set(http::field::host, masterIP);
        req.set(http::field::content_type, "application/json");
        req.content_length(body.size());
        req.body() = body;

        // Send request
        http::write(socket, req);

        // Receive response
        boost::beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(socket, buffer, res);

        std::cout << "MasterNode response: " << res.result_int() << " " << res.reason() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Failed to notify MasterNode: " << ex.what() << std::endl;
    }
}
