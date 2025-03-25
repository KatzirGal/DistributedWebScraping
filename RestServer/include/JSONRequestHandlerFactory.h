#pragma once

#include "WebServiceBase.h"

#include <Poco/Net/HTTPRequestHandlerFactory.h>

class JSONRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    JSONRequestHandlerFactory(WebServiceBase& webServiceApp);

public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest&) override;

private:
    WebServiceBase& m_webService;
};