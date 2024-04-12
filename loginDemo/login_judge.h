#ifndef LOGIN_JUDGE_H
#define LOGIN_JUDGE_H

#include<map>
#include<QWidget>
#include<QString>
#include"clientthread.h"

class Login_Judge
{
    std::map<QString,QString>* userInfo; //用户名和密码


public:
    Login_Judge(QString username,QString passwd,std::map<QString,QString>*);
    ~Login_Judge();
    bool is_exit() const;//检查用户是否存在
    bool judge_passwd(QString,QString);//密码判断
    void registe_info(QString,QString);//写入注册信息到map
    void send_userInfo_to_server(ClientThread* ct);

private:
    QString username;
    QString passwd;
};

#endif // LOGIN_JUDGE_H
