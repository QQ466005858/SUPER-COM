!isEmpty(PLUGINMANAGERLIBRARY_PRI_INCLUDED):error("PluginManager.pri already included")
PLUGINMANAGERLIBRARY_PRI_INCLUDED = 1

# enable c++11
CONFIG += c++11


QT += core
IDE_SOURCE_TREE = $$PWD
#message("IDE_SOURCE_TREE is: $$IDE_SOURCE_TREE")

INCLUDEPATH += \
    $$IDE_SOURCE_TREE/PluginManager

SOURCES += \
        $$IDE_SOURCE_TREE/PluginManager/PluginManager.cpp

#message("INCLUDEPATH is: $$INCLUDEPATH")

