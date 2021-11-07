#ifndef STRAYMAP_H
#define STRAYMAP_H

#include <iostream>
using namespace std;

#include "straylist.h"
#include "ustrayset.h"
#include "straytree.h"



template < typename K, typename V >
class StrayMap
{
private:
    class StrayMapNode
    {
    public:

        uint64_t itemSize()
        {
            return sizeof ( K ) + sizeof ( V );
        }


        StrayMapNode( )
        {
            this->key = K();
            this->value = V();
        }


        StrayMapNode( K key )
        {
            this->key = key;
            this->value = V();
        }


        StrayMapNode( K key, V value )
        {
            this->key = key;
            this->value = value;
        }

        ~StrayMapNode() {}


        bool operator==( const StrayMapNode &other )
        {
            return key == other.key;
        }

        bool operator<( const StrayMapNode &other )
        {
            return key < other.key;
        }

        bool operator>( const StrayMapNode &other )
        {
            return key > other.key;
        }


        K key;
        V value;
    };

public:
    StrayMap()
    {}

    ~StrayMap()
    {}


    void erase()
    {
        map.clear();
        itemCount = 0;
    }


    int count()
    {
        return itemCount;
    }


    bool isEmpty()
    {
        return ( itemCount == 0 );
    }


    bool containsKey( K key )
    {
        bool res = false;
        StrayMapNode node( key );
        res = map.find( node );
        return res;
    }


    V value( K key )
    {
        StrayMapNode node( key );
        node = map.peek( node );
        return node.value;
    }


    void put( K key, V value )
    {
        StrayMapNode node( key, value );

        if ( !containsKey( key ) )
        {
            map.insert( node );
            itemCount++;
        }
        else
        {
            map.purge( node );
            map.insert( node );
        }
    }


    void purge( K key )
    {
        StrayMapNode node( key );
        map.purge( node );
        itemCount--;
    }



    StrayVector<K> keys()
    {
        StrayVector<K> k;

        if ( isEmpty() ) return k;

        StrayVector<StrayMapNode> *vec = map.visit( VisitMode::BreadthOrder );

        for ( uint64_t i = 0; i < vec->count(); i++ )
        {
            StrayMapNode curr = vec->get( i );
            k.append( curr.key );
        }
        return k;
    }

    StrayVector<V> values()
    {
        StrayVector<V> v;

        if ( isEmpty() ) return v;

        StrayVector<StrayMapNode> *vec = map.visit( VisitMode::BreadthOrder );

        for ( uint64_t i = 0; i < vec->count(); i++ )
        {
            StrayMapNode curr = vec->get( i );
            v.append( curr.value );
        }
        return v;
    }

private:
    StrayBST<StrayMapNode> map;

    uint64_t itemCount = 0;
};






#endif // STRAYMAP_H
