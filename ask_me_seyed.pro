QT       += core gui multimedia widgets
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
    difficulty.cpp \
    first_page.cpp \
    main.cpp \
    mainwindow.cpp \
    names.cpp \
    pvp_mode.cpp \
    survival_mode.cpp

HEADERS += \
    difficulty.h \
    first_page.h \
    mainwindow.h \
    names.h \
    pvp_mode.h \
    qst.h \
    quiz.h \
    quiz2.h \
    survival_mode.h

FORMS += \
    difficulty.ui \
    first_page.ui \
    mainwindow.ui \
    names.ui \
    pvp_mode.ui \
    survival_mode.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Add the curl library
LIBS += -lcurl

# Other configurations
INCLUDEPATH += /usr/include/nlohmann /usr/include/x86_64-linux-gnu/curl
