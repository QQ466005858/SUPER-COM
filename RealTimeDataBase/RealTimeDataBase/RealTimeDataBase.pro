QT -= gui
QT += core xml
TEMPLATE = lib
#CONFIG += plugin
include(../../ComConfig/ComConfig.pri)

include(../../log4qt/log4qt.pri)


CONFIG += c++11

win32 {
    LIBS += -lpthread -lwsock32 -lws2_32
} else {

}

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
    DBTagObject.cpp \
    RealTimeDB.cpp \
    RtDb.cpp \
    ShareMemory.cpp

HEADERS += \
    DBTagObject.h \
    RealTimeDB.h \
    RtDb.h \
    ShareMemory.h \
    public.h

#DISTFILES += RealTimeDataBase.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
