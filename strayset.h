#ifndef STRAYSET_H
#define STRAYSET_H

#include "straytree.h"
#include <iostream>

using namespace std;


template< typename T > class StraySetIterator;


template< typename T >
class StraySet
{

public:
    StraySet() {}

    ~StraySet() {}

    int count()
    {
        return size;
    }

    bool isEmpty()
    {
        if( size == 0 ) return true;
        else return false;
    }

    bool contains( const T &elem )
    {
        return set.find( elem );
    }

    void insert( const T &elem )
    {
        if ( !set.find( elem ) )
            set.insert( elem );
    }

    StrayVector<T> *toVector()
    {
        return set.visit( VisitMode::BreadthOrder );
    }

private:
    int size = 0;
    StrayBST<T> set;

};






#endif // STRAYSET_H
