//
//  avlTree.h
//  Project3SC
//
//  Created by Chad Cooper on 6/15/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#ifndef avlTree_h
#define avlTree_h

#include "treeNode.h"
#include <stdio.h>
#include <stdexcept>


using namespace std;

template <typename Type>
class AVL {

private:
    
    TreeNode<Type> *root;
    
    // holds the number of elements in the tree
    int size;
    
    // holds the total height of the tree
    int height;
    
    // holds the number of leaves in the tree
    int numberOfLeaves;
    
    
    

public:
    
    // Constructor
    AVL(){
        root = nullptr;
        
        size = 0;
        
        height = 0;
        
        numberOfLeaves = 0;
        
    }
    
    // Destructor
    ~AVL(){
        clear();
    }
    
    // Accessors
    
    //returns the root of the tree's data.
    Type getRoot() throw (underflow_error) {
        if(!empty()){
            return root->value;
        } else {
            throw underflow_error("The tree is empty.\n");
        }
    }
    
    //returns number of elements in the tree.
    int getSize() {
        return size;
    }
    
    // returns the height of the tree.
    int getHeight() throw (underflow_error) {
        
        // does not return 0 if the tree is empty, since the height of the root is 0.
        if(!empty()){
            return height;
        } else {
            throw underflow_error("The tree is empty.\n");
        }
    }
    
    // returns the height of the node in the argument (from the root). The height from the root is = to the depth.
    int getHeight(TreeNode<Type> *selectedNode) {
        
        return selectedNode->nodeDepth;
    }
    
    // returns true if the tree is empty, false otherwise.
    bool empty() {
        return (root == nullptr);
    }
    
    
    // returns the number of leaves in the tree.
    int leaves(){
        // number of leaves is set to 0 before each call
        // in case rotations caused the number of leaves to change
        numberOfLeaves = 0;
        recTraversal(root, 'l');
        return numberOfLeaves;
    }
    
   
    
    
    
    
    
    // returns the number of siblings of the node in the argument.
    int siblings(TreeNode<Type> * selectedNode) {
        
        if(selectedNode == root){
            return 0;
        }
        
        TreeNode<Type> *parentNode = selectedNode->parent;
        
        if ((parentNode->left != nullptr) && (parentNode->right != nullptr)){
            return 1;
        } else {
            return 0;
        }
    }
    
    
    
    
    
    
    //returns a pointer to a node that holds the data in the argument.
    TreeNode<Type>* findNode(Type data) throw(underflow_error){
        
        TreeNode<Type> *node = root;
        
        while (node != nullptr){
            
            if (node->value == data) {
                return node;
            }
            
            if (data < node->value){
                node = node->left;
                
            } else {
                node = node->right;
                
            }
        }
        
        throw underflow_error("The data was not found in the tree.\n");
    }
    
    
    
    
    void preorder() throw (underflow_error) {
            recTraversal(root, 'e');
    }
    
    
    
    
    
    
    void inorder() throw(underflow_error){
            recTraversal(root, 'i');
    }
    
    
    
    
    
    
    void postorder() {
            recTraversal(root, 'o');
    }
    
    
    
    
    
    
    

    

    // Mutators
    
    // removes all the elements in the tree
    void clear() {
        while(!empty()){
            del(root->value);
        }
    }
    
   
    
    void insert(Type data){
        try {
            // tests to see if the data is in the tree. If not present, findNode throws an error, which insert catches
            findNode(data);
            cout << "The data already exists in this tree.\n";
        }
        
        catch (const exception &e){
            
            // Size is increased
            size++;
            
            // If the tree is empty, the root is set.
            if(!empty()){
                insert(data, root);
            } else {
                root = new TreeNode<Type>(data);
            }
            
            // Height is adjusted for all nodes,
            // and the balance factors are checked.
            setHeight(root);
            balanceNode(root);
            
        }
    }
    
