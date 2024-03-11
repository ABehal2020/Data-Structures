//
//  BPlusTree.hpp
//  hw8
//
//  Created by Aditya Behal on 4/4/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

/* ASSUMPTIONS:
 1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
 2. There will never be a duplicate key passed to insert.
 */

#ifndef BPlusTree_hpp
#define BPlusTree_hpp

#include <vector>
#include <iomanip>
#include <stdio.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
    BPlusTreeNode() : parent(NULL) {};
    bool is_leaf();
    bool contains(const T& key);
    
    //For grading only. This is bad practice to have, because
    //it exposes a private member variable.
    BPlusTreeNode* get_parent() { return parent; }
    
    //We need this to let BPlusTree access private members
    friend class BPlusTree<T>;
private:
    bool contains(const T& key,std::size_t low,std::size_t high);
    std::vector<T> keys;
    std::vector<BPlusTreeNode*> children;
    BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
    for(unsigned int i=0; i<children.size(); i++){
        if(children[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
    return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
    if(low>high){
        return false;
    }
    if(low==high){
        return key == keys[low];
    }
    std::size_t mid = (low+high)/2;
    if(key<=keys[mid]){
        return contains(key,0,mid);
    }
    else{
        return contains(key,mid+1,high);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
public:
    // default constructor
    BPlusTree(unsigned int bNumChildrenIn);
    // copy constructor
    BPlusTree(const BPlusTree<T>& old);
    // destructor
    ~BPlusTree() { this->destroy_tree(root); }
    // assignment operator
    BPlusTree& operator=(const BPlusTree<T>& old);
    // comparison operators
    bool operator==(const BPlusTree<T>& old) const;
    bool operator!=(const BPlusTree<T>& old) const;
    BPlusTreeNode<T>* find(const T& key_value) const;
    void insert(const T& key_value);
    // print methods for debugging
    void print_sideways(ofstream& outfile);
    void print_BFS(ofstream& outfile);
    void print_BFS_pretty(ofstream& outfile);
private:
    // private member variables (representation)
    BPlusTreeNode<T>* root;
    unsigned int b_num_children;
    // private helpder methods
    BPlusTreeNode<T>* find(const T& key_value, BPlusTreeNode<T>* p) const;
    void insertAtNode(const T& key_value, BPlusTreeNode<T>* p, BPlusTreeNode<T>* source = nullptr);
    void splitRootNode(BPlusTreeNode<T>* p);
    void splitLeafNode(BPlusTreeNode<T>*& p);
    void insertHelper(const T& key_value, BPlusTreeNode<T>* p);
    BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root);
    void destroy_tree(BPlusTreeNode<T>* p);
    void print_sideways_helper(ofstream& outfile, const BPlusTreeNode<T>* p, int depth) const;
};

// default constructor
template <class T>
BPlusTree<T>::BPlusTree(unsigned int bNumChildrenIn) {
    b_num_children = bNumChildrenIn;
    root = nullptr;
}

// copy constructor
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& old) {
    b_num_children = old.b_num_children;
    root = this->copy_tree(old.root);
}

// assignment operator
template <class T>
BPlusTree<T>& BPlusTree<T>::operator=(const BPlusTree<T>& old) {
    // check for self-assignment
    if (this != &old) {
        this->destroy_tree(root);
        root = this->copy_tree(old.root);
    }
    return *this;
}

// comparison operators are straightforward
template <class T>
bool BPlusTree<T>::operator==(const BPlusTree<T>& old) const {
    return (old.root = this->root);
}

// copmarison operators are straightforward
template <class T>
bool BPlusTree<T>::operator!=(const BPlusTree<T>& old) const {
    return (old.root != this->root);
}

// find method to locate where a key_value is
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key_value, BPlusTreeNode<T>* p) const {
    if (p == nullptr) {
        return nullptr;
    } else if (!p->is_leaf()) {
        // iterate through the keys and find the corresponding child to progress to leaf node
        for (unsigned int i = 0; i < p->keys.size(); i++) {
            if (key_value < p->keys[i]) {
                p = p->children[i];
                return find(key_value, p);
            }
        }
        p = p->children[p->keys.size()];
        return find(key_value, p);
    } else {
        // matches key_value or at least where it should be
        return p;
    }
}

