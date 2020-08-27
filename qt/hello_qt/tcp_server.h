//
// Created by liyanan on 8/4/20.
//

#ifndef HELLOQT_TCP_SERVER_H
#define HELLOQT_TCP_SERVER_H


#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : QTcpServer
{
Q_OBJECT

public:
  TcpServer(QTcpServer *p = 0);
  ~TcpServer();

public slots:
  void accept_connection(); // 处理连接请求
  void read_and_reply(); // 读信息并回复，然后断连

private:
  QTcpServer *tServer;
  QTcpSocket *tSocket;
};


#endif //HELLOQT_TCP_SERVER_H
