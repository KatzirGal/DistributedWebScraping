#include "JSONRequestHandlerFactory.h"

#include "WebServiceBase.h"

#include "Poco/JSON/Object.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"


class JSONRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    JSONRequestHandler(WebServiceBase& webServiceBase) : m_webServiceBase(webServiceBase) {};

public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override
    {
        response.setContentType("application/json");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

        std::ostream& out = response.send();

        if (request.getMethod() == "GET")
        {
            std::string command = request.getURI();
            const Poco::URI uri(command);
            const Poco::URI::QueryParameters queryParams = uri.getQueryParameters();

            m_webServiceBase.HandleRequest(uri, queryParams, response, out);
        }
        else
        {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            Poco::JSON::Object errorResponse;
            errorResponse.set("status", "error");
            errorResponse.set("message", "Unsupported HTTP method");
            errorResponse.stringify(out);
        }
    }

private:
    WebServiceBase& m_webServiceBase;
};

JSONRequestHandlerFactory::JSONRequestHandlerFactory(WebServiceBase& webServiceApp)
    :m_webService(webServiceApp)
{

}

Poco::Net::HTTPRequestHandler* JSONRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&)
{
    return new JSONRequestHandler(m_webService);
}
