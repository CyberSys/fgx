#ifndef XDEBUGTREEWIDGET_H
#define XDEBUGTREEWIDGET_H


#include <QWidget>
#include <QActionGroup>
#include <QSortFilterProxyModel>

#include "xobjects/mainobject.h"
class MainObject;



class XDebugTreeWidget : public QWidget
{
Q_OBJECT

public:
	explicit XDebugTreeWidget(MainObject *mob, QWidget *parent = 0);

	MainObject *mainObject;

	QActionGroup *groupFilter;

	QSortFilterProxyModel *proxyModel;


signals:


public slots:
	void on_filter(QAction*);

};

#endif // XDEBUGTREEWIDGET_H
