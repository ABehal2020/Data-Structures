#include <cassert>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// defined in performance.cpp
void usage();

// O(n)
void hash_table_remove_duplicates(std::istream &istr, std::ostream &ostr, int &output_count, bool intFormat) {
    if (intFormat) {
        unordered_map<int,int> hash_table;
        int v;
        // O(n)
        while (istr >> v) {
            // O(1)
            // duplicate entries not allowed
            if (hash_table.insert(make_pair(v, 1)).second) {
                ostr << v << "\n";
            }
        }
        output_count = hash_table.size();
    } else {
        unordered_map<string,int> hash_table;
        string v;
        // O(n)
        while (istr >> v) {
            // O(1)
            // duplicate entries not allowed
            if (hash_table.insert(make_pair(v, 1)).second) {
                ostr << v << "\n";
            }
        }
        output_count = hash_table.size();
    }
}


// O(n)
template <class T>
void hash_table_mode(std::unordered_map<T,int>& hash_table, std::ostream &ostr, int &output_count) {
    typename unordered_map<T,int>::const_iterator mode_itr = hash_table.begin();
    // O(n)
    // use key-value pair association and find max value and its associated key for the mode
    for (typename unordered_map<T,int>::const_iterator itr = hash_table.begin(); itr != hash_table.end(); itr++) {
        if (itr->second > mode_itr->second) {
            mode_itr = itr;
        }
    }
    T mode = mode_itr->first;
    // save the mode to the output list
    output_count = 1;
    ostr << mode << "\n";
}

// note: closest_pair is only available for integer data (not string data)
void hash_table_closest_pair(std::unordered_map<int,int>& hash_table, std::ostream &ostr, int &output_count) {
    assert (hash_table.size() >= 2);
    output_count = 2;
    int best;
    typename unordered_map<int,int>::iterator best_index_itr = hash_table.end();
    typename unordered_map<int,int>::iterator best_index_itr_incremented = hash_table.end();
    typename unordered_map<int,int>::iterator itr = hash_table.begin();
    typename unordered_map<int,int>::iterator nextItr = hash_table.begin();
    bool sameNumber = false;
    // the two elements with closest value must be next to each other in sorted order
    // O(n)
    for ( ; itr != hash_table.end(); itr++) {
        if (itr->second > 1) {
            best_index_itr = itr;
            sameNumber = true;
            break;
        }
        typename unordered_map<int,int>::iterator itr_copy = itr;
        // O(n)
        // keep track of minimum distance with nested loops
        for (nextItr = ++itr_copy; nextItr != hash_table.end(); nextItr++) {
            int diff = nextItr->first - itr->first;
            if (best_index_itr == hash_table.end() || abs(diff) < abs(best)) {
                best = diff;
                best_index_itr = itr;
                best_index_itr_incremented = nextItr;
            }
        }
    }
    // print the two elements
    output_count = 2;
    if (sameNumber) {
        ostr << best_index_itr->first << "\n";
        ostr << best_index_itr->first << "\n";
    } else {
        ostr << best_index_itr->first << "\n";
        ostr << best_index_itr_incremented->first << "\n";
    }
}

// find matching substring using find algorithm
bool find_substring(const std::unordered_map<std::string,int>& bst, const string& search, const std::unordered_map<std::string,int>::const_iterator& pos) {
    for (typename unordered_map<std::string,int>::const_iterator bst_itr = bst.begin(); bst_itr != bst.end(); bst_itr++) {
        if (bst_itr != pos && search.size() <= bst_itr->first.size()) {
            if (bst_itr->first.find(search) != -1) {
                return true;
            }
        }
    }
    return false;
}

// note: longest_substring is only available for string data (not integer data)
void hash_table_longest_substring(const std::unordered_map<std::string,int>& bst, std::ostream &ostr, int &output_count) {
    string bestMatch;
    string search;
    // vector and string elements --> use nested for loops to traverse them
    for (typename unordered_map<string,int>::const_iterator map_itr = bst.begin(); map_itr != bst.end(); map_itr++) {
        for (typename string::const_iterator str_itr = map_itr->first.begin(); str_itr != map_itr->first.end(); str_itr++) {
            search.push_back(*str_itr);
            typename string::const_iterator str_itr_copy = str_itr;
            // find matching substring
            if (find_substring(bst, search, map_itr)) {
                if (search.size() >= bestMatch.size()) {
                    bestMatch = search;
                }
            }
            // loop over remaining elements
            for (typename string::const_iterator str_itr2 = ++str_itr_copy; str_itr2 != map_itr->first.end(); str_itr2++) {
                search.push_back(*str_itr2);
                if (find_substring(bst, search, map_itr)) {
                    if (search.size() >= bestMatch.size()) {
                        bestMatch = search;
                    }
                }
            }
            search.clear();
        }
    }
    ostr << bestMatch << "\n";
}

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {
    if (type == "string") {
        // load the data into a hash map
        std::unordered_map<std::string,int> hash_table;
        std::string s;
        input_count = 0;
        if (operation != "remove_duplicates") {
            while (istr >> s) {
                hash_table[s]++;
                input_count++;
            }
        }
        if (operation == "remove_duplicates") { hash_table_remove_duplicates (istr,ostr,output_count,false); }
        else if (operation == "mode")              { hash_table_mode              (hash_table,ostr,output_count); }
        // "closest_pair" not available for strings
        else if (operation == "longest_substring") { hash_table_longest_substring (hash_table,ostr,output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    } else {
        assert (type == "integer");
        // load the data into a hash map
        std::unordered_map<int,int> hash_table;
        int v;
        input_count = 0;
        if (operation != "remove_duplicates") {
            while (istr >> v) {
                hash_table[v]++;
                input_count++;
            }
        }
        if (operation == "remove_duplicates") { hash_table_remove_duplicates (istr,ostr,output_count,true); }
        else if (operation == "mode")              { hash_table_mode              (hash_table,ostr,output_count); }
        else if (operation == "closest_pair")      { hash_table_closest_pair      (hash_table,ostr,output_count); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}

