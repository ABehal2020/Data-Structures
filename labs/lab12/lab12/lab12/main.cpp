#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// -------------------------------------------------------------
// helper functions for heap as a vector
int parent(int i) { return (i-1)/2; }
int left_child(int i) { return 2*i+1; }
int right_child(int i) { return 2*i+2; }
int last_non_leaf(int size) { return (size-2)/2; }


// -------------------------------------------------------------
// helper functions for printing & debugging
template <class T>
void print (std::vector<T> v, std::string s) {
    std::cout << s;
    for (unsigned int i = 0; i < v.size(); i++) {
        std::cout << " " << v[i];
    }
    std::cout << std::endl;
}


template <class T>
bool check_sorted(std::vector<T> &v) {
    bool answer = true;
    for (unsigned int i = 1; i < v.size(); i++) {
        // compare each element to its previous
        if (v[i] < v[i-1]) {
            std::cout << "WHOOPS! v[" << i << "]=" << v[i]
            << " < v[" << i-1 << "]=" << v[i-1] << std::endl;
            answer = false;
        }
    }
    return answer;
}


template <class T>
bool check_heap(std::vector<T> &heap) {
    bool answer = true;
    for (unsigned int i = 1; i < heap.size(); i++) {
        int p = parent(i);
        // compare each element to its parent in the heap as vector
        if (heap[i] < heap[p]) {
            std::cout << "WHOOPS! heap[" << i << "]=" << heap[i]
            << " < heap[" << p << "]=" << heap[p] << std::endl;
            answer = false;
        }
    }
    return answer;
}


// -------------------------------------------------------------
// we only need percolate down to implement heap sort!
template <class T>
void percolate_down(std::vector<T> &heap, int i ) {
    // if the element has at least one child, we must consider a swap
    while (left_child(i) < (int)heap.size()) {
        int child = left_child(i);
        int rchild = right_child(i);
        // find the smaller of the two children (if both exist)
        if (rchild < (int)heap.size() &&
            heap[rchild] < heap[child])
            child = rchild;
        // if the child is smaller, swap and keep looping
        if (heap[child] < heap[i]) {
            T tmp = heap[child];
            heap[child] = heap[i];
            heap[i] = tmp;
            i = child;
        } else {
            // otherwise we can stop
            break;
        }
    }
}


// -------------------------------------------------------------
// remove and return the smallest value in the heap
// O(log n) worst case
template <class T>
T pop_and_return(std::vector<T> &heap) {
    assert(heap.size() > 0);
    // return the first thing, at the top of the heap
    T answer = heap[0];
    heap[0] = heap.back();
    // put the last thing into the "hole" at the top,
    // then let it settle to where it belongs
    heap.pop_back();
    percolate_down(heap, 0);
    return answer;
}


// -------------------------------------------------------------
// take an unorganized vector and convert it into a heap
// this should run in O(n) time (where n is the size of the heap)
// you don't have to do swaps all the time and a lot of the time only 1 swap is needed rather than swaps traversing through the whole height of the tree
template <class T>
void heapify(std::vector<T> &heap) {
    
    
    // CHECKPOINT 1: IMPLEMENT THIS FUNCTION
    
    // Starting at the bottom levels, build small 3 element miniheaps,
    // then join two 3 element heaps those to form 7 element heaps, then
    // join two 7 element heaps, etc.
    
    // Empty or just 1 element
    if (heap.size() == 0 || heap.size() == 1) return;
    
    for (int i = last_non_leaf(heap.size()); i >= 0; i--) {
        percolate_down(heap, i);
    }
}

// -------------------------------------------------------------
template <class T>
void heap_sort( std::vector<T> & v ) {
    
    // First quickly build a heap of the unorganized data (in place).
    heapify(v);
    print (v,"after heapify ");
    assert(check_heap(v));
    
    
    // CHECKPOINT 2: FINISH THIS FUNCTION
    
    
    // Repeatedly remove the smallest item (storing it
    // somewhere... ) from the heap until the heap is empty.
    
    const unsigned int size = v.size();
    
    // First draft:  You can use a scratch vector.
    
    /*
    vector<T> scratch;
    // O(n log n) sorting method
    for (unsigned int i = 0; i < size; i++) {
        scratch.push_back(pop_and_return(v));
    }
    v = scratch;
    */
    
    // Second draft: What do you need to modify/rewrite so that you
    // don't need a scratch vector?
    
    // One by one extract an element from heap
    // Empty or just 1 element
    if (v.size() == 0 || v.size() == 1) return;
    
    // build a binary heap
    for (int i = size / 2 - 1; i >= 0; --i) {
        unsigned int parent = i;
        unsigned int child = parent * 2 + 1;
        while (child < size) {
            if (child + 1 < size && v[child] < v[child + 1]) child += 1;
            if (v[parent] < v[child]) {
                std::swap(v[parent], v[child]);
                parent = child;
                child = parent * 2 + 1;
            } else break;
        }
    }
    
    for (unsigned int i = size - 1; i > 0; --i) {
        std::swap(v[0], v[i]);
        
        unsigned int parent = 0;
        unsigned int child = parent * 2 + 1;
        while (child < i) {
            if (child + 1 < i && v[child] < v[child + 1]) child += 1;
            if (v[parent] < v[child]) {
                std::swap(v[parent], v[child]);
                parent = child;
                child = parent * 2 + 1;
            } else break;
        }
    }
    
    // When we're done, the vector should be sorted
    assert(check_sorted(v));
}


// -------------------------------------------------------------
int main() {
    
    // sort of random looking input
    std::vector<int> v;
    v.push_back(9);
    v.push_back(5);
    v.push_back(8);
    v.push_back(7);
    v.push_back(3);
    v.push_back(1);
    v.push_back(11);
    v.push_back(12);
    v.push_back(6);
    v.push_back(13);
    v.push_back(10);
    v.push_back(15);
    v.push_back(2);
    v.push_back(14);
    v.push_back(4);
    
    print (v,"before ");
    heap_sort( v );
    print (v,"after  ");
    assert (check_sorted(v));
    
    
    // reverse sorted input
    std::vector<char> v2;
    v2.push_back('O');
    v2.push_back('N');
    v2.push_back('M');
    v2.push_back('L');
    v2.push_back('K');
    v2.push_back('J');
    v2.push_back('I');
    v2.push_back('H');
    v2.push_back('G');
    v2.push_back('F');
    v2.push_back('E');
    v2.push_back('D');
    v2.push_back('C');
    v2.push_back('B');
    v2.push_back('A');
    
    print (v2,"before ");
    heap_sort( v2 );
    print (v2,"after  ");
    assert (check_sorted(v2));
    
    return 0;
}
