#pragma once

#include "RestServer.h"

#include <boost/beast/http.hpp>
#include <string>

class WorkerCore : public RestServer
{
public:
    WorkerCore(net::io_context& ioc, unsigned short port);
    ~WorkerCore();

    // Overrides RestServer's virtual handler
    virtual boost::beast::http::response<boost::beast::http::string_body>
        HandleRequest(const boost::beast::http::request<boost::beast::http::string_body>& req) override;

private:
    void NotifyMaster(const std::string& masterIP, unsigned short masterPort, unsigned short workerPort);
};
