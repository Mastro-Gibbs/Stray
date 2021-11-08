#ifndef STRAYITERATOR_H
#define STRAYITERATOR_H

#include "straynode.h"

template < typename T >
class StrayIterator
{

public:

    /**
     * @brief StrayIterator constructor;
     * @param h -> head
     * @param t -> tail; default: nullprt
     * @param s -> pointer to list size;
     */
    StrayIterator( StrayNode<T> *h, StrayNode<T> *t = nullptr, int *s = nullptr )
    {
        head = h;
        tail = t;
        size = s;
    }

    /**
     * @brief empty destructor
     */
    ~StrayIterator() {}


    /**
     * @brief Check if iterator pointer is valid
     * @return bool
     */
    bool isValid() { return curr; }


    /**
     * @brief Set iterator to head
     */
    void begin() { curr = head; }


    /**
     * @brief Set iterator to end
     */
    void end() { curr = tail; }

    /**
     * @brief Check if iterator has next elem
     * @return bool
     */
    bool hasNext()
    {
        if ( curr != nullptr ) return true;
        else return false;
    }

    /**
     * @brief Check if iterator has prev elem
     * @return bool
     */
    bool hasPrev()
    {
        if ( curr != nullptr ) return true;
        else return false;
    }

    /**
     * @brief Return item incapsulated in StrayNode pointed by iterator
     * @return T
     */
    T peek()
    {
        return curr->item;
    }

    /**
     * @brief Return item incapsulated in StrayNode pointed by iterator. Set iterator to next
     * @return T
     */
    T next()
    {
        T item = curr->item;
        curr = curr->next;
        return item;
    }

    /**
     * @brief Return item incapsulated in StrayNode pointed by iterator. Set iterator to prev
     * @return T
     */
    T prev()
    {
        T item = curr->item;
        curr = curr->prev;
        return item;
    }


    /**
     * @brief Set item incapsulated to elem
     */
    void set( const T &elem ) { curr->set( elem ); }


    /**
     * @brief Get StrayNode instance
     * @return StrayNode pointer
     */
    StrayNode<T>* get() { return curr; }

private:
    StrayNode<T> *curr;
    StrayNode<T> *head;
    StrayNode<T> *tail;
    int *size;
};


#endif // STRAYITERATOR_H
