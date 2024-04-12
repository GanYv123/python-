// clientthread.h

#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include "client.h"

class ClientThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientThread(QObject *parent = nullptr);
    ~ClientThread();
    void startThread(); // 添加一个公共方法来启动线程
    void stopThread(); // 停止线程的方法
    bool isConnected()const;
    Client* getClientPoint();  

signals:
    void dataReceived(const QString &data); // 接收到消息的信号
    void connectedToServer();
    void disconnectedFromServer();

private slots:
    void handleConnection();
    void handleDisconnection();

protected:
    void run() override;
private:
    Client *client;
    bool connected; // 连接状态标志
};

#endif // CLIENTTHREAD_H
