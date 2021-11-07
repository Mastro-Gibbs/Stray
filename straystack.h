#ifndef STRAYSTACK_H
#define STRAYSTACK_H

#include "straylist.h"

template< typename T >
class StrayStack
{
public:
    StrayStack() {}
    ~StrayStack() {}


    bool isEmpty()
    {
        return stack.isEmpty();
    }

    void erase()
    {
        stack.clear();
    }

    void push( const T &item )
    {
        stack.append( item );
    }

    T pop()
    {
        return stack.removeLast();
    }

    T peek()
    {
        T res = stack.removeLast();
        stack.append( res );
        return res;
    }

    StrayList<T> data()
    {
        return stack;
    }

    uint64_t count()
    {
        return stack.count();
    }

private:
    StrayList<T> stack;

};


#endif // STRAYSTACK_H
