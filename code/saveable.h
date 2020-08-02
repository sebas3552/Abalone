#ifndef SAVEABLE_H
#define SAVEABLE_H

#include <QtGlobal>
#include <vector>

using namespace std;

/**
 * @brief The Saveable class represents a saveable object.
 */
class Saveable
{
    public:

        /**
         * @brief Destroys the object.
         */
        virtual ~Saveable(){}

    protected:

        /**
         * @brief Pushes back to a vector the saveable objects that represent the object, even itself.
         * @param objects Vector containing pointers to saveable objects. Only implemented by saveable objects that need to do so.
         */
        virtual void represent(vector<Saveable*>& objects)
        {
            Q_UNUSED(objects);
        }
};

#endif // SAVEABLE_H
