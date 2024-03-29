#ifndef USTRAYSET_H
#define USTRAYSET_H

#include <iostream>

using namespace std;


template< typename T > class StraySetIterator;


template< typename T >
class UStraySet
{
friend class StraySetIterator<T>;
private:
    class StrayListNode
    {
    public:

        uint64_t itemSize()
        {
            return sizeof( T );
        }


        StrayListNode( const T &item )
        {
            this->item = item;
        }

        ~StrayListNode() {}

        T item;
        StrayListNode *prevoius = nullptr;
        StrayListNode *next     = nullptr;
    };

public:
    UStraySet() {}

    ~UStraySet()
    {
        if ( !size )
            clear();
    }

    void clear()
    {
        StrayListNode *iter = head;
        StrayListNode *tmp  = nullptr;

        while ( iter )
        {
            tmp = iter;
            iter = iter->next;
            delete tmp;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    uint64_t memSize()
    {
        uint64_t listSize = 0;

        StrayListNode *curr = head;
        for ( int i = 0; i < size; i++ )
        {
            listSize += curr->itemSize();
            curr = curr->next;
        }
        listSize += sizeof ( this );
        return listSize;
    }

    int indexOf( const T &elem )
    {
        int res = - 1;
        StrayListNode*find = new StrayListNode( elem );
        StrayListNode *curr = head;
        for ( int i = 0; i < size; i++ )
        {
            if ( curr->item == find->item )
            {
                res = i;
                break;
            }
            curr = curr->next;
        }
        return res;
    }

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
        bool res = false;
        StrayListNode *find = new StrayListNode( elem );
        StrayListNode*curr = head;
        for ( int i = 0; i < size; i++ )
        {
            if ( curr->item == find->item )
            {
                res = true;
                break;
            }
            curr = curr->next;
        }
        return res;
    }

    void prepend( const T &elem )
    {
        if ( !contains( elem ) )
        {
            StrayListNode *curr = new StrayListNode( elem );
            head->prevoius = curr;
            curr->next = head;
            head = curr;
            size++;
        }
    }

    void prepend( UStraySet<T> *list )
    {
        StrayListNode *curr = list->tail;
        for ( int i = list->size; i > 0; i-- )
        {
            if ( !contains( curr->item ) )
                prepend( curr->item );
            curr = curr->prevoius;
        }
    }

    void append( const T &elem )
    {
        StrayListNode *curr = new StrayListNode( elem );

        if ( !contains( elem ) )
        {
            switch ( size )
            {
                case 0:
                    head = curr;
                    tail = head;
                    break;
                case 1:
                    tail = curr;
                    head->next = tail;
                    tail->prevoius = head;
                    break;
                default:
                    curr->prevoius = tail;
                    tail->next = curr;
                    tail = curr;
                    break;
            }
            size++;
        }
        else
            delete curr;
    }

    void append( UStraySet<T> *list )
    {
        StrayListNode *curr = list->head;
        for ( int i = 0; i < list->size; i++ )
        {
            if ( !contains( curr->item ) )
                append( curr->item );
            curr = curr->next;
        }
    }

    void insert( const T &elem, int index )
    {
        if ( index > size ) return;
        if ( !contains( elem ) )
        {
            if ( index == 0 ) prepend( elem );
            else if ( index == size ) append( elem );
            else
            {
                StrayListNode *newNode = new StrayListNode( elem );
                StrayListNode *nextNode = head->next;
                StrayListNode *prevNode = head;

                for ( int i = 1; i < index; i++ )
                {
                    prevNode = nextNode;
                    nextNode = nextNode->next;
                }

                prevNode->next = newNode;
                newNode->prevoius = prevNode;
                newNode->next  = nextNode;
                nextNode->prevoius = newNode;
            }
            size++;
        }
    }

    T removeFirst()
    {
        T item = head->item;
        head = head->next;
        head->prevoius = nullptr;
        size--;
        return item;
    }

    T removeLast()
    {
        T item = tail->item;
        tail = tail->prevoius;
        tail->next = nullptr;
        size--;
        return item;
    }

    bool compare( const UStraySet &other )
    {
        UStraySet<T> &param = const_cast<UStraySet<T> &>( other );

        bool res = false;
        if ( size != other.size ) return res;

        UStraySet<T> copy( *this );
        copy.sort();
        param.sort();

        StraySetIterator<T> it1( head, tail, vsize );
        StraySetIterator<T> it2( param.head, param.tail, param.vsize );

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

    StraySetIterator<T>* iterate()
    {
        return new StraySetIterator<T>( head, tail, vsize );
    }

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

        StrayListNode *curr = head;
        for ( int i = 0; i < size; i++ )
        {
            curr->item = arr[ i ];
            curr = curr->next;
        }

        delete [] aux;
        delete [] arr;
    }

    void operator<<( const T &elem )
    {
        append( elem );
    }

    void operator<<( UStraySet<T> *list )
    {
        append( list );
    }

    void toArray( T *array )
    {
        StrayListNode *curr = head;
        array[ 0 ] = head->item;
        int i = 1;
        for ( ; i < size; i++ )
        {
            curr = curr->next;
            array[ i ] = curr->item;
        }
    }

private:
    int size = 0;
    int *vsize = &size;
    StrayListNode *head = nullptr;
    StrayListNode *tail = nullptr;

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



template< typename T >
class StraySetIterator
{
friend class UStraySet<T>;
public:
    void startFrom( const T &item )
    {
        begin();
        while ( hasNext() )
        {
            if ( next() == item )
            {
                curr = curr->prevoius;
                break;
            }
        }
    }

    void startFromLast( const T &item )
    {
        end();
        while ( hasPrev() )
        {
            if ( prev() == item )
            {
                curr = curr->next;
                break;
            }
        }
    }

    void begin() { curr = startNode; }

    void end() { curr = endNode; }

    bool hasNext()
    {
        if ( curr != nullptr ) return true;
        else return false;
    }

    bool hasPrev()
    {
        if ( curr != nullptr ) return true;
        else return false;
    }

    T next()
    {
        T item = curr->item;
        curr = curr->next;
        return item;
    }

    T prev()
    {
        T item = curr->item;
        curr = curr->prevoius;
        return item;
    }

    T peek() { return curr->item; }

    void set( const T &elem ) { curr->item = elem; }

    bool compare( const T &elem )
    {
        if ( curr->item == elem ) return true;
        else return false;
    }

    T remove()
    {
        typename UStraySet<T>::StrayListNode *nextNode = curr->next;
        typename UStraySet<T>::StrayListNode *prevNode = curr->prevoius;

        if ( curr != startNode && curr != endNode )
        {
            nextNode->prevoius = prevNode;
            prevNode->next     = nextNode;
        }
        else if ( curr == startNode )
        {
            startNode = nextNode;
            startNode->prevoius = nullptr;
        }
        else
        {
            endNode = prevNode;
            endNode->next = nullptr;
        }
        *vsize = *vsize - 1;
        return curr->item;
    }

private:
    StraySetIterator( typename UStraySet<T>::StrayListNode *head, typename UStraySet<T>::StrayListNode *tail, int *size )
    {
        startNode = head;
        endNode = tail;
        vsize = size;
    };

    int *vsize         = nullptr;
    typename UStraySet<T>::StrayListNode *curr      = nullptr;
    typename UStraySet<T>::StrayListNode *startNode = nullptr;
    typename UStraySet<T>::StrayListNode *endNode   = nullptr;
};

#endif // USTRAYSET_H
