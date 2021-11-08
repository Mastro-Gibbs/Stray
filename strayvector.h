#ifndef STRAYVECTOR_H
#define STRAYVECTOR_H

#include <iostream>
#include <cstdint>
#include <string.h>
#include <initializer_list>

using namespace std;


enum Order
{
    Preserve = 1,
    Unordered = 0
};

enum Shift
{
    Left = 0,
    Right = 1
};


template< typename T >
class StrayVector
{
public:

    StrayVector( uint64_t size = 1 )
    {
        this->size = size;
        this->elemsCount = 0;
        this->fillValue = 0.f;
        this->vec = new T[ size ];
    }

    StrayVector( initializer_list<T> list )
    {
        this->size = list.size();
        this->elemsCount = 0;
        this->fillValue = 0.f;
        this->vec = new T[ size ];

        for ( T item : list )
        {
            append( item );
        }

    }

    ~StrayVector()
    {
        delete [] vec;
    }


    void clear()
    {
        elemsCount = 0;
    }

    void setPrefSize( uint64_t newSize )
    {
        realloc( newSize );
    }

    uint64_t memSize()
    {
        return ( sizeof (T) * elemsCount );
    }

    uint64_t count() const { return elemsCount; }

    uint64_t vecSize() { return size; }

    void prepend( T item )
    {
        updateFillValue();

        if (  size < 100 && fillValue > 75 )
            realloc();
        else if ( size < 500 && fillValue > 85 )
            realloc();
        else if ( size < 2000 && fillValue > 95 )
            realloc();
        else if ( fillValue > 95 )
            realloc();

        shift( 0, size, Right );
        vec[ 0 ] = item;
        elemsCount++;
    }

    void append( const T &item )
    {
        updateFillValue();

        if (  size < 100 && fillValue > 75 )
            realloc();
        else if ( size < 500 && fillValue > 85 )
            realloc();
        else if ( size < 2000 && fillValue > 95 )
            realloc();
        else if ( fillValue > 95 )
            realloc();

        vec[ elemsCount ] = item;
        elemsCount++;
    }

    void merge( StrayVector *other )
    {
        for ( uint64_t i = 0; i < other->elemsCount; i++ )
        {
            append( other->get( i ) );
        }
    }

    int64_t indeOf( const T &elem )
    {
        int64_t res = 0;
        bool find = false;
        for ( uint64_t i = 0; i < size; i++ )
        {
            if ( vec[ i ] == elem )
            {
                find = true;
                res = i;
                break;
            }
        }

        if ( !find )
            res = -1;

        return res;
    }


    void set( const T &elem, uint64_t index )
    {
        vec[ index ] = elem;
    }

    T &get ( uint64_t index ) const
    {
        return vec[ index ];
    }


    T last()
    {
         T res = vec[ elemsCount - 1 ];
         return res;
    }

    T removeFirst()
    {
        T res = vec[ 0 ];

        shift( 0, elemsCount );

        elemsCount--;

        return res;
    }

    T removeLast()
    {
        T res = vec[ elemsCount - 1 ];

        vec[ elemsCount - 1 ] = T();

        elemsCount--;

        return res;
    }

    T remove( uint64_t index, Order ord = Unordered )
    {
        T res = vec[ index ];

        if ( ord  )
            shift( index, elemsCount );
        else
        {
            vec[ index ] = vec[ elemsCount - 1 ];
            vec[ elemsCount - 1 ] = T();
        }

        elemsCount--;

        return res;
    }

    T removeOne( const T &elem, Order ord = Unordered )
    {
        int64_t i = indeOf( elem );
        uint64_t index = static_cast<uint64_t>( i );

        T res = T();

        if ( i != -1 )
        {
            res = vec[ index ];

            if ( ord  )
                shift( index, elemsCount );
            else
            {
                vec[ index ] = vec[ elemsCount - 1 ];
                vec[ elemsCount - 1 ] = T();
            }

            elemsCount--;
        }

        return res;
    }


    void sort()
    {
        int64_t i = 0, t1 = 0, t2 = 0, dim = 1;
        T *aux = new T[ elemsCount ];


        for(int64_t i = 0; i < static_cast<int64_t>(elemsCount); i++)
            aux[ i ] = vec[ i ];

        for ( ; dim < static_cast<int64_t>(elemsCount); dim = dim + dim )
        {
            for ( i = 0; i < static_cast<int64_t>(elemsCount) - dim; i = i + dim + dim )
            {
                t1 = i + dim + dim - 1;
                t2 = static_cast<int64_t>(elemsCount) - 1;

                merge( aux, i, i + dim - 1, t1 < t2 ? t1 : t2);
            }
        }

        delete [] aux;
    }


    T operator[]( int index )
    {
        return get( index );
    }

    T operator<<( const T &elem )
    {
       return append( elem );
    }

    void shift( uint64_t start, uint64_t stop, Shift s = Left )
    {
        if ( s == Left )
        {
            for ( ; start < stop; )
            {
                uint64_t i = start;
                vec[ i ] = vec[ ++start ];
            }
        }
        else if ( s == Right )
        {
            for ( ; stop > start; )
            {
                uint64_t i = stop;
                vec[ i ] = vec[ --stop ];
            }
        }

    }

    T* data()
    {
        return vec;
    }


private:
    uint64_t size;
    uint64_t elemsCount;
    double fillValue;
    T *vec = nullptr;

    void merge( T *aux, int64_t low, int64_t mid, int64_t high )
    {
        int64_t i = 0;
        int64_t j = 0;
        int64_t k = 0;

        for ( i = mid + 1; i > low; i-- )
            aux[ i - 1 ] = vec[ i - 1 ];

        for ( j = mid; j < high; j++ )
            aux[ high + mid - j ] = vec[ j + 1 ];

        for ( k = low; k <= high; k++ )
        {
            if ( aux[ j ] < aux[ i ] )
               vec[ k ] = aux[ j-- ];
           else
               vec[ k ] = aux[ i++ ];
        }
    }

    void updateFillValue()
    {
        if ( size == 0 )
        {
            fillValue = 100;
            return;
        }

        double _size   = static_cast<double>( size );
        double _elemsC = static_cast<double>( elemsCount );

        fillValue = ( 100 * _elemsC ) / _size;
    }


    uint64_t space()
    {
        double _size   = static_cast<double>( size );

        uint64_t new_size = static_cast<uint64_t>( ( _size * 25 ) / 100 );

        if ( new_size < 1 )
            return 1;
        else
            return new_size;
    }


    void realloc( uint64_t newSize = 0 )
    {
        uint64_t oldS = size;

        if ( newSize )
            size = newSize;
        else
            size = size + space();

        T *newVec = new T[ size ];

        for ( uint64_t i = 0; i < oldS; i++  )
            newVec[ i ] = vec[ i ];

        delete [] vec;

        vec = newVec;

        /*
        uint64_t oldsize = size;
        size = size + space();
        T *newVec = new T[ size ];
        copy( vec, vec + min( oldsize, size), newVec);
        delete [] vec;
        vec = newVec;
        */
    }

};


#endif // STRAYVECTOR_H
