//
//  genome_hashmap.hpp
//  hw9
//
//  Created by Aditya Behal on 4/18/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef genome_hashmap_hpp
#define genome_hashmap_hpp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>

using namespace std;

// The genome hash map is templated over the type of the hash function, a function object.
template <class HashFunc>
class genome_hashmap {
public:
    // =================================================================
    // HASH MAP IMPLEMENTATION
    
    // Constructor for the hash map just accepts the size of the table.
    // The default constructor for the hash function object is
    // implicitly used.
    genome_hashmap(unsigned int init_size = 100, const float LOAD_FRACTION = 0.5) : m_table(init_size), m_size(0), LOAD_FRACTION_FOR_RESIZE(LOAD_FRACTION) {}
    
    // Copy constructor just uses the member function copy constructors.
    genome_hashmap(const genome_hashmap<HashFunc>& old) : m_table(old.m_table), m_size(old.m_size) {}
    
    // Destructor
    ~genome_hashmap() {}
    
    // Assignment Operator
    genome_hashmap& operator=(const genome_hashmap<HashFunc>& old) {
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
    
    // Insert the key-value pair if it is not already there.
    void insert(const string& key, const int pos) {
        // O(1)
        if (m_size >= LOAD_FRACTION_FOR_RESIZE * m_table.size()) {
            // O(L*k*(k + p))
            this->resize_table(2*m_table.size() + 1);
        }
        
        // Compute the hash value and then the table index
        // O(k)
        unsigned int hash_value = m_hash(key);
        // O(1)
        unsigned int index = hash_value % m_table.size();
        
        // If the key is not already in the table
        if (m_table[index].first.empty()) {
            // add it to the table and construct an iterator
            // O(k + p)
            m_table[index] = make_pair(key, list<int>());
            m_table[index].second.push_back(pos);
            m_size++;
        } else {
            // O(L)
            // use linear probing to handle collisions
            while (m_table[index].first != key && !m_table[index].first.empty()) {
                index++;
                if (index == m_table.size()) {
                    index = 0;
                }
            }
            // entry does not already exist
            if (m_table[index].first.empty()) {
                // O(k)
                m_table[index] = make_pair(key, list<int>());
                m_table[index].second.push_back(pos);
                m_size++;
            } else {
                // O(1)
                m_table[index].second.push_back(pos);
            }
        }
    }
    
    // Find all instances of a sequence in the hash table
    const list<int> find(const string& query, unsigned int kmer_length) const {
        // O(k)
        string querySearch = query.substr(0, kmer_length);
        // O(k)
        unsigned int hash_value = m_hash(querySearch);
        // O(1)
        unsigned int index = hash_value % m_table.size();
        const unsigned int originalIndex = index;
        
        // O(L)
        // linear probing to deal with collisions
        while (m_table[index].first != querySearch) {
            index++;
            if (index == m_table.size()) {
                index = 0;
            }
            if (index == originalIndex) {
                return list<int>();
            }
        }
        // O(p)
        return m_table[index].second;
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
    vector<pair<string, list<int>>> m_table; // actual table
    HashFunc m_hash; // hash function
    unsigned int m_size; // number of key-value pairs
    float LOAD_FRACTION_FOR_RESIZE;
    
    // private helper function
    // resize the table with the same values but with increased capacity
    // O(L*(k + p))
    void resize_table(unsigned int new_size) {
        // O(L)
        vector<pair<string, list<int>>> old_table = m_table;
        // O(L)
        m_table.clear();
        // O(L) simplified from O(2*L + 1)
        m_table.resize(new_size);
        // O(L)
        // loop through entries of old table
        for (unsigned int i = 0; i < old_table.size(); i++) {
            if (!old_table[i].first.empty()) {
                // O(k)
                // make new hash values for newly sized table
                unsigned int hash_value = m_hash(old_table[i].first);
                unsigned int index = hash_value % new_size;
                while (!m_table[index].first.empty()) {
                    index++;
                    if (index == m_table.size()) {
                        index = 0;
                    }
                }
                // O(k + p)
                // copy entries from old table to new table
                m_table[index] = old_table[i];
            }
        }
    }
};

#endif /* genome_hashmap_hpp */
