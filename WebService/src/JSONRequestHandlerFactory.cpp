#include "JSONRequestHandlerFactory.h"

#include "WebServiceBase.h"

JSONRequestHandlerFactory::JSONRequestHandlerFactory(WebServiceBase& webServiceApp)
    :m_webService(webServiceApp)
{

}

Poco::Net::HTTPRequestHandler* JSONRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest&)
{
    return nullptr;
}
