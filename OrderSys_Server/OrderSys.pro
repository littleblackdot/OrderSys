QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBHelper.cpp \
    User.cpp \
    adddishform.cpp \
    cashierForm.cpp \
    chefForm.cpp \
    client_tcp.cpp \
    form.cpp \
    main.cpp \
    managerForm.cpp \
    message.cpp \
    pwdchangeform.cpp \
    serverThread.cpp \
    server_tcp.cpp \
    typechangeform.cpp \
    widget.cpp

HEADERS += \
    DBHelper.h \
    Menu.h \
    User.h \
    adddishform.h \
    cashierForm.h \
    chefForm.h \
    client_tcp.h \
    form.h \
    managerForm.h \
    message.h \
    pwdchangeform.h \
    serverThread.h \
    server_tcp.h \
    typechangeform.h \
    widget.h

FORMS += \
    adddishform.ui \
    cashierform.ui \
    chefform.ui \
    form.ui \
    managerform.ui \
    pwdchangeform.ui \
    typechangeform.ui \
    widget.ui

TRANSLATIONS += \
    OrderSys_zh_CN.ts

LIBS += -lpthread
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    others.qrc
