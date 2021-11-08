#ifndef STRAYMAP_H
#define STRAYMAP_H

#include <iostream>
using namespace std;

#include "strayrecord.h"
#include "straylist.h"
#include "ustrayset.h"
#include "straytree.h"



template < typename K, typename V >
class StrayMap
{
private:
    class StrayMapNode : public StrayRecord<K, V>
    {
    public:

        uint64_t itemSize()
        {
            return sizeof ( K ) + sizeof ( V );
        }


        StrayMapNode( ) : StrayRecord<K, V> ( )
        {}


        StrayMapNode( K key ) : StrayRecord<K, V> ( key, Item::First )
        {}


        StrayMapNode( K key, V value ) : StrayRecord<K, V> ( key, value )
        {}

        ~StrayMapNode() {}

        bool operator==( const StrayMapNode &other )
        {
            return this->compare( other, Cmp::EQ, Item::First );
        }

        bool operator<( const StrayMapNode &other )
        {
            return this->compare( other, Cmp::LT, Item::First );
        }

        bool operator>( const StrayMapNode &other )
        {
            return this->compare( other, Cmp::GT, Item::First );
        }

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
        return node.second();
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
            StrayMapNode nodeOld( key );
            map.update( nodeOld, node );
        }
    }


    void purge( K key )
    {
        StrayMapNode node( key );
        map.purge( node );
        itemCount--;
    }


    UStraySet<StrayRecord<K, V>> couples()
    {
        UStraySet<StrayRecord<K, V>> kv;
        StrayVector<StrayMapNode> *vec = map.visit( VisitMode::BreadthOrder );

        StrayRecord<K, V> curr;
        for ( uint64_t i = 0; i < vec->count(); i++ )
        {
            curr = vec->get( i );
            kv.append( curr );
        }
        return kv;
    }


    StrayVector<K> keys()
    {
        StrayVector<K> k;

        if ( isEmpty() ) return k;

        StrayVector<StrayMapNode> *vec = map.visit( VisitMode::BreadthOrder );

        for ( uint64_t i = 0; i < vec->count(); i++ )
        {
            StrayMapNode curr = vec->get( i );
            k.append( curr.first() );
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
            v.append( curr.second() );
        }
        return v;
    }

private:
    StrayBST<StrayMapNode> map;

    uint64_t itemCount = 0;
};






#endif // STRAYMAP_H
