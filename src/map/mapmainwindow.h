#ifndef MAPMAINWINDOW_H
#define MAPMAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include "xobjects/mainobject.h"

#include "mpmap/flightswidget.h"
class FlightsWidget;

#include "mpmap/flightsmodel.h"
class FlightsModel;

//#include "marble/MarbleGlobal.h"
//#include "marble/MarbleWidget.h"

#include "map/mapcorewidget.h"
class MapCoreWidget;



class MapMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapMainWindow(MainObject*, QWidget *parent = 0);

    MainObject *mainObject;

    MapCoreWidget *mapWidget;

    QDockWidget *dockPilots;
    FlightsWidget *flightsWidget;
    FlightsModel *flightModel;


signals:

public slots:

};

#endif // MAPMAINWINDOW_H
