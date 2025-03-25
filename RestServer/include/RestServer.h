#pragma once

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class RestServer {
public:
    RestServer(net::io_context& ioc, unsigned short port);
    virtual ~RestServer();

    void start();

protected:
    virtual http::response<http::string_body> HandleRequest(const http::request<http::string_body>& req) = 0;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
