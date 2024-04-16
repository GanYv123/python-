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

void Widget::init_tableWidget()
{//初始化表格

    ui->textEdit->close();
    if(qtw == nullptr)
        qtw = new QTableWidget(this);
    qtw->setRowCount(10);
    qtw->setColumnCount(5);
    //qtw->setGeometry(ui->frame_2->x(),ui->frame_2->y(),ui->frame_2->width(),ui->frame_2->height());
    ui->verticalLayout_5->addWidget(qtw);

    //获取学生信息

    QStringList headText;
    headText<<"学生ID"<<"成绩"<<"绩点"<<"是否及格"<<"备注";
    //qtw->setHorizontalHeaderLabels(headText); //设置水平表头
    for (int var = 0; var < headText.size(); ++var) {
        QTableWidgetItem *tableItem = new QTableWidgetItem(headText.at(var));
        QFont font = tableItem->font();
        font.setBold(true);
        font.setPointSize(14);
        tableItem->setFont(font);
        if(var&1)
            tableItem->setForeground(QBrush(Qt::red));
        qtw->setHorizontalHeaderItem(var,tableItem);
    }

    auto au = clientThread->getClientPoint();
    QString stu_infos = au->get_stu_infos();

    QStringList stu_Lists = stu_infos.split(',');
//    foreach (auto var, stu_Lists) {
//        qDebug()<<var<<'\n';
//    }
    for(int i = 0,j = 0;i < stu_Lists.size();i+=3,j++){
        if(stu_Lists.at(i).size())
            creatItemsARow(j,stu_Lists.at(i),stu_Lists.at(i+1),stu_Lists.at(i+2),!stu_Lists.at(i+1).toDouble() == 0);
    }

    qtw->show();
}

void Widget::creatItemsARow(int cu_row,QString stu_ID, QString stu_score, QString stu_GPA, bool is_jige)
{
    QTableWidgetItem *item = new QTableWidgetItem(stu_ID);
    qtw->setItem(cu_row,0,item);

    item = new QTableWidgetItem(stu_score);
    qtw->setItem(cu_row,1,item);

    item = new QTableWidgetItem(stu_GPA);
    qtw->setItem(cu_row,2,item);

    if(is_jige)
        item = new QTableWidgetItem("及格");
    else
        item = new QTableWidgetItem("不及格");
    qtw->setItem(cu_row,3,item);
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


void Widget::on_pb1_clicked(bool checked)
{
    if(checked){
        send_instruction("on_pb1_clicked");
        QTimer::singleShot(50, this, [this]() {
            //初始化tablewidget
            init_tableWidget();
        });

    }else{
        if(qtw){
            delete qtw;
            qtw = nullptr;
        }
        ui->textEdit->show();
    }
}

