QT       += core gui
QT       += core gui network
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    clientthread.cpp \
    login_judge.cpp \
    login_ui.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    client.h \
    clientthread.h \
    login_judge.h \
    login_ui.h \
    widget.h

FORMS += \
    login_ui.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    backgroundPNG.qrc
