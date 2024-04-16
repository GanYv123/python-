#include "Client.h"
#include <QDebug>
#include <widget.h>
#include"ui_widget.h"
#include "login_ui.h"

Client::Client(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::handleReceivedData);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    m_socket->connectToHost(QHostAddress(host), port);
}

void Client::sendButtonClickedSignal()
{
    QByteArray data = "ButtonClicked";
    m_socket->write(data);
}

void Client::sendTableData(const QString &data)
{
    QByteArray sendData = data.toUtf8(); // 将数据转换为字节数组
    m_socket->write(sendData);
}

QString Client::readData()
{
    QString decodedData;
    while (m_socket->bytesAvailable() > 0) { // 检查套接字中是否有可读数据
        QByteArray receivedData = m_socket->readAll(); // 从套接字中读取所有可用的数据
        decodedData = QString::fromUtf8(receivedData); // 将接收到的数据解码为 UTF-8 字符串并添加到已接收的数据中
    }

    if(!decodedData.isEmpty()) {
        qDebug() << "Received data:" << decodedData;
        current_Data = decodedData;
        if(decodedData.contains("Stem"))
            leaf_info = decodedData;
        if(decodedData.contains("students_infos")){
            students_infos = decodedData;
            students_infos.remove("students_infos");

        }
    }

    return decodedData;
}

QString Client::get_Current_Data()
{
    return current_Data;
}

QString Client::get_leaf_info()
{
    return leaf_info;
}

QString Client::get_stu_infos()
{
    return students_infos;
}


void Client::handleReceivedData()
{
    QByteArray receivedData = m_socket->readAll(); // 从套接字中读取所有可用的数据
    QJsonDocument doc = QJsonDocument::fromJson(receivedData); // 解析 JSON 数据
    if (!doc.isNull() && doc.isObject()) {
        QVariantMap data = doc.toVariant().toMap();
        emit signalReceived(data); // 发出信号，将接收到的数据发送给槽函数处理
    }
}
