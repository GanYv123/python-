#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <QDialog>
#include "login_judge.h" //用于登陆验证
#include <map>
#include "clientthread.h"

namespace Ui {
class login_UI;
}



class login_UI : public QDialog
{
    Q_OBJECT

public:
    explicit login_UI(QWidget *parent = nullptr);
    ~login_UI();
    //my_fun
    void send_tips_to_server(QString s);
    void send_oper_to_server(QString s);
    QString read_operSender_from_server(QString s);
    ClientThread* get_thread_client_point();


private slots:
    void on_pb_sign_up_clicked();
    void on_pb_login_in_clicked();
    void onDataReceived(const QString &data);
    void on_pb_randPasswd_clicked();

private:
    Ui::login_UI *ui;
    Login_Judge *lg;
    std::map<QString, QString> *register_infos;
    QString t_username;
    QString t_passwd;

    ClientThread *clientThread;//client thread point
};

#endif // LOGIN_UI_H
