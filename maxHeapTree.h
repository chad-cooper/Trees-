//  maxHeapTree.h
//  Project3SC
//
//  Created by Kin NG on 6/15/17.
//  Copyright 2017 Kin NG. All rights reserved.

#ifndef maxHeapTree_h
#define maxHeapTree_h

#include "treeNode.h"
#include <stdexcept>
#include <math.h>

using namespace std;

template <typename Type>

class MaxHeapTree {
    
private:
    
    TreeNode<Type>* array;					//Pointer to dynamic array of objects
    TreeNode<Type> heapNode;				//TreeNode object
    int count;								//Number of elements in the Heap.
    int initialSize; 						//The initial size of the array, int initialSize.
    int arraySize;         					//The current size of the array, int arraySize.
    
public:
    
    //Constructor
    
    MaxHeapTree(int n = 4) {
        
        if (n < 1) {
            array = new TreeNode<Type>[1];
            initialSize = 1;
            arraySize = 1;
            
        }
        else {
            
            array = new TreeNode<Type>[n];
            initialSize = n;
            arraySize = n;
            
        }
        
        count = 0;
    }
    
    //Destructor
    ~MaxHeapTree() {
        
        delete[] array;
    }
    
    /*Accessors*/
    
    /*Returns the root of the tree.*/
    void getMax() const {
        
        if (!empty()) {
            
            cout << "Heap Index: " << 0 << ". Key: " << array[0].getKey();
            cout << ". Value: " << array[0].getValue() << endl;
        }
        else
            throw underflow_error("The heap is empty.\n");
        
    }
    
    
    /*Returns number of elements in the tree.*/
    int getSize() const {
        
        return count;
    }
    
    /*Returns the current size of the array.*/
    int capacity() const {
        return arraySize;
    }
    
    /*Returns the height of the tree.*/
    int getHeight() const {
        
        if (!empty()) {
            
            int height;
            
            height = (int)log2(count);
            
            return height;
        }
        else
            throw underflow_error("The heap is empty.\n");
    }
    
    /*Returns true if the tree is empty, false otherwise.*/
    bool empty() const {
        
        return count == 0;
    }
    
    int leaves() const {
        
        int numLeaf;
        
        numLeaf = (int)ceil((double)count / 2);
        
        return numLeaf;
    }
    
    /*Prints the heap.*/
    void print() const {
        
        if (!empty()) {
            
            for (int i = 0; i < count; i++) {
                cout << "Heap Index: " << i << ". Key: " << array[i].getKey();
                cout << ". Value: " << array[i].getValue() << endl;
            }
        }
        else
            throw underflow_error("The heap is empty.\n");
    }
    
    /*Mutators*/
    
    /*Inserts data in the tree. This operation must satisfy the heap property.*/
    void insert(int mKey, Type const& data) {
        
        heapNode.setKey(mKey);
        heapNode.setValue(data);
        
        //Check if heap is full
        if (count == arraySize) {
            
            // construct new array twice the size of current array
            arraySize *= 2;
            
            TreeNode<Type> *replacementArray = nullptr;
            
            replacementArray = new TreeNode<Type>[arraySize];
            
            // copy contents of old array to new array
            for (int i = 0; i < count; i++) {
                replacementArray[i] = array[i];
            }
            
            // destroy old array
            delete[] array;
            
            // array now points to new array.
            array = replacementArray;
            
        }
        
        array[count] = heapNode;	//Store object in the array.
        siftUp(0, count);			//Perform siftUp operation to keep heap property.
        count++;
        
    }
    
    
    /*Auxiliary function for insert(key, data). If the value inserted has a larger
     key than its parent, then it moves up until it is no larger than the
     value above it.*/
    void siftUp(int low, int high) {
        
        TreeNode<Type> temp;
        
        int parent;
        
        if (high > low) {
            
            parent = (high - 1) / 2;
            
            if (array[parent].getKey() < array[high].getKey()) {
                
                temp = array[parent];
                array[parent] = array[high];
                array[high] = temp;
                
                //Maintain recursion until heap property is satisfied
                siftUp(low, parent);
            }
        }
    }
    
    
    /*Removes the entry specified by maximum key in the tree.
     This operation must satisfy the heap property.*/
    void delMax() {
        
        if (!empty()) {
            
            count--;
            
            array[0] = array[count]; //make last element in the maxheap be the first.
            
            siftDown(0, count - 1);
            
            //Check if heap is 1/4 full
            if (arraySize > initialSize && count == arraySize / 4) {
                
                // construct new array 1/2 the size of current array
                arraySize /= 2;
                
                TreeNode<Type> *replacementArray = nullptr;
                
                replacementArray = new TreeNode<Type>[arraySize];
                
                // copy contents of old array to new array
                for (int i = 0; i < count; i++) {
                    replacementArray[i] = array[i];
                }
                
                // destroy old array
                delete[] array;
                
                // array now points to new array.
                array = replacementArray;
            }
        }
        else
            throw underflow_error("The heap is empty.\n");
    }
    
    /*Auxiliary function for delMax(). It moves the key down the tree by successively 
     exchanging the key with the smaller of its two children. The operation continues until 
     the value reaches a position where it is less than both its children, or
     until it reaches a leaf.*/
    void siftDown(int low, int high) {
        
        int rChild = (2 * low) + 2;			//Right child of max key in the heap
        
        int lChild = (2 * low) + 1;			//Left child of max key in the heap
        
        int maxKey;							//Max key value
        
        if (lChild <= high) {
            
            if (lChild == high) {
                maxKey = lChild;
            }
            else {
                
                if (array[lChild].getKey() <= array[rChild].getKey())
                    maxKey = rChild;
                else
                    maxKey = lChild;
            }
            
            if (array[low].getKey() < array[maxKey].getKey()) {
                
                TreeNode<Type> temp;
                
                temp = array[low];
                array[low] = array[maxKey];
                array[maxKey] = temp;
                
                //Maintain recursion until heap property is satisfied
                siftDown(maxKey, high);		
            }
        }
    }
    
    /*Clear all the elements stored in the tree.*/
    void clear() {
        
        while (!empty()) {
            delMax();
        }
    }
    
};

#endif
