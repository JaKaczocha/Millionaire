TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cMillionaire.cpp \
        cMillionaireData.cpp \
        cStageData.cpp \
        cMillionaireDisplaying.cpp \
        main.cpp

HEADERS += \
    cMillionaire.h \
    cStageData.h \
    cMillionaireDisplaying.h
