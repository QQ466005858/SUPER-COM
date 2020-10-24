QT -= gui
QT += core
TEMPLATE = lib

#CONFIG += plugin

include(../../../ComConfig/ComConfig.pri)
include(../../../ComShareMemory/ComShareMemory.pri)
include(../../../ComPortLibrary/ComPortLibrary.pri)
include(../../DeviceLibrary.pri)
include(../libmodbus.pri)

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
    ModBusRtuClient.cpp

HEADERS += \
    ModBusRtuClient.h


IDE_SOURCE_TREE = $$PWD
#message("IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")



DISTFILES += DeviceModbusRtuClient.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
