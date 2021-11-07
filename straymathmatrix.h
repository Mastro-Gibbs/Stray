#ifndef STRAYMATHMATRIX_H
#define STRAYMATHMATRIX_H



#include "straymatrix.h"

template< typename T >
class StrayMathMatrix : public StrayMatrix<T>
{
public:
    StrayMathMatrix( uint_fast32_t row, uint_fast32_t col ) : StrayMatrix<T> ( row, col )
    {}

    ~StrayMathMatrix()
    {}


    void fill( const StrayVector<T> &data )
    {
        uint_fast32_t roof;

        if ( data.count() < this->size() )
            roof = data.count();
        else
            roof = this->size();


        for ( uint64_t i = 0; i < roof; i++ )
        {
            this->matrix->set( data.get( i ), i );
        }
    }


    StrayMathMatrix<T> sum( const StrayMathMatrix<T> &b )
    {
        StrayMathMatrix<T> res( this->row, this->col );
        for( uint64_t i = 0; i < this->col * this->row; i++ )
        {
            T item = this->matrix->get( i ) + b.matrix->get( i );
            res.matrix->set( item, i );
        }
        return res;
    }


    StrayMathMatrix<T> subtract( const StrayMathMatrix<T> &b )
    {
        StrayMathMatrix<T> res( this->row, this->col );
        for( uint64_t i = 0; i < this->col * this->row; i++ )
        {
            T item = this->matrix->get( i ) - b.matrix->get( i );
            res.matrix->set( item, i );
        }
        return res;
    }


    StrayMathMatrix<T> multiply( const StrayMathMatrix<T> &b )
    {
        StrayMathMatrix<T> res( this->row, this->col );
        for( uint64_t i = 0; i < this->col * this->row; i++ )
        {
            T item = this->matrix->get( i ) * b.matrix->get( i );
            res.matrix->set( item, i );
        }
        return res;
    }


    T determinant()
    {
        T det = T();
        if ( this->row != this->col )
            return det;

        if ( this->size() == 4 )
            det = matrix_2x2();
        else if ( this->size() == 9 )
            det = sarrus();

        return det;
    }


    bool isIdentity()
    {
        bool res = true;

        if ( this->row != this->col ) return false;

        for( uint64_t i = 0, j = 0; j < this->col * this->row; j++ )
        {
            T item = this->matrix->get( j );

            if ( i == j )
            {
                if ( item != 1 )
                res = false;
                i = i + this->row + 1;
            }
            else
            {
                if ( item != 0 )
                res = false;
            }

        }
        return res;
    }


private:

    T matrix_2x2 ()
    {
        T a = this->matrix->get( 0 );
        T b = this->matrix->get( 1 );
        T c = this->matrix->get( 2 );
        T d = this->matrix->get( 3 );
        return ( ( a * d ) - ( b * c ) );
    }

    T sarrus()
    {
        StrayMathMatrix<T> aux ( 3, 3 );
        this->clone( aux );

        aux.addColumns( 2 );

        T a = aux.matrix->get( 0 );
        T b = aux.matrix->get( 1 );
        T c = aux.matrix->get( 5 );
        T d = aux.matrix->get( 6 );
        T e = aux.matrix->get( 10 );
        T f = aux.matrix->get( 11 );

        aux.matrix->set( a, 3 );
        aux.matrix->set( b, 4 );
        aux.matrix->set( c, 8 );
        aux.matrix->set( d, 9 );
        aux.matrix->set( e, 13 );
        aux.matrix->set( f, 14 );

        T posFirstG  = aux.matrix->get( 0 );
        T posSecondG = aux.matrix->get( 1 );
        T posThirdG  = aux.matrix->get( 2 );
        T negFirstG  = aux.matrix->get( 2 );
        T negSecondG = aux.matrix->get( 3 );
        T negThirdG  = aux.matrix->get( 4 );

        for ( uint32_t i = 0; i < aux.size(); i++ )
        {
            if ( i == 6 || i == 12 )
            {
                posFirstG *= aux.matrix->get( i );
            }
            if ( i == 7 || i == 13 )
            {
                posSecondG *= aux.matrix->get( i );
            }
            if ( i == 8 || i == 14 )
            {
                posThirdG *= aux.matrix->get( i );
            }
            if ( i == 6 || i == 10 )
            {
                negFirstG *= aux.matrix->get( i );
            }
            if ( i == 7 || i == 11 )
            {
                negSecondG *= aux.matrix->get( i );
            }
            if ( i == 8 || i == 12 )
            {
                negThirdG *= aux.matrix->get( i );
            }
        }

        return ( ( posFirstG + posSecondG + posThirdG ) - ( negFirstG + negSecondG + negThirdG ) );
    }

};



#endif // STRAYMATHMATRIX_H
