#include "networking.h"

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPCookie.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/Context.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>  // For std::unique_ptr

bool DownloadFile(const std::string& url, const std::string& outputFilename)
{
    try {
        // Parse the URL
        Poco::URI uri(url);
        std::string scheme = uri.getScheme();
        std::string host = uri.getHost();
        unsigned short port = uri.getPort();
        std::string path = uri.getPathAndQuery();
        if (path.empty()) path = "/";

        // Create the appropriate session type dynamically
        std::unique_ptr<Poco::Net::HTTPClientSession> session;

        if (scheme == "https") {
            // Create HTTPS session with SSL context
            Poco::Net::Context::Ptr context = new Poco::Net::Context(
                Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_RELAXED
            );
            session = std::make_unique<Poco::Net::HTTPSClientSession>(host, port, context);
        }
        else {
            // Create HTTP session
            session = std::make_unique<Poco::Net::HTTPClientSession>(host, port);
        }

        // Set timeout (30 seconds)
        session->setTimeout(Poco::Timespan(30, 0));

        // Create an HTTP GET request
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);

        // Set a real User-Agent to prevent blocks
        request.set("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36");

        // Enable cookies
        request.add("test_cookie", "test_value");

        // Send the request
        session->sendRequest(request);

        // Get the HTTP response
        Poco::Net::HTTPResponse response;
        std::istream& responseStream = session->receiveResponse(response);

        // Read cookies from the response
        std::vector<Poco::Net::HTTPCookie> cookies;
        response.getCookies(cookies);
        for (const auto& c : cookies) {
            //session->add(c);
        }

        // Check if the request was successful (status 200 OK)
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            throw std::runtime_error("Failed to download file, HTTP Status: " + std::to_string(response.getStatus()));
        }

        // Open the output file for writing
        std::ofstream outFile(outputFilename, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for writing: " + outputFilename);
        }

        // Copy response stream to file
        Poco::StreamCopier::copyStream(responseStream, outFile);
        outFile.close();

        std::cout << "File downloaded successfully: " << outputFilename << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error downloading file: " << e.what() << std::endl;
        return false;
    }
}
