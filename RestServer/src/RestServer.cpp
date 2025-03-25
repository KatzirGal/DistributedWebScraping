#include "RestServer.h"

#include "rest_server.hpp"

#include <iostream>

class RestServer::Impl {
public:
    Impl(RestServer& parent, net::io_context& ioc, unsigned short port)
        : m_parent(parent), m_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), m_socket(ioc) {
    }

    void start() {
        do_accept();
    }

private:
    RestServer& m_parent;
    tcp::acceptor m_acceptor;
    tcp::socket m_socket;

    void do_accept() {
        m_acceptor.async_accept(m_socket, [this](beast::error_code ec) {
            if (!ec) {
                std::make_shared<Session>(std::move(m_socket), m_parent)->start();
            }
            do_accept();
            });
    }

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket, RestServer& parent)
            : m_socket(std::move(socket)), m_parent(parent) {
        }

        void start() {
            do_read();
        }

    private:
        tcp::socket m_socket;
        beast::flat_buffer m_buffer;
        http::request<http::string_body> m_req;
        RestServer& m_parent;

        void do_read() {
            auto self = shared_from_this();
            http::async_read(m_socket, m_buffer, m_req,
                [self](beast::error_code ec, std::size_t) {
                    if (!ec) self->do_write();
                });
        }

        void do_write() {
            http::response<http::string_body> res = m_parent.handle_request(m_req);

            auto self = shared_from_this();
            http::async_write(m_socket, res, [self](beast::error_code ec, std::size_t) {
                self->m_socket.shutdown(tcp::socket::shutdown_send, ec);
                });
        }
    };
};

RestServer::RestServer(net::io_context& ioc, unsigned short port)
    : m_impl(std::make_unique<Impl>(*this, ioc, port)) {
}

void RestServer::start() {
    m_impl->start();
}
