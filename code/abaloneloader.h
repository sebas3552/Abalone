#ifndef LOADERABALONE_H
#define LOADERABALONE_H

#include <QDebug>
#include <QFile>
#include <QString>

#include "loader.h"
#include "game.h"

/**
 * @brief The AbaloneLoader class states a specific loader for the Abalone game.
 * Inherits from Loader.
 */
class AbaloneLoader : public Loader
{
    public:

        /**
         * @brief Constructs the object.
         */
        AbaloneLoader(){}

        /**
         * @brief Destroys the object.
         */
        ~AbaloneLoader(){}

        /**
         * @brief Loads the game from a file.
         * @param fileName Name of the file containing the state of the game.
         * @return A new game object constructed from the information in the file.
         */
        Game * load(QString fileName);
};

#endif // LOADERABALONE_H
