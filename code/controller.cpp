#include "abalonesaver.h"
#include "abaloneboard.h"
#include "abalonearbiter.h"
#include "controller.h"

int Controller::main()
{
    w->show();
    return a->exec();
}

Controller::Controller(QApplication* app, MainWindow* mw, Game* game, HelpWindow* helpWindow, ChooseColor* colorWindow, GameWindow* gameWindow, GameOver* gameOver, Saver* saver, QObject* parent)
: QObject(parent), game(nullptr), helpWindow(nullptr)
{
    this->a = app;
    this->w = mw;
    this->game = game;
    this->helpWindow = helpWindow;
    this->colorWindow = colorWindow;
    this->gameWindow = gameWindow;
    this->gameOver = gameOver;
    this->saver = saver;
    QObject::connect(w, SIGNAL(playRequest()), this, SLOT(playRequested()));
    QObject::connect(w, SIGNAL(helpRequest()), this, SLOT(helpRequested()));
    QObject::connect(w, SIGNAL(saveRequest(QString)), this, SLOT(saveRequested(QString)));
    QObject::connect(w, SIGNAL(loadRequest(QString)), this, SLOT(loadGameRequested(QString)));
    QObject::connect(colorWindow, SIGNAL(setColor(int, Color)), this, SLOT(setColor(int, Color)));
    QObject::connect(colorWindow, SIGNAL(startGame(int)), this, SLOT(startGameRequested(int)));
    QObject::connect(colorWindow, SIGNAL(helpRequest()), this, SLOT(helpRequested()));
    QObject::connect(gameWindow, SIGNAL(saveRequest(QString)), this, SLOT(saveRequested(QString)));
    QObject::connect(gameWindow, SIGNAL(helpRequest()), this, SLOT(helpRequested()));
    QObject::connect(dynamic_cast<Abalone*>(game), SIGNAL(requestColors()), this, SLOT(colorsRequested()));
    QObject::connect(gameWindow, SIGNAL(requestColor(int)), this, SLOT(askGameColors(int)));
    QObject::connect(this, SIGNAL(respondColor(Color, int)), gameWindow, SLOT(colorReceived(Color, int)));
    QObject::connect(this, SIGNAL(updateUI(vector<vector<Piece*> >,vector<Piece*>, int, vector<QPoint>)), gameWindow, SLOT(update(vector<vector<Piece*> >,vector<Piece*>, int, vector<QPoint>)));
    QObject::connect(gameWindow, SIGNAL(select(QPoint)), this, SLOT(selected(QPoint)));
    QObject::connect(gameOver, SIGNAL(finishGame()), this, SLOT(finishGameRequested()));
}

Controller::~Controller()
{
}

void Controller::playRequested()
{
    qDebug() << qPrintable(QString("Play was called!"));
    game->init();   //prompts user to select the pieces' colors
}

void Controller::helpRequested()
{
    helpWindow->show();
}

void Controller::colorsRequested()
{
    colorWindow->show();
}

void Controller::saveRequested(QString fileName)
{
    game->save(this->saver, fileName);
}

void Controller::setColor(int player, Color color)
{
    game->chooseColor(player, color);
    emit this->respondColor(color, player);
}

void Controller::loadGameRequested(QString filename)
{
    this->game = game->load(filename);
    w->setVisible(false);
    emit this->updateUI(this->game->getBoard()->getBoard(), dynamic_cast<AbaloneBoard*>(this->game->getBoard())->lostPieces,  game->getCurrentPlayer(), dynamic_cast<AbaloneArbiter*>(this->game->getArbiter())->canMoveList);
    gameWindow->setVisible(true);
}

void Controller::startGameRequested(int initialPlayer)
{
    colorWindow->setVisible(false);
    gameWindow->setVisible(true);
    game->play(initialPlayer);
    emit this->updateUI(this->game->getBoard()->getBoard(), dynamic_cast<AbaloneBoard*>(this->game->getBoard())->lostPieces, game->getCurrentPlayer(), dynamic_cast<AbaloneArbiter*>(this->game->getArbiter())->canMoveList);

}

void Controller::askGameColors(int player)
{
    emit this->respondColor(game->getColor(player), player);
}

void Controller::selected(QPoint p)
{
    /*The interface sees a piece as a coordinate of the form (x,y). Just swap the coordinates to use in the game.*/
    QPoint point(p.y(), p.x());
    /*For now, just print the coordinates of the pressed piece.*/
    qDebug() << "Selected point: " << point << endl;
    int status = GAME_NOT_OVER;
    status = dynamic_cast<AbaloneArbiter*>(this->game->getArbiter())->select(point);
    emit this->updateUI(this->game->getBoard()->getBoard(), dynamic_cast<AbaloneBoard*>(this->game->getBoard())->lostPieces, game->getCurrentPlayer(), dynamic_cast<AbaloneArbiter*>(this->game->getArbiter())->canMoveList);
    if(status != GAME_NOT_OVER){
        int loser = status;
        int winner = status == PLAYER_1_GAME_OVER ? PLAYER_2_GAME_OVER : PLAYER_1_GAME_OVER;
        qDebug() << "GAME OVER!!\n";
        gameOver->setWindowInfo(loser, winner, game->getColor(loser), game->getColor(winner));
        gameOver->show();
    }
}

void Controller::finishGameRequested()
{
    QApplication::quit();
}

int main(int argc, char* argv[])
{
    QApplication* a = new QApplication(argc, argv);
    MainWindow* w = new MainWindow();
    Abalone* game = new Abalone();
    HelpWindow* helpWindow = new HelpWindow(nullptr, game->showRules());
    ChooseColor* colorWindow = new ChooseColor(w);
    GameWindow* gameWindow = new GameWindow(w);
    GameOver* gameOver = new GameOver(w);
    Saver* saver = new AbaloneSaver();
    Controller controller(a, w, game, helpWindow, colorWindow, gameWindow, gameOver, saver);
    
    int status = controller.main();
    
    delete a;
    delete w;
    delete game;
    delete helpWindow;
    delete colorWindow;
    delete gameWindow;
    delete gameOver;
    delete saver;
    
    return status;
    
}
