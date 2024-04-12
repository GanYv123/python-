#include "login_judge.h"
#include <QDebug>
#include "clientthread.h"
#include "login_ui.h"

QString INF = "";

Login_Judge::Login_Judge(QString username,QString passwd,std::map<QString,QString>* register_infors):
    username(username),passwd(passwd),userInfo(register_infors)
{
    userInfo->insert({"admin","admin@123"});
}

Login_Judge::~Login_Judge()
{
    //userInfo = nullptr;
}

bool Login_Judge::is_exit() const //查询用户是否存在
{
    for(auto it = userInfo->begin();it != userInfo->end(); it++){
        if(username == it->first)
            return true;
    }
    return false;
}

bool Login_Judge::judge_passwd(QString t_username,QString passwd) //验证密码
{
    return userInfo->at(t_username) == passwd;
}

void Login_Judge::registe_info(QString r_username, QString r_passwd) //写入注册信息到map
{
    userInfo->insert({r_username,r_passwd});

}

void Login_Judge::send_userInfo_to_server(ClientThread* ct)
{
    // 获取客户端指针，并向服务器发送数据
    Client *client = ct->getClientPoint();
    //将信息拼接成字符串
    QString user_data = ""; //username:passwd
    for(auto it = userInfo->begin(); it != userInfo->end(); ++it) {
        user_data += QString(it->first) + ':' + QString(it->second) + ',';
    }
    qDebug()<<user_data;
    client->sendTableData(user_data+QString("map"));
}

