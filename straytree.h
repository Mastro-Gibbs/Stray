#ifndef STRAYTREE_H
#define STRAYTREE_H

#include <cstdint>
#include "straysort.h"
#include <iostream>
#include "strayvector.h"



enum VisitMode
{
    PreOrder = 0,
    //PostOrder = 1,
    //DepthOrder = 2,
    BreadthOrder = 3,
    ChildOrder = 4
};


template< typename T > class StrayTreeIterator;


template< typename T >
class StrayBST
{
friend class StrayTreeIterator<T>;
private:
    class StrayTreeNode
    {
    public:

        uint64_t itemSize()
        {
            return sizeof( T );
        }


        StrayTreeNode( const T &item )
        {
            this->item = item;
        }

        ~StrayTreeNode() {}

        T item;
        StrayTreeNode *previous   = nullptr;
        StrayTreeNode *leftChild  = nullptr;
        StrayTreeNode *rightChild = nullptr;
    };


public:
    StrayBST()
    {
        root = nullptr;
        size = 0;
    }

    ~StrayBST()
    {
        clear();
    }

    void clear()
    {
        StrayVector<StrayTreeNode*> *nodes = new StrayVector<StrayTreeNode*>( size );
        toVec( nodes, root );

        for ( uint64_t index = 0; index < size; index++ )
        {
            StrayTreeNode* curr = nodes->get( index );
            delete curr;
        }
        delete nodes;
        root = nullptr;
        size = 0;
    }

    void insert( const T &item )
    {
        StrayTreeNode *curr;

        if ( !root )
            root = new StrayTreeNode( item );
        else
        {
            curr = new StrayTreeNode( item );

            append( curr );

        }
        size++;
        balance();
    }

    void purge( const T &elem )
    {
        StrayVector<T> *nodes = new StrayVector<T>( size );
        breadthOrder( nodes, root );

        nodes->removeOne( elem, Order::Preserve );

        root = sortedArrayToBST( nodes->data(), 0, size - 2 );
        size--;
    }

    bool find( const T &elem )
    {
        uint16_t *find = static_cast<uint16_t*>( malloc( sizeof ( uint16_t* ) ));
        *find = 0;

        StrayTreeIterator<T> *it = new StrayTreeIterator<T>( root );

        it->begin();

        if ( it->isValid() )
            locate( it, elem, find );

        delete it;

        return *find;
    }

    void update( const T &old, const T &elem )
    {
        StrayTreeIterator<T> *it = new StrayTreeIterator<T>( root );

        it->begin();

        if ( it->isValid() )
            set( it, old, elem );

        delete it;
    }

    T peek( T &elem )
    {
        StrayTreeIterator<T> *it = new StrayTreeIterator<T>( root );

        it->begin();

        if ( it->isValid() )
            get( it, elem, &elem );

        delete it;

        return elem;
    }

    void balance()
    {
        StrayVector<T> *v = new StrayVector<T>( size );
        transform( v, root );

        v->sort();

        root = sortedArrayToBST( v->data(), 0 , size - 1 );
        delete v;
    }


    T* toArray( )
    {
        StrayVector<T> *v = new StrayVector<T>( size );
        transform( v, root );
        T *arr = v->data();

        delete v;
        return arr;
    }



    StrayVector<T>* visit( VisitMode ord )
    {
        StrayVector<T> *nodes = new StrayVector<T>( size );
        if ( ord == PreOrder )
            preOrder( nodes, root );
        /*
        else if ( ord == PostOrder )
            postOrder( nodes, root );
        else if ( ord == DepthOrder )
            depthOrder( nodes, root );
        */
        else if ( ord == BreadthOrder )
            breadthOrder( nodes, root );
        else if ( ord == ChildOrder )
            childOrder( nodes, root );

        return nodes;
    }


    StrayTreeIterator<T>* iterate()
    {
        return new StrayTreeIterator<T>( root );
    }

    uint64_t count()
    {
        return size;
    }


private:
    StrayTreeNode *root;
    uint64_t size;

    void append( StrayTreeNode *curr )
    {
        StrayTreeIterator<T> *it = new StrayTreeIterator<T>( root );

        it->begin();

        if ( it->isValid() )
            appendInDepth( it, curr );

        delete it;
    }

    void appendInDepth( StrayTreeIterator<T> *it, StrayTreeNode *curr )
    {
        if ( it->examinate() > curr->item )
        {
            if ( it->hasLeft() )
            {
                it->moveLeft();
                appendInDepth( it, curr );
            }
            else
                it->setLeft( curr );
        }
        else if ( it->examinate() < curr->item )
        {
            if ( it->hasRight() )
            {
                it->moveRight();
                appendInDepth( it, curr );
            }
            else
                it->setRight( curr );
        }
    }


    void locate( StrayTreeIterator<T> *it, const T &elem, uint16_t *find )
    {
        if ( it->examinate() > elem )
        {
            if ( it->hasLeft() )
            {
                it->moveLeft();
                locate( it, elem, find );
            }
        }
        else if ( it->examinate() < elem )
        {
            if ( it->hasRight() )
            {
                it->moveRight();
                locate( it, elem, find );
            }
        }
        else if ( it->examinate() == elem )
        {
            *find = 1;
            return;
        }
    }


