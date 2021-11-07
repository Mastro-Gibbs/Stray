#ifndef STRAYMATRIX_H
#define STRAYMATRIX_H


#include <cstdint>
#include "strayvector.h"


template< typename T >
class StrayMatrix
{
public:
    StrayMatrix( uint_fast32_t row, uint_fast32_t col )
    {
        this->row = row;
        this->col = col;
        matrix = new StrayVector<T>( row * col );
    }

    ~StrayMatrix()
    {
        delete matrix;
    }


    void draw()
    {
        for ( uint32_t i = 0; i < row*col; i++ )
        {
            T item = matrix->get( i );
            cout << "|" << item;

            if ( ((i+1) % col) == 0 )
                cout << endl;
        }

    }


    uint_fast32_t rowCount()
    {
        return row;
    }

    uint_fast32_t colCount()
    {
        return col;
    }


    void addRows( uint_fast32_t qnt = 1 )
    {
        row += qnt;

        matrix->setPrefSize( row * col );
    }

    void addColumns( uint_fast32_t qnt = 1 )
    {

        col += qnt;

        matrix->setPrefSize( row * col );

        uint64_t base = col - qnt;

        for ( uint32_t i = 1; i < row; i++ )
        {
            T nv = matrix->get( ( col * row ) - 1 );

            for ( uint32_t j = 0; j < qnt; j++ )
            {
                matrix->shift( base, col*row-1, Shift::Right );
                matrix->set( nv, ( col - qnt) + j );
            }
            base += ( col - 1 );
        }
    }


    void put( const T &item, uint_fast32_t row, uint_fast32_t col )
    {
        if ( isValid( row, col ) )
        {
            uint_fast32_t index = cellId( row, col );
            matrix->set( item, index );
        }
    }


    T peek( uint_fast32_t row, uint_fast32_t col )
    {
        T item;
        if ( isValid( row, col ) )
        {
            uint_fast32_t index = cellId( row, col );
            item = matrix->get( index );
        }
        return item;
    }

    T pop( uint_fast32_t row, uint_fast32_t col )
    {
        T item;
        if ( isValid( row, col ) )
        {
            uint_fast32_t index = cellId( row, col );
            item = matrix->get( index );
            matrix->set( T(), index );
        }
        return item;
    }



    bool isValid( uint_fast32_t row, uint_fast32_t col )
    {
        bool valid = false;
        if ( row < this->row && col < this->col )
            valid = true;
        return valid;
    }

    uint64_t size()
    {
        return col * row;
    }


    void clone( StrayMatrix<T> &other )
    {
        for ( uint32_t i = 0; i < size(); i++ )
        {
            T item = matrix->get( i );
            other.matrix->set( item, i );
        }
    }

protected:
    StrayVector<T> *matrix = nullptr;
    uint_fast32_t row;
    uint_fast32_t col;

    uint_fast32_t cellId( uint_fast32_t row, uint_fast32_t col )
    {
        return  col + ( this->col * row );
    }

};


#endif // STRAYMATRIX_H
