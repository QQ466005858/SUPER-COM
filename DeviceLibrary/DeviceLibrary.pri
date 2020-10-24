!isEmpty(DEVICELIBRARY_PRI_INCLUDED):error("DeviceLibrary.pri already included")
DEVICELIBRARY_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11
CONFIG += plugin

QT += serialbus
QT += core
QT += serialport

IDE_SOURCE_TREE = $$PWD
#message("IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/DeviceLibrary/DeviceDL645Client \
    $$IDE_SOURCE_TREE/DeviceLibrary/DeviceDL645Master \
    $$IDE_SOURCE_TREE/DeviceLibrary/DeviceIEC60870_CS101Client \
    $$IDE_SOURCE_TREE/DeviceLibrary/DeviceIEC60870_CS101Master \
    $$IDE_SOURCE_TREE/DeviceLibrary/DeviceIEC60870_CS104Client \
    $$IDE_SOURCE_TREE/DeviceLibrary/DeviceIEC60870_CS104Server \
    $$IDE_SOURCE_TREE/DeviceModel \
    $$IDE_SOURCE_TREE/DeviceModel/DeviceModelClient \
    $$IDE_SOURCE_TREE/DeviceModel/DeviceModelServer





SOURCES += \
    $$IDE_SOURCE_TREE/DeviceModel/DeviceModel.cpp \
#    $$IDE_SOURCE_TREE/DeviceModel/DeviceEvent.cpp

HEADERS += \
 $$IDE_SOURCE_TREE/DeviceModel/DeviceModel.h \
# $$IDE_SOURCE_TREE/DeviceModel/DeviceEvent.h

#message("INCLUDEPATH is: $$INCLUDEPATH")

