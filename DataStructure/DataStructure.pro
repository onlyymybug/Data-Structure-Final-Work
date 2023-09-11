#-------------------------------------------------
#
# Project created by QtCreator 2023-05-18T10:13:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataStructure
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        login.cpp \
    studentoperation.cpp \
    teacheroperation.cpp \
    mytime.cpp \
    activity.cpp \
    searchclass.cpp \
    mymessagebox.cpp \
    outclassactivitymanage.cpp \
    map.cpp \
    deletecourse.cpp \
    addcourse.cpp \
    record.cpp \
    exam.cpp \
    addexam.cpp \
    addoutclass.cpp \
    deleteoutclass.cpp \
    temporarymanage.cpp \
    addtemp.cpp \
    deletetemp.cpp

HEADERS += \
        login.h \
    studentoperation.h \
    teacheroperation.h \
    mytime.h \
    activity.h \
    searchclass.h \
    mymessagebox.h \
    outclassactivitymanage.h \
    map.h \
    deletecourse.h \
    addcourse.h \
    record.h \
    exam.h \
    addexam.h \
    addoutclass.h \
    deleteoutclass.h \
    temporarymanage.h \
    addtemp.h \
    deletetemp.h

FORMS += \
        login.ui \
    map.ui

RESOURCES += \
    resource.qrc
