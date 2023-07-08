QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GradeList.cpp \
    Guy2PlayModeChoose.cpp \
    Guy4PlayModeChoose.cpp \
    StayTuned.cpp \
    beginscene.cpp \
    card.cpp \
    cardslot.cpp \
    choosemode.cpp \
    finishscene.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    play1v1.cpp \
    play1v3.cpp \
    player.cpp \
    rule.cpp \
    settings.cpp

HEADERS += \
    GradeList.h \
    Guy2PlayModeChoose.h \
    Guy4PlayModeChoose.h \
    MyPushButton.h \
    Myalgorithm/AIChooseCard.h \
    Myalgorithm/GiveCardAlgorithm.h \
    StayTuned.h \
    beginscene.h \
    card.h \
    cardslot.h \
    choosemode.h \
    finishscene.h \
    mainwindow.h \
    play1v1.h \
    play1v3.h \
    player.h \
    rule.h \
    settings.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

CONFIG += resources_big

RC_ICONS = Icon.ico
