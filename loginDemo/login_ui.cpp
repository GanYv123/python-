#include "login_ui.h"
#include "ui_login_ui.h"
#include "widget.h"
#include "client.h"
#include "clientthread.h"
#include <Windows.h>
#include <shellapi.h>

login_UI::login_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login_UI)
{
    ui->setupUi(this);
    QThread *serverThread = new start_server_thread;
    serverThread->start();
    QThread::sleep(1);//等待 确保服务器正常启动
    //register_infos = new std::map<QString,QString>;
    clientThread = new ClientThread(this);
    connect(clientThread, &ClientThread::dataReceived, this, &login_UI::onDataReceived);
    clientThread->startThread(); // 在构造函数中启动线程
}

login_UI::~login_UI()
{
    delete ui;
    //delete register_infos;
    delete clientThread;
}


//像服务器发送数据
void login_UI::send_tips_to_server(QString s){
    auto c = clientThread->getClientPoint();
    c->sendTableData(s);
}

void login_UI::send_oper_to_server(QString s)
{//发送指令
    auto c = clientThread->getClientPoint();
    c->sendTableData(s);
}

QString login_UI::read_operSender_from_server(QString s)
{//得到返回的指令
    auto c = clientThread->getClientPoint();
    QString data = c->get_Current_Data();
    if(data.contains(s))
        return data.remove(s);
    else
        return "Admin@123";
}

ClientThread *login_UI::get_thread_client_point()
{
    return clientThread;
}

void start_server_thread::start_server()
{//启动服务器
    const char* _PATH_SERVER_  = "python C:\\Users\\17255\\Desktop\\python\\codeDemo\\shiyan1\\main.py";
    system(_PATH_SERVER_);

}

void login_UI::on_pb_sign_up_clicked()
{
    if(ui->le_username->text().isEmpty())
    {
        send_tips_to_server("输入正确格式");
        ui->label_tips->setText("输入正确格式");
        return;
    }
    t_username = ui->le_username->text();
    t_passwd = ui->le_passwd->text();
    lg = new Login_Judge(t_username,t_passwd,register_infos);

    if(lg->is_exit()){
        //如果存在
        //qDebug()<<"用户存在可直接登录";
        send_tips_to_server("用户存在可直接登录");
        ui->label_tips->setText("用户存在可直接登录");

        delete lg;
        return;
    }
    //不存在进行信息写入
    lg->registe_info(t_username,t_passwd);
    //qDebug()<<"注册成功";
    //send_tips_to_server("注册成功->\n");
    ui->label_tips->setText("注册成功");
    //将本次的用户信息发送给服务器
    lg->send_userInfo_to_server(clientThread);
    delete lg;
}

void login_UI::on_pb_login_in_clicked()
{
    t_username = ui->le_username->text();
    t_passwd = ui->le_passwd->text();
    lg = new Login_Judge(t_username,t_passwd,register_infos);

    if(!lg->is_exit()){
        //qDebug()<<"用户不存在，请注册";
        ui->label_tips->setText("用户不存在，请注册");
        send_tips_to_server("用户不存在，请注册");
        delete lg;
        return;
    }
    //如果用户名正确 进行密码验证
    if(!lg->judge_passwd(t_username,t_passwd)){
        //qDebug()<<"密码错误";
        ui->label_tips->setText("密码错误");
        send_tips_to_server("密码错误");
        delete lg;
        return;
    }
    //密码正确,跳转页面
    //qDebug()<<"密码正确，登录成功！";
    ui->label_tips->setText("密码正确，登录成功！");
    send_tips_to_server("密码正确，登录成功！"+QString("用户UID ： %1").arg(ui->le_username->text()));
    delete lg;
    //登录成功之后的函数
    Widget* w = new Widget(clientThread);
    w->show();
    //菜单选择界面
    this->close();
}

QString check_connected = "_Tips_";
QString check_userInfos = "userInfos:";

void login_UI::onDataReceived(const QString &data)
{
    qDebug()<<data;
    if(data.contains(check_connected)){
        QString ts = data;
        ts.remove(check_connected);
        QMetaObject::invokeMethod(ui->label_tips, "setText", Qt::QueuedConnection, Q_ARG(QString, ts));
        return;
    }
    if(data.contains(check_userInfos)){
        qDebug()<<"infos = "<<data;
        //从后端初始化用户信息
        QString infos = data;
        infos.remove(check_userInfos);

        QStringList str = infos.split("\t");
        std::map<QString,QString> *tp = new std::map<QString,QString>;

        for(int i = 0;i < str.size()-1; i+=2)
            tp->insert({QString(str[i]),QString(str[i+1])});
        register_infos = tp;
    }
}

void login_UI::on_pb_randPasswd_clicked()
{//点击生成随机密码到密码栏
    send_oper_to_server("login_UI::on_pb_randPasswd_clicked()");
    QString data = read_operSender_from_server("login_UI::on_pb_randPasswd_clicked()");
    if(data.size()){
        ui->label_tips->setText(data);
        ui->le_passwd->setText(data);
    }
}

void start_server_thread::run()
{
    start_server();

}
