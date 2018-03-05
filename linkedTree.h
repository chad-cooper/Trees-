//  linkedTree.h
//  Project3SC
//
//  Created by Kin NG on 6/15/17.
//  Copyright 2017 Kin NG. All rights reserved.

#ifndef linkedTree_h
#define linkedTree_h

#include "treeNode.h"
#include <algorithm> //max function
#include <stdexcept>

using namespace std;

template <typename Type>
class LinkedTree {
    
private:
    
    TreeNode<Type> *root;
    int mSize;				//stores number of elements in the Tree
    
public:
    
    //constructor
    LinkedTree() {
        root = nullptr;
        mSize = 0;
    }
    
    //Destructor
    ~LinkedTree() {
        clear();
    }
    
    /*Accessors*/
    
    /*returns the root of the tree.*/
    Type getRoot() const {
        
        if (!empty()) {
            return root->value;
        }
        else
            throw underflow_error("The Tree is empty.\n");
    }
    
    /*returns number of elements in the tree.*/
    int getSize() const {
        return mSize;
    }
    
    /*returns the height of the three.*/
    int getHeight() const {
        if (!empty()) {
            return getRootHeight(root);
        }
        else
            throw underflow_error("The Tree is empty.\n");
    }
    
    //Auxiliary function for getHeight()
    int getRootHeight(TreeNode<Type> *node) const {
        if (node == NULL)
            return -1;
        
        return max(getRootHeight(node->left), getRootHeight(node->right)) + 1;
    }
    
    /* Returns the height of the node that was passed (from the root).*/
    int getHeight(TreeNode<Type> *node) {
        if (node->parent == nullptr) {
            root->nodeDepth = 0;
            return 0; // root has depth 0
        }
        else {
            
            int d = 0;
            
            d = getHeight(node->parent);
            
            // depth is set to 1 more than its parent's depth
            node->nodeDepth = 1 + d;
            
            return 1 + d;
            
        }
    }
    
    /*returns true if the tree is empty, false otherwise.*/
    bool empty() const {
        return mSize == 0;
    }
    
    /*returns the number of leaves in the tree.*/
    int leaves() const {
        return leaves(root);
    }
    
    //Auxiliary function of leaves()
    int leaves(TreeNode<Type> *node) const {
        if (node == NULL)
            return 0;
        else if (node->left == NULL && node->right == NULL)
            return 1;
        else
            return leaves(node->left) + leaves(node->right);
    }
    
    /*returns the number of siblings of the node in the argument.*/
    int siblings(TreeNode<Type> * selectedNode) {
        
        if (selectedNode == root) {
            return 0;
        }
        
        TreeNode<Type> *parentNode = selectedNode->parent;
        
        if ((parentNode->left != nullptr) && (parentNode->right != nullptr)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    
    /*returns a pointer to a node that holds the data in the argument.*/
    TreeNode<Type>* findNode(const Type& data) {
        
        TreeNode<Type>* locptr = root;
        
        while (locptr != NULL) {
            if (locptr->value == data)
                return locptr;
            else if (data < locptr->value)
                locptr = locptr->left;
            else
                locptr = locptr->right;
        }
        
        throw underflow_error("The data was not found in the tree.\n");
    }
    
    /*performs in order traversal.*/
    void inorder() const {
        
        if (!empty()) {
            
            return inorder(root);
        }
        else
            throw underflow_error("The Tree is empty.\n");
    }
    
    //Auxiliary function for inorder()
    void inorder(TreeNode<Type> *node) const {
        
        if (node == NULL)
            return;
        
        inorder(node->left);
        
        cout << node->value << " ";
        
        inorder(node->right);
    }
    
    /*performs preorder traversal.*/
    void preorder() const {
        
        if (!empty()) {
            
            return preorder(root);
        }
        else
            throw underflow_error("The Tree is empty.\n");
    }
    
    //Auxiliary function for preorder()
    void preorder(TreeNode<Type> *node) const {
        
        if (node == NULL)
            return;
        
        cout << node->value << " ";
        
        preorder(node->left);
        
        preorder(node->right);
    }
    
    /*performs postorder traversal.*/
    void postorder() const {
        
        if (!empty()) {
            
            return postorder(root);
        }
        else
            throw underflow_error("The Tree is empty.\n");
    }
    
    //Auxiliary function for postorder()
    void postorder(TreeNode<Type> *node) const {
        
        if (node == NULL)
            return;
        
        postorder(node->left);
        
        postorder(node->right);
        
        cout << node->value << " ";
    }
    
    /*Mutators*/
    
    /*inserts data in the tree.*/
    void insert(const Type& data) {
        
        TreeNode<Type>* locptr = root;
        TreeNode<Type>* parent = new TreeNode<Type>;
        
        parent = 0;
        
        bool found = false;
        
        //Makes sure that the data is not already in the tree
        while (!found && locptr != 0) {
            parent = locptr;
            if (data < locptr->value)
                locptr = locptr->left;
            else if (data > locptr->value)
                locptr = locptr->right;
            else
                found = true;
        }
        
        //if data is not in the tree, perform insertion
        if (!found) {
            locptr = new TreeNode<Type>(data, parent);
            
            if (parent == 0)
                root = locptr;
            else if (data < parent->value)
                parent->left = locptr;
            else
                parent->right = locptr;
            
            mSize++;
        }
        else
            cout << "Item already in the tree.\n";
    }
    
    /*removes data from the tree.*/
    void del(const Type& data) {
        if (!empty()) {
            del(root, data);
        }
        else
            throw underflow_error("The Tree is empty.\n");
    }
    
    //Auxialiary function for del()
    TreeNode<Type>* del(TreeNode<Type> *node, const Type& data) {
        
        //Find the location of the node to be deleted
        if (node == NULL) {
            cout << "Item is not in the Tree.\n";
            return node;
        }
        else if (data < node->value) {
            node->left = del(node->left, data);
        }
        else if (data > node->value) {
            node->right = del(node->right, data);
        }
        else {
            //No Child
            if (node->left == NULL && node->right == NULL) {
                if (node == root) {
                    root = nullptr;
                }
                delete node;
                mSize--;
                return NULL;
            }
            //One Children
            else if (node->left == NULL) {
                if (node == root) {
                    root = node->right;
                }
                TreeNode<Type>* delNode = node;
                node = node->right;
                delete delNode;
                mSize--;
                return node;
            }
            else if (node->right == NULL) {
                if (node == root) {
                    root = node->left;
                }
                TreeNode<Type>* delNode = node;
                node = node->left;
                delete delNode;
                mSize--;
                return node;
            }
            //Two Children
            else {
                
                TreeNode<Type>* delNode = findMax(node->left);
                node->value = delNode->value;
                node->left = del(node->left, delNode->value);
            }
        }
        
        return node;
    }
    
    //Auxiliary function to find the maximum value located at the left subtree
    TreeNode<Type>* findMax(TreeNode<Type> *node) {
        
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }
    
    
    /*removes all the elements in the tree*/
    void clear() {
        while (!empty()) {
            del(root->value);
        }
    }
    
};

#endif
