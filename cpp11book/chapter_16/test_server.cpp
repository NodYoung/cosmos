//
// Created by liyanan on 5/16/19.
//
#include <boost/asio.hpp>
using namespace boost::asio;

#include "Server.h"

void TestServer() {
    boost::asio::io_service ios;
    //boost::asio::io_service::work work(ios);
    //std::thread thd([&ios]{ios.run();});

    Server server(ios, 9900);
    server.Accept();
    ios.run();

    //thd.join();

}

int main() {
    TestServer();
    return 0;
}