/*
 *  main.cpp
 *  fgx
 *
 *  Created by Yves Sablonier, Zurich
 *  © 2011 --- GPL2
 *
 */


#include <QApplication>

#include "xobjects/mainobject.h"

int main( int argc, char* argv[])
{

	QApplication app(argc, argv);
	QApplication::setOrganizationName("fgx");
	QApplication::setOrganizationDomain("fgx.googlecode.com");
	QApplication::setApplicationName("FGX FlightGear Launcher");
	QApplication::setApplicationVersion("2.2-1 (alpha)");
	//QApplication::setQuitOnLastWindowClosed(false);

	MainObject mainObject;


	return app.exec();
}


