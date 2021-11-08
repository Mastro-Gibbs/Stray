


/**
 * @author Stefano Fattore ( aka MastroGibbs )
 *
 * @brief StrayRecord< TYPE1, TYPE2 > aka Tuple< E1, E2 >. It's a class to manage couples of data as key-value.
 *
 * @date 07/11/2021
 *
 * @copyright Stefano Fattore
 */



#ifndef STRAYRECORD_H
#define STRAYRECORD_H

#include <ostream>
#include "strayenums.h"

using namespace std;


template< typename TYPE1, typename TYPE2 >
/**
 * @brief The StrayRecord class
 */
class StrayRecord
{
public:

    /**
     * @brief Empty constructor
     */
    StrayRecord()
    {
        item1 = TYPE1();
        item2 = TYPE2();
    }

    /**
     * @brief StrayRecord constructor. Params must have the same type otherwise undefined behavior
     * @param t1 -> first template
     * @param e -> Which item { First, Second, Both }
     * @attention Params must have the same type otherwise undefined behavior
     * @
     */
    StrayRecord( TYPE1 t, Item e )
    {
        if ( e == First )
        {
            item1 = t;
            item2 = TYPE2();
        }
        else if ( e == Second )
        {
            item1 = TYPE1();
            item2 = t;
        }
        else if ( e == Both )
        {
            item1 = t;
            item2 = t;
        }
    }


    /**
     * @brief StrayRecord constructor
     * @param t1 -> first template
     * @param t2 -> second template
     */
    StrayRecord( TYPE1 t1, TYPE2 t2 )
    {
        item1 = t1;
        item2 = t2;
    }


    /**
     * @brief StrayRecord constructor from another StrayRecord
     * @param other -> StrayRecord
     */
    StrayRecord( const StrayRecord &other )
    {
        *this = other;
    }


    ~StrayRecord() {}

    /**
     * @brief Get data
     * @return StrayRecord*
     */
    StrayRecord* get() { return this; }

    /**
     * @brief Copy a StrayRecord Obj
     * @return StrayRecord
     */
    StrayRecord copy() { return StrayRecord( item1, item2 ); }

    /**
     * @brief Get first item
     * @return template
     */
    TYPE1 first() { return item1; }

    /**
     * @brief Get second item
     * @return template
     */
    TYPE2 second() { return item2; }

    /**
     * @brief Set first item
     * @param t -> Template
     */
    void setFirst( TYPE1 t ) { item1 = t; }

    /**
     * @brief Set second item
     * @param t -> Template
     */
    void setSecond( TYPE2 t ) { item2 = t; }


    /**
     * camparing system
     *
     * @brief Choose what to compare and how
     * @param other -> StrayRecord
     * @param c -> Comparator
     * @param e -> which item
     * @return bool
     */
    bool compare( const StrayRecord &other, Cmp c, Item e )
    {
        bool res = false;
        if ( e == First )
        {
            if ( c == EQ )
                res = ( item1 == other.item1 );
            else if ( c == LT )
                res = ( item1 < other.item1 );
            else if ( c == GT )
                res = ( item1 > other.item1 );
            else if ( c == LE )
                res = ( item1 <= other.item1 );
            else if ( c == GE )
                res = ( item1 >= other.item1 );
            else if ( c == NE )
                res = ( item1 != other.item1 );
        }
        else if ( e == Second )
        {
            if ( c == EQ )
                res = ( item2 == other.item2 );
            else if ( c == LT )
                res = ( item2 < other.item2 );
            else if ( c == GT )
                res = ( item2 > other.item2 );
            else if ( c == LE )
                res = ( item2 <= other.item2 );
            else if ( c == GE )
                res = ( item2 >= other.item2 );
            else if ( c == NE )
                res = ( item2 != other.item2 );
        }
        else if ( e == Both )
        {
            if ( c == EQ )
                res = operator==( other );
            else if ( c == LT )
                res = operator<( other );
            else if ( c == GT )
                res = operator>( other );
            else if ( c == LE )
                res = operator<=( other );
            else if ( c == GE )
                res = operator>=( other );
            else if ( c == NE )
                res = operator!=( other );
        }
        return res;
    }


    StrayRecord& operator=( const StrayRecord &other )
    {
        item1 = other.item1;
        item2 = other.item2;
        return *this;
    }


    bool operator<( const StrayRecord &other )
    {
        return ( item1 < other.item1 ) && ( item2 < other.item2 );
    }

    bool operator>( const StrayRecord &other )
    {
        return ( item1 > other.item1 ) && ( item2 > other.item2 );
    }

    bool operator<=( const StrayRecord &other )
    {
        return ( item1 <= other.item1 ) && ( item2 <= other.item2 );
    }

    bool operator>=( const StrayRecord &other )
    {
        return ( item1 >= other.item1 ) && ( item2 >= other.item2 );
    }

    bool operator==( const StrayRecord &other )
    {
        return ( item1 == other.item1 ) && ( item2 == other.item2 );
    }

    bool operator!=( const StrayRecord &other )
    {
        return ( item1 != other.item1 ) && ( item2 != other.item2 );
    }

    friend ostream &operator<<( ostream& os, const StrayRecord& rec )
    {
       os << "(" << rec.item1 << ", " << rec.item2 << ")";
       return os;
    }

    friend ostream &operator<<( ostream& os, const StrayRecord* rec )
    {
       os << "(" << rec->item1 << ", " << rec->item2 << ")";
       return os;
    }



private:
    TYPE1 item1;
    TYPE2 item2;
};




#endif // STRAYRECORD_H
