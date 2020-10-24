!isEmpty(LIBMODBUS_PRI_INCLUDED):error("libmodbus.pri already included")
LIBMODBUS_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11
CONFIG += plugin

IDE_SOURCE_TREE = $$PWD
#message("IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/libmodbus/inc

unix {
}
macx {
}
win32 {
    LIBS += -Ldll -lws2_32
}

SOURCES += \
    $$IDE_SOURCE_TREE/libmodbus/src/modbus.c \
    $$IDE_SOURCE_TREE/libmodbus/src/modbus-data.c \
    $$IDE_SOURCE_TREE/libmodbus/src/modbus-rtu.c \
    $$IDE_SOURCE_TREE/libmodbus/src/modbus-tcp.c \

HEADERS += \
 $$IDE_SOURCE_TREE/libmodbus/inc/config.h \
 $$IDE_SOURCE_TREE/libmodbus/inc/modbus.h \
 $$IDE_SOURCE_TREE/libmodbus/inc/modbus-rtu.h \
 $$IDE_SOURCE_TREE/libmodbus/inc/config.h \
 $$IDE_SOURCE_TREE/libmodbus/inc/modbus-tcp.h \

#message("INCLUDEPATH is: $$INCLUDEPATH")

