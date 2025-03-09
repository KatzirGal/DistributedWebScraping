#pragma once

#include <vector>
#include <string>

#include "WebServiceBase.h"

#include <Poco/URI.h>


class WorkerCore : public WebServiceBase
{
public:
	WorkerCore();
	~WorkerCore();

	virtual bool HandleRequest(const Poco::URI& uri, const Poco::URI::QueryParameters& queryParameters, Poco::Net::HTTPServerResponse& response, std::ostream& out) override;

protected:
	int main(const std::vector<std::string>& argv) override;

private:
	void NotifyMaster(const std::string& masterIP, unsigned short masterPort, unsigned short workerPort);

private:

};