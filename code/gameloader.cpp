#include "gameloader.h"

void GameLoader::setLoader(Loader::MODE modo)
{
    switch(modo){
        case Loader::MODE::ABALONE:
            loader = new AbaloneLoader();
            break;
        default:
            qDebug("Loader not implemented!");
    }
}

Game * GameLoader::load(QString filename)
{
    //check file errors
    Game * loadedGame = loader->load(filename);
    //Close file
    return loadedGame;
}


