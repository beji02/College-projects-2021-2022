QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ActiuneUndo.cpp \
    Exceptions.cpp \
    ShoppingCart.cpp \
    console.cpp \
    coscrudgui.cpp \
    cosreadonlygui.cpp \
    customlistwidget.cpp \
    dialogfilter.cpp \
    dialogfind.cpp \
    dialogproduct.cpp \
    dialogsort.cpp \
    gui.cpp \
    main.cpp \
    mainwindow.cpp \
    myvector.cpp \
    product.cpp \
    repository.cpp \
    service.cpp

HEADERS += \
    ActiuneUndo.h \
    Exceptions.h \
    Pet.h \
    ShoppingCart.h \
    common.h \
    console.h \
    coscrudgui.h \
    cosreadonlygui.h \
    customlistwidget.h \
    dialogfilter.h \
    dialogfind.h \
    dialogproduct.h \
    dialogsort.h \
    gui.h \
    mainwindow.h \
    myvector.h \
    observer.h \
    product.h \
    repository.h \
    service.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
