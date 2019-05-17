//
// Created by liyanan on 5/16/19.
//

#ifndef COSMOS_CONNECTOR_H
#define COSMOS_CONNECTOR_H

#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;

#include "Message.h"
#include "RWHandler.h"

class Connector {
public:
    Connector(io_service& ios, const std::string& strIp, short port) : m_ios(ios),
            m_socket(ios), m_serverAddr(tcp::endpoint(address::from_string(strIp), port)), m_isConnected(false), m_chkThread(nullptr) {
        CreateEventHandler(ios);
    }
    ~Connector() {

    }

    bool Start() {
        m_eventHandler->GetSocket().async_connect(m_serverAddr, [this](const boost::system::error_code& error) {
            if (error) {
                HandleConnectError(error);
                return;
            }
            LOG(INFO) << "connect ok";
            m_isConnected = true;
            m_eventHandler->HandleRead();
        });
        boost::this_thread::sleep(boost::posix_time::seconds(1));
        return m_isConnected;
    }

    bool IsConnected() const {
        return m_isConnected;
    }

    void Send(const char* data, int len) {
        if(!m_isConnected) {
            return;
        }
        m_eventHandler->HandleWrite(data, len);
    }

private:
    void CreateEventHandler(io_service& ios) {
        m_eventHandler = std::make_shared<RWHandler>(ios);
        m_eventHandler->SetCallBackError([this](int connid){HandleRWError(connid);});
    }
    void CheckConnect(){
        if(m_chkThread != nullptr) {
            return;
        }
        m_chkThread = std::make_shared<std::thread>([this] {
            while(true) {
                if(!IsConnected()) {
                    Start();
                }
                boost::this_thread::sleep(boost::posix_time::seconds(1));
            }
        });
    };
    void HandleConnectError(const boost::system::error_code& error) {
        m_isConnected = false;
        LOG(INFO) << error.message();
        m_eventHandler->CloseSocket();
        CheckConnect();
    }
    void HandleRWError(int connid) {
        m_isConnected = false;
        CheckConnect();
    }


private:
    io_service& m_ios;
    tcp::socket m_socket;

    tcp::endpoint m_serverAddr;

    std::shared_ptr<RWHandler> m_eventHandler;
    bool m_isConnected;
    std::shared_ptr<std::thread> m_chkThread;
};

#endif //COSMOS_CONNECTOR_H
