//
// Created by liyanan on 8/4/20.
//

#ifndef HELLOQT_TCP_CLIENT_H
#define HELLOQT_TCP_CLIENT_H


#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
Q_OBJECT

public:
  TcpClient(QObject *p = 0);
  ~TcpClient();

public slots:
  void send_msg(); // 向server发信息
  void read_msg(); // 读server回复的信息
  void end_connent(); // 被断开连接后提示

private:
  QTcpSocket *tSocket;
};


#endif //HELLOQT_TCP_CLIENT_H
