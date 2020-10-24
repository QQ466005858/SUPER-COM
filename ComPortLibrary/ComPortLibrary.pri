!isEmpty(COMPORTLIBRARY_PRI_INCLUDED):error("ComPortLibrary.pri already included")
COMPORTLIBRARY_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11

#
QT += serialport
QT += network

IDE_SOURCE_TREE = $$PWD
#message("COMCONFIG IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/ComPortLibrary/ComPortLibrary \
    $$IDE_SOURCE_TREE/ComPortLibrary/NetPortLibrary \
    $$IDE_SOURCE_TREE/ComPortLibrary/SerialPortLibrary \
    $$IDE_SOURCE_TREE/ComPortLibrary/WireLessPortLibrary

message("INCLUDEPATH is: $$INCLUDEPATH")

#SOURCES += \
#    $$IDE_SOURCE_TREE/ComConfig/ComConfig/ComConfig.cpp


#message("SOURCES is: $$SOURCES")
