#include <QCoreApplication>
#include "tcp_client.h"
#include <iostream>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  std::cout << "--- TCP Client ---" << std::endl;
  TcpClient tc;

  return a.exec();
}

