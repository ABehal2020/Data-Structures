#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// defined in performance.cpp
void usage();

// O(n*log(n))
template <class T>
void vector_sort(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
    // use the vector sort algorithm
    sort(vec.begin(),vec.end());
    output_count = vec.size();
    for (int i = 0; i < output_count; i++)
        ostr << vec[i] << "\n";
}

// O(n^2)
template <class T>
void vector_remove_duplicates(const std::vector<T> &vec, std::ostream &ostr, int &output_count) {
    // don't reorder the elements, just do all pairwise comparisons
    output_count = 0;
    for (int i = 0; i < (int)vec.size(); i++) {
        bool dup = false;
        for (int j = 0; j < i; j++) {
            if (vec[i] == vec[j]) {
                dup = true;
                break;
            }
        }
        // if it has not already been added to the output list
        if (!dup) {
            ostr << vec[i] << "\n";
            output_count++;
        }
    }
}

// O(n*log(n))
template <class T>
void vector_mode(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
    // use the vector sort algorithm
    // O(n*log(n))
    sort(vec.begin(),vec.end());
    int current_count = 1;
    T mode;
    int mode_count = 0;
    // keep track of two iterators into the structure
    typename std::vector<T>::iterator current = vec.begin();
    ++current;
    typename std::vector<T>::iterator previous = vec.begin();
    // O(n)
    for (; current != vec.end(); ++current, ++previous) {
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
    // save the mode to the output vector
    output_count = 1;
    ostr << mode << "\n";
}

// O(n*log(n))
// note: closest_pair is only available for integer data (not string data)
void vector_closest_pair(std::vector<int> &vec, std::ostream &ostr, int &output_count) {
    assert (vec.size() >= 2);
    // use the vector sort algorithm
    // O(n*log(n))
    sort(vec.begin(),vec.end());
    output_count = 2;
    int best;
    int best_index = -1;
    // the two elements with closest value must be next to each other in sorted order
    // O(n)
    for (unsigned int i = 0; i < vec.size()-1; i++) {
        int diff = vec[i+1]-vec[i];
        if (best_index == -1 || diff < best) {
            best = diff;
            best_index = i;
        }
    }
    // print the two elements
    output_count = 2;
    ostr << vec[best_index] << "\n";
    ostr << vec[best_index+1] << "\n";
}

// O(n*log(n) + f)
template <class T>
void vector_first_sorted(std::vector<T> &vec, std::ostream &ostr, int &output_count, int optional_arg) {
    assert (optional_arg >= 1);
    assert ((int)vec.size() >= optional_arg);
    // use the vector sort algorithm
    // O(n*log(n))
    sort(vec.begin(),vec.end());
    output_count = optional_arg;
    // O(f)
    for (int i = 0; i < output_count; i++) {
        ostr << vec[i] << "\n";
    }
}

// O(n*l)
bool find_substring(const vector<string>& vec, const string& search, const vector<string>::const_iterator& pos) {
    // O(n)
    // loop through strings
    for (typename vector<string>::const_iterator vec_itr = vec.begin(); vec_itr != vec.end(); vec_itr++) {
        if (vec_itr != pos && search.size() <= vec_itr->size()) {
            // O(l)
            // use find algorithm
            if (vec_itr->find(search) != -1) {
                return true;
            }
        }
    }
    return false;
}
// O(n^2*l^2) simplified from O(n*l*(l*n*l)) (n*l*(n*l + l*n*l + l)
// O(n*l*(n*l + l*n*l + l)) --> O(n^2*l^3)
// note: longest_substring is only available for string data (not integer data)
void vector_longest_substring(const std::vector<std::string> &vec, std::ostream &ostr, int &output_count) {
    string bestMatch;
    string search;
    // O(n)
    // nested for loops for vector and string elements
    for (typename vector<string>::const_iterator vec_itr = vec.begin(); vec_itr != vec.end(); vec_itr++) {
        // O(l)
        for (typename string::const_iterator str_itr = vec_itr->begin(); str_itr != vec_itr->end(); str_itr++) {
            // O(1)
            search.push_back(*str_itr);
            typename string::const_iterator str_itr_copy = str_itr;
            // O(n*l)
            // use this function to find longest substring
            if (find_substring(vec, search, vec_itr)) {
                if (search.size() >= bestMatch.size()) {
                    bestMatch = search;
                }
            }
            // O(l)
            // looping through remaining string
            for (typename string::const_iterator str_itr2 = ++str_itr_copy; str_itr2 != vec_itr->end(); str_itr2++) {
                // O(1)
                search.push_back(*str_itr2);
                // O(n*l)
                if (find_substring(vec, search, vec_itr)) {
                    if (search.size() >= bestMatch.size()) {
                        bestMatch = search;
                    }
                }
            }
            // O(l)
            search.clear();
        }
    }
    ostr << bestMatch << "\n";
}

void vector_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {
    if (type == "string") {
        // load the data into a vector of strings
        std::vector<std::string> vec;
        std::string s;
        input_count = 0;
        while (istr >> s) {
            vec.push_back(s);
            input_count++;
        }
        if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
        else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
        else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
        // "closest_pair" not available for strings
        else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
        else if (operation == "longest_substring") { vector_longest_substring (vec,ostr,output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    } else {
        assert (type == "integer");
        // load the data into a vector of integers
        std::vector<int> vec;
        int v;
        input_count = 0;
        while (istr >> v) {
            vec.push_back(v);
            input_count++;
        }
        if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
        else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
        else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
        else if (operation == "closest_pair")      { vector_closest_pair      (vec,ostr,output_count); }
        else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
        // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
}
