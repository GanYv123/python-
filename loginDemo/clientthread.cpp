// clientthread.cpp

#include "clientthread.h"
#include "QTimer"

ClientThread::ClientThread(QObject *parent)
    : QThread(parent), client(new Client), connected(false)
{
    client->connectToServer("127.0.0.1", 12345);

    //client->sendTableData("客户端 ClientThread is running!");
    // 添加延迟 1000 毫秒（1 秒）
    QThread::msleep(1000);
    client->sendTableData("first_connected");//初次登录验证

    QTimer::singleShot(1000, this, [this]() {
        client->sendTableData("send_infos");//初始化用户信息
    });


}

ClientThread::~ClientThread()
{
    stopThread();
    delete client;
}

void ClientThread::startThread(){start();}

void ClientThread::stopThread(){requestInterruption();wait();}

bool ClientThread::isConnected() const
{//返回连接状态
    return this->connected;
}

Client *ClientThread::getClientPoint()
{
    return this->client;
}

void ClientThread::run()
{
    while (!isInterruptionRequested()) {
        QString s = client->readData();
        if (s.size()) {
            emit dataReceived(s);
        }
    }
}

void ClientThread::handleConnection()
{
    connected = true; // 设置连接状态为true
}

void ClientThread::handleDisconnection()
{
    connected = false; // 设置连接状态为false
}
