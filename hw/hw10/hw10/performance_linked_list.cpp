#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>

using namespace std;

// defined in performance.cpp
void usage();

// O(n*log(n))
template <class T>
void list_sort(std::list<T>& lst, std::ostream &ostr, int &output_count) {
    // use the list sort algorithm
    lst.sort();
    output_count = lst.size();
    for (typename list<T>::iterator itr = lst.begin(); itr != lst.end(); itr++) {
        ostr << *itr << "\n";
    }
}

// O(n^2)
template <class T>
void list_remove_duplicates(const std::list<T>& lst, std::ostream &ostr, int &output_count) {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    // O(n)
    for (typename list<T>::const_iterator itr1 = lst.begin(); itr1 != lst.end(); itr1++) {
        bool dup = false;
        // O(n)
        for (typename list<T>::const_iterator itr2 = lst.begin(); itr2 != itr1; itr2++) {
            if (*itr1 == *itr2) {
                dup = true;
                break;
            }
        }
        // if it has not already been added to the output list
        if (!dup) {
            ostr << *itr1 << "\n";
            output_count++;
        }
    }
}

// O(n*log(n))
template <class T>
void list_mode(std::list<T>& lst, std::ostream &ostr, int &output_count) {
    // use the list sort algorithm
    // O(n*log(n))
    lst.sort();
    int current_count = 1;
    T mode;
    int mode_count = 0;
    // keep track of two iterators into the structure
    typename std::list<T>::iterator current = lst.begin();
    ++current;
    typename std::list<T>::iterator previous = lst.begin();
    // O(n)
    for (; current != lst.end(); ++current, ++previous) {
        if (*current == *previous) {
            // if they are the same element increment the count
            current_count++;
        } else if (current_count >= mode_count) {
            // found a new mode!
            mode = *previous;
            mode_count = current_count;
            current_count = 1;
        } else {
            current_count = 1;
        }
    }
    if (current_count >= mode_count) {
        // last entry is a new mode!
        mode = *previous;
        mode_count = current_count;
    }
    // save the mode to the output list
    output_count = 1;
    ostr << mode << "\n";
}

// note: closest_pair is only available for integer data (not string data)
// O(n*log(n))
void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
    assert (lst.size() >= 2);
    // use the list sort algorithm
    // O(n*log(n))
    lst.sort();
    output_count = 2;
    int best;
    typename list<int>::iterator best_index_itr = lst.end();
    typename list<int>::iterator nextItr = ++lst.begin();
    // the two elements with closest value must be next to each other in sorted order
    // O(n)
    for (typename list<int>::iterator itr = lst.begin(); itr != --lst.end(); itr++) {
        int diff = *nextItr - *itr;
        if (best_index_itr == lst.end() || diff < best) {
            best = diff;
            best_index_itr = itr;
        }
        nextItr++;
    }
    // print the two elements
    output_count = 2;
    ostr << *best_index_itr << "\n";
    ostr << *(++best_index_itr) << "\n";
}

// O(n*log(n) + f)
template <class T>
void list_first_sorted(std::list<T>& lst, std::ostream &ostr, int &output_count, int optional_arg) {
    assert (optional_arg >= 1);
    assert ((int)lst.size() >= optional_arg);
    // use the list sort algorithm
    // O(n*log(n))
    lst.sort();
    output_count = optional_arg;
    typename list<T>::iterator itr = lst.begin();
    // O(f)
    for (int i = 0; i < output_count; i++) {
        ostr << *itr << "\n";
        itr++;
    }
}

// use find algorithm to check for substring
bool find_substring(const list<string>& lst, const string& search, const list<string>::const_iterator& pos) {
    for (typename list<string>::const_iterator lst_itr = lst.begin(); lst_itr != lst.end(); lst_itr++) {
        if (lst_itr != pos && search.size() <= lst_itr->size()) {
            if (lst_itr->find(search) != -1) {
                return true;
            }
        }
    }
    return false;
}

// note: longest_substring is only available for string data (not integer data)
void list_longest_substring(const std::list<std::string>& lst, std::ostream &ostr, int &output_count) {
    string bestMatch;
    string search;
    // nested for loops to traverse through string and vector elements
    for (typename list<string>::const_iterator lst_itr = lst.begin(); lst_itr != lst.end(); lst_itr++) {
        for (typename string::const_iterator str_itr = lst_itr->begin(); str_itr != lst_itr->end(); str_itr++) {
            search.push_back(*str_itr);
            typename string::const_iterator str_itr_copy = str_itr;
            // call find substring function to find matching substring
            if (find_substring(lst, search, lst_itr)) {
                if (search.size() >= bestMatch.size()) {
                    bestMatch = search;
                }
            }
            // loop through remaining string
            for (typename string::const_iterator str_itr2 = ++str_itr_copy; str_itr2 != lst_itr->end(); str_itr2++) {
                search.push_back(*str_itr2);
                if (find_substring(lst, search, lst_itr)) {
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


void list_test(const std::string &operation, const std::string &type,
               std::istream &istr, std::ostream &ostr,
               int &input_count, int &output_count, int optional_arg) {
    
    // HINT: For the string element type, declare your list like this:
    // std::list<std::string> lst;
    
    if (type == "string") {
        // load the data into a list of strings
        list<string> lst;
        std::string s;
        input_count = 0;
        while (istr >> s) {
            lst.push_back(s);
            input_count++;
        }
        if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
        else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
        else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
        else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
    
    else {
        assert (type == "integer");
        // load the data into a list of integers
        list<int> lst;
        int v;
        input_count = 0;
        while (istr >> v) {
            lst.push_back(v);
            input_count++;
        }
        if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
        else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
        else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
        else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
        else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
