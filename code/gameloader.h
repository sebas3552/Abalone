#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <QString>

#include "abaloneloader.h"
#include "game.h"

/**
 * @brief The GameLoader class defines a loader object. Implemented using the strategy design pattern.
 */
class GameLoader
{
    private:

        ///Pointer to a general loader.
        Loader * loader;
    public:

        /**
         * @brief Constructs the object.
         */
        GameLoader() : loader(nullptr){}

        /**
          * @brief Destroys the object.
          */
        ~GameLoader()
        {
            if(loader){
                delete loader;
            }
        }

        /**
         * @brief Sets the specific loader type to be used within a game.
         * @param modo Specific loader mode to be set.
         */
        void setLoader(Loader::MODE modo);

        /**
         * @brief Loads a previous game state from a file.
         * @param fileName File where the previous state of the game was saved.
         * @return A pointer to a Game object created from the file.
         */
        Game * load(QString fileName);

};

#endif // GAMELOADER_H
