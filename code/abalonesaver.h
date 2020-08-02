#ifndef ABALONESAVER_H
#define ABALONESAVER_H

#include "saver.h"

/**
 * @brief The AbaloneSaver class defines a specific saver for the Abalone game.
 * @From Saver interface.
 */
class AbaloneSaver : public Saver
{
    public:

        /**
         * @brief Constructs the object.
         */
        AbaloneSaver();

        /**
         * @brief Saves the game state represented by a collection of saveable objects.
         * @param objects Collection of pointers to saveable objects that represent the state of the game.
         */
        virtual void save(vector<Saveable*>& objects, QString fileName);
};

#endif // ABALONESAVER_H
