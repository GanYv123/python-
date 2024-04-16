#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QHostAddress>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port); // 连接服务器
    void sendButtonClickedSignal(); // 发送按钮点击信号
    void sendTableData(const QString &data); // 发送表格数据
    QString readData(); // 读取服务器返回的数据
    QString get_Current_Data(); //返回最新读取到的数据
    QString get_leaf_info();
    QString get_stu_infos();

signals:
    void signalReceived(const QVariantMap &data); // 收到信号的信号

private slots:
    void handleReceivedData(); // 处理接收到的数据

private:
    QTcpSocket *m_socket;
    QString current_Data,leaf_info,students_infos;
};

#endif // CLIENT_H