    // This function is called when there is already a root.
    void insert(Type data, TreeNode<Type> *node) {
        
        // insert into left subtree
        if(data < node->value){
            if (node->left != nullptr){
                insert(data, node->left);
            } else {
                node->left = new TreeNode<Type>(data, node);
            }
            // the node's depth is set.
            setDepth(node->left);
        } else {
            if (node->right != nullptr) {
                insert(data, node->right);
            } else {
                node->right = new TreeNode<Type>(data, node);
            }
            setDepth(node->right);
        }
    }
    
    
    

    // removes data from the tree.
    void del(Type data) throw(underflow_error){
        try {
            
            TreeNode<Type> * targetNode = findNode(data);
            
            // if node is external, delete it
            if(targetNode->isALeaf()){
                if(targetNode == root) {
                    root = nullptr;
                }
                
                // if the targetNode is the left child
                else if(targetNode->parent->left == targetNode){
                    targetNode->parent->left = nullptr;
                } else {
                    targetNode->parent->right = nullptr;
                }
                
                delete targetNode;
                targetNode = nullptr; // resolves dangling pointer
                
            } else {
            
                // if node has left and right children
                if(targetNode->left != nullptr && targetNode->right != nullptr){
                    
                    // find the greatest value of the left subtree
                    TreeNode<Type> *greatestNode = targetNode->left;
                    
                    while (greatestNode->right != nullptr){
                        greatestNode = greatestNode->right;
                    }
                    
                    // if there are no right children in left subtree
                    if(greatestNode == targetNode->left){
                        
                        // if there is only one node in the left subtree
                        if(greatestNode->left == nullptr){
                            targetNode->left = nullptr;
                        }
                        // the left subtree has left children
                        else {
                            greatestNode->left->parent = greatestNode->parent;
                            targetNode->left = greatestNode->left;
                        }
                    }
                    // disconnect the node from its parent, so that it can be deleted
                    else {
                        greatestNode->parent->right = nullptr;
                    }
                    
                    // replace the targetNode's value with it's greatest left grandchild.
                    Type replacementValue = greatestNode->value;
                    targetNode->value = replacementValue;
                    
                    delete greatestNode;
                    greatestNode = nullptr;
                    
                }
                
                // target only has one child
                else {
                    
                    // the child is left
                    if(targetNode->left != nullptr) {
                        if(targetNode == root){
                            root = targetNode->left;
                            targetNode->left->parent = nullptr;
                        }
                        // if the target node is the left child
                        else if(targetNode->parent->left == targetNode){
                            targetNode->left->parent = targetNode->parent;
                            targetNode->parent->left = targetNode->left;
                        } else {
                            targetNode->left->parent = targetNode->parent;
                            targetNode->parent->right = targetNode->left;
                        }
                    }
            
                    // target only has a right child
                    else {
                        if(targetNode == root) {
                            root = targetNode->right;
                            targetNode->right->parent = nullptr;
                        }
                        // if the target node is the left child
                        else if(targetNode->parent->left == targetNode){
                            targetNode->right->parent = targetNode->parent;
                            targetNode->parent->left = targetNode->right;
                        } else {
                            targetNode->right->parent = targetNode->parent;
                            targetNode->parent->right = targetNode->right;
                        }
                    }
                
                    delete targetNode;
                    targetNode = nullptr;
                }
            }
            
            // decrease the size
            size--;
            
            //adjust the node heights
            setHeight(root);
            
            // adjust the node depths
            recTraversal(root, 'd');
            //setDepthForAll(root);
            
            // adjust the node balance factors and perform rotations if necessary
            balanceNode(root);
            
        }
            
        catch (const exception& e){
            cout << e.what();
        }
        
    }
    
    
    
    
    
    // Auxiliary Functions
            
