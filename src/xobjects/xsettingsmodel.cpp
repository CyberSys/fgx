// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// FGx FlightGear Launcher // xsettingsmodel.cpp
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// (c) 2010-2012
// Yves Sablonier, Pete Morgan
// Geoff McLane
// GNU GPLv2, see main.cpp and shipped licence.txt for further information

#include "app_config.h"
#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QFileDialog>

#include "xobjects/xsettingsmodel.h"
#include "utilities/utilities.h"


/*! \class XSettingsModel
 * \brief The XSettingsModel is an extended QStandardItemModel, and the main "setting and state" for FGx
 *
 *
 * @authors: Peter Morgan
 */



XSettingsModel::XSettingsModel(MainObject *mob, QObject *parent) :
	QStandardItemModel(parent)
{
	mainObject = mob;

	_loading = false;

	setColumnCount(7);

	QStringList headers;
	headers  << "Option" << "Ena" << "Val" << "Default" << "Level" << "Description" << "Class";
	setHorizontalHeaderLabels(headers);



	//=================================================================================
	// This list will be the main issue and debates for a long time probably, said pete
	//=================================================================================


	//==================
	add_option("profile", false, "", "", 0, "", "profiles");
	
	//==================
	add_option("fgfs_path", false,"","",0,"","paths");
	add_option("fgroot_path", false,"","",0,"","paths");
	add_option("terrasync_enabled", false,"","",0,"","paths");
	add_option("terrasync_exe_path", false,"","",0,"","paths");
	add_option("terrasync_data_path", false,"","",0,"","paths");
	add_option("custom_scenery_enabled", false,"","",0,"","paths");
	add_option("custom_scenery_path", false,"","",0,"","paths");
    add_option("fgcom_exe_path", false, "", "", 0, "", "paths");
	add_option("jsdemo_enabled", false, "", "", 0, "", "paths");
    add_option("jsdemo_exe_path", false, "", "", 0, "", "paths");



	add_option("extra_args", false,"","",0,"","expert");
	add_option("extra_env", false,"","",0,"","expert");

	add_option("runtime", false,"","",0,"","expert");
	add_option("--log-level=", false,"","",0,"","expert");

	add_option("first_launcher_close", false, "", "", 0, "Check for launcher window close", "Launcher Window");

    // Coordinates
    add_option( "use_coordinates",false, "", "",3,"","Coordinates");
    add_option( "--vor=",false, "", "",3,"","Coordinates");
    add_option( "--ndb=",false, "", "",3,"","Coordinates");
    add_option( "--fix=",false, "", "",3,"","Coordinates");
    add_option( "--lat=",false, "", "",3,"","Coordinates");
    add_option( "--lon=",false, "", "",3,"","Coordinates");
    add_option( "--offset-distance=",false, "", "",3,"","Coordinates");
    add_option( "--altitude=",false, "", "",3,"","Coordinates");
    add_option( "--heading=",false, "", "",3,"","Coordinates");

    //==

	add_option( "show_mpmap", false, "", "",10,"Follow in MpMap","Map");

	add_option( "--enable-auto-coordination",false, "", "",10,"Enabled Rudder and Airelon","Control");

	add_option( "--callsign=", true,"CALLSIG", "", 1 ,"Your Callsign","Core");

	//= Season
	add_option("--season=", false,"","summer",1,"Season", "time");

	//= Time
	add_option("--timeofday=", false,"","realtime",1,"Time of day", "time");

	//= Weather
	add_option("weather",						true, "","none",2,"Weather Flag","weather");
	add_option("--enable-real-weather-fetch",	false, "","",1,"Enable Real Weather","weather");
	add_option("--disable-real-weather-fetch",	false, "","",1,"Disable Real Weather","weather");
	add_option("--metar=",						false,"","",1,"","weather");
	
	//= Rendering
	add_option( "--prop:/sim/rendering/multi-sample-buffers=",false, "", "",1,"","Rendering");
	add_option( "--prop:/sim/rendering/multi-samples=",false, "", "",1,"","Rendering");
	
	add_option( "--prop:/sim/rendering/shaders/quality-level-internal=",true, "", "3",1,"","Rendering");
	
	add_option( "--prop:/sim/rendering/shaders/skydome=",false, "", "", 1, "", "Rendering");
	
	add_option( "--prop:/sim/rendering/rembrandt/enabled=",true, "", "0",1,"","Rendering");
	add_option( "--prop:/sim/rendering/shadows/map-size=",true, "", "4096",1,"","Rendering");
	add_option( "--prop:/sim/rendering/shadows/num-cascades=",true, "", "4",1,"","Rendering");
	
	add_option( "--materials-file=",false, "", "", 1, "", "Rendering");
	
	add_option( "--prop:/sim/rendering/clouds3d-enable=",true, "", "",1,"","Rendering");
	add_option( "--prop:/sim/rendering/clouds3d-vis-range=",true, "", "10000",1,"","Rendering");
	add_option( "--prop:/sim/rendering/clouds3d-density=",true, "", "0.25",1,"","Rendering");
	
	add_option("--geometry=", false, "", "", 1, "Screen Size","");
	add_option( "--enable-fullscreen",false, "", "", 1 ,"Enable Full Screen at Startup","Startup");
	add_option( "--disable-splash-screen", false, "", "", 1 ,"Enable Splash Screen at Startup","Startup");
	add_option( "--prop:/sim/menubar/native=",false, "", "", 1, "OSX switch for native/pui menubar", "Rendering"); 
	


	//= MultiPlayer
	add_option( "--multiplay=in",  false,"", ",10,localhost,20",2,"Multiplayer In","MultiPlayer");
	add_option( "--multiplay=out", false, "", ",10,localhost,20",2,"Multiplayer In","MultiPlayer");

	//= FGCom Related
	add_option( "fgcom_server",false, "", "fgcom.flightgear.org.uk:16661",3,"FgCom","FgCom");
	add_option( "fgcom_enabled", false, "", "",10,"FgCom Socket","FgCom");

	//= Local Servers
	add_option( "--telnet=",false, "", "",3,"Enable Telnet","servers");
	add_option( "--httpd=",false, "", "",3,"Enable Httpd","servers");
	add_option( "--jpg-httpd=",false, "", "",3,"Enable Screenshot","servers");

	//-- Radio
	add_option( "--nav1=",false, "", "",3,"","Radio");
	add_option( "--nav2=",false, "", "",3,"","Radio");
	add_option( "--adf1=",false, "", "",3,"","Radio");
	add_option( "--adf2=",false, "", "",3,"","Radio");
	add_option( "--com1=",false, "", "",3,"","Radio");
	add_option( "--com2=",false, "", "",3,"","Radio");

	//== Aircraft
	add_option( "--aircraft=", false,"", "", 1 ,"Aircraft","Aircraft");
	add_option( "--fg-aircraft=", false,"", "", 1 ,"Custom Aircraft Folder","Aircraft");
	add_option( "custom_hangar_enabled",false, "", "",1,"Custom Hangar Checked","Aircraft");

	//-- Fuel
	//add_option( "use_default_fuel",true,"","",3,"","Aircraft");
	add_option( "--enable-fuel-freeze",false,"","",3,"","Aircraft");
	add_option( "--prop:/consumables/fuels/tank[1]/level-gal=",false, "", "",9,"","Fuel");
	add_option( "--prop:/consumables/fuels/tank[2]/level-gal=",false, "", "",9,"","Fuel");
	add_option( "--prop:/consumables/fuels/tank[3]/level-gal=",false, "", "",9,"","Fuel");

	//= Airport Tab
	add_option( "start_postition", true, "","0",0,"Start Location", "Airport");
	add_option( "--airport=", false,"", "", 1 ,"Airport","Airport");
	add_option( "--runway=", false,"", "", 1 ,"Runway","Airport");
	add_option( "--parking-id=", false,"", "", 1 ,"Parking","Airport");
	add_option("runway_stand", false, "", "",1,"Flag to whether runway or stand", "Airport" );



}



//==================================================
// == Add an Option
void XSettingsModel::add_option( QString option, bool enabled, QString value, QString preset, int level, QString description, QString area)
{
	Q_UNUSED(value); //= Uses preset intead
	QList<QStandardItem *>items;
	items 	<< new QStandardItem(option)
			<< new QStandardItem(enabled ? "1" : "0")
			<< new QStandardItem(preset)
			<< new QStandardItem(preset)
			<< new QStandardItem(QString::number(level))
			<< new QStandardItem(description)
			<< new QStandardItem(area);
	appendRow(items);

}



//==================================================
// == Set An Option
void XSettingsModel::set_option(QString option, bool enabled, QString value)
{
	//qDebug() << "set " << option << _loading;
	if(_loading){
		return;
	}
	//= Find item matching the "option"
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);
	//qDebug() << "opts" << items;

	//TODO handle error if not found
    if (items.size() == 0) {
        outLog("set_option:setx called with INVALID option ["+option+"]");
        return;
    }

	//= Get/update the "enabled" item in the same row
	QStandardItem *eItem = item(items[0]->row(),C_ENABLED);
	eItem->setText(enabled ? "1" : "0");


	//= Get/update the "value" item in the same row
	QStandardItem *vItem = item(items[0]->row(),C_VALUE);
	vItem->setText(value);

	set_row_bg(items[0]->row(), enabled ? QColor(200,255,200) : QColor(240,240,240));

	//= Announce the change
	//emit upx(option, enabled,  value);
	emit updated(get_fgfs_list());
}

//==================================================
// == Set An Option Enabled or Disabled
void XSettingsModel::set_enabled(QString option, bool enabled)
{
	//qDebug() << "set " << option << _loading;
	if(_loading){
		return;
	}
	//= Find item matching the "option"
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);
	//qDebug() << "opts" << items;

	//TODO handle error if not found

	//= Get/update the "enabled" item in the same row
	QStandardItem *eItem = item(items[0]->row(),C_ENABLED);
	eItem->setText(enabled ? "1" : "0");

	set_row_bg(items[0]->row(), enabled ? QColor(200,255,200) : QColor(240,240,240));

	QStandardItem *vItem = item(items[0]->row(),C_VALUE);

	emit upx(option, enabled, vItem->text());
	emit updated(get_fgfs_list());
}

//==================================================
// == Set An Option's  Value
void XSettingsModel::set_value(QString option, QString value)
{
	//qDebug() << "set " << option << _loading;
	if(_loading){
		return;
	}
	//= Find item matching the "option"
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);
	//qDebug() << "opts" << items;

	//TODO handle error if not found

	//= Get/update the "enabled" item in the same row
	QStandardItem *vItem = item(items[0]->row(),C_VALUE);
	vItem->setText(value);

	QStandardItem *eItem = item(items[0]->row(),C_ENABLED);



	emit upx(option, eItem->text() == "1",  value);
	emit updated(get_fgfs_list());
}



QModelIndex XSettingsModel::get_index(QString option)
{
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);
	return indexFromItem(items[0]);
}

//==================================================
// == Get Option
//==================================================
QString XSettingsModel::getx(QString option)
{
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);

	// Get the item in the same row in the enabled field
	QStandardItem *xItem = item(items[0]->row(),C_VALUE);
	return xItem->text();

}

QString XSettingsModel::getx(QString option, bool return_default)
{
	//=PETE - I dont think this is being used...
	Q_UNUSED(return_default);
	XOpt opt = get_opt(option);
	if(opt.value.length() == 0){
		return opt.default_value;
	}
	return opt.value;
}

QString XSettingsModel::getx(QString option, QString default_string)
{
	QString v = getx(option);
	if(v.length() == 0){
		return default_string;
	}
	return v;

}

//==================================================
// == Get Option enabled
bool XSettingsModel::get_ena(QString option)
{
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);

	// Get the item in the same row in the enabled field
	QStandardItem *xItem = item(items[0]->row(),C_ENABLED);
	return xItem->text() == "1";

}

XOpt XSettingsModel::get_opt(QString option)
{
	QList<QStandardItem *>items = findItems(option, Qt::MatchExactly,C_OPTION);
	return XOpt(item(items[0]->row(), C_OPTION)->text(),
				item(items[0]->row(), C_ENABLED)->text() == "1",
				item(items[0]->row(), C_VALUE)->text(),
				item(items[0]->row(), C_DEFAULT)->text()
				);
}


//==================================================
// == Read Default Ini File: First Startup and Reset
/** \brief Read Values from ini
 */

void XSettingsModel::read_default_ini()
{
	QString defaultSettings("");
	switch (mainObject->runningOs()) {
		case OS_MAC:
			defaultSettings = ":/default/osx_default.ini";
			break;
		case OS_WINDOWS:
			defaultSettings = ":/default/win_default.ini";
			break;
		case OS_LINUX:
			defaultSettings = ":/default/x_default.ini";
			break;
		default:
			outLog("*** FGx shout: No default settings for this system");
			break;
	}
	
	QSettings settings(defaultSettings,QSettings::IniFormat);

	bool ena;
	for(int row_idx=0; row_idx < rowCount(); row_idx++){
		//= loop rows and load each "option" as an [ini section] with enabled, value as values
		settings.beginGroup(item(row_idx, C_OPTION)->text());
			ena = settings.value("enabled").toBool() ;
			item(row_idx, C_ENABLED)->setText( ena ? "1" : "0");
			QString val = settings.value("value").toString();
			if(val == ""){
				val = item(row_idx, C_DEFAULT)->text();
			}
			item(row_idx, C_VALUE)->setText(val );
			set_row_bg(row_idx, ena ? QColor(200,255,200) : QColor(240,240,240));
			//= Broadcast changes
			emit upx(item(row_idx, C_OPTION)->text(),
					 item(row_idx, C_ENABLED)->text() == "1",
					 item(row_idx, C_VALUE)->text()
					 );
		settings.endGroup();
	}
	//qDebug() << "Read ini";
	emit updated(get_fgfs_list());
	
}

//=============================================
// == Load Last Profile
/** \brief Opens last used profile
 */

void XSettingsModel::load_last_profile(QString profile)
{
	_loading = true;
	
	QString filename = profile;
	QSettings settings(filename,QSettings::IniFormat);
	
	outLog("*** FGx loading last used profile:"+filename);
	
	bool ena;
	for(int row_idx=0; row_idx < rowCount(); row_idx++){
		//= loop rows and load each "option" as an [ini section] with enabled, value as values
		settings.beginGroup(item(row_idx, C_OPTION)->text());
		ena = settings.value("enabled").toBool() ;
		item(row_idx, C_ENABLED)->setText( ena ? "1" : "0");
		QString val = settings.value("value").toString();
		if(val == ""){
			val = item(row_idx, C_DEFAULT)->text();
		}
		item(row_idx, C_VALUE)->setText(val );
		set_row_bg(row_idx, ena ? QColor(200,255,200) : QColor(240,240,240));
		//= Broadcast changes
		emit upx(item(row_idx, C_OPTION)->text(),
				 item(row_idx, C_ENABLED)->text() == "1",
				 item(row_idx, C_VALUE)->text()
				 );
		settings.endGroup();
	}
	_loading = false;
	emit updated(get_fgfs_list());
	
}

//========================================
// == get last used Profile file name
//========================================
QString XSettingsModel::getLastUsed()
{
    QString key("lastprofile");
    QSettings lastused;
    QString previous = lastused.value(key,
                "NewProfile.ini").toString();
    return previous;
}

//========================================
// == set last used Profile file name
//========================================
void XSettingsModel::setLastUsed(QString previous)
{
    QString key("lastprofile");
    QSettings lastused;
    lastused.setValue(key,previous);
}

//=============================================
// == Load Profile
/** \brief Opens Profile Dialog for loading a .ini File
 */

bool XSettingsModel::load_profile()
{
	_loading = true;
    // get lastused profile name
    QString previous = getLastUsed();   // or default if none

#ifdef USE_ALTERNATE_GETFILE
    QString filename = util_getFileName(0,  "Load Profiles",  previous, QStringList("*.ini") );
#else // !#ifdef USE_ALTERNATE_GETFILE
    QString filename = QFileDialog::getOpenFileName(0,  "Load Profiles",  previous, "Profile files (*.ini)" );
#endif // #ifdef USE_ALTERNATE_GETFILE y/n

    QFile file;
    if ((filename.length() == 0) || (!file.exists(filename))) {
        outLog("*** Profile load abandonned!");
        _loading = false;
        return false;   // NO LOAD POSSIBLE
    }

	QSettings settings(filename,QSettings::IniFormat);
	
	bool ena;
	for(int row_idx=0; row_idx < rowCount(); row_idx++){
		//= loop rows and load each "option" as an [ini section] with enabled, value as values
		settings.beginGroup(item(row_idx, C_OPTION)->text());
		ena = settings.value("enabled").toBool() ;
		item(row_idx, C_ENABLED)->setText( ena ? "1" : "0");
		QString val = settings.value("value").toString();
		if(val == ""){
			val = item(row_idx, C_DEFAULT)->text();
		}
		item(row_idx, C_VALUE)->setText(val );
		set_row_bg(row_idx, ena ? QColor(200,255,200) : QColor(240,240,240));
		//= Broadcast changes
		emit upx(item(row_idx, C_OPTION)->text(),
				 item(row_idx, C_ENABLED)->text() == "1",
				 item(row_idx, C_VALUE)->text()
				 );
		settings.endGroup();
	}
	emit updated(get_fgfs_list());
	outLog("*** Profile loaded: "+filename);

    setLastUsed(filename);  // store lastused profile name
    return true;

}

//=============================================
// == Save Profile
/** \brief Opens Profile Dialog for loading a .ini File
 */

bool XSettingsModel::save_profile()
{
    // get lastused profile name
    QString previous = getLastUsed(); // or default if none

#ifdef USE_ALTERNATE_GETFILE
    QString filename = util_getFileName(0, "Save Profiles", previous, QStringList("*.ini"));
#else // !#ifdef USE_ALTERNATE_GETFILE
    QString filename = QFileDialog::getSaveFileName(0, "Save Profiles", previous, "Profile files (*.ini)" );
#endif // #ifdef USE_ALTERNATE_GETFILE y/n

    if (filename.length() == 0) {
        outLog("*** Profile write abandoneed");
        return false;
    }

    QSettings settings(filename,QSettings::IniFormat);
	
	// selected profile filename will be stored in settings
	set_option("profile", true, filename);

    setLastUsed(filename);

	//= loop rows and save each "option" as an [ini section] with enabled, value as values
	for(int row_idx=0; row_idx < rowCount(); row_idx++){
		settings.beginGroup(item(row_idx, C_OPTION)->text());
		settings.setValue( "enabled", item(row_idx, C_ENABLED)->text());
		settings.setValue( "value", item(row_idx, C_VALUE)->text());
		settings.endGroup();
	}
	
	outLog("*** Profile written to disk: "+filename);
    return true;
}


//==========================================================
//= Get Options
//==========================================================
QStringList XSettingsModel::get_fgfs_args()
{
	//= Read --options from tree
	QStringList args;
    QString str("");

	for(int row_idx=0; row_idx < rowCount(); row_idx++){

		if(item(row_idx, C_ENABLED)->text() == "1"){
			QString op = item(row_idx, C_OPTION)->text();
            str = "";
			if(op.startsWith("--")){
				str.append(item(row_idx, C_OPTION)->text()).append(item(row_idx, C_VALUE)->text());
			}
			if(str.length() > 0){
                if (str.indexOf(QChar(' ')) > 0) {
                    str = "\""+str+"\"";    // encase in QUOTE if it contains a SPACE char
                }
				args << str;
			}
		}
	}
	
	// Process unique items, like fgcom socket
	if(fgcom_enabled()){
		// This option needs an overhaul once. Server and port separated. It is never needed
		// as server:port for fgfs or fgcom. It???s just splitted everywhere ...
		// For the fgfs command line option we only need the port, for starting fgcom
		// we need the server and the port, but this can come to separated setting values (?)
		// Anyway ... took an age this one.
		QString serverandport(getx("fgcom_server"));
		QString portonly(serverandport.split(":").at(1));
		args << QString("--generic=socket,out,10,localhost,%1,udp,fgcom").arg(portonly);
	}
	
	//txtFgComPort->setText( value.split(":").at(1));

	//= add Extra args
	XOpt opt = get_opt("extra_args");
    if (opt.enabled && (opt.value.length() > 0)) {
		QStringList parts = opt.value.split("\n");
		if(parts.count() > 0){
			for(int i=0; i < parts.count(); i++){
				QString part = parts.at(i).trimmed();
				if(part.length() > 0){
					args << part;
				}
			}
		}
	}

	//== FgRoot
    str = fgroot();
    if (str.length() > 0) {
        // only ADDED if we have a FGROOT
        // Maybe the user sets FG_ROOT in the environment, so do NOT need any here
        str = "--fg-root="+str;
        if (str.indexOf(QChar(' ')) > 0) {
            str = "\""+str+"\"";    // encase in QUOTE if it contains a SPACE char
        }
        args <<  str;
    }

	//= Terrasync and custom scenery path
    // setup the DIFFERENT path separators!!!
    QString path_sep = ":"; // normal unix path separator
#ifdef Q_OS_WIN
    path_sep = ";"; // oops, switch the WINDOWS spearator
#endif
    // FIX20120410 - For Windows, and most other OSes, put paths with a SPACE in quotes
    // TODO - should check if paths are not BLANK, and are valid paths before blithly adding them
    // Helps no one to add BLANK or INVALID paths
    if (terrasync_enabled() && !custom_scenery_enabled()) {
        str = "--fg-scenery=";
        str.append(terrasync_data_path()).append(path_sep).append(scenery_path());
        if (str.indexOf(QChar(' ')) > 0) {
            str = "\""+str+"\"";    // encase in QUOTE if it contains a SPACE char
        }
        args << str;
		args << QString("--atlas=socket,out,5,localhost,5505,udp");
    }
	
    else if (terrasync_enabled() && custom_scenery_enabled()) {
        str = "--fg-scenery=";
        str.append(custom_scenery_path()).append(path_sep).append(terrasync_data_path()).append(path_sep).append(scenery_path());
        if (str.indexOf(QChar(' ')) > 0) {
            str = "\""+str+"\"";    // encase in QUOTE if it contains a SPACE char
        }
        args << str;
		args << QString("--atlas=socket,out,5,localhost,5505,udp");
	}

	else if (!terrasync_enabled() && custom_scenery_enabled())  {
        str = "--fg-scenery=";
        str.append(custom_scenery_path()).append(path_sep).append(scenery_path());
        if (str.indexOf(QChar(' ')) > 0) {
            str = "\""+str+"\"";    // encase in QUOTE if it contains a SPACE char
        }
        args << str;
	}
	
	else if (!terrasync_enabled() && !custom_scenery_enabled())  {
        str = "--fg-scenery=";
        str.append(scenery_path());
        if (str.indexOf(QChar(' ')) > 0) {
            str = "\""+str+"\"";    // encase in QUOTE if it contains a SPACE char
        }
        args << str;
	}
	
	return args;
}


QStringList XSettingsModel::get_fgfs_list()
{
	//TODO append the commands here
	QStringList args;
    QString fgfs = fgfs_path();
    if (fgfs.indexOf((QChar(' ')) > 0)) {
        fgfs = "\""+fgfs+"\"";  // Quote it if it contains a SPACE
    }
    args << fgfs;
	args << get_fgfs_args();
	return args;
}

QString XSettingsModel::get_fgfs_command_string()
{
    QString fgfs = fgfs_path();
    QFile file(fgfs);
    if (file.exists()) {
        outLog("XSettingsModel::get_fgfs_command_string: Found valid file ["+fgfs+"]");
    } else {
        outLog("XSettingsModel::get_fgfs_command_string: File ["+fgfs+"] NOT valid!");
    }
    if (fgfs.indexOf((QChar(' ')) > 0)) {
        fgfs = "\""+fgfs+"\"";  // quote it if it contains a SPACE
    }
    fgfs.append(" ");
    fgfs.append( get_fgfs_args().join(" ") );
    return fgfs;
}


//========================================================
//** Get Enviroment

QStringList XSettingsModel::get_fgfs_env(){

	QStringList args;
	if (!mainObject->X->get_ena("extra_env")) {
        return args;
    }
	QString extra = getx("extra_env");
	if (extra.length() > 0) {
		QStringList parts = extra.split("\n");
		if(parts.count() > 0){
			for(int i=0; i < parts.count(); i++){
				QString part = parts.at(i).trimmed();
				if(part.length() > 0){
					args << part;
				}
			}
		}
	}
	return args;
}

//===========================================================================
//== Get recent profile
//===========================================================================
/** \brief Path to fgfs executable
 */
QString XSettingsModel::profile(){
	return QString(getx("profile"));
	
}


//===========================================================================
//== fgfs Executable
//===========================================================================
/** \brief Path to fgfs executable
 */
QString XSettingsModel::fgfs_path(){
	QSettings firstsettings;
	
	if(!firstsettings.value("firststartup").toBool()){
		// OSX: prepending current app path for firststartup
		if(mainObject->runningOs() == OS_MAC) {
			return QDir::currentPath().append("/").append(getx("fgfs_path"));
		}else {
			return QString(getx("fgfs_path"));
		}
	// Not firststartup
	}else {
		return QString(getx("fgfs_path"));
	}


}

//===========================================================================
//== terrasync enabled/disabled
//===========================================================================
/** \brief Sert terrasync enabled/disabled
 */
bool XSettingsModel::terrasync_enabled(){
	return get_ena("terrasync_enabled");
	
}


//===========================================================================
//== terrasync Executable
//===========================================================================
/** \brief Path to terrasync executable
 */
QString XSettingsModel::terrasync_exe_path(){
	QSettings firstsettings;
	
	if(!firstsettings.value("firststartup").toBool()){
		// OSX: prepending current app path for firststartup
		if(mainObject->runningOs() == OS_MAC) {
			return QDir::currentPath().append("/").append(getx("terrasync_exe_path"));
		}else {
			return QString(getx("terrasync_exe_path"));
		}
		// Not firststartup
	}else {
		return QString(getx("terrasync_exe_path"));
	}
	
}

//===========================================================================
//== terrasync Data Path
//===========================================================================
/** \brief Path to terrasync executable
 */
QString XSettingsModel::terrasync_data_path(){
	return QString(getx("terrasync_data_path"));
}

//===========================================================================
//** Return FGCom enabled/disabled
//===========================================================================

bool XSettingsModel::fgcom_enabled(){
	return get_ena("fgcom_enabled");
}


//===========================================================================
//== fgcom Executable
//===========================================================================
/** \brief Path to fgcom executable
 */
QString XSettingsModel::fgcom_exe_path(){
	QSettings firstsettings;
	
	if(!firstsettings.value("firststartup").toBool()){
		// OSX: prepending current app path for firststartup
		if(mainObject->runningOs() == OS_MAC) {
			return QDir::currentPath().append("/").append(getx("fgcom_exe_path"));
		}else {
			return QString(getx("fgcom_exe_path"));
		}
		// Not firststartup
	}else {
		return QString(getx("fgcom_exe_path"));
	}
	
	
}


//===========================================================================
//== js_demo path
//===========================================================================

QString XSettingsModel::jsdemo_exe_path(){
    QSettings firstsettings;
	
	if(!firstsettings.value("firststartup").toBool()){
		// OSX: prepending current app path for firststartup
		if(mainObject->runningOs() == OS_MAC) {
			return QDir::currentPath().append("/").append(getx("jsdemo_exe_path"));
		}else {
			return QString(getx("jsdemo_exe_path"));
		}
		// Not firststartup
	}else {
		return QString(getx("jsdemo_exe_path"));
	}
	
}



//===========================================================================
//== fgroot  path
//===========================================================================
/** \return The absolute path to FG_ROOT ie /fgdata directory */
QString XSettingsModel::fgroot(){
	QSettings firstsettings;
	
	if(!firstsettings.value("firststartup").toBool()){
		// OSX: prepending current app path for firststartup
		if(mainObject->runningOs() == OS_MAC) {
			return QDir::currentPath().append("/").append(getx("fgroot_path"));
		}else {
			return QString(getx("fgroot_path"));
		}
		// Not firststartup
	}else {
		return QString(getx("fgroot_path"));
	}
}


/** \brief Path to FG_ROOT with appended path
 *
 * Returns the path to the FG_ROOT. If the default install
 * is selected, then that is returned, otherwise the custom selected fg_data path.
 * The file is appended with the append_path
 * \return The absolute path.
 */

QString XSettingsModel::fgroot(QString append_path){
	return this->fgroot().append(append_path);
}

//===========================================================================
//** Paths Sane
//===========================================================================
/** \brief Checks whether the executablem FG_ROOT paths are sane.
 *
 * \return true if sane
 */
bool XSettingsModel::paths_sane(){
	if(!QFile::exists(fgfs_path())){
		return false;
	}
	if(!QFile::exists(fgroot())){
		return false;
	}
	return true;
}


//===========================================================================
//** Aircraft Path
//===========================================================================
/** \brief The path to the /Aircraft directory
 *
  * \return fgroot/Aircraft absolute path --fg-aircraft path in case
 */
QString XSettingsModel::aircraft_path(){
	
	if (!mainObject->X->get_ena("custom_hangar_enabled")) {
		return fgroot().append("/Aircraft");
	}else{
		return mainObject->X->getx("--fg-aircraft=");
	}
}

/** \brief Path to the /Aircraft directory with a dir appended.
 *
 * \return absolute path.
 */
QString XSettingsModel::aircraft_path(QString dir){
	return fgroot().append("/Aircraft/").append(dir);
}


//===========================================================================
//** Airports path
//===========================================================================
/** \brief Return the absolute path to the /Airports directory
 *
 * \return If TerraSync is enabled, then returns a terrasync folder, otherwise the default.
 */
QString XSettingsModel::airports_path(){
	QString rpath;
	//= Using terrasync
	if(terrasync_enabled()){
		//if(mainObject->runningOs() == MainObject::MAC){   // what the h. says gral to himself
		//	rpath = QDir::homePath();
		//	rpath.append("/Documents/TerrasyncScenery");
		//}else{
			// Use the terra sync path
		rpath = terrasync_data_path().append("/Airports");
		}
	
	else{ // Otherwise return the FG_ROOT airports/
		rpath = fgroot().append("/Scenery/Airports");
	}
	//outLog("*** FGx settings: Airports path: " + rpath + " ***");
	return rpath;
}

//===========================================================================
//** Scenery Path - TODO x/win
//===========================================================================
/** \brief Returns the absolute path to the /Scenery file
 *
 * \return The absolute path.
 */
QString XSettingsModel::scenery_path(){

	return fgroot("/Scenery");
}

//===========================================================================
//** Custom scenery
//===========================================================================
QString XSettingsModel::custom_scenery_path(){
	return getx("custom_scenery_path");
}

bool XSettingsModel::custom_scenery_enabled(){
	return get_ena("custom_scenery_enabled");
}

void XSettingsModel::set_row_bg(int row_idx, QColor  bg_color)
{
	for(int col_idx=0; col_idx < columnCount(); col_idx++)
	{
		item(row_idx, col_idx)->setBackground(bg_color);
	}
}

// return a list of valid scenery directories
QStringList XSettingsModel::getSceneryDirs()
{
    QStringList list;
    QString path, msg;
    QDir dir;
    QFile file;
    int i, ind, j;
#ifdef Q_OS_WIN
    QChar psep(';');
#else
    QChar psep(':');
#endif

    // 1 - get FG_ROOT/Scenery
    path = fgroot("/Scenery");
    ind = path.indexOf(QChar('"'));
    if (ind == 0)
        path = path.mid(1,msg.length()-2);
    if ( !list.contains(path) ) {
        if (dir.exists(path)) {
            list += path;
        }
    }
    // 2 - if terrasync enabled
    if (terrasync_enabled()) {
        path = terrasync_data_path();
        ind = path.indexOf(QChar('"'));
        if (ind == 0)
            path = path.mid(1,msg.length()-2);
        if ( !list.contains(path) ) {
            if (dir.exists(path)) {
                list += path;
            }
        }
    }
    // 3 - if custom scenery enabled
    if (custom_scenery_enabled()) {
        path = custom_scenery_path();
        ind = path.indexOf(QChar('"'));
        if (ind == 0)
            path = path.mid(1,msg.length()-2);
        if ( !list.contains(path) ) {
            if (dir.exists(path)) {
                list += path;
            }
        }
    }

    // 4 - check fgfs command for any others, avoiding DUPLICATION
    QStringList fgfs_args = get_fgfs_args();
    for (i = 0; i < fgfs_args.size(); i++) {
        msg = fgfs_args.at(i);
        ind = msg.indexOf(QChar('"'));
        if (ind == 0)
            msg = msg.mid(1,msg.length()-2);
        if (msg.indexOf("--fg-scenery=") == 0) {
            msg = msg.mid(13);
            ind = msg.indexOf(QChar('"'));
            if (ind == 0)
                msg = msg.mid(1,msg.length()-2);
            QStringList path_list = msg.split(psep);
            for (j = 0; j < path_list.size(); j++) {
                path = path_list.at(j);
                ind = path.indexOf(QChar('"'));
                if (ind == 0)
                    path = path.mid(1,msg.length()-2);
                if ( !list.contains(path) ) {
                    if (dir.exists(path)) {
                        list += path;
                    }
                }
            }
        }
    }
    return list;
}

