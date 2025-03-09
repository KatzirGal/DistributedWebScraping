#include "WorkerCore.h"

#include "JSONRequestHandlerFactory.h"
#include "WebServiceBase.h"

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/JSON/Object.h>

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
    else if (uri.getPath() == "/api/v1/stats") // stats will handle also here
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
    unsigned short port = 8000;
    Poco::Net::ServerSocket svs(port);
    Poco::Net::HTTPServer server(new JSONRequestHandlerFactory(*this), svs, new Poco::Net::HTTPServerParams());

    std::cout << "Starting REST API server on port " << port << std::endl;
    server.start();

    waitForTerminationRequest(); // Wait for CTRL-C or kill
    std::cout << "Stopping server..." << std::endl;
    server.stop();

    return Application::EXIT_OK;
}