// driver function for find method
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key_value) const {
    return find(key_value, root);
}

// insert at node private helper function
template <class T>
void BPlusTree<T>::insertAtNode(const T& key_value, BPlusTreeNode<T>* p, BPlusTreeNode<T>* source) {
    bool pWasNullPtr = false;
    if (p == nullptr) {
        // for cases where root must be split upwards
        p = new BPlusTreeNode<T>;
        p->children.push_back(nullptr);
        pWasNullPtr = true;
    }
    // insert key_value in sorted order (overflow if applicable gets handled later)
    for (typename vector<T>::iterator itr = p->keys.begin(); itr != p->keys.end(); itr++) {
        if (key_value < *itr) {
            p->keys.insert(itr, key_value);
            p->children.push_back(nullptr);
            return;
        }
    }
    p->keys.push_back(key_value);
    p->children.push_back(nullptr);
    if (pWasNullPtr) {
        // updating parent and children pointers appropraitely
        p->children[0] = source;
        source->parent = p;
        root = p;
    }
    return;
}

// splitting root node downwards for initial split
template <class T>
void BPlusTree<T>::splitRootNode(BPlusTreeNode<T>* p) {
    // getting boundaries for splitting the node
    unsigned int middleValueIndex = b_num_children/2;
    T middleValue = p->keys[middleValueIndex];
    // creating left and right child nodes with split values
    BPlusTreeNode<T>* leftChild = new BPlusTreeNode<T>;
    for (unsigned int i = 0; i < middleValueIndex; i++) {
        leftChild->keys.push_back(p->keys[i]);
    }
    leftChild->parent = p;
    for (unsigned int i = 0; i <= leftChild->keys.size(); i++) {
        leftChild->children.push_back(nullptr);
    }
    BPlusTreeNode<T>* rightChild = new BPlusTreeNode<T>;
    for (unsigned int i = middleValueIndex; i < p->keys.size(); i++) {
        rightChild->keys.push_back(p->keys[i]);
    }
    rightChild->parent = p;
    for (unsigned int i = 0; i <= rightChild->keys.size(); i++) {
        rightChild->children.push_back(nullptr);
    }
    // cleaning up parent node values (for find method help only)
    p->keys.clear();
    p->keys.push_back(middleValue);
    p->children.pop_back();
    int counter = 0;
    for (unsigned int i = 0; i < p->children.size(); i++) {
        if (p->children[i] == nullptr) {
            counter = i;
            break;
        }
    }
    // configuring parent node with newly created children
    p->children[counter] = leftChild;
    p->children[counter + 1] = rightChild;
}

