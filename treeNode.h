//
//  treeNode.h
//  Project3SC
//
//  Created by Chad Cooper on 6/15/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef treeNode_h
#define treeNode_h

template <typename Type>
class TreeNode {
    
public:
    
    int key; // For the heap tree
    
    Type value; // Holds the data in the node. Can be used by all trees
    
    short balanceFactor; // for AVL tree. -1 for right high, 0 or even, 1 for left high
    
    int nodeHeight; // stores the height of the node from its deepest descdendant
    
    int nodeDepth; // stores how "deep" the node is from the root.
    
    TreeNode<Type> *parent, *left, *right; // pointers to related TreeNodes. Unused by heap tree
    
    // Constructor for all trees
    TreeNode(Type nodeValue = "", TreeNode<Type> * parentNode = nullptr) {
        
        // value is used by all trees
        value = nodeValue;
        
        // the node pointers are not used by the max heap tree
        parent = parentNode;
        left = nullptr;
        right = nullptr;
        
        // nodeHeight may be used by all trees
        nodeDepth = 0;
        nodeHeight = 0;
        
        
        
        // key is used only for the max heap tree
        key = 0;
        
        // balanceFactor is only used by the AVL tree
        balanceFactor = 0;
        
        
    }
    
    // Accessors
    
    int getKey() const {
        return key;
    }
    
    Type getValue() const {
        return value;
    }
    
    short getBalanceFactor() const {
        return balanceFactor;
    }
    
    TreeNode* getParent() const {
        return parent;
    }
    
    TreeNode* getLeft() const {
        return left;
    }
    
    TreeNode* getRight() const {
        return right;
    }
    
    int getNodeHeight() {
        return nodeHeight;
    }
    
    // tells whether the node is a leaf or not.
    bool isALeaf() const {
        if (left == nullptr && right == nullptr){
            return true;
        } else {
            return false;
        }
    }
    
    /*mutators*/
    
   	void setValue(Type nodeValue) {
        value = nodeValue;
   	}
    
   	void setKey(int heapKey) {
        key = heapKey;
   	}

    
};

#endif /* treeNode_h */
