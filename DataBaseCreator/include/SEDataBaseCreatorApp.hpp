#pragma once 

#include "SBDApp.hpp"
#include "SEDataBaseCreatorAppGUI.hpp"

#include "SBQuantity.hpp"

#include <fstream>
#include <iostream>
#include "SAMSON.hpp"
#include "SBStructuralModel.hpp"
#include "SBAtom.hpp"
#include "SBResidue.hpp"
#include <math.h>
#include "SBMStructuralModelNode.hpp"
#include "SBBackbone.hpp"
#include <QtWidgets>
#include <QApplication>

#include <QTextEdit>   // Nous allons tout de même afficher le contenu du fichier ^^

#include <QFile>       // Pour utiliser le fichier

#include <QString>     // Stocke le contenu du fichier

#include <QTextStream> // Flux sortant du fichier



/// This class implements the functionality of the app

// SAMSON Element generator pro tip: add non-GUI functionality in this class. The GUI functionality should go in the SEDataBaseCreatorAppGUI class

class SEDataBaseCreatorApp : public SBDApp {

	SB_CLASS

public :

	/// \name Constructors and destructors
	//@{

	SEDataBaseCreatorApp();																													///< Constructs an app
	virtual ~SEDataBaseCreatorApp();																											///< Destructs the app

	//@}

	/// \name GUI
	//@{

	SEDataBaseCreatorAppGUI*											getGUI() const;															///< Returns a pointer to the GUI of the app
    static double                                                   dist(SBAtom* P1, SBAtom* P2);
    void createDataSet();

	//@}

};


SB_REGISTER_TARGET_TYPE(SEDataBaseCreatorApp, "SEDataBaseCreatorApp", "7F5E735C-C255-273C-AE68-F1FFCB4C4C40");
SB_DECLARE_BASE_TYPE(SEDataBaseCreatorApp, SBDApp);
