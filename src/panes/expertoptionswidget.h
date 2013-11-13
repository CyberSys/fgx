// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// FGx FlightGear Launcher // expertoptionswidget.h
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// (c) 2010-2012
// Yves Sablonier, Pete Morgan
// Geoff McLane
// GNU GPLv2, see main.cpp and shipped licence.txt for further information

#ifndef EXPERTOPTIONSWIDGET_H
#define EXPERTOPTIONSWIDGET_H

#include <QPlainTextEdit>
#include <QPushButton>
#include <QWidget>
#include <QButtonGroup>

#include "xobjects/mainobject.h"

#include "xwidgets/xcommandpreviewidget.h"
class XCommandPrevieWidget;

class ExpertOptionsWidget : public QWidget
{
Q_OBJECT
public:
	explicit ExpertOptionsWidget(MainObject *mOb, QWidget *parent = 0);

	MainObject *mainObject;

	XGroupVBox *groupBoxArgs;
	XGroupVBox *groupBoxEnv;

	// Advanced Options
	QPlainTextEdit *txtExtraArgs;
	QPlainTextEdit *txtExtraEnv;
	QLineEdit *txtRuntime;

	XGroupVBox *groupBoxWriteLog;
	QComboBox *comboLogLevels;

	// preview
	XCommandPrevieWidget *commandPreviewWidget;

signals:
	void setx(QString option, bool enabled, QString value);

public slots:



	void on_extra();
	void on_env();
	void on_runtime();
	void on_log_level();

	void on_upx(QString option, bool enabled, QString value);
};

#endif // EXPERTOPTIONSWIDGET_H
