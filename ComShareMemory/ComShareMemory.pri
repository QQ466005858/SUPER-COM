!isEmpty(COM_SHARE_MEM_PRI_INCLUDED):error("ComShareMemory.pri already included")
COM_SHARE_MEM_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11

#
QT += core

IDE_SOURCE_TREE = $$PWD

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/ComShareMemory/ \

message("INCLUDEPATH is: $$INCLUDEPATH")

SOURCES += \
    $$IDE_SOURCE_TREE/ComShareMemory/ComShareMemory.cpp


#message("SOURCES is: $$SOURCES")
