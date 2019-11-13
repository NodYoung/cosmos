//
// Created by liyanan on 5/16/19.
//

#include <boost/asio.hpp>
using namespace boost::asio;

#include "Connector.h"

int main() {
    io_service ios;
    boost::asio::io_service::work work(ios);
    boost::thread thd([&ios]{ios.run();});

    Connector conn(ios, "192.168.2.154", 9900);
    conn.Start();

    std::string str;

    if(!conn.IsConnected()) {
        std::cin >> str;
        return -1;
    }

    const int len = 512;
    char line[len] = "";

    while(std::cin >> str) {
        char header[HEAD_LEN] = {};
        //int totalLen = str.length() + 1 + HEAD_LEN;
        int totalLen = str.length() + HEAD_LEN;
        std::sprintf(header, "%04d", totalLen);
        memcpy(line, header, HEAD_LEN);
        memcpy(line+HEAD_LEN, str.c_str(), str.length() + 1);
        conn.Send(line, totalLen);
        memset(line, 0, 512* sizeof(char));
    }

    return 0;
}