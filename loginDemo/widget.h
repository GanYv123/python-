#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "clientthread.h"
#include "QTableWidget"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(ClientThread* ct,QWidget *parent = nullptr);
    ~Widget();
    void send_instruction(QString instruction);
    QString read_instruction();
    Ui::Widget* getUi();
    void init_tableWidget();
    void creatItemsARow(int cu_row,QString stu_ID,QString stu_score,QString stu_GPA,bool is_jige);

private slots:
    void on_pb2_clicked();

    void on_pb3_clicked();

    void on_pb1_clicked(bool checked);

private:
    Ui::Widget *ui;
    ClientThread *clientThread;
    QTableWidget *qtw = nullptr;
};
#endif // WIDGET_H
