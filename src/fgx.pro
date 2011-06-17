# #####################################################################
# Automatically generated by qmake (2.01a) Do. Mrz 3 00:45:52 2011
# #####################################################################
TEMPLATE = app
TARGET = fgx
DEPENDPATH += .
INCLUDEPATH += .
QT += network \
    xml \
    xmlpatterns \
    sql \
    webkit
# Input
HEADERS += xobjects/xsettings.h \
    settings/settingsdialog.h \
    network/networkwidget.h \
    network/mptelnet.h \
    aircraft/aircraftwidget.h \
	aircraft/aircraftimport.h \
    airports/airportswidget.h \
    airports/importairportswidget.h \
    airports/aptdatparser.h \
    xwidgets/execontrols.h \
    panes/timeweatherwidget.h \
    panes/advancedoptionswidget.h \
    panes/outputpreviewwidget.h \
    panes/coresettingswidget.h \
    xwidgets/xgroupboxes.h \
    xobjects/mainobject.h \
    launcher/launcherwindow.h \
    mpmap/mpmapwidget.h \
    settings/pathssettingswidget.h \
    settings/dbsettingswidget.h \
    utilities/statusbar.h \
    xwidgets/xtreewidgetitem.h \
    airports/airportsimport.h \
    utilities/utilities.h
SOURCES += main.cpp \
    xobjects/xsettings.cpp \
    settings/settingsdialog.cpp \
    network/networkwidget.cpp \
    network/mptelnet.cpp \
    aircraft/aircraftwidget.cpp \
	aircraft/aircraftimport.cpp \
    airports/airportswidget.cpp \
    airports/aptdatparser.cpp \
    airports/importairportswidget.cpp \
    xwidgets/execontrols.cpp \
    panes/timeweatherwidget.cpp \
    panes/advancedoptionswidget.cpp \
    panes/outputpreviewwidget.cpp \
    panes/coresettingswidget.cpp \
    xwidgets/xgroupboxes.cpp \
    xobjects/mainobject.cpp \
    launcher/launcherwindow.cpp \
    mpmap/mpmapwidget.cpp \
    settings/pathssettingswidget.cpp \
    settings/dbsettingswidget.cpp \
    utilities/statusbar.cpp \
    airports/airportsimport.cpp \
    utilities/utilities.cpp
RESOURCES += resources/icons.qrc \
    resources/artwork.qrc
CONFIG += console