    void get( StrayTreeIterator<T> *it, const T &elem, T *item )
    {
        if ( it->examinate() > elem )
        {
            if ( it->hasLeft() )
            {
                it->moveLeft();
                get( it, elem, item );
            }
        }
        else if ( it->examinate() < elem )
        {
            if ( it->hasRight() )
            {
                it->moveRight();
                get( it, elem, item );
            }
        }
        else if ( it->examinate() == elem )
        {
            *item = it->examinate();
            return;
        }
    }


    void set( StrayTreeIterator<T> *it, const T &elem, const T &item )
    {
        if ( it->examinate() > elem )
        {
            if ( it->hasLeft() )
            {
                it->moveLeft();
                set( it, elem, item );
            }
        }
        else if ( it->examinate() < elem )
        {
            if ( it->hasRight() )
            {
                it->moveRight();
                set( it, elem, item );
            }
        }
        else if ( it->examinate() == elem )
        {
            it->set( new StrayTreeNode( item ) );
        }
    }


    StrayTreeNode* sortedArrayToBST( T arr[], int start, int end, StrayTreeNode *node = nullptr )
    {
        if ( start > end ) return nullptr;

        int mid = ( start + end ) / 2;
        StrayTreeNode *root = new StrayTreeNode( arr[ mid ] );
        root->previous = node;

        root->leftChild = sortedArrayToBST( arr, start, mid - 1, root );

        root->rightChild = sortedArrayToBST( arr, mid + 1, end, root );

        return root;
    }


    void transform( StrayVector<T> *arr, StrayTreeNode *node )
    {
        if ( node != nullptr )
        {
            arr->append( node->item );
            transform( arr, node->leftChild );
            transform( arr, node->rightChild );
        }
        else return;
    }


    void preOrder( StrayVector<T> *nodes, StrayTreeNode* node = nullptr )
    {
        if ( node == nullptr ) return;
        nodes->append( node->item );
        preOrder( nodes, node->leftChild );
        preOrder( nodes, node->rightChild );

    }


    void postOrder( StrayVector<T> *nodes, StrayTreeNode* node = nullptr )
    {
        if ( node == nullptr ) return;
        nodes->prepend( node->item );
        preOrder( nodes, node->leftChild );
        preOrder( nodes, node->rightChild );

    }


    void breadthOrder( StrayVector<T> *nodes, StrayTreeNode* node = nullptr )
    {
        if ( node == nullptr ) return;
        breadthOrder( nodes, node->leftChild );
        nodes->append( node->item );
        breadthOrder( nodes, node->rightChild );

    }


    void depthOrder( StrayVector<T> *nodes, StrayTreeNode* node = nullptr )
    {
        if ( node == nullptr ) return;
        breadthOrder( nodes, node->leftChild );
        nodes->prepend( node->item );
        breadthOrder( nodes, node->rightChild );

    }


    void childOrder( StrayVector<T> *nodes, StrayTreeNode* node = nullptr )
    {
        if ( node == nullptr ) return;
        childOrder( nodes, node->leftChild );
        childOrder( nodes, node->rightChild );
        nodes->append( node->item );
    }


    void toVec( StrayVector<StrayTreeNode*> *nodes, StrayTreeNode* node = nullptr )
    {
        if ( node == nullptr ) return;
        toVec( nodes, node->leftChild );
        nodes->append( node );
        toVec( nodes, node->rightChild );
    }
};


template< typename T >
class StrayTreeIterator
{
friend class StrayBST<T>;
public:

    bool isValid()
    {
        if ( curr != nullptr ) return true;
        else return false;
    }

    void begin()
    {
        curr = start;
    }

    bool hasLeft()
    {
        if ( curr->leftChild != nullptr ) return true;
        else return false;
    }

    bool hasRight()
    {
        if ( curr->rightChild != nullptr ) return true;
        else return false;
    }

    bool hasParent()
    {
        if ( curr->previous != nullptr ) return true;
        else return false;
    }

    void moveLeft()
    {
        curr = curr->leftChild;
    }

    void moveRight()
    {
        curr = curr->rightChild;
    }

    void regress()
    {
        curr = curr->previous;
    }

    T examinate()
    {
        return curr->item;
    }

    void setLeft( typename StrayBST<T>::StrayTreeNode *node )
    {
        curr->leftChild = node;
        node->previous = curr;
    }

    void setRight( typename StrayBST<T>::StrayTreeNode *node )
    {
        curr->rightChild = node;
        node->previous = curr;
    }

    void set( typename StrayBST<T>::StrayTreeNode *node )
    {
        curr->item = node->item;
    }




private:
    typename StrayBST<T>::StrayTreeNode *start;
    typename StrayBST<T>::StrayTreeNode *curr;

    StrayTreeIterator( typename StrayBST<T>::StrayTreeNode *root )
    {
        start = root;
    }


    typename StrayBST<T>::StrayTreeNode* get()
    {
        return curr;
    }

};


#endif // STRAYTREE_H
