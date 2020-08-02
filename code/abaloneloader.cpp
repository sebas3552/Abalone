#include "abalone.h"
#include "abaloneboard.h"
#include "abaloneloader.h"

Game * AbaloneLoader::load(QString file_name){

    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File not found";
        return nullptr;
    }

    QTextStream in(&file);
    QString game_line = in.readLine();
    if(game_line != "abalone"){
        qDebug() << "File from different game";
        return nullptr;
    }

    Abalone * loadedGame = new Abalone();
    qDebug() << "Loading game";

    //Assign color to player 1
    QString player1 = in.readLine(); //hacer split
    QStringList player1list = player1.split(',');
    QStringList::const_iterator player1iterator = player1list.begin();
    player1iterator++;
    int player1color = (*player1iterator).toInt();
    loadedGame->chooseColor(0, (Color)player1color);

    //Assign color to player 2
    QString player2 = in.readLine(); //hacer split
    QStringList player2list = player2.split(',');
    QStringList::const_iterator player2iterator = player2list.begin();
    player2iterator++;
    int player2color = (*player2iterator).toInt();
    loadedGame->chooseColor(1, (Color)player2color);

    /*Creates board. Reads exactly 81 piece fields and then, if there are lost pieces reads them.*/
    for (int row = 0; row < DEFAULT_SIZE; row++) {
        for (int col = 0; col < DEFAULT_SIZE; col++) {
            QPoint point(col, row);
            QString pieceInfo = in.readLine();
            QStringList pieceList = pieceInfo.split(',');
            QStringList::const_iterator iterator = pieceList.begin();
            int owner = (*iterator).toInt();
            if(owner == -1) //if there is no piece
                continue;
            iterator++;
            QString name = *iterator;
            iterator++;
            int color = (*iterator).toInt();
            Piece * piece = new Piece(owner, name, (Color)color);
            loadedGame->getBoard()->addPiece(piece, point);
            qDebug() << "Loading piece: owner = player " << owner << " name = " << name << " color = " << color << endl;
        }
    }

    //Add lost pieces
    while (!in.atEnd()) {
        QString pieceInfo = in.readLine();
        QStringList list = pieceInfo.split(',');
        QStringList::const_iterator iterator = list.begin();
        int owner = (*iterator).toInt();
        if(owner == -1)
            continue;
        iterator++;
        QString name = *iterator;
        iterator++;
        int color = (*iterator).toInt();
        Piece * piece = new Piece(owner, name, (Color)color);
        dynamic_cast<AbaloneBoard*>(loadedGame->getBoard())->addLostPiece(piece);
        qDebug() << "Loading lost piece: owner = player " << owner << " name = " << name << " color = " << color << endl;
    }
    qDebug() << "Game loaded successfully";
    return loadedGame;
}
