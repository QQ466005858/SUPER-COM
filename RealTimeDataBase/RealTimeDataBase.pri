!isEmpty(RTDB_PRI_INCLUDED):error("RealTimeDataBase.pri already included")
RTDB_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11
CONFIG += plugin

QT += serialbus
QT += core
QT += serialport

IDE_SOURCE_TREE = $$PWD
#message("IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/RealTimeDataBase \


SOURCES += \
    $$IDE_SOURCE_TREE/RealTimeDataBase/DBTagObject.cpp \
    $$IDE_SOURCE_TREE/RealTimeDataBase/RealTimeDB.cpp \
    $$IDE_SOURCE_TREE/RealTimeDataBase/RtDb.cpp \
    $$IDE_SOURCE_TREE/RealTimeDataBase/ShareMemory.cpp


HEADERS += \
 $$IDE_SOURCE_TREE/RealTimeDataBase/DBTagObject.h \
 $$IDE_SOURCE_TREE/RealTimeDataBase/public.h \
 $$IDE_SOURCE_TREE/RealTimeDataBase/RealTimeDB.h \
 $$IDE_SOURCE_TREE/RealTimeDataBase/RtDb.h \
 $$IDE_SOURCE_TREE/RealTimeDataBase/ShareMemory.h \


#message("INCLUDEPATH is: $$INCLUDEPATH")

