
#include <QDebug>

#include <QtCore/QDir>

#include <QtGui/QProgressDialog>

#include <QtXmlPatterns/QXmlQuery>
#include <QtXml/QDomDocument>
#include <QtScript/QScriptEngine>

#include "aerotools.h"

AeroTools::AeroTools(QObject *parent) :
    QObject(parent)
{
}




//========================================================
//*** Walk XML - sets
//========================================================

/* This function walsk the /Aircraft/* directory
 its find files in a directory maching "*-set.xml"
   and therby engquires the xml fo
   */

QStringList AeroTools::scan_xml_sets(){

	int c = 0;
	int found = 0;
	QProgressDialog progress("Recanning Aircraft to Cache", "Cancel", 0, 0);
	progress.setWindowModality(Qt::WindowModal);
	progress.show();

	QStringList aeroList;

	QDir aircraftDir( settings.aircraft_path() );
	qDebug() << settings.aircraft_path();
	aircraftDir.setFilter( QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	QStringList entries = aircraftDir.entryList();
	progress.setMaximum(entries.size());

	for( QStringList::ConstIterator entry=entries.begin(); entry!=entries.end(); ++entry ){

		// Filter out default dir names, should be a QDir name filter?
		if (*entry != "Instruments" &&  *entry != "Instruments-3d" && *entry != "Generic") {
			progress.setValue(progress.value() + 1);
			//** get the List of *-set.xml files in dir
			QDir dir( settings.aircraft_path(*entry) );
			QStringList filters;
			filters << "*-set.xml";
			QStringList list_xml = dir.entryList(filters);
			qDebug() << list_xml;
			if(list_xml.count() > 0){ // << Scan MOdels
				QString directory;
				QString description;
				QString author;
				QString fdm;
				QString xml_file;
				QString aero;

				//** Add Path Node
				directory = QString(*entry);
				//** Add Models
				for (int i = 0; i < list_xml.size(); ++i){

					xml_file = QString(list_xml.at(i));
					aero = QString(xml_file);
					aero.chop(8);

					//** parse the Xml file - fucking long winded
					QString file_path =  settings.aircraft_path(*entry);
					file_path.append("/");
					file_path.append(list_xml.at(i));
					QFile xmlFile( file_path);
					if (xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)){

						//* The filexontent are converted to UTF-8. Some files are Windows etc
						QString xmlString = QString(xmlFile.readAll()).toUtf8();

						QXmlQuery query;
						query.setFocus(xmlString);
						//query.setFocus(&xmlFile);
						query.setQuery("PropertyList/sim");
						if (query.isValid()){

							QString res;
							query.evaluateTo(&res);
							xmlFile.close();

							QDomDocument dom;
							dom.setContent("" + res + "");
							QDomNodeList nodes = dom.elementsByTagName("sim");

							QDomNode n = nodes.at(0);
							description = n.firstChildElement("description").text();
							author = n.firstChildElement("author").text();
							fdm = n.firstChildElement("flight-model").text();
						} /* !query.isValid() */
					} /*  xmlFile.open() */

					//## TODO Here we go with stuff to cache - Later DB
					//#1 This version saves to settings and an embedded dam dirty delimiter string stuff..

					QString record = QString("%1~|~%2~|~%3~|~%4~|~%5~|~%6").arg(directory, xml_file, aero, fdm, description, author );
					qDebug() << record;
					aeroList << record;

					found++;

					if(progress.wasCanceled()){
						break;
					}
					c++;
				} // <Add models

			} /* list_xml.count() > 0 */
		} /* entry != INstruments etc */
	} /* loop entries.() */	
	return aeroList;

}


