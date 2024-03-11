#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include "ds_set.hpp"

using namespace std;

int main() {
    
    ds_set<std::string> set1;
    set1.insert("hello");
    set1.insert("good-bye");
    set1.insert("friend");
    set1.insert("abc");
    set1.insert("puppy");
    set1.insert("zebra");
    set1.insert("daddy");
    set1.insert("puppy");  // should recognize that this is a duplicate!
    
    assert(set1.sanity_check());
    assert (set1.size() == 7);
    
    ds_set<std::string>::iterator p = set1.begin();
    assert(p != set1.end() && *p == std::string("abc"));
    
    p = set1.find( "foo" );
    assert (p == set1.end());
    
    p = set1.find("puppy");
    assert (p != set1.end());
    assert (*p == "puppy");
    
    std::cout << "Here is the tree, printed sideways.\n"
    << "The indentation is proportional to the depth of the node\n"
    << "so that the value stored at the root is the only value printed\n"
    << "without indentation.  Also, for each node, the right subtree\n"
    << "can be found above where the node is printed and indented\n"
    << "relative to it\n";
    set1.print_as_sideways_tree( std::cout );
    std::cout << std::endl;
    
    
    // copy the set
    ds_set<std::string> set2( set1 );
    assert(set1.sanity_check());
    assert(set2.sanity_check());
    assert(set1.size() == set2.size());
    
    
    //  Now add stuff to set2
    set2.insert( std::string("a") );
    set2.insert( std::string("b") );
    std::cout << "After inserting stuff:\n";
    set2.print_as_sideways_tree( std::cout );
    std::cout << std::endl;
    assert(set1.sanity_check());
    assert(set2.sanity_check());
    assert(set1.size() == set2.size() - 2);
    
    
    //  Now erase stuff from set2
    set2.erase("hello");
    set2.erase("a");
    set2.erase("hello"); // should recognize that it's not there anymore!
    set2.erase("abc");
    set2.erase("friend");
    std::cout << "After erasing stuff:\n";
    set2.print_as_sideways_tree( std::cout );
    std::cout << std::endl;
    assert(set1.sanity_check());
    assert(set2.sanity_check());
    assert(set1.size() == set2.size() + 2);
    
    
    // Checkpoints 2 & 3
    // Write code to test the forwards & backwards iterators!
    ds_set<int> balanced;
    balanced.insert(8);
    balanced.insert(4);
    balanced.insert(12);
    balanced.insert(2);
    balanced.insert(6);
    balanced.insert(10);
    balanced.insert(14);
    balanced.insert(1);
    balanced.insert(3);
    balanced.insert(5);
    balanced.insert(7);
    balanced.insert(9);
    balanced.insert(11);
    balanced.insert(13);
    balanced.insert(15);
    balanced.print_as_sideways_tree(cout);
    
    for (ds_set<int>::iterator itr = balanced.begin(); itr != balanced.end(); itr++) {
        cout << *itr << " ";
    }
    
    cout << endl;
    
    for (ds_set<int>::iterator itr = --balanced.end(); itr != --balanced.begin(); itr--) {
        cout << *itr << " ";
    }
    
    cout << endl;
    cout << endl;
    
    ds_set<int> unbalanced1;
    unbalanced1.insert(1);
    unbalanced1.insert(2);
    unbalanced1.insert(3);
    unbalanced1.insert(4);
    unbalanced1.insert(5);
    unbalanced1.insert(6);
    unbalanced1.insert(7);
    unbalanced1.insert(8);
    unbalanced1.insert(9);
    unbalanced1.insert(10);
    unbalanced1.insert(11);
    unbalanced1.insert(12);
    unbalanced1.insert(13);
    unbalanced1.insert(14);
    unbalanced1.insert(15);
    
    for (ds_set<int>::iterator itr = unbalanced1.begin(); itr != unbalanced1.end(); itr++) {
        cout << *itr << " ";
    }
    
    cout << endl;
    
    for (ds_set<int>::iterator itr = --unbalanced1.end(); itr != --unbalanced1.begin(); itr--) {
        cout << *itr << " ";
    }
    
    cout << endl;
    cout << endl;
    
    ds_set<int> unbalanced2;
    unbalanced2.insert(15);
    unbalanced2.insert(14);
    unbalanced2.insert(13);
    unbalanced2.insert(12);
    unbalanced2.insert(11);
    unbalanced2.insert(10);
    unbalanced2.insert(9);
    unbalanced2.insert(8);
    unbalanced2.insert(7);
    unbalanced2.insert(6);
    unbalanced2.insert(5);
    unbalanced2.insert(4);
    unbalanced2.insert(3);
    unbalanced2.insert(2);
    unbalanced2.insert(1);
    
    for (ds_set<int>::iterator itr = unbalanced2.begin(); itr != unbalanced2.end(); itr++) {
        cout << *itr << " ";
    }
    
    cout << endl;
    
    for (ds_set<int>::iterator itr = --unbalanced2.end(); itr != --unbalanced2.begin(); itr--) {
        cout << *itr << " ";
    }
    
    cout << endl;
    cout << endl;
    
    // worst case for operator++ in balanced tree is log n and unbalanced tree n (worst case in general is proportional to height of tree)
    // total cost is O(n) for iterating over the whole tree --> you may have to visit each node up to c number of times but c is a constant so O(c*n) simplifies to O(n) overall
    // average or amortized cost for operator++ for a single call is O(1)
    // these conclusions match what we discussed in lecture 18
    
    return 0;
}
