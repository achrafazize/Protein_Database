#include "SEDataBaseCreatorApp.hpp"
#include "SEDataBaseCreatorAppGUI.hpp"


#include "SBAtom.hpp"
#include "SAMSON.hpp"
#include "SBRandom.hpp"

#include <fstream>
#include "SAMSON.hpp"
#include "SBStructuralModel.hpp"
#include "SBAtom.hpp"
#include "SBResidue.hpp"
#include "SBBackbone.hpp"


SEDataBaseCreatorApp::SEDataBaseCreatorApp() {

    setGUI(new SEDataBaseCreatorAppGUI(this));
    getGUI()->loadDefaultSettings();

}

SEDataBaseCreatorApp::~SEDataBaseCreatorApp() {

    getGUI()->saveDefaultSettings();
    delete getGUI();

}

SEDataBaseCreatorAppGUI* SEDataBaseCreatorApp::getGUI() const { return static_cast<SEDataBaseCreatorAppGUI*>(SBDApp::getGUI()); }

double SEDataBaseCreatorApp::dist(SBAtom* P1, SBAtom* P2) {
    // Calculer la distance entre deux atomes
    SBPosition3 const& p1 = P1->getPosition();
    SBPosition3 const& p2 = P2->getPosition();
    double d= pow((SBQuantity::angstrom(p1.v[0]).getValue()-SBQuantity::angstrom(p2.v[0]).getValue()),2)+ pow((SBQuantity::angstrom(p1.v[1]).getValue()-SBQuantity::angstrom(p2.v[1]).getValue()),2) + pow((SBQuantity::angstrom(p1.v[2]).getValue()-SBQuantity::angstrom(p2.v[2]).getValue()),2);
    return sqrt(d);
}

