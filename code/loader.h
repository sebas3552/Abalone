#ifndef LOADER_H
#define LOADER_H

#include <QString>

#include "game.h"

/**
 * @brief The Loader class represents an abstract game loader.
 */
class Loader{

    public:

        /**
         * @brief Destroys the object.
         */
        virtual ~Loader(){}

        /**
         * @brief Loads a previous game state from a file.
         * @param fileName File where the previous state of the game was saved.
         * @return A pointer to a Game object created from the file.
         */
        virtual Game * load(QString fileName) = 0;

        /**
         * @brief The MODE enum holds different game loaders to be implemented by other developers using the framework.
         */
        enum MODE{
            ABALONE
        };
};

#endif // LOADER_H
