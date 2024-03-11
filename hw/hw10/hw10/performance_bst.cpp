#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

// defined in performance.cpp
void usage();

// O(1)
template <class T>
void bst_sort(std::map<T,int>& bst, std::ostream &ostr, int &output_count) {
    // bst is already sorted due to operator<
    for (typename map<T,int>::iterator itr = bst.begin(); itr != bst.end(); itr++) {
        for (int i = 0; i < itr->second; i++) {
            ostr << itr->first << "\n";
        }
    }
}

// O(n*log(n))
void bst_remove_duplicates(std::istream &istr, std::ostream &ostr, int &output_count, bool intFormat) {
    if (intFormat) {
        map<int,int> bst;
        int v;
        // O(n)
        while (istr >> v) {
            // O(log n)
            // if it can't be inserted, it's a duplicate
            if (bst.insert(make_pair(v, 1)).second) {
                ostr << v << "\n";
            }
        }
        output_count = bst.size();
    } else {
        map<string,int> bst;
        string v;
        while (istr >> v) {
            // if it can't be inserted it's a duplicate
            if (bst.insert(make_pair(v, 1)).second) {
                ostr << v << "\n";
            }
        }
        output_count = bst.size();
    }
}

// O(n*log(n))
template <class T>
void bst_mode(std::map<T,int>& bst, std::ostream &ostr, int &output_count) {
    typename map<T,int>::const_iterator mode_itr = bst.begin();
    // O(n*log(n))
    // loop through and check the values (integers) and retain the greatest one and its associated key
    for (typename map<T,int>::const_iterator itr = bst.begin(); itr != bst.end(); itr++) {
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
// O(n)
void bst_closest_pair(std::map<int,int>& bst, std::ostream &ostr, int &output_count) {
    assert (bst.size() >= 2);
    output_count = 2;
    int best;
    typename map<int,int>::iterator best_index_itr = bst.end();
    typename map<int,int>::iterator nextItr = ++bst.begin();
    bool sameNumber = false;
    // the two elements with closest value must be next to each other in sorted order
    // O(n)
    for (typename map<int,int>::iterator itr = bst.begin(); itr != --bst.end(); itr++) {
        if (itr->second > 1) {
            best_index_itr = itr;
            sameNumber = true;
            break;
        }
        // keep track of minimum gap between consecutive entries
        int diff = nextItr->first - itr->first;
        if (best_index_itr == bst.end() || diff < best) {
            best = diff;
            best_index_itr = itr;
        }
        nextItr++;
    }
    if (nextItr->second > 1) {
        best_index_itr = nextItr;
        sameNumber = true;
    }
    // print the two elements
    output_count = 2;
    if (sameNumber) {
        ostr << best_index_itr->first << "\n";
        ostr << best_index_itr->first << "\n";
    } else {
        ostr << best_index_itr->first << "\n";
        ostr << (++best_index_itr)->first << "\n";
    }
}

// O(f)
template <class T>
void bst_first_sorted(std::map<T,int>& bst, std::ostream &ostr, int &output_count, int optional_arg) {
    assert (optional_arg >= 1);
    assert ((int)bst.size() >= optional_arg);
    output_count = optional_arg;
    typename map<T,int>::iterator itr = bst.begin();
    int i = 0;
    // O(f)
    // already sorted so  we loop through f times
    while (i < output_count) {
        for (int j = 0; j < itr->second; j++) {
            if (i >= output_count) {
                break;
            }
            ostr << itr->first << "\n";
            i++;
        }
        itr++;
    }
}

// use find algorithm to find substring
bool find_substring(const std::map<std::string,int>& bst, const string& search, const std::map<std::string,int>::const_iterator& pos) {
    for (typename map<std::string,int>::const_iterator bst_itr = bst.begin(); bst_itr != bst.end(); bst_itr++) {
        if (bst_itr != pos && search.size() <= bst_itr->first.size()) {
            if (bst_itr->first.find(search) != -1) {
                return true;
            }
        }
    }
    return false;
}

// note: longest_substring is only available for string data (not integer data)
void bst_longest_substring(const std::map<std::string,int>& bst, std::ostream &ostr, int &output_count) {
    string bestMatch;
    string search;
    // loop through vectors and strings
    for (typename map<string,int>::const_iterator map_itr = bst.begin(); map_itr != bst.end(); map_itr++) {
        for (typename string::const_iterator str_itr = map_itr->first.begin(); str_itr != map_itr->first.end(); str_itr++) {
            search.push_back(*str_itr);
            typename string::const_iterator str_itr_copy = str_itr;
            // call find substring function
            if (find_substring(bst, search, map_itr)) {
                if (search.size() >= bestMatch.size()) {
                    bestMatch = search;
                }
            }
            // loop through remaining string
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


void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {
    if (type == "string") {
        // load the data into a map
        std::map<std::string,int> bst;
        std::string s;
        input_count = 0;
        if (operation != "remove_duplicates") {
            while (istr >> s) {
                bst[s]++;
                input_count++;
            }
        }
        if      (operation == "sort")              { bst_sort              (bst,ostr,output_count); }
        else if (operation == "remove_duplicates") { bst_remove_duplicates (istr,ostr,output_count,false); }
        else if (operation == "mode")              { bst_mode              (bst,ostr,output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted")      { bst_first_sorted      (bst,ostr,output_count,optional_arg); }
        else if (operation == "longest_substring") { bst_longest_substring (bst,ostr,output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    } else {
        assert (type == "integer");
        // load the data into a map
        std::map<int,int> bst;
        int v;
        input_count = 0;
        if (operation != "remove_duplicates") {
            while (istr >> v) {
                bst[v]++;
                input_count++;
            }
        }
        if      (operation == "sort")              { bst_sort              (bst,ostr,output_count); }
        else if (operation == "remove_duplicates") { bst_remove_duplicates (istr,ostr,output_count,true); }
        else if (operation == "mode")              { bst_mode              (bst,ostr,output_count); }
        else if (operation == "closest_pair")      { bst_closest_pair      (bst,ostr,output_count); }
        else if (operation == "first_sorted")      { bst_first_sorted      (bst,ostr,output_count,optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
