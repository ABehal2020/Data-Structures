//
//  main.cpp
//  hw9
//
//  Created by Aditya Behal on 4/17/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "genome_hashmap.hpp"
#include "ec_hashmap.hpp"

using namespace std;

// O(k)
// hash function doing bitwise math on strings
class hash_string_obj {
public:
    unsigned int operator() (std::string const& key) const {
        // This implementation comes from
        // http://www.partow.net/programming/hashfunctions/
        unsigned int hash = 1315423911;
        for (unsigned int i = 0; i < key.length(); i++) {
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        }
        return hash;
    }
};

// O(L*k*(k + p))
// reading in genome file
void readGenomeFile(ifstream& genome_file, genome_hashmap<hash_string_obj>& genome, unsigned int kmer_length, string& genome_characters) {
    string genome_file_line;
    string kmer;
    // O(L)
    // reading in genome characters
    while (genome_file >> genome_file_line) {
        genome_characters += genome_file_line;
    }
    // O(L)
    // building indexes in hash table
    for (unsigned int i = 0; i <= genome_characters.size() - kmer_length; i++) {
        // O(k)
        for (unsigned int j = i; j < i + kmer_length; j++) {
            kmer.push_back(genome_characters[j]);
        }
        // O(L*k*(k + p))
        // inserting entries in hash table
        // O(k)
        genome.insert(kmer, i);
        // O(k)
        kmer.clear();
    }
}

// finding query sequences
void findQuerySequences(const pair<unsigned int, string>& query, const list<int>& queryResults, const string& genome_characters) {
    bool atLeastOneMatch = false;
    // O(p)
    // looping through query results
    for (list<int>::const_iterator itr = queryResults.begin(); itr != queryResults.end(); itr++) {
        unsigned int numMismatchesSoFar = 0;
        unsigned int numMismatchesAllowed = query.first;
        unsigned int counter = 0;
        bool match = true;
        string currentString;
        // O(q)
        // checking for mismatches using seeds as starting positions
        for (unsigned int j = *itr; j < *itr + query.second.size(); j++) {
            currentString.push_back(genome_characters[j]);
            if (query.second[counter] != genome_characters[j]) {
                numMismatchesSoFar++;
            }
            if (numMismatchesSoFar > numMismatchesAllowed) {
                // too many mismatches so not a match
                match = false;
                break;
            }
            counter++;
        }
        if (match) {
            atLeastOneMatch = true;
            cout << *itr << " " << numMismatchesSoFar << " " << currentString << endl;
        }
        currentString.clear();
    }
    if (!atLeastOneMatch) {
        // zero matches overall so no match
        cout << "No Match" << endl;
    }
}

// getting list of positions
void findQuerySeeds(const genome_hashmap<hash_string_obj>& genome, const vector<pair<unsigned int, string>>& queries, unsigned int kmer_length, const string& genome_characters) {
    list<int> queryResults;
    for (unsigned int i = 0; i < queries.size(); i++) {
        // O(k + L + p)
        // getting list of positions for each query
        // O(k + p)
        queryResults = genome.find(queries[i].second, kmer_length);
        cout << "Query: " << queries[i].second << endl;
        // checking for matches using list of positions
        findQuerySequences(queries[i], queryResults, genome_characters);
        queryResults.clear();
    }
}

// extra credit version
// only underlying difference is that extra credit hash table uses list implementation of hash table
// usage logic still stands from vector implementation of hash table
void readGenomeFileEC(ifstream& genome_file, ec_hashmap<hash_string_obj>& genome, unsigned int kmer_length, string& genome_characters) {
    string genome_file_line;
    string kmer;
    while (genome_file >> genome_file_line) {
        genome_characters += genome_file_line;
    }
    for (unsigned int i = 0; i <= genome_characters.size() - kmer_length; i++) {
        // cout << "i value: " << i << endl;
        for (unsigned int j = i; j < i + kmer_length; j++) {
            kmer.push_back(genome_characters[j]);
        }
        genome.insert(kmer, i);
        kmer.clear();
    }
}

