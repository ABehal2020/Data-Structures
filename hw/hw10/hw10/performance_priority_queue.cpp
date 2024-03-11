#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

// defined in performance.cpp
void usage();

// O(1)
template <class T>
void pq_sort(std::priority_queue<T,vector<T>, greater<T> >& pq, std::ostream &ostr, int &output_count) {
    // pq is already sorted since it's a min binary heap in this case
    output_count = pq.size();
    for (int i = 0; i < output_count; i++) {
        ostr << pq.top() << "\n";
        pq.pop();
    }
}

// O(n)
template <class T>
void pq_mode(std::priority_queue<T,vector<T>, greater<T> >& pq, std::ostream &ostr, int &output_count) {
    int current_count = 1;
    int mode_count = 0;
    T mode;
    T prev = pq.top();
    pq.pop();
    // keep track of current entry and previous entries only using int helper variables
    while (pq.size() != 0) {
        if (prev == pq.top()) {
            current_count++;
        } else if (current_count >= mode_count) {
            mode = prev;
            mode_count = current_count;
            current_count = 1;
        } else {
            current_count = 1;
        }
        prev = pq.top();
        pq.pop();
    }
    // last one can be mode as well
    if (current_count >= mode_count) {
        mode = prev;
        mode_count = current_count;
    }
    // save the mode to the output vector
    output_count = 1;
    ostr << mode << "\n";
}

// note: closest_pair is only available for integer data (not string data)
void pq_closest_pair(std::priority_queue<int,vector<int>, greater<int> >& pq, std::ostream &ostr, int &output_count) {
    assert(pq.size() >= 2);
    int num1 = pq.top();
    pq.pop();
    int num2 = pq.top();
    pq.pop();
    int best = num2 - num1;
    int prev = num2;
    int prevPrev;
    // O(n)
    // loop through whole pq
    while (pq.size() != 0) {
        int diff = pq.top() - prev;
        prevPrev = prev;
        prev = pq.top();
        // if new minimum is found, then new closest pair is found
        if (diff < best) {
            best = diff;
            num1 = prevPrev;
            num2 = pq.top();
        }
        pq.pop();
    }
    // print the two elements
    output_count = 2;
    ostr << num1 << endl;
    ostr << num2 << endl;
}

// O(f)
template <class T>
void pq_first_sorted(std::priority_queue<T,vector<T>, greater<T> >& pq, std::ostream &ostr, int &output_count, int optional_arg) {
    assert (optional_arg >= 1);
    assert ((int)pq.size() >= optional_arg);
    output_count = optional_arg;
    // O(f)
    // already sorted so we want f elements
    for (int i = 0; i < output_count; i++) {
        ostr << pq.top() << "\n";
        pq.pop();
    }
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {
    
    // HINT: For the string element type, declare your priority_queue like this:
    
    // std::priority_queue<std::string,std::vector<std::string> > pq;
    // (this will make a "max" priority queue, with big values at the top)
    
    // OR
    
    // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
    // (this will make a "min" priority queue, with big values at the bottom)
    
    if (type == "string") {
           // load the data into a priority queue
           std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
           std::string s;
           input_count = 0;
           while (istr >> s) {
               pq.push(s);
               input_count++;
           }
           if      (operation == "sort")              { pq_sort              (pq,ostr,output_count); }
           else if (operation == "mode")              { pq_mode              (pq,ostr,output_count); }
           // "closest_pair" not available for strings
           else if (operation == "first_sorted")      { pq_first_sorted      (pq,ostr,output_count,optional_arg); }
           else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
       } else {
           assert (type == "integer");
           // load the data into a priority queue
           std::priority_queue<int,std::vector<int>, std::greater<int> > pq;
           int v;
           input_count = 0;
           while (istr >> v) {
               pq.push(v);
               input_count++;
           }
           if      (operation == "sort")              { pq_sort              (pq,ostr,output_count); }
           else if (operation == "mode")              { pq_mode              (pq,ostr,output_count); }
           else if (operation == "closest_pair")      { pq_closest_pair      (pq,ostr,output_count); }
           else if (operation == "first_sorted")      { pq_first_sorted      (pq,ostr,output_count,optional_arg); }
           // "longest_substring" not available for integers
           else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
       }
}