    // Traverses the tree and will execute different functions depending on the code passed
    void recTraversal(TreeNode<Type> *node, const char &code){
        
        if(node == nullptr){
            return;
        }
        
        // counts leaves
        if (code == 'l'){
            if(node->isALeaf()){
                numberOfLeaves++;
                return;
            }
        }
        
        // sets depths for all nodes, in case of rotations
        if (code == 'd'){
            setDepth(node);
        }
        
        // preorder output
        if(code == 'e'){
            
            if(is_same<Type, string>::value){
                cout << "\"";
            }
            
            cout << node->value;// << " ";
            
            if(is_same<Type, string>::value){
                cout << "\"";
            }
            
            cout << " ";
            
        }
        
        recTraversal(node->left, code);
        
        // inorder output
        if(code == 'i'){
            
            if(is_same<Type, string>::value){
                cout << "\"";
            }
            
            cout << node->value;// << " ";
            
            if(is_same<Type, string>::value){
                cout << "\"";
            }
            
            cout << " ";
            
            //cout << node->value << " ";
        }
        
        recTraversal(node->right, code);
        
        // postorder output
        if(code == 'o'){
            if(is_same<Type, string>::value){
                cout << "\"";
            }
            
            cout << node->value;// << " ";
            
            if(is_same<Type, string>::value){
                cout << "\"";
            }
            
            cout << " ";
            //cout << node->value << " ";
        }
        
    }
            
    // returns the depth of the node that was passed.
    int setDepth(TreeNode<Type> *node) {
        if (node->parent == nullptr){
            root->nodeDepth = 0;
            return 0; // root has depth 0
        }
        else {
            
            int d = 0;
            
            d = setDepth(node->parent);
            
            // depth is set to 1 more than its parent's depth
            node->nodeDepth = 1 + d;
            
            return 1 + d;
            
        }
    }

    
    void balanceNode(TreeNode<Type> *node){
        
        // If the node is NULL, return
        if(node == nullptr){
            return;
        }
        
        // if the node is a leaf, its balance factor is 0
        if(node->isALeaf()){
            node->balanceFactor = 0;
            return;
        }
        
        // set the balance factors of the children before the current node
        balanceNode(node->left);
        balanceNode(node->right);
        
        int nodeLeft = -1;
        int nodeRight = -1;
        
        
        if(node->left != nullptr){
            nodeLeft = node->left->nodeHeight;
        }
        if(node->right != nullptr){
            nodeRight = node->right->nodeHeight;
        }
        
        
        
        // the balance factor is the difference between the left and right children's heights.
        node->balanceFactor = nodeLeft - nodeRight;
        
        if(node->balanceFactor > 1 || node->balanceFactor < -1){
            determineRotation(node);
            balanceNode(root);
        }
        
        
        
    }
    
    
    void determineRotation(TreeNode<Type> *node) {
    
        // Node is left high and must be balanced.
        if(node->balanceFactor > 1){
        
            // single right rotation
            if(node->left->balanceFactor > 0){
                singleRightRotation(node);
            }
            // double right rotation
            else if(node->left->balanceFactor < 0){
                doubleRightRotation(node);
            }
        }
        // Node is right high and must be balanced.
        else if (node->balanceFactor < -1){
            
            // single left rotation;
            if (node->right->balanceFactor < 0){
                singleLeftRotation(node);
            }
            // double left rotation;
            else if (node->right->balanceFactor > 0) {
                doubleLeftRotation(node);
                
            }
        }
        
        // adjusts the heights and depths of nodes after rotations
        setHeight(root);
        recTraversal(root, 'd');
    }
    
    
    void singleRightRotation(TreeNode<Type> * node){
        TreeNode<Type> *tempPtr = node->left;
        
        // Sets the nodes left pointer to the temp->right
        // and if temp->right != NULL, its parent is set to the node
        node->left = tempPtr->right;
        if(tempPtr->right != nullptr){
            tempPtr->right->parent = node;
        }
        
        // Sets the temp as the nodes parent,
        // and the nodes parent points to temp
        tempPtr->right = node;
        tempPtr->parent = node->parent;
        
        if (node->parent != nullptr){
            if(node->parent->right == node){
                node->parent->right = tempPtr;
            } else if(node->parent->left == node){
                node->parent->left = tempPtr;
            }
        } else {
            root = tempPtr;
        }
        
        node->parent = tempPtr;
        
    }
    
