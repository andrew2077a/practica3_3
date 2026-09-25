TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        LZ78.cpp \
        RLE.cpp \
        encriptacion_descomprension.cpp \
        leer_arch.cpp \
        main.cpp

HEADERS += \
    librerias.h

DISTFILES += \
    frases
