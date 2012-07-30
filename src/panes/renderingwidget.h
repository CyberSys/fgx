// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// FGx FlightGear Launcher // renderingwidget.h
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// (c) 2010-2012
// Yves Sablonier, Pete Morgan
// Geoff McLane
// GNU GPLv2, see main.cpp and shipped licence.txt for further information

#ifndef RENDERINGWIDGET_H
#define RENDERINGWIDGET_H


#include <QtCore/QString>
#include <QtCore/QMap>


#include <QtGui/QWidget>
#include <QtGui/QButtonGroup>
#include <QtGui/QPlainTextEdit>


#include "xobjects/mainobject.h"
#include "xwidgets/xgroupboxes.h"

class MainObject;


class RenderingWidget : public QWidget
{
Q_OBJECT
public:
	explicit RenderingWidget(MainObject *mOb, QWidget *parent = 0);

	MainObject *mainObject;
	
	XGroupHBox *grpAntiAliasing;
	QComboBox *comboAntiAliasing;
	
	XGroupHBox *grpShaderQuality;
	QComboBox *comboShaderQuality;
	
	XGroupGBox *grp3dClouds;
	QLabel *labelVisibility;
	QSlider *sliderVisibility;
	QLabel *sliderLabelVisValue;
	QLabel *labelDensity;
	QSlider *sliderDensity;
	QLabel *sliderLabelDenValue;


signals:
	void setx(QString option, bool enabled, QString value);

public slots:
	
	void set_anti_aliasing();
	void set_anti_aliasing_strength();
	
	void set_shader_quality();
	
	void set_vis_value(int value);
	void set_den_value(int value);

};

#endif // RENDERINGWIDGET_H
