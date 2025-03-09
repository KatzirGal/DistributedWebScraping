#pragma once

#include <string>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>
#include <Poco/Util/ServerApplication.h>

class WebServiceBase : public Poco::Util::ServerApplication
{
public:
	WebServiceBase();
	~WebServiceBase();

	virtual bool HandleRequest(const Poco::URI& uri, const Poco::URI::QueryParameters& queryParameters, Poco::Net::HTTPServerResponse& response, std::ostream& out) = 0;
};