// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// FGx FlightGear Launcher // xcommandpreview.h
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// (c) 2010-2012
// Yves Sablonier, Pete Morgan
// Geoff McLane
// GNU GPLv2, see main.cpp and shipped licence.txt for further information

#ifndef XCOMMANDPREVIEWIDGET_H
#define XCOMMANDPREVIEWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QButtonGroup>

#include "xobjects/mainobject.h"
class MainObject;


class XCommandPrevieWidget : public QWidget
{
Q_OBJECT
public:
	explicit XCommandPrevieWidget(MainObject *mob, QWidget *parent = 0);

	MainObject *mainObject;

	QPlainTextEdit *txtPreviewOutput;
	QButtonGroup *buttonGroup;

signals:

public slots:
	void on_command_help();
	void on_command_version();
	void preview();
};

#endif // XCOMMANDPREVIEWIDGET_H
