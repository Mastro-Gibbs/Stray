#ifndef STRAYLIST_H
#define STRAYLIST_H

#include <ostream>
#include "strayiterator.h"
#include "straynode.h"

using namespace std;


template< typename T >
class StrayList
{
public:
    /**
     * @brief StrayList empty constructor
     */
    StrayList()
    {}


    /**
     * @brief StrayList other
     * @param other -> StrayList
     */
    StrayList( const StrayList &other )
    {
        StrayIterator<T> it( other.head, other.tail, other.vsize );
        it.begin();

        while( it.hasNext() )
            append( it.next() );
    }


    /**
     * @brief Destructor
     */
    ~StrayList()
    {
        clear();
    }

    /**
     * @brief clean this
     */
    void clear()
    {
        StrayIterator<T> *it = iterate();
        it->begin();

        StrayNode<T> *curr;
        while ( it->hasNext() )
        {
            curr = it->get();
            it->next();
            delete curr;
        }

        curr = nullptr;
        head = nullptr;
        tail = nullptr;
        size = 0;

        delete it;
    }


    /**
     * @brief return unsigned long, memory allocated by this
     * @return
     */
    uint64_t memSize()
    {
        uint64_t listSize = 0;

        StrayIterator<T> *it = iterate();
        it->begin();

        while( it->hasNext() )
        {
            StrayNode<T>* curr = it->get();
            listSize += curr->mem_size();
            it->next();
        }

        delete it;

        return listSize;
    }


    /**
     * @brief First index of elem
     * @param elem -> T
     * @return int
     */
    int indexOf( const T &elem )
    {
        int res = - 1;
        StrayIterator<T> *it = iterate();
        it->begin();

        int i = 0;
        while( it->hasNext() )
        {
            if ( it->peek() == elem )
            {
                res = i;
                break;
            }
            it->next();
            i++;
        }

        delete it;
        return res;
    }


    /**
     * @brief Last index of elem
     * @param elem -> T
     * @return int
     */
    int lastIndexOf( const T &elem )
    {
        int res = -1;

        StrayIterator<T> *it = iterate();
        it->end();

        int i = count() - 1;
        while( it->hasPrev() )
        {
            if ( it->peek() == elem )
            {
                res = i;
                break;
            }
            it->prev();
            i--;
        }

        delete it;

        return res;
    }


    /**
     * @brief Return elems count
     * @return int
     */
    int count()
    {
        return size;
    }


    /**
     * @brief True is size == 0 otherwise false
     * @return boolean
     */
    bool isEmpty()
    {
        if( size == 0 ) return true;
        else return false;
    }


    /**
     * @brief Check if this contains elem
     * @param elem -> T
     * @return bool
     */
    bool contains( const T &elem )
    {
        bool res = false;

        StrayIterator<T> *it = iterate();
        it->begin();

        while( it->hasNext() )
        {
            if ( it->peek() == elem )
            {
                res = true;
                break;
            }
            it->next();
        }

        delete it;

        return res;
    }


    /**
     * @brief Prepend elem on head
     * @param elem -> T
     */
    void prepend( const T &elem )
    {
        StrayNode<T> *curr = new StrayNode<T>( elem );

        if ( !head )
        {
            head = curr;
            tail = head;
        }
        else
        {
            head->link( curr );
            curr->link( nullptr, head );
            head = curr;
        }
        size++;
    }


    /**
     * @brief Prepend list on head
     * @param list -> StrayList
     */
    void prepend( StrayList<T> *list )
    {
        StrayIterator<T> *it = list->iterate();
        it->end();

        int i = list->count();
        while( it->hasPrev()  && i )
        {
            prepend( it->peek() );
            it->prev();
            i--;
        }

        delete it;
    }


    /**
     * @brief Append elem on tail
     * @param elem -> T
     */
    void append( const T &elem )
    {
        StrayNode<T> *curr = new StrayNode<T>( elem );

        switch ( size )
        {
            case 0:
                head = curr;
                tail = head;
                break;
            case 1:
                tail = curr;
                tail->link( head );
                head->link( nullptr, tail );
                break;
            default:
                curr->link( tail );
                tail->link( nullptr, curr );
                tail = curr;
                break;
        }
        size++;
    }

    /**
     * @brief Append list on tail
     * @param list -> StrayList
     */
    void append( StrayList<T> *list )
    {
        StrayIterator<T> *it = list->iterate();
        it->begin();

        int i = list->count();
        while( it->hasNext() && i )
        {
            append( it->peek() );
            it->next();
            i--;
        }

        delete it;
    }


    /**
     * @brief Insert elem on specific index
     * @param elem -> T
     * @param index -> int
     */
    void insert( const T &elem, int index )
    {
        if ( index > size ) return;

        if ( index == 0 ) prepend( elem );
        else if ( index == size ) append( elem );
        else
        {
            StrayNode<T> *newNode = new StrayNode<T>( elem );


            StrayIterator<T> *it = iterate();
            it->begin();

            int i = index + 1;
            while( it->hasNext() && i )
            {
                i--;
                if ( !i )
                {
                    StrayNode<T> *next = it->get();
                    it->prev();
                    StrayNode<T> *prev = it->get();

                    newNode->link( prev, next );
                    prev->link( nullptr, newNode );
                    next->link( newNode );
                }
                it->next();
            }
            delete it;
        }
        size++;
    }

    /**
     * @brief Remove first elem
     * @return elem removed
     */
    T removeFirst()
    {
        T item = T();

        if ( size == 1 )
        {
            item = head->data();
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            StrayIterator<T> *it = iterate();
            it->begin();

            if ( it->isValid() )
            {
                StrayNode<T> *tmp = it->get();
                item = it->peek();
                it->next();
                if ( it->isValid() )
                {
                    StrayNode<T> *next = it->get();
                    next->unlink_left();
                    head = next;
                }
                delete tmp;
            }
            delete it;
        }
        size--;

        return item;
    }

