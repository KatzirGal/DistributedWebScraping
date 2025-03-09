#include "WorkerCore.h"

#include "JSONRequestHandlerFactory.h"
#include "WebServiceBase.h"
#include <argparse/argparse.hpp> 
#include <iostream>
#include <sstream>

#include <Poco/JSON/Object.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>

WorkerCore::WorkerCore()
{
}

WorkerCore::~WorkerCore()
{
}

bool WorkerCore::HandleRequest(const Poco::URI& uri, const Poco::URI::QueryParameters& queryParameters, Poco::Net::HTTPServerResponse& response, std::ostream& out)
{
    std::unordered_map<std::string, std::string> params;
    for (const auto& queryParameter : queryParameters) {
        params[queryParameter.first] = queryParameter.second;
    }


    if (uri.getPath() == "/api/v1/similar")
    {
        return true;
    }
    else if (uri.getPath() == "/api/v1/stats")
    {
        Poco::JSON::Object responseObj;

        responseObj.set("totalRequests", 5432);
        responseObj.stringify(out);

        return true;
    }

    return false;
}

int WorkerCore::main(const std::vector<std::string>& argv)
{
    // Workaround for program.parse_args cause it expect to have the first parameter (executable name) 
    // The poco server omit it but argparse expect it.
    std::vector<std::string> argvFix = { "WorkerNode" }; 
    argvFix.insert(argvFix.end(), argv.begin(), argv.end());
    argparse::ArgumentParser program("WorkerNode");

    program.add_argument("master_ip")
        .help("IP address of the MasterNode")
        .default_value(std::string("127.0.0.1"));  // Default to localhost

    program.add_argument("master_port")
        .help("Port number of the MasterNode")
        .default_value(8000)
        .scan<'i', int>();

    try {
        // Pass argv, but skip argv[0] (executable name)
        program.parse_args(std::vector<std::string>(argvFix.begin(), argvFix.end()));

        std::string masterIP = program.get<std::string>("master_ip");
        unsigned short masterPort = static_cast<unsigned short>(program.get<int>("master_port"));

        std::cout << "WorkerNode started with Master IP: " << masterIP
            << " and Port: " << masterPort << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing arguments: " << e.what() << std::endl;
        return 1;  // Exit with error
    }

    std::string masterIP = program.get<std::string>("master_ip");
    unsigned short masterPort = static_cast<unsigned short>(program.get<int>("master_port"));

    // Choose an available port
    Poco::Net::ServerSocket svs(0);
    unsigned short workerPort = svs.address().port();
    std::cout << "WorkerNode listening on port: " << workerPort << std::endl;

    // Notify MasterNode
    NotifyMaster(masterIP, masterPort, workerPort);

    Poco::Net::HTTPServer server(new JSONRequestHandlerFactory(*this), svs, new Poco::Net::HTTPServerParams());
    server.start();

    waitForTerminationRequest();
    server.stop();

    return Application::EXIT_OK;
}

void WorkerCore::NotifyMaster(const std::string& masterIP, unsigned short masterPort, unsigned short workerPort)
{
    try {
        Poco::URI masterURI("http://" + masterIP + ":" + std::to_string(masterPort) + "/register_worker");
        Poco::Net::HTTPClientSession session(masterURI.getHost(), masterURI.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, masterURI.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);
        request.setContentType("application/json");

        Poco::JSON::Object json;
        json.set("ip", "worker_ip");  // You need to retrieve the actual IP of the worker
        json.set("port", workerPort);

        std::ostringstream jsonStream;
        json.stringify(jsonStream);
        std::string jsonString = jsonStream.str();

        request.setContentLength(jsonString.length());
        std::ostream& os = session.sendRequest(request);
        os << jsonString;

        Poco::Net::HTTPResponse response;
        std::istream& rs = session.receiveResponse(response);
        std::cout << "MasterNode response: " << response.getStatus() << " " << response.getReason() << std::endl;
    }
    catch (const Poco::Exception& ex) {
        std::cerr << "Failed to notify MasterNode: " << ex.displayText() << std::endl;
    }
}

