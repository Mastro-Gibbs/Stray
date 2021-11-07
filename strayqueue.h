#ifndef STRAYQUEUE_H
#define STRAYQUEUE_H


#include "straylist.h"

template< typename T >
class StrayQueue
{
public:
    StrayQueue() {}
    ~StrayQueue() {}

    void enqueue( const T &item )
    {
        queue.append( item );
    }

    T dequeue()
    {
        return queue.removeFirst();
    }

    bool isEmpty()
    {
        return queue.isEmpty();
    }

    void clear()
    {
        queue.clear();
    }

    StrayList<T> data()
    {
        return queue;
    }


    uint64_t count()
    {
        return queue.count();
    }

private:
    StrayList<T> queue;
};


#endif // STRAYQUEUE_H