void SEDataBaseCreatorApp::createDataSet(){
    // Ouverture du fichier dataset.txt en mode ecriture
    ofstream file("/users/misc-b/INF473N-2019/achraf.azize/Elements/DataBaseCreator/dataSet.txt", ios::out);

    // Lecture de la dataset de pdb
    QDir directory("/users/misc-b/INF473N-2019/achraf.azize/Elements/DataBaseCreator/PDB_SMALL");
    QStringList files = directory.entryList(QStringList() << "*.pdb" ,QDir::Files);
    int nbrDeProteins = 0;
    int nbrDeVecteurEcrit =0;

    // Premiere Iteration pour compter le nombre de proteins et de vecteurs
    foreach(QString filename, files) {
        nbrDeProteins++;
        // Creation de la liste de parametres de lecture du fichier sur Samson
        SBList<std::string>* parameters= new SBList<std::string>;
        parameters->push_back("0");
        parameters->push_back("1");
        parameters->push_back("1");
        parameters->push_back("0");
        parameters->push_back("0");
        parameters->push_back("1");
        parameters->push_back("0");
        parameters->push_back("0");

        // Creation du layer
        SBPointer<SBDDocumentLayer> lay= new SBDDocumentLayer();
        lay->create();

        // on importe le fichier pdb en utilisant le parser de SAMSON
        SAMSON::importFromFile(("/users/misc-b/INF473N-2019/achraf.azize/Elements/AtomShaker/PDB_SMALL/"+filename).toStdString(),parameters,lay());

        // on obtient les noeuds de type Residue
        SBNodeIndexer atomIndexer;
        lay->getNodes(atomIndexer, SBNode::IsType(SBNode::Residue));
        int n=0;


        // On compte le nombre de carbone alpha
        SB_FOR(SBNode* node, atomIndexer){
            SBResidue* residue = static_cast<SBResidue *>(node);
            if (residue->isAminoAcid()&&residue->getBackbone()&&residue->getBackbone()->getAlphaCarbon()){
                n++;
            }
        }

        // Creation d'une liste de carbonne alpha
        SBAtom** listCarbon = new SBAtom*[n];
        int p=0;
        for (int i=0;i<atomIndexer.size();i++){
            SBResidue* residue = static_cast<SBResidue *>(atomIndexer[i]);
            if (residue->isAminoAcid()&&residue->getBackbone()&&residue->getBackbone()->getAlphaCarbon()){
                listCarbon[p]=residue->getBackbone()->getAlphaCarbon();
                p++;
            }
        }

        if (n>9) {
            // Creation de la matrice de distance
            double** distAll= new double*[n-9];
            for (int i=0; i<n-9; i++){
                distAll[i]= new double[13];
                for (int k=0; k<7; k++){
                    distAll[i][k]=dist(listCarbon[i+k],listCarbon[i+k+2]);
                }
                for (int k=0; k<5; k++){
                    distAll[i][k+7]=dist(listCarbon[i+k],listCarbon[i+k+4]);
                }
                distAll[i][12]=dist(listCarbon[i],listCarbon[i+8]);
            }

            // On ne garde que les distances inferieur a 12.0 A
            for (unsigned int i = 0; i < n-9; i++) {
                bool ajoute = true;

                for (int k=0;k<13;k++){
                    if (distAll[i][k] > 12.0){
                        ajoute = false;
                        break;

                    }
                }

                // On ecrit la matrice de distance sur le fichier dataSet.txt
                if (ajoute){
                    nbrDeVecteurEcrit++;
                }

            }


            // Suppression des tableaux
            for (int i=0; i<n-9; i++){
                delete[] distAll[i];
            }

            delete[] distAll;

        }

        delete parameters;
        delete[] listCarbon;

        SAMSON::undo();
        lay.deleteReferenceTarget();



    }

    file << nbrDeProteins;
    file <<  "\n" ;
    file << nbrDeVecteurEcrit;
    file <<  "\n" ;

    // Deuxieme Iteration pour ecrire toutes les lignes de la dataset
    foreach(QString filename, files) {

        // Creation de la liste de parametres de lecture du fichier sur Samson
        SBList<std::string>* parameters= new SBList<std::string>;
        parameters->push_back("0");
        parameters->push_back("1");
        parameters->push_back("1");
        parameters->push_back("0");
        parameters->push_back("0");
        parameters->push_back("1");
        parameters->push_back("0");
        parameters->push_back("0");

        // Creation du layer
        SBPointer<SBDDocumentLayer> lay= new SBDDocumentLayer();
        lay->create();

        // on importe le fichier pdb en utilisant le parser de SAMSON
        SAMSON::importFromFile(("/users/misc-b/INF473N-2019/achraf.azize/Elements/AtomShaker/PDB_SMALL/"+filename).toStdString(),parameters,lay());

        // on obtient les noeuds de type Residue
        SBNodeIndexer atomIndexer;
        lay->getNodes(atomIndexer, SBNode::IsType(SBNode::Residue));
        int n=0;


        // On compte le nombre de carbone alpha
        SB_FOR(SBNode* node, atomIndexer){
            SBResidue* residue = static_cast<SBResidue *>(node);
            if (residue->isAminoAcid()&&residue->getBackbone()&&residue->getBackbone()->getAlphaCarbon()){
                n++;
            }
        }

        // Creation d'une liste de carbonne alpha
        SBAtom** listCarbon = new SBAtom*[n];
        int p=0;
        for (int i=0;i<atomIndexer.size();i++){
            SBResidue* residue = static_cast<SBResidue *>(atomIndexer[i]);
            if (residue->isAminoAcid()&&residue->getBackbone()&&residue->getBackbone()->getAlphaCarbon()){
                listCarbon[p]=residue->getBackbone()->getAlphaCarbon();
                p++;
            }
        }

        if (n>9) {
            // Creation de la matrice de distance
            double** distAll= new double*[n-9];
            for (int i=0; i<n-9; i++){
                distAll[i]= new double[13];
                for (int k=0; k<7; k++){
                    distAll[i][k]=dist(listCarbon[i+k],listCarbon[i+k+2]);
                }
                for (int k=0; k<5; k++){
                    distAll[i][k+7]=dist(listCarbon[i+k],listCarbon[i+k+4]);
                }
                distAll[i][12]=dist(listCarbon[i],listCarbon[i+8]);
            }

            // On ne garde que les distances inferieur a 12.0 A
            for (unsigned int i = 0; i < n-9; i++) {
                bool ajoute = true;

                for (int k=0;k<13;k++){
                    if (distAll[i][k] > 12.0){
                        ajoute = false;
                        break;

                    }
                }

                // On ecrit la matrice de distance sur le fichier dataSet.txt
                if (ajoute){
                    for (int k=0;k<13;k++){
                        file << distAll[i][k] << " ";

                    }
                    file << filename.toStdString()<< "\n" ;


                }

            }

            // Suppression des tableaux
            for (int i=0; i<n-9; i++){
                delete[] distAll[i];
            }

            delete[] distAll;

        }

        delete parameters;
        delete[] listCarbon;

        SAMSON::undo();
        lay.deleteReferenceTarget();


    }



    // Fermeture du fichier
    file.close();

}