// extra credit version
// only underlying difference is that extra credit hash table uses list implementation of hash table
// usage logic still stands from vector implementation of hash table
void findQuerySeedsEC(const ec_hashmap<hash_string_obj>& genome, const vector<pair<unsigned int, string>>& queries, unsigned int kmer_length, const string& genome_characters) {
    list<int> queryResults;
    for (unsigned int i = 0; i < queries.size(); i++) {
        queryResults = genome.find(queries[i].second, kmer_length);
        cout << "Query: " << queries[i].second << endl;
        findQuerySequences(queries[i], queryResults, genome_characters);
        queryResults.clear();
    }
}

int main(int argc, const char * argv[]) {
    string extra_credit;
    string command;
    unsigned int init_size = 100;
    float LOAD_FRACTION = 0.5;
    string genome_file_name;
    unsigned int kmer_length;
    vector<pair<unsigned int, string>> queries;
    unsigned int mismatch_length;
    string query_sequence;
    string genome_characters;
    // error checking
    if (argc != 1 && argc != 2) {
        cerr << "Invalid number of arguments supplied" << endl;
        return 1;
    }
    if (argc == 2) {
        extra_credit = argv[1];
    }
    if (extra_credit != "" && extra_credit != string("extra_credit")) {
        cerr << "Invalid argument for extra credit option" << endl;
        return 1;
    }
    if (extra_credit == string("extra_credit")) {
        // using list implementation of hash table
        ec_hashmap<hash_string_obj> genome;
        while (cin >> command) {
            if (command == "genome") {
                cin >> genome_file_name;
            } else if (command == "table_size") {
                cin >> init_size;
            } else if (command == "occupancy") {
                cin >> LOAD_FRACTION;
            } else if (command == "kmer") {
                cin >> kmer_length;
                ifstream genome_file(genome_file_name);
                if (!genome_file.good()) {
                    cerr << "Unable to open and read genome file: " << genome_file_name << endl;
                }
                genome.updateConfigs(init_size, LOAD_FRACTION);
                // begin process of reading in genome characters from file
                readGenomeFileEC(genome_file, genome, kmer_length, genome_characters);
            } else if (command == "query") {
                cin >> mismatch_length;
                cin >> query_sequence;
                // keep track of queries and allowed mismatches
                queries.push_back(make_pair(mismatch_length, query_sequence));
                query_sequence = "";
            } else if (command == "quit") {
                // find the query seeds
                findQuerySeedsEC(genome, queries, kmer_length, genome_characters);
                break;
            } else {
                cerr << "ERROR: Unknown command: " << command << endl;
                return 1;
            }
        }
    } else {
        // using vector implementation of hash table
        genome_hashmap<hash_string_obj> genome;
        while (cin >> command) {
            if (command == "genome") {
                // O(1)
                cin >> genome_file_name;
            } else if (command == "table_size") {
                // O(1)
                cin >> init_size;
            } else if (command == "occupancy") {
                // O(1)
                cin >> LOAD_FRACTION;
            } else if (command == "kmer") {
                // O(1)
                cin >> kmer_length;
                ifstream genome_file(genome_file_name);
                if (!genome_file.good()) {
                    cerr << "Unable to open and read genome file: " << genome_file_name << endl;
                }
                // O(1)
                genome.updateConfigs(init_size, LOAD_FRACTION);
                // begin process of reading in genome characters from file
                readGenomeFile(genome_file, genome, kmer_length, genome_characters);
            } else if (command == "query") {
                cin >> mismatch_length;
                cin >> query_sequence;
                // keep track of queries and allowed mismatches
                queries.push_back(make_pair(mismatch_length, query_sequence));
                query_sequence = "";
            } else if (command == "quit") {
                // find the query seeds
                findQuerySeeds(genome, queries, kmer_length, genome_characters);
                break;
            } else {
                cerr << "ERROR: Unknown command: " << command << endl;
                return 1;
            }
        }
    }
    return 0;
}
