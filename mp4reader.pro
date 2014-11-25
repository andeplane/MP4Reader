TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    mp4reader.cpp \
    mp4box.cpp \
    atommvhd.cpp \
    atomftyp.cpp \
    atomtkhd.cpp \
    atommoov.cpp \
    atomtrak.cpp \
    atommdia.cpp \
    atommdhd.cpp \
    atomhdlr.cpp \
    atomminf.cpp \
    atomstbl.cpp \
    atomstsd.cpp \
    atomavc1.cpp \
    atommp4a.cpp \
    atomesds.cpp \
    atomavcc.cpp \
    atombtrt.cpp \
    atomstts.cpp \
    atomstss.cpp \
    atomstsc.cpp \
    atomstsz.cpp \
    atomstco.cpp \
    atomsmhd.cpp \
    atommdat.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    mp4reader.h \
    mp4box.h \
    atommvhd.h \
    atomftyp.h \
    atomtkhd.h \
    atommoov.h \
    atomtrak.h \
    atommdia.h \
    atommdhd.h \
    atomhdlr.h \
    atomminf.h \
    atomstbl.h \
    atomstsd.h \
    atomavc1.h \
    atommp4a.h \
    atomesds.h \
    atomavcc.h \
    atombtrt.h \
    atomstts.h \
    atomstss.h \
    atomstsc.h \
    atomstsz.h \
    atomstco.h \
    atomsmhd.h \
    atommdat.h \
    atoms.h

