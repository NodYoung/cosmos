//
// Created by liyanan on 8/4/20.
//

#include "tcp_server.h"
#include <QByteArray>
#include <QHostAddress>
#include <iostream>
#include <QtCore/QJsonParseError>
#include <QtCore/QFile>

const quint16 PORT = 2333;

TcpServer::TcpServer(QTcpServer *p) :
    QTcpServer(p)
{
  tServer = new QTcpServer;
  tSocket = new QTcpSocket;
  /* 监听端口 */
  if(tServer->listen(QHostAddress::Any, PORT))
    std::cout << "--- Linsting to Port ---" << std::endl;
  else
    std::cout << "*** FAIL LISTING ***" << std::endl;
  /* 有新连接请求就处理它 */
  connect(tServer, SIGNAL(newConnection()),
          this, SLOT(accept_connection()));
}

TcpServer::~TcpServer()
{
  delete tServer;
  delete tSocket;
}

void TcpServer::accept_connection()
{
  std::cout << "--- Accept Connection ---" << std::endl;
  /* server让自己的socket与client的socket相连 */
  tSocket = tServer->nextPendingConnection();
  /* socket一收到信息就读取并回复 */
  connect(tSocket, SIGNAL(readyRead()),
          this, SLOT(read_and_reply()));
}

void TcpServer::read_and_reply()
{
  std::cout << "--- Read Message ---" << std::endl;
  /* 读信息 */
  QByteArray ba = tSocket->readAll();

  QJsonParseError json_error;
  QJsonDocument json_doc = QJsonDocument::fromJson(ba, &json_error);
  if (!json_doc.isNull() && (json_error.error == QJsonParseError::NoError)) {
    std::cout << "write to file" << std::endl;
    QFile file("/home/liyanan/gitlab/message_xmate_vision/a.json");
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(json_doc.toJson());
    file.close();
  }

  std::cout << ba.data() << std::endl;
  std::cout << "--- Reply ---" << std::endl;
  /* 回复 */
  tSocket->write("Nice day");
  tSocket->close();
}