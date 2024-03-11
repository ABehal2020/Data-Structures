//
//  ec_hashmap.hpp
//  hw9
//
//  Created by Aditya Behal on 4/20/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef ec_hashmap_hpp
#define ec_hashmap_hpp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>

using namespace std;

// The extra credit hash map is templated over both the type of the hash function, a function object
template <class HashFunc>
class ec_hashmap {
public:
    // =================================================================
    // HASH MAP IMPLEMENTATION
    
    // Constructor for the hash map just accepts the size of the table.
    // The default constructor for the hash function object is
    // implicitly used.
    ec_hashmap(unsigned int init_size = 100, const float LOAD_FRACTION = 0.5) : m_table(init_size), m_size(0), LOAD_FRACTION_FOR_RESIZE(LOAD_FRACTION) {}
    
    // Copy constructor just uses the member function copy constructors.
    ec_hashmap(const ec_hashmap<HashFunc>& old) : m_table(old.m_table), m_size(old.m_size) {}
    
    // Destructor
    ~ec_hashmap() {}
    
    // Assignment Operator
    ec_hashmap& operator=(const ec_hashmap<HashFunc>& old) {
        if (&old != this) {
            *this = old;
        }
    }
    
    // Update size and load_fraction if specified by user
    void updateConfigs(unsigned int init_size, const float LOAD_FRACTION) {
        m_table.resize(init_size);
        LOAD_FRACTION_FOR_RESIZE = LOAD_FRACTION;
    }
    
    // keep track of number of elements in the table
    unsigned int size() const { return m_size; }
    
    // advance iterator to replace operator[] for vectors
    list<pair<string, list<int>>>::iterator advance(unsigned int index) {
        list<pair<string, list<int>>>::iterator itr = m_table.begin();
        for (unsigned int i = 0; i < index; i++) {
            itr++;
        }
        return itr;
    }
    
    // const_iterator version of advance function
    list<pair<string, list<int>>>::const_iterator const_advance(unsigned int index) const {
        list<pair<string, list<int>>>::const_iterator const_itr = m_table.begin();
        for (unsigned int i = 0; i < index; i++) {
            const_itr++;
        }
        return const_itr;
    }
    
    // Insert the key-value pair if it is not already there.
    void insert(const string& key, const int pos) {
        if (m_size >= LOAD_FRACTION_FOR_RESIZE * m_table.size()) {
            this->resize_table(2*m_table.size() + 1);
        }
        
        // Compute the hash value and then the table index
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % m_table.size();
        
        list<pair<string, list<int>>>::iterator itr = advance(index);
        
        // If the key is not already in the table
        if (itr->first.empty()) {
            // add it to the table and construct an iterator
            *itr = make_pair(key, list<int>());
            itr->second.push_back(pos);
            m_size++;
        } else {
            // linear probing to deal with collisions
            while (itr->first != key && !itr->first.empty()) {
                itr++;
                if (itr == m_table.end()) {
                    itr = m_table.begin();
                }
            }
            if (itr->first.empty()) {
                // entry does not exist so insert it
                *itr = make_pair(key, list<int>());
                itr->second.push_back(pos);
                m_size++;
            } else {
                itr->second.push_back(pos);
            }
        }
    }
    
    // Find all instances of a sequence in the hash table
    const list<int> find(const string& query, unsigned int kmer_length) const {
        string querySearch = query.substr(0, kmer_length);
        unsigned int hash_value = m_hash(querySearch);
        unsigned int index = hash_value % m_table.size();
        
        list<pair<string, list<int>>>::const_iterator itr = const_advance(index);
        list<pair<string, list<int>>>::const_iterator original_itr = const_advance(index);
        
        // linear probing to deal with collisions
        while (itr->first != querySearch) {
            itr++;
            if (itr == m_table.end()) {
                itr = m_table.begin();
            }
            if (itr == original_itr) {
                return list<int>();
            }
        }
        return itr->second;
    }
    
    // A public print utility
    void print(ostream& ostr) const {
        // loop through whole table
        for (unsigned int i = 0; i < m_table.size(); i++) {
            if (!m_table[i].first.empty()) {
                ostr << i << ": (" << m_table[i].first << ",";
                list<int> currentList = m_table[i].second;
                for (list<int>::iterator itr = currentList.begin(); itr != currentList.end(); itr++) {
                    ostr << " " << *itr;
                }
                ostr << ")" << endl;
                currentList.clear();
            }
        }
    }
    
private:
    // HASH MAP REPRESENTATION
    list<pair<string, list<int>>> m_table; // actual table
    HashFunc m_hash; // hash function
    unsigned int m_size; // number of key-value pairs
    float LOAD_FRACTION_FOR_RESIZE;
    
    // private helper function
    // resize the table with the same values but with increased capacity
    void resize_table(unsigned int new_size) {
        list<pair<string, list<int>>> old_table = m_table;
        m_table.clear();
        m_table.resize(new_size);
        list<pair<string, list<int>>>::iterator old_itr = old_table.begin();
        // loop through whole table
        for ( ; old_itr != old_table.end(); old_itr++) {
            if (old_itr->first.empty()) {
                // calculate new hash values for insertion into new table
                unsigned int hash_value = m_hash(old_itr->first);
                unsigned int index = hash_value % new_size;
                list<pair<string, list<int>>>::iterator m_itr = advance(index);
                // linear probing to deal with collisions
                while (!m_itr->first.empty()) {
                    m_itr++;
                    if (m_itr == m_table.end()) {
                        m_itr = m_table.begin();
                    }
                }
                *m_itr = *old_itr;
            }
        }
    }
};

#endif /* ec_hashmap_hpp */
