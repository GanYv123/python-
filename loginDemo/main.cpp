#include "widget.h"
#include "login_ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login_UI lu;
    lu.show();

    return a.exec();
}
