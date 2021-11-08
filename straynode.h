#ifndef STRAYNODE_H
#define STRAYNODE_H

template<typename T>
class StrayIterator;

template<typename T>
class StrayList;

template <typename T>
class StrayNode
{
public:

    ////////////////
    /// FRIENDS ///
    ///////////////

    friend class StrayIterator<T>;
    friend class StrayList<T>;


    //////////////////
    /// NODE IMPL ///
    /////////////////


    /**
     * @brief StrayNode default constructor
     */
    StrayNode()
    {
        this->item = T();
        link( nullptr, nullptr );
    }

    /**
     * @brief StrayNode constructor, set item
     * @param item -> T
     */
    StrayNode( const T &item )
    {
        this->item = item;
        link ( nullptr, nullptr );
    }

    ~StrayNode() {}

    /**
     * @brief Return node memory size ( bytes )
     * @return -> long
     */
    long mem_size() { return sizeof (T); }


    /**
     * @brief Return data incapsulated in it
     * @return T
     */
    T data() { return item; }

private:
    T item;
    StrayNode* next;
    StrayNode* prev;


    /**
     * @brief Link this to prev and next
     * @param p -> StrayNode
     * @param n -> StrayNode
     */
    void link( StrayNode* p = nullptr, StrayNode* n = nullptr )
    {
        if ( p )
            prev = p;

        if ( n )
            next = n;
    }

    /**
     * @brief Unlink left reference
     */
    void unlink_left( )
    {
        prev = nullptr;
    }


    /**
     * @brief @brief Unlink right reference
     */
    void unlink_right( )
    {
        next = nullptr;
    }


    /**
     * @brief Set node item
     * @param item -> T
     */
    void set( const T &item ) { this->item = item; }
};


#endif // STRAYNODE_H
