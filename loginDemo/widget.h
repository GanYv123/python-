#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "clientthread.h"

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

private slots:
    void on_pb2_clicked();

    void on_pb3_clicked();

private:
    Ui::Widget *ui;
    ClientThread *clientThread;
};
#endif // WIDGET_H
