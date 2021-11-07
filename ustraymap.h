#ifndef USTRAYMAP_H
#define USTRAYMAP_H

#include <iostream>
using namespace std;

#include "straylist.h"
#include "ustrayset.h"


template < typename K, typename V > class StrayMapIterator;


template < typename K, typename V >
class UStrayMap
{
friend class StrayMapIterator<K, V>;
private:
    class UStrayMapNode
    {
    public:

        uint64_t itemSize()
        {
            return sizeof ( K ) + sizeof ( V );
        }

        UStrayMapNode( K key, V value )
        {
            this->key = key;
            this->value = value;
        }

        ~UStrayMapNode() {}


        K key;
        V value;

        UStrayMapNode *prev;
        UStrayMapNode *next;
    };

public:
    UStrayMap() {}

    ~UStrayMap()
    {
        clear();
    }


    void clear()
    {
        UStrayMapNode *curr = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            head = head->next;
            delete curr;
            curr = head;
        }
    }


    int count()
    {
        return itemCount;
    }


    bool isEmpty()
    {
        return itemCount;
    }


    V peek( K key )
    {
        V res;

        UStrayMapNode *node = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            if ( node->key == key )
            {
                res = node->value;
                break;
            }
            node = node->next;
        }

        return res;
    }


    void purge( const K &key )
    {
        UStrayMapNode *node = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            if ( node->key == key )
            {
                UStrayMapNode *prev = node->prev;
                UStrayMapNode *next = node->next;
                delete node;

                if ( i == 0 )
                    head = next;

                if ( i == itemCount - 1 )
                    tail = prev;

                if ( prev )
                    prev->next = next;

                if ( next )
                    next->prev = prev;

                itemCount--;
                break;
            }
            node = node->next;
        }
    }


    bool containsKey( K key )
    {
        bool res = false;

        UStrayMapNode *node = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            if ( node->key == key )
            {
                res = true;
                break;
            }
            node = node->next;
        }

        return res;
    }


    bool containsValue( V value )
    {
        bool res = false;

        UStrayMapNode *node = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            if ( node->value == value )
            {
                res = true;
                break;
            }
            node = node->next;
        }

        return res;
    }


    void put( K key, V value )
    {
        bool finded = false;

        UStrayMapNode *node = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            if ( node->key == key )
            {
                finded = true;
                node->value = value;
                break;
            }
            node = node->next;
        }
        if ( !finded )
        {
            UStrayMapNode *newNode = new UStrayMapNode( key, value );

            switch ( itemCount )
            {
                case 0:
                    head = newNode;
                    tail = head;
                    break;
                case 1:
                    tail = newNode;
                    head->next = tail;
                    tail->prev = head;
                    break;
                default:
                    tail->next = newNode;
                    newNode->prev = tail;
                    tail = newNode;
                    break;
            }
            itemCount++;
        }
    }


    void merge( UStrayMap *other )
    {
        UStrayMapNode *curr = other->head;
        for ( uint64_t i = 0; i < other->itemCount; i++ )
        {
            put( curr->key, curr->value );
            curr = curr->next;
        }
    }


    UStraySet<K> keys()
    {
        UStraySet<K> keys;

        UStrayMapNode *curr = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            keys.append( curr->key );
            curr = curr->next;
        }
        return keys;
    }

    StrayList<V> values()
    {
        StrayList<V> values;

        UStrayMapNode *curr = head;
        for ( uint64_t i = 0; i < itemCount; i++ )
        {
            values.append( curr->value );
            curr = curr->next;
        }
        return values;
    }

    StrayMapIterator<K, V> *iterate()
    {
        return new StrayMapIterator<K, V>( head, tail, size );
    }

private:
    UStrayMapNode *head = nullptr;
    UStrayMapNode *tail = nullptr;

    uint64_t itemCount = 0;
    uint64_t *size = &itemCount;
};


template< typename K, typename V >
class StrayMapIterator
{
public:

    friend class UStrayMap<K, V>;

    void begin()
    {
        curr = head;
    }

    void end()
    {
        curr = tail;
    }

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

    void next()
    {
        curr = curr->next;
    }

    void prev()
    {
        curr = curr->prev;
    }

    K key()
    {
        return curr->key;
    }

    V value()
    {
        return curr->value;
    }

    void set( const V &val )
    {
        curr->value = val;
    }

private:
    StrayMapIterator( typename UStrayMap<K, V>::UStrayMapNode *start, typename UStrayMap<K, V>::UStrayMapNode *end, uint64_t *size )
    {
        head = start;
        tail = end;
        this->size = size;
    }

    typename UStrayMap<K, V>::UStrayMapNode *head = nullptr;
    typename UStrayMap<K, V>::UStrayMapNode *tail = nullptr;
    typename UStrayMap<K, V>::UStrayMapNode *curr = nullptr;
    uint64_t *size = nullptr;
};



#endif // USTRAYMAP_H