    /**
     * @brief Remove last elem
     * @return return elem removed
     */
    T removeLast()
    {
        T item = T();

        if ( size == 1 )
        {
            item = head->data();
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            StrayIterator<T> *it = iterate();
            it->end();

            if ( it->isValid() )
            {
                StrayNode<T> *tmp = it->get();
                item = it->peek();
                it->prev();
                if ( it->isValid() )
                {
                    StrayNode<T> *next = it->get();
                    next->unlink_right();
                    tail = next;
                }
                delete tmp;
            }
            delete it;
        }
        size--;

        return item;
    }


    /**
     * @brief Remode first occurence of elem
     * @param elem ->
     */
    void remove( const T &elem )
    {
        if ( size == 1 || head->data() == elem )
        {
            if ( head->data() == elem )
                removeFirst();
        }
        else
        {
            StrayIterator<T> it( head, tail, vsize );
            it.begin();

            while( it.hasNext() )
            {
                if( it.peek() == elem )
                {
                    StrayNode<T> *tmp = it.get();
                    it.next();

                    StrayNode<T> *next = it.get();
                    it.prev();
                    it.prev();

                    StrayNode<T> *prev = it.get();

                    prev->link( nullptr, next );
                    next->link( prev );

                    delete tmp;
                    tmp = nullptr;
                    size--;

                    break;
                }
                it.next();
            }
        }
    }


    /**
     * @brief Compare this to other list
     * @param other -> StrayList
     * @return bool
     */
    bool compare( const StrayList &other )
    {
        StrayList<T> &param = const_cast<StrayList<T> &>( other );

        bool res = false;
        if ( size != other.size ) return res;

        StrayList<T> copy( *this );
        copy.sort();
        param.sort();

        StrayIterator<T> it1( head, tail, vsize );
        StrayIterator<T> it2( param.head, param.tail, param.vsize );

        it1.begin();
        it2.begin();

        res = true;
        while ( it1.hasNext() )
        {
            if ( it1.next() != it2.next() )
            {
                res = false;
                break;
            }
        }

        return res;
    }

    /**
     * @brief retrurn StrayIterator pointer to this
     * @return StrayIterator ptr
     */
    StrayIterator<T>* iterate()
    {
        return new StrayIterator<T>( head, tail, vsize );
    }

    /**
     * @brief retrurn StrayIterator to this
     * @return StrayIterator
     */
    StrayIterator<T> static_iterate()
    {
        return StrayIterator<T>( head, tail, vsize );
    }


    /**
     * @brief Sort list, based on merge sort
     */
    void sort()
    {
        int i = 0, t1 = 0, t2 = 0, dim = 1;
        T *arr = new T[ size ];
        T *aux = new T[ size ];

        toArray( arr );

        for(int i=0; i < size; i++)
            aux[ i ] = arr[ i ];

        for ( ; dim < size; dim = dim + dim )
        {
            for ( i = 0; i < size - dim; i = i + dim + dim )
            {
                t1 = i + dim + dim - 1;
                t2 = size - 1;

                merge( arr, aux, i, i + dim - 1, t1 < t2 ? t1 : t2);
            }
        }

        StrayIterator<T> *it = iterate();
        it->begin();

        int index = 0;
        while ( it->hasNext() && index < size )
        {
            it->set( arr[ index++ ] );
            it->next();
        }
        delete it;

        delete [] aux;
        delete [] arr;
    }


    /**
     * @brief Return list converted to array
     * @param array -> T[]
     */
    void toArray( T *array )
    {
        StrayIterator<T> *it = iterate();
        it->begin();

        int i = 0;
        while( it->hasNext() )
        {
            array[ i++ ] = it->next();
        }

        delete it;
    }


    StrayList& operator = ( const StrayList &l )
    {
        clear();

        StrayIterator<T> it ( l.head, l.tail, l.vsize );
        it.begin();

        while( it.hasNext() )
        {
            append( it.next() );
        }

        size = l.size;

        return *this;
    }


    StrayList operator + ( const StrayList &l )
    {
        StrayList<T> res;

        StrayIterator<T> it_this ( head, tail, vsize );
        it_this.begin();
        while( it_this.hasNext() )
        {
            res.append( it_this.next() );
        }

        StrayIterator<T> it ( l.head, l.tail, l.vsize );
        it.begin();
        while( it.hasNext() )
        {
            res.append( it.next() );
        }

        return res;
    }


    friend ostream &operator<<( ostream& os, const StrayList<T>& l )
    {
        os << '[';
        StrayIterator<T> it( l.head, l.tail, l.vsize );
        it.begin();

        while( it.hasNext() )
        {
            if ( it.get() == l.tail ) break;
            os << it.next() << ", ";
        }
        os << it.next();
        os << ']';

        return os;
    }


    friend ostream &operator<<( ostream& os, const StrayList<T>* l )
    {
        os << '[';
        StrayIterator<T> it( l->head, l->tail, l->vsize );
        it.begin();

        while( it.hasNext() )
        {
            if ( it.get() == l->tail ) break;
            os << it.next() << ", ";
        }
        os << it.next();
        os << ']';

        return os;
    }


private:
    int size = 0;
    int *vsize = &size;
    StrayNode<T> *head = nullptr;
    StrayNode<T> *tail = nullptr;

    void merge( T *array, T *aux, int low, int mid, int high )
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


#endif // STRAYLIST_H