// splitting leaf node
template <class T>
void BPlusTree<T>::splitLeafNode(BPlusTreeNode<T>*& p) {
    unsigned int middleValueIndex = b_num_children/2;
    T middleValue = p->keys[middleValueIndex];
    
    // insert in proper node and handle overflow later in this function if appropriate
    insertAtNode(middleValue, p->parent, p);
    
    vector<T> new_node_values = p->keys;
    
    typename vector<T>::iterator itrP = p->keys.begin();
    T comparisonValue = middleValue;

    // node p is the left child and right child created later on
    while (itrP != p->keys.end()) {
        if (*itrP >= comparisonValue) {
            itrP = p->keys.erase(itrP);
        } else {
            itrP++;
        }
    }
    
    // filtering out values for right child
    typename vector<T>::iterator itrNewNode = new_node_values.begin();
    if (p->is_leaf()) {
        while (itrNewNode != new_node_values.end()) {
            if (*itrNewNode < comparisonValue) {
                itrNewNode = new_node_values.erase(itrNewNode);
            } else {
                break;
            }
        }
    } else {
        while (itrNewNode != new_node_values.end()) {
            if (*itrNewNode <= comparisonValue) {
                itrNewNode = new_node_values.erase(itrNewNode);
            } else {
                break;
            }
        }
    }
    
    // initializing right child with correct values and children
    BPlusTreeNode<T>* rightChild = new BPlusTreeNode<T>;
    rightChild->keys = new_node_values;
    rightChild->parent = p->parent;
    for (unsigned int i = middleValueIndex + 1; i < p->children.size(); i++) {
        rightChild->children.push_back(p->children[i]);
    }
    
    vector<BPlusTreeNode<T>*> children_filtered;
    for (unsigned int i = 0; i <= middleValueIndex; i++) {
        children_filtered.push_back(p->children[i]);
    }
    p->children.clear();
    p->children = children_filtered;
    
    // inserting rightChild in sorted order in B+ tree
    unsigned int counter = 0;
    if (p->parent != nullptr) {
        bool prematureExit = false;
        for (unsigned int i = 0; i < p->parent->keys.size(); i++) {
            if (rightChild->keys[0] < p->parent->keys[i]) {
                counter = i;
                prematureExit = true;
                break;
            }
        }
        if (!prematureExit) {
            counter = p->parent->keys.size();
        }
        typename vector<BPlusTreeNode<T>*>::iterator itr = p->parent->children.begin() + counter;
        p->parent->children.insert(itr, rightChild);
    } else {
        BPlusTreeNode<T>* newParent = new BPlusTreeNode<T>;
        newParent->keys.push_back(comparisonValue);
        int counter = 0;
        for (unsigned int i = 0; i < newParent->children.size(); i++) {
            if (newParent->children[i] == nullptr) {
                counter = i;
                break;
            }
        }
    }
    
    // updating rightChild parent pointers from incorrect node p defaults
    if (!rightChild->is_leaf() && rightChild != nullptr && rightChild->children[0] != nullptr) {
        for (unsigned int i = 0; i < rightChild->children.size(); i++) {
            if (rightChild->children[i] != nullptr) {
                rightChild->children[i]->parent = rightChild;
            }
        }
    }
}

// insert private helper function
template <class T>
void BPlusTree<T>::insertHelper(const T& key_value, BPlusTreeNode<T>* p) {
    if (p == nullptr) {
        // handle root nullptr case
        p = new BPlusTreeNode<T>;
        p->keys.push_back(key_value);
        p->children.push_back(nullptr);
        p->children.push_back(nullptr);
        return;
    } else if (p->is_leaf() && p->keys.size() < b_num_children - 1) {
        // node does not overflow after insertion so we are done
        insertAtNode(key_value, p);
        return;
    } else if (p->is_leaf() && p->keys.size() == b_num_children - 1) {
        // node overflows after insertion so we split it
        insertAtNode(key_value, p);
        if (p == root) {
            splitRootNode(p);
        } else {
            splitLeafNode(p);
        }
        // recursively go up the B+ tree and split overflowing nodes
        while (p->parent != nullptr && p->parent->keys.size() == b_num_children) {
            splitLeafNode(p->parent);
            p = p->parent;
        }
        return;
    } else if (!p->is_leaf()) {
        // make sure to perform insertion only at leaf node so we recurse to bottom of tree
        bool insertedAlready = false;
        for (unsigned int i = 0; i < p->keys.size(); i++) {
            if (key_value < p->keys[i]) {
                p = p->children[i];
                insertHelper(key_value, p);
                insertedAlready = true;
                break;
            }
        }
        if (!insertedAlready) {
            p = p->children[p->keys.size()];
            insertHelper(key_value, p);
        }
    }
}

// insert main function
template <class T>
void BPlusTree<T>::insert(const T& key_value) {
    if (root == nullptr) {
        // handling base case of root == nullptr
        root = new BPlusTreeNode<T>;
        root->keys.push_back(key_value);
        root->children.push_back(nullptr);
        root->children.push_back(nullptr);
    } else {
        insertHelper(key_value, root);
    }
}

