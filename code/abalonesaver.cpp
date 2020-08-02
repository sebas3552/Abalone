#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QApplication>
#include <QPushButton>
#include <QTranslator>
#include <QObject>
#include "abalone.h"
#include "abalonesaver.h"
#include "abaloneboard.h"

using namespace std;

AbaloneSaver::AbaloneSaver()
{

}

void AbaloneSaver::save(vector<Saveable *> &objects, QString fileName)
{
    if(objects.empty()){
        qDebug("No objects to save!");
        return;
    }
    qDebug() << fileName;
    std::string gameFile = fileName.toLocal8Bit().constData();
    ofstream outputFile(gameFile, ios::out);

    for(auto object : objects){
        if(dynamic_cast<Abalone*>(object)){
            Abalone* savedGame = dynamic_cast<Abalone*>(object);
            outputFile << "abalone" << endl;
            outputFile << savedGame->player1.getId() << "," << savedGame->player1.getColor() << endl;
            outputFile << savedGame->player2.getId() << "," << savedGame->player2.getColor() << endl;
            for(auto row : savedGame->getBoard()->getBoard()){
                for(auto piece : row){
                    if(!piece){
                        outputFile << "-1" << endl;
                    }else{
                        outputFile << piece->getOwner() << "," << qPrintable(piece->getName()) << "," << piece->getColor() << endl;
                    }
                }
            }
            if(!dynamic_cast<AbaloneBoard*>(savedGame->getBoard())->lostPieces.empty()){
                for(auto piece : dynamic_cast<AbaloneBoard*>(savedGame->getBoard())->lostPieces){
                    outputFile << piece->getOwner() << "," << qPrintable(piece->getName()) << "," << piece->getColor() << endl;
                }
            }
        }
    }

}
