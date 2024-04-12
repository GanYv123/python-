#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "QTimer"

Widget::Widget(ClientThread* ct,QWidget *parent)
    :clientThread(ct),QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->setFontPointSize(20);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::send_instruction(QString instruction)
{
    auto c = clientThread->getClientPoint();
    c->sendTableData(instruction);
}

QString Widget::read_instruction()
{
    return "NU";
}

Ui::Widget *Widget::getUi()
{
    return ui;
}

void Widget::on_pb2_clicked()
{//绘制直方图
    //发送绘制直方图指令
    if(ui->pb2->isChecked()){
        //开启直方图
        qDebug()<<"开启直方图";
        send_instruction("Enable_histogram");
    }
    else{
        //关闭直方图
        qDebug()<<"关闭直方图";
        send_instruction("Turn_off_histogram");
    }
}

void Widget::on_pb3_clicked()
{//绘制茎叶图
    if(ui->pb3->isChecked()){
        qDebug()<<"开启茎叶";
        send_instruction("Enable_leaf");

        QTimer::singleShot(500, this, [this]() {
            auto a = clientThread->getClientPoint();
            qDebug()<<"茎叶图";
            ui->textEdit->setReadOnly(true);
            ui->textEdit->setText(a->get_leaf_info());

        });


    }
    else{
        //关闭直方图
        qDebug()<<"关闭茎叶";
        send_instruction("Turn_off_leaf");
        ui->textEdit->clear();
    }
}

