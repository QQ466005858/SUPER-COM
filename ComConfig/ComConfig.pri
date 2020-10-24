!isEmpty(COMCONFIG_PRI_INCLUDED):error("ComConfig.pri already included")
COMCONFIG_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11
QT += xml

IDE_SOURCE_TREE = $$PWD
#message("COMCONFIG IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/ComConfig/ComConfig \


#SOURCES += \
#        ComConfig.cpp

#message("INCLUDEPATH is: $$INCLUDEPATH")

SOURCES += \
    $$IDE_SOURCE_TREE/ComConfig/ComConfig/ComConfig.cpp


message("SOURCES is: $$SOURCES")
