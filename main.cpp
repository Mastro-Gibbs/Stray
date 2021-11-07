#include <iostream>

#include "stray.h"
#include "strayrecord.h"

#include <cstdlib>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>


using namespace std;

/*
void fill( StrayList<int> *stray )
{
    auto t1 = chrono::high_resolution_clock::now();
    for ( int i = 0; i < 100000000; i++ )
        stray->append( rand() % 101 );
    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::cout << "TIME TO FILL: " << ms_double.count() << "ms" << endl;
}


void sortIt( StrayList<int> *stray )
{
    auto t1 = chrono::high_resolution_clock::now();
    stray->sort();
    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::cout << "TIME TO SORT: " <<  ms_double.count() << "ms" << endl;
}
*/



int main()
{


    /*
    StrayMap<int, double> map;

    map.put( 1, 1.2 );
    map.put( 8, 14.6 );
    map.put( 9, 1.2 );
    map.put( 2, 14.6 );




    StrayVector<double> vals = map.values();
    StrayVector<int> k = map.keys();

    for ( uint64_t i = 0; i < vals.count(); i++ )
    {
        cout << k.get( i ) << ", " << vals.get( i ) << endl;
    }


    cout << "##############################" << endl;

    map.put( 2, 30.16 );
    map.purge( 9 );


    StrayVector<double> vals1 = map.values();
    StrayVector<int> k1 = map.keys();

    for ( uint64_t i = 0; i < vals1.count(); i++ )
    {
        cout << k1.get( i ) << ", " << vals1.get( i ) << endl;
    }



*/















    /*
    StraySet<int> set;
    set.insert( 4 );
    set.insert( 7 );
    set.insert( 4 );
    set.insert( 1 );
    set.insert( 5 );

    StrayVector<int> *vec = set.toVector();

    for( uint64_t i = 0; i < vec->count(); i++ )
    {
        cout << vec->get( i ) << endl;
    }
    delete vec;

    cout << "######################" << endl;
    cout << set.contains( 8 ) << endl;
*/













    /*
    StrayBST<int> tree;
    tree.insert( 3 );
    tree.insert( 4 );
    tree.insert( 2 );
    tree.insert( 1 );
    tree.insert( 8 );
    tree.insert( 6 );
    tree.insert( 10 );


    StrayVector<int> *nodes = tree.visit( VisitMode::PreOrder);
    for ( uint64_t i = 0; i < nodes->count(); i++ )
    {
        cout << nodes->get( i ) << " ";
    }
    cout << endl;

    delete nodes;


    tree.remove( 2 );

    nodes = tree.visit( VisitMode::PreOrder);
    for ( uint64_t i = 0; i < nodes->count(); i++ )
    {
        cout << nodes->get( i ) << " ";
    }
    cout << endl;

    delete nodes;


    cout << tree.find( 13 ) << endl ;

    */






















    /*
    StrayTree<int> tree;
    tree.insert( 3 );
    tree.insert( 4 );
    tree.insert( 2 );
    tree.insert( 1 );
    tree.insert( 8 );
    tree.insert( 6 );
    tree.insert( 10 );
    */






















    /*
    StrayMathMatrix<int> mm( 3, 3 );

    StrayVector<int> data = { 9, 2, 3, 4, 5, 6, 7, 8, 9 };

    mm.fill( data );

    mm.draw();

    cout << mm.determinant() << endl;
*/

























    /*
    StrayVector<int> *v = new StrayVector<int>( 5 );
    v->append( 3 );
    v->append( 0 );
    v->append( 1 );
    v->append( 2 );
    v->append( 5 );

    v->setPrefSize( 3 );

    cout << v->get( 2 ) << endl;
*/

    /*
    StrayMatrix<int> matrix( 5, 5 );
    matrix.put( 6, 0, 0 );
    matrix.put( 6, 1, 1 );
    matrix.put( 6, 2, 2 );
    matrix.put( 6, 3, 3 );
    matrix.put( 6, 4, 4 );


    matrix.draw();

    cout << "#########################" << endl;

    StrayMatrix<int> mul = matrix.multiply( matrix );
    mul.draw();


    cout << "#########################" << endl;


    StrayMatrix<int> add = mul.sum( matrix );
    add.draw();

    cout << "#########################" << endl;


    StrayMatrix<int> sub = add.subtract( matrix );
    sub.draw();

    cout << "#########################" << endl;

    cout << matrix.isIdentity() << endl;

*/










/*
    UStrayMap<int , double> map;
    map.put( 2, 5.0 );
    map.put( 7, 3.0 );
    map.put( 3, 7.0 );
    map.put( 1, -5.0 );

    UStrayMap<int , double> map2;
    map2.put( 3, 10.9 );
    map2.put( 5, 8.6 );

    map.merge( &map2 );


    cout << "PEEK TEST: " << map.peek( 3 ) << endl;


    map.purge( 5 );


    UStraySet<int> s;
    s = map.keys();

    s.sort();

    StraySetIterator<int> *it = s.iterate();
    it->begin();

    while( it->hasNext() )
    {
        cout << it->next() << endl;
    }

    delete it;

    cout << "#############################" << endl;

    StrayMapIterator<int, double> *it2 = map.iterate();

    it2->begin();
    while( it2->hasNext() )
    {
        cout << it2->key() << ", " << it2->value() << endl;
        it2->set( -13.5 );
        it2->next();
    }

    cout << "#############################" << endl;

    it2->begin();
    while( it2->hasNext() )
    {
        cout << it2->key() << ", " << it2->value() << endl;
        it2->set( -13.5 );
        it2->next();
    }


*/






















/*

    StrayList<int> li;
    li.append( 1 );
    li.append( 2 );
    li.append( 3 );
    li.append( 4 );

    li.prepend( 0 );

    StrayList<int> li2;
    li2.append( 20 );
    li2.append( 30 );
    li2.append( 40 );

    li.append( &li2 );
    li.prepend( &li2 );

    li.insert( 666, 1 );


    StrayList<int> l;
    for ( long i = 0 ; i < 10000000; i++ ) l.append( rand() % 101 );

    auto t1 = chrono::high_resolution_clock::now();
    l.sort();
    auto t2 = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_double.count() << "ms" << endl;




    StrayListIterator<int> *it = li.iterate();

    it->begin();
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }

    cout << "###########################" << endl;

    it->startFrom( 0 );
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }

    cout << "###########################" << endl;

    it->startFromLast( 20 );
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }


    cout << "****************************************" << endl;

    cout << "CONTAINS 30( BOOL): " << li.contains( 30 ) << endl;

    cout << "****************************************" << endl;

    cout << "CONTAINS 50( BOOL): " << li.contains( 50 ) << endl;

    cout << "****************************************" << endl;

    cout << "INDEX OF 4: " << li.indexOf( 4 ) << endl;

    cout << "****************************************" << endl;

    cout << "LAST INDEX OF 30: " << li.lastIndexOf( 30 ) << endl;

    cout << "****************************************" << endl;

    cout << "IS EMPTY( BOOL ): " << li.isEmpty() << endl;

    cout << "****************************************" << endl;

    cout << "COUNT: " << li.count() << endl;

    cout << endl << "************ LIST COMPARING  [ O( n log n ) ]****************" << endl;
    cout << "li.compare( li ) [equal] -> ( BOOL ): " << li.compare( li ) << endl;
    cout << "li.compare( li2 ) [not equal] -> ( BOOL ): " << li.compare( li2 ) << endl;
    StrayList<int> li3;
    li2.append( 20 );
    li2.append( 30 );
    li2.append( 50 );
    cout << "li2.compare( li3 ) [same size, not equal] -> ( BOOL ): " << li2.compare( li3 ) << endl;


    cout << "*********** LIST SORTING ****************" << endl;
    li.sort();


    it->begin();
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }


    cout << "****************************************" << endl;
    cout << "REMOVE FIRST: " << li.removeFirst() << endl;
    cout << "REMOVE LAST: " << li.removeLast() << endl;
    it = li.iterate();


    cout << endl << "**************** ITERATOR TEST *****************" << endl;

    cout << "FROM HEAD TO TAIL ( aka it->next() )" << endl;

    it->begin();
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }

    cout << "FROM TAIL TO HEAD ( aka it->prev() )" << endl;
    it->end();
    while ( it->hasPrev() )
    {
        cout << it->prev() << endl;
    }

    cout << "************ PEEK TEST ****************" << endl;
    it->begin();
    while ( it->hasNext() )
    {
        cout << it->peek() << endl;
        it->next();
    }

    cout << "************ COMPARE TEST ( VALUE: 30 ) ****************" << endl;
    it->begin();
    while ( it->hasNext() )
    {
        cout << it->peek() << " IS 30? -> ( BOOL ) " << it->compare( 30 ) << endl;
        it->next();
    }

    cout << "************ DELETING TEST ****************" << endl;
    cout << "SIZE OF STRAYLIST BEFORE REMOVING ACT: " << li.count() << endl;

    it->begin();
    while ( it->hasNext() )
    {
        if ( it->compare( 30 ) ) cout << "REMOVED: " << it->remove() << endl;
        it->next();
    }


    it->begin();
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }

    cout << "SIZE OF STRAYLIST AFTER REMOVING ACT: " << li.count() << endl;


    cout << "************ SET TEST ( VALUE: 500 ) ****************" << endl;
    it->begin();
    while ( it->hasNext() )
    {
        cout << it->peek() << " IS 20? -> SET TO 500 -> ";
        if ( it->compare( 20 ) )
            it->set( 500 );
        cout << it->peek() << endl;
        it->next();
    }


    cout << "********************* CLEARING LIST li ********" << endl;
    li.clear();

    it = li.iterate();
    it->begin();
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }


    cout << "********* DELETING TEST ***** ( new ) *********" << endl;
    StrayList<int> *list = new StrayList<int>( li2 );
    it = list->iterate();
    it->begin();
    while ( it->hasNext() )
    {
        cout << it->next() << endl;
    }

    delete list;
*/
    return 0;
}