    void doubleRightRotation(TreeNode<Type> * node){
        TreeNode<Type> *j, *k, *i;
        j = node;
        k = node->left;
        i = node->left->right;
        
        // first rotation
        
        // linking k and i's left child, if it exists
        if(i->left != nullptr){
            k->right = i->left;
            i->left->parent = k;
        } else {
            k->right = nullptr;
        }
        
        // linking i to k
        i->left = k;
        k->parent = i;
        
        // linking j to i
        j->left = i;
        i->parent = j;
        
        // second rotation
        
        // linking j and i's right child, if it exists
        if(i->right != nullptr){
            i->right->parent = j;
            j->left = i->right;
        } else {
            j->left = nullptr;
        }
        
        // linking i to j's parent
        i->parent = j->parent;
        
        // linking j's parent's left or right pointer to i.
        if(j->parent != nullptr){
            if(j->parent->right == j){
                j->parent->right = i;
            }
            if(j->parent->left == j){
                j->parent->left = i;
            }
        } else {
            root = i;
        }
        
        // linking i and j
        j->parent = i;
        i->right = j;
        
    }
    
    void singleLeftRotation(TreeNode<Type> * node){
        TreeNode<Type> *tempPtr = node->right;
        
        node->right = tempPtr->left;
        if(tempPtr->left != nullptr){
            tempPtr->left->parent = node;
        }
        
        tempPtr->left = node;
        tempPtr->parent = node->parent;
        
        if (node->parent != nullptr){
            if(node->parent->right == node){
                node->parent->right = tempPtr;
            } else if(node->parent->left == node){
                node->parent->left = tempPtr;
            }
        } else {
            root = tempPtr;
        }
       
        node->parent = tempPtr;
    }
    
    void doubleLeftRotation(TreeNode<Type> * node){
        TreeNode<Type> *j, *k, *i;
        j = node;
        k = node->right;
        i = node->right->left;
        
        // first rotation
        
        // linking k and i's left child, if it exists
        if(i->right != nullptr){
            k->left = i->right;
            i->right->parent = k;
        } else {
            k->left = nullptr;
        }
        
        // linking i to k
        i->right = k;
        k->parent = i;
        
        // linking j to i
        j->right = i;
        i->parent = j;
        
        // second rotation
        
        // linking j and i's right child, if it exists
        if(i->left != nullptr){
            i->left->parent = j;
            j->right = i->left;
        } else {
            j->right = nullptr;
        }
        
        // linking i to j's parent
        i->parent = j->parent;
        
        // linking j's parent's left or right pointer to i.
        if(j->parent != nullptr){
            if(j->parent->right == j){
                j->parent->right = i;
            }
            if(j->parent->left == j){
                j->parent->left = i;
            }
        } else {
            root = i;
        }
        
        // linking i and j
        j->parent = i;
        i->left = j;
    }
    
    
    int setHeight(TreeNode<Type> *node) {
        if ((node == nullptr) || (node->isALeaf())) {
            
            // leaves have a height of 0
            if(node != nullptr){
                node->nodeHeight = 0;
            }
            return 0;
        }
        
        int h = 0;
        
        // height is 1 more than the max height of its children.
        h = max(setHeight(node->left), setHeight(node->right));

        node->nodeHeight = 1 + h;
        
        // updates height to be equal to the root's height;
        if (node == root){
            height = node->nodeHeight;
        }
        
        return 1 + h; // 1 + max height of children
    }

    // Returns the maximum of two integers.
    int max(int a, int b){
        return ((a>=b)?a:b);
    }
    
};

#endif /* avlTree_h */
