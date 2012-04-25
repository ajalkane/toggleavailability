#-------------------------------------------------
#
# Project created by QtCreator 2012-04-24T22:45:10
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

TARGET = toggleavailability
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += link_pkgconfig
PKGCONFIG += accounts-qt
PKGCONFIG += TelepathyQt4

TEMPLATE = app


SOURCES += main.cpp \
    toggleavailability.cpp

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/toggleavailability/bin
    INSTALLS += target

}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    toggleavailability.h

# Copied from qmlapplicationviewer
installPrefix = /opt/$${TARGET}

desktopfile.files = $${TARGET}_harmattan.desktop
desktopfile.path = /usr/share/applications
icon.files = $${TARGET}80.png
icon.path = /usr/share/icons/hicolor/80x80/apps

export(icon.files)
export(icon.path)
export(desktopfile.files)
export(desktopfile.path)
INSTALLS += icon desktopfile

target.path = $${installPrefix}/bin
export(target.path)
INSTALLS += target

export (ICON)
export (INSTALLS)
export (DEPLOYMENT)
export (TARGET.EPOCHEAPSIZE)
export (TARGET.CAPABILITY)
export (LIBS)
export (QMAKE_EXTRA_TARGETS)
