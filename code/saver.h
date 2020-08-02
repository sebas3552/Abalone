#ifndef SAVER_H
#define SAVER_H

#include "saveable.h"

/**
 * @brief The Saver class represents an abstract saver.
 */
class Saver
{
    public:

        /**
         * @brief Destroys the object.
         */
        virtual ~Saver() {}

        /**
         * @brief Saves the saveable objects in the vector to an output file with specified format.
         * @param objects Vector containing pointers to saveable objects.
         */
        virtual void save(vector<Saveable*>& objects, QString fileName) = 0;
};

#endif // SAVER_H
