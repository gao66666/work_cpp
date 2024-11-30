QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    invite_join_group.cpp \
    main.cpp \
    new_friends_group.cpp \
    widget.cpp

HEADERS += \
    chat.h \
    invite_join_group.h \
    new_friends_group.h \
    widget.h

FORMS += \
    chat.ui \
    invite_join_group.ui \
    new_friends_group.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src_pic/OIP-C.jpg \
    src_pic/QQ_ico.png

RESOURCES += \
    images.qrc
