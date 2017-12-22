QT += core
QT -= gui
TARGET = appInst

# qmake CONFIG+=debug    - for release
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app

SOURCES += src/main.cpp \
    src/util/helpers.cpp \
    src/model/packagemanager.cpp \
    src/model/category.cpp \
    src/model/subcategory.cpp \
    src/model/packages.cpp \
    src/appinst.cpp

HEADERS += \
    src/util/helpers.h \
    src/model/packagemanager.h \
    src/model/category.h \
    src/model/subcategory.h \
    src/model/packages.h \
    src/appinst.h

# Build directories
release: DESTDIR = build/release
debug:   DESTDIR = build/debug
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
