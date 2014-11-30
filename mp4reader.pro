TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

#DEFINES += MP4DEBUG

SOURCES += main.cpp \
    mp4reader.cpp \
    mp4box.cpp \
    atoms/atommvhd.cpp \
    atoms/atomftyp.cpp \
    atoms/atomtkhd.cpp \
    atoms/atommoov.cpp \
    atoms/atomtrak.cpp \
    atoms/atommdia.cpp \
    atoms/atommdhd.cpp \
    atoms/atomhdlr.cpp \
    atoms/atomminf.cpp \
    atoms/atomstbl.cpp \
    atoms/atomstsd.cpp \
    atoms/atomavc1.cpp \
    atoms/atommp4a.cpp \
    atoms/atomesds.cpp \
    atoms/atomavcc.cpp \
    atoms/atombtrt.cpp \
    atoms/atomstts.cpp \
    atoms/atomstss.cpp \
    atoms/atomstsc.cpp \
    atoms/atomstsz.cpp \
    atoms/atomstco.cpp \
    atoms/atomsmhd.cpp \
    atoms/atommdat.cpp \
    track.cpp \
    mp4file.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    mp4reader.h \
    mp4box.h \
    atoms/atommvhd.h \
    atoms/atomftyp.h \
    atoms/atomtkhd.h \
    atoms/atommoov.h \
    atoms/atomtrak.h \
    atoms/atommdia.h \
    atoms/atommdhd.h \
    atoms/atomhdlr.h \
    atoms/atomminf.h \
    atoms/atomstbl.h \
    atoms/atomstsd.h \
    atoms/atomavc1.h \
    atoms/atommp4a.h \
    atoms/atomesds.h \
    atoms/atomavcc.h \
    atoms/atombtrt.h \
    atoms/atomstts.h \
    atoms/atomstss.h \
    atoms/atomstsc.h \
    atoms/atomstsz.h \
    atoms/atomstco.h \
    atoms/atomsmhd.h \
    atoms/atommdat.h \
    atoms/atoms.h \
    track.h \
    mp4file.h

