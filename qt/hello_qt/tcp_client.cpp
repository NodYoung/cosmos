//
// Created by liyanan on 8/4/20.
//

#include "tcp_client.h"

#include <QByteArray>
#include <QHostAddress>
#include <QTcpSocket>
#include <iostream>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtGui/QPixmap>
#include <QtCore/QBuffer>
#include <QtCore/QJsonArray>
#include "tcp_client.h"

const quint16 PORT = 2333;

TcpClient::TcpClient(QObject *p) :
    QObject(p) {
  tSocket = new QTcpSocket(this);
  std::cout << "--- Connect to Host ---" << std::endl;
  /* 向 server 发送连接请求 */
  tSocket->connectToHost(QHostAddress::LocalHost, PORT);
  /*------- 连接信号与槽 -------*/
  /* 一连上 server 就发信息 */
  connect(tSocket, SIGNAL(connected()),
          this, SLOT(send_msg()));
  /* server 有回复就读取 */
  connect(tSocket, SIGNAL(readyRead()),
          this, SLOT(read_msg()));
  /* server 把连接断了就发出提示 */
  connect(tSocket, SIGNAL(disconnected()),
          this, SLOT(end_connent()));
}

TcpClient::~TcpClient() {
  delete tSocket;
}

void TcpClient::send_msg() {
  std::cout << "--- Successfully Connected ---\n"
            << "--- Sending Message ---"
            << std::endl;
  QJsonObject json_msg;
  json_msg.insert("session", 85596);
  json_msg.insert("station_id", "OP170");
  json_msg.insert("module", "station");
  json_msg.insert("action", "update");
  QJsonArray json_picture_array;
  QJsonObject json_picture;
  json_picture.insert("p_name", 58);
  QImage img_msg_raw("/home/liyanan/gitlab/message_xmate_vision/a.png");
  QImage img_msg = img_msg_raw.scaled(150, 100, Qt::KeepAspectRatio);
  QByteArray ba;
  QBuffer buf(&ba);
  buf.open(QIODevice::WriteOnly);
  img_msg.save(&buf, "BMP");
  QByteArray ba2 = ba.toBase64();
  QString b64str = QString::fromLatin1(ba2);
  json_picture.insert("p_code", b64str);
  json_picture.insert("p_result", "ok");
  json_picture_array.append(json_picture);
  json_msg.insert("picture", QJsonValue(json_picture_array));
  QJsonDocument doc_msg;
  doc_msg.setObject(json_msg);
  QByteArray byte_msg = doc_msg.toJson();

  /* 发信息 */
  tSocket->write(byte_msg);
//  tSocket->write(QByteArray("Hello world!"));
}

void TcpClient::read_msg() {
  /* 读信息 */
  QByteArray ba = tSocket->readAll();
  std::cout << ba.data() << std::endl;
}

void TcpClient::end_connent() {
  std::cout << "--- Connection Ended ---" << std::endl;
}
