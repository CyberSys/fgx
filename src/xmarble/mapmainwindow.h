#ifndef MAPMAINWINDOW_H
#define MAPMAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QTabWidget>


#include "xobjects/mainobject.h"
class MainObject;

#include "mpmap/flightswidget.h"
class FlightsWidget;

//#include "mpmap/flightsmodel.h"
//class FlightsModel;

//#include "marble/MarbleGlobal.h"
//#include "marble/MarbleWidget.h"

#include "xmarble/mappanel.h"
class MapPanel;



class MapMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapMainWindow(MainObject*, QWidget *parent = 0);

    MainObject *mainObject;


    QTabWidget *tabWidget;


signals:

public slots:

};

#endif // MAPMAINWINDOW_H