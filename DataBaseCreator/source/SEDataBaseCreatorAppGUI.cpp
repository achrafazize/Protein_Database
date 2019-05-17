#include "SEDataBaseCreatorAppGUI.hpp"
#include "SEDataBaseCreatorApp.hpp"
#include "SAMSON.hpp"
#include "SBGWindow.hpp"

SEDataBaseCreatorAppGUI::SEDataBaseCreatorAppGUI( SEDataBaseCreatorApp* t ) : SBGApp( t ) {

	ui.setupUi( this );

}

SEDataBaseCreatorAppGUI::~SEDataBaseCreatorAppGUI() {

}

SEDataBaseCreatorApp* SEDataBaseCreatorAppGUI::getApp() const { return static_cast<SEDataBaseCreatorApp*>(SBGApp::getApp()); }

void SEDataBaseCreatorAppGUI::loadSettings(SBGSettings* settings) {

	if (settings == NULL) return;
	
	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

void SEDataBaseCreatorAppGUI::saveSettings(SBGSettings* settings) {

	if (settings == NULL) return;

	// SAMSON Element generator pro tip: complete this function so your app can save its GUI state from one session to the next

}

SBCContainerUUID SEDataBaseCreatorAppGUI::getUUID() const { return SBCContainerUUID( "68C91AC3-E173-9B95-2A8A-C7BEC457C0C0" );}

QPixmap SEDataBaseCreatorAppGUI::getLogo() const { 
	
	// SAMSON Element generator pro tip: this icon will be visible in the GUI title bar. 
	// Modify it to better reflect the purpose of your app.

	return QPixmap(QString::fromStdString(SB_ELEMENT_PATH + "/Resource/icons/SEDataBaseCreatorAppIcon.png"));

}

QString SEDataBaseCreatorAppGUI::getName() const { 

	// SAMSON Element generator pro tip: this string will be the GUI title. 
	// Modify this function to have a user-friendly description of your app inside SAMSON

	return "SEDataBaseCreatorApp"; 

}

int SEDataBaseCreatorAppGUI::getFormat() const { 
	
	// SAMSON Element generator pro tip: modify these default settings to configure the window
	//
	// SBGWindow::Savable : let users save and load interface settings (implement loadSettings and saveSettings)
	// SBGWindow::Lockable : let users lock the window on top
	// SBGWindow::Resizable : let users resize the window
	// SBGWindow::Citable : let users obtain citation information (implement getCitation)
	
	return (SBGWindow::Savable | SBGWindow::Lockable | SBGWindow::Resizable | SBGWindow::Citable);

}

QString SEDataBaseCreatorAppGUI::getCitation() const {

	// SAMSON Element generator pro tip: modify this function to add citation information

	return
		"If you use this app in your work, please cite: <br/>"
		"<br/>"
		"[1] <a href=\"https://www.samson-connect.net\">https://www.samson-connect.net</a><br/>";
	
}

void SEDataBaseCreatorAppGUI::onCreate(){
    getApp()->createDataSet();

}
