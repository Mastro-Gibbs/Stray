#ifndef STRAYSORT_H
#define STRAYSORT_H


#include <cstdint>

#include "straytree.h"


template < typename T >
class StraySort
{
public:
    StraySort( T *arr, uint64_t size )
    {
        this->array = arr;
        this->size = size;
    }

    void sort()
    {
        uint64_t i = 0, t1 = 0, t2 = 0, dim = 1;
        T *aux = new T[ size ];

        for(uint64_t i=0; i < size; i++)
            aux[ i ] = array[ i ];

        for ( ; dim < size; dim = dim + dim )
        {
            for ( i = 0; i < size - dim; i = i + dim + dim )
            {
                t1 = i + dim + dim - 1;
                t2 = size - 1;

                merge( aux, i, i + dim - 1, t1 < t2 ? t1 : t2);
            }
        }

        delete [] aux;
    }




private:
    T *array;
    uint64_t size;


    void merge( T *aux, int low, int mid, int high )
    {
        int i = 0;
        int j = 0;
        int k = 0;

        for ( i = mid + 1; i > low; i-- )
            aux[ i - 1 ] = array[ i - 1 ];

        for ( j = mid; j < high; j++ )
            aux[ high + mid - j ] = array[ j + 1 ];

        for ( k = low; k <= high; k++ )
        {
            if ( aux[ j ] < aux[ i ] )
               array[ k ] = aux[ j-- ];
           else
               array[ k ] = aux[ i++ ];
        }
    }

};



#endif // STRAYSORT_H
