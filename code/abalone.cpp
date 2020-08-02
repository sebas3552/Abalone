#include <random>
#include <ctime>

#include "abalone.h"
#include "abaloneboard.h"
#include "abalonearbiter.h"

#define RANDOMIZE srand(time(0))

Abalone::Abalone(QObject* parent)
: QObject(parent)
{

    board = new AbaloneBoard();    
    arbiter = new AbaloneArbiter(dynamic_cast<AbaloneBoard*>(board));
    gameLoader = new GameLoader();
    gameLoader->setLoader(Loader::MODE::ABALONE);
}

Abalone::~Abalone()
{
    delete board;
    delete gameLoader;
}

void Abalone::chooseColor(int id, Color color)
{
	if(id == 0){
        player1.setId(0);
        player1.setColor(color);
	}else{
        player2.setId(1);
        player2.setColor(color);
    }
    qDebug() << "Color " << color << " has been chosen for player " << id << endl;
}

Color Abalone::getColor(int player)
{
    if(player == 0)
        return player1.getColor();
    else
        return player2.getColor();
}

int Abalone::getCurrentPlayer() const
{
    return this->arbiter->getCurrentPlayer();
}

void Abalone::init()
{
    emit requestColors();
}

void Abalone::finalize()
{

}

int Abalone::won()
{
    return 0;
}

int Abalone::gameOver()
{
    return 0;
}


QString Abalone::showRules()
{
    return QString("The aim of the game is to eject six of the opponents\n marbles from the board. You can move up to three\n marbles of your color, which must be connected in a\n straight line, in any direction, if the destination fields are\n free or occupied by a minor number of opponents marbles.");
}

void Abalone::play(int initialPlayer)
{
    qDebug() << qPrintable(QString("Player %0 started the game!").arg(initialPlayer));
    initialState();
}

void Abalone::initialState(){
    int piece = 0;
    for(int i = 4; i < 9; ++i )
       this->board->addPiece(new Piece(player1.getId(), QString("Piece %0").arg(piece++), player1.getColor()), QPoint(i,0));
    for(int i = 3; i < 9; ++i )
       this->board->addPiece(new Piece(player1.getId(), QString("Piece %0").arg(piece++), player1.getColor()), QPoint(i,1));
    for(int i = 4; i < 7; ++i )
       this->board->addPiece(new Piece(player1.getId(), QString("Piece %0").arg(piece++), player1.getColor()), QPoint(i,2));

    for(int i = 0; i < 5; ++i )
       this->board->addPiece(new Piece(player2.getId(), QString("Piece %0").arg(piece++), player2.getColor()), QPoint(i,8));
    for(int i = 0; i < 6; ++i )
       this->board->addPiece(new Piece(player2.getId(), QString("Piece %0").arg(piece++), player2.getColor()), QPoint(i,7));
    for(int i = 2; i < 5; ++i )
       this->board->addPiece(new Piece(player2.getId(), QString("Piece %0").arg(piece++), player2.getColor()), QPoint(i,6));
}

Game * Abalone::load(QString filename)
{
    Game * loadedGame = gameLoader->load(filename);
    return loadedGame;
}

void Abalone::represent(vector<Saveable *> &objects)
{
    //insert all game objects into objects vector here
    objects.push_back(this);
}