// print sideways function for debugging
template <class T>
void BPlusTree<T>::print_sideways_helper(ofstream& outfile, const BPlusTreeNode<T>* p, int depth) const {
    if (p != nullptr) {
        // in order traversal where left is from 0 to < middleValueIndex
        unsigned int middleValueIndex = (p->keys.size() + 1)/2;
        if (!p->children.empty() && p->children[0] != nullptr) {
            for (unsigned int i = 0; i < middleValueIndex; i++) {
                print_sideways_helper(outfile, p->children[i], depth + 1);
            }
        }
        // printing out node value itself
        for (unsigned int j = 0; j < depth; j++) {
            outfile << "\t";
        }
        outfile << p->keys[0];
        for (unsigned int k = 1; k < p->keys.size(); k++) {
            outfile << "," << p->keys[k];
        }
        outfile << endl;
        // right is from middleValueIndex to end
        if (!p->children.empty() && p->children[0] != nullptr) {
            for (unsigned int l = middleValueIndex; l < p->keys.size() + 1; l++) {
                print_sideways_helper(outfile, p->children[l], depth + 1);
            }
        }
    }
}

// print sideways driver function
template <class T>
void BPlusTree<T>::print_sideways(ofstream& outfile) {
    if (root == nullptr) {
        outfile << "Tree is empty." << endl;
    } else {
        print_sideways_helper(outfile, root, 0);
    }
}

// breadth first traversal
template <class T>
void BPlusTree<T>::print_BFS(ofstream& outfile) {
    if (root == nullptr) {
        outfile << "Tree is empty." << endl;
    } else {
        vector<BPlusTreeNode<T>*> current;
        vector<BPlusTreeNode<T>*> next;
        current.push_back(root);
        // we iterate each level at a time
        while (current.size() > 0) {
            for (unsigned int i = 0; i < current.size(); i++) {
                outfile << current[i]->keys[0];
                for (unsigned int j = 1; j < current[i]->keys.size(); j++) {
                    outfile << "," << current[i]->keys[j];
                }
                // get all nodes below current level into next vector
                if (!current[i]->is_leaf()) {
                    for (unsigned int k = 0; k <= current[i]->keys.size(); k++) {
                        next.push_back(current[i]->children[k]);
                    }
                }
                if (i < current.size() - 1) {
                    outfile << "\t";
                }
            }
            // going to next level of tree
            current = next;
            next.clear();
            outfile << endl;
        }
    }
}

// extra credit function
template <class T>
void BPlusTree<T>::print_BFS_pretty(ofstream& outfile) {
    if (root == nullptr) {
        outfile << "Tree is empty." << endl;
    } else {
        // vary tabs at each level to visualize children better
        unsigned int tabsNum = 5;
        vector<BPlusTreeNode<T>*> current;
        vector<BPlusTreeNode<T>*> next;
        current.push_back(root);
        // we iterate each level at a time
        while (current.size() > 0) {
            for (unsigned int i = 0; i < current.size(); i++) {
                for (unsigned int t = 0; t < tabsNum; t++) {
                    outfile << "\t";
                }
                outfile << current[i]->keys[0];
                for (unsigned int j = 1; j < current[i]->keys.size(); j++) {
                    outfile << "," << current[i]->keys[j];
                }
                // get all nodes below current level into next vector
                if (!current[i]->is_leaf()) {
                    for (unsigned int k = 0; k <= current[i]->keys.size(); k++) {
                        next.push_back(current[i]->children[k]);
                    }
                }
                if (i < current.size() - 1) {
                    outfile << "\t";
                }
            }
            // going to next level of tree
            current = next;
            next.clear();
            outfile << endl;
            // decreasing number of tabs at each level
            if (tabsNum > 2) {
                tabsNum -= 2;
            } else if (tabsNum == 1) {
                tabsNum--;
            }
        }
    }
}

// copy tree helper function
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root) {
    if (old_root == nullptr) {
        return nullptr;
    }
    // note that the copying mechanism is pre-order traversal
    BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>();
    newNode->keys = old_root->keys;
    newNode->children = old_root->children;
    newNode->parent = old_root->parent;
    // recursion to copy each child node as well
    for (unsigned int i = 0; i < old_root->children.size(); i++) {
        copy_tree(old_root->children[i]);
    }
    return newNode;
}

// destroy tree private helper function for destructor
template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p) {
    if (p == nullptr) {
        return;
    }
    // note that the destroying mechanism is post-order traversal
    for (unsigned int i = 0; i < p->children.size(); i++) {
        destroy_tree(p->children[i]);
    }
    delete p;
}

#endif
