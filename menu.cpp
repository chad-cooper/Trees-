//
//  main.cpp
//  Project3SC
//
//  Created by Chad Cooper on 6/15/17.
//  Copyright © 2017 Chad Cooper. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include "treeNode.h"
#include "linkedTree.h"
#include "maxHeapTree.h"
#include "avlTree.h"



using namespace std;


int main() {
    
    int code;
   	char letter;
    clock_t start, stop;
    
    
    cout << "Enter 'g' for a general tree, 'h' for a max heap, or 'a' for an AVL tree: ";
   	cin >> letter;
    cout << endl;
    
   	switch (letter) {
            
            
        case 'g':
        {
            cout << "1. Return root\n"
            "2. Return size\n"
            "3. Return height\n"
            "4. Return height (node)\n"
            "5. Is tree empty?\n"
            "6. Return number of leaves\n"
            "7. Return number of siblings (node)\n"
            "8. Find node (data)\n"
            "9. Print preorder\n"
            "10. Print postorder\n"
            "11. Print inorder\n"
            "12. Clear tree\n"
            "13. Insert (data)\n"
            "14. Delete (data)\n"
            "15. Exit\n\n";
            
            
            
            
            LinkedTree<string> myLinkedTree;
            
            for (;;) {
                
                cout << "Enter operation code: ";
                cin >> code;
                
                
                
                switch (code) {
                        
                    case 1: // root value
                    {
                        try{
                            start = clock();
                            cout << myLinkedTree.getRoot();
                            stop = clock();
                        }
                        catch (exception &e){
                            stop = clock();
                            cout << e.what();
                        }
                       	break;
                    }
                    case 2: // size
                    {
                        start = clock();
                       	cout << "There are " <<  myLinkedTree.getSize() << " items in your tree." << endl;
                        stop = clock();
                       	break;
                    }
                    case 3: // height
                    {
                        try {
                            start = clock();
                            myLinkedTree.getHeight();
                            stop = clock();
                            
                            cout << "The height of the tree is: " << myLinkedTree.getHeight() << endl;
                        }
                        catch (exception &e){
                            stop = clock();
                            cout << e.what();
                        }
                       	break;
                    }
                    case 4: // height of a node
                    {
                        string data;
                        cout << "Enter data to identify which node you wish to know the height of: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try{
                            // This is called before necessary for output, so that only the exception prints if the data is not found.
                            myLinkedTree.findNode(data);
                            
                            start = clock();
                            cout << "The height of the node containing \"" << data << "\" is: "
                            << myLinkedTree.getHeight(myLinkedTree.findNode(data)) << endl;
                            stop = clock();
                            
                        }
                        catch (exception &e){
                            cout << e.what();
                        }
                        
                       	break;
                    }
                    case 5: // empty?
                    {
                        start = clock();
                        bool yes = myLinkedTree.empty();
                        stop = clock();
                        
                        cout << "The tree is " << (yes?"empty.\n":"not empty.\n") << endl;
                        
                       	break;
                    }
                    case 6: // number of  leaves
                    {
                        start = clock();
                        cout << "The tree has " << myLinkedTree.leaves() << " leaves.\n";
                        stop = clock();
                       	break;
                    }
                    case 7: // number of siblings of a node
                    {
                        string data;
                        cout << "Enter data to identify for which node you wish to know the number of siblings: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try{
                            // This is called before necessary for output, so that only the exception prints if the data is not found.
                            myLinkedTree.findNode(data);
                            
                            start = clock();
                            cout << "The node containing \"" << data << "\" has "
                            << myLinkedTree.siblings(myLinkedTree.findNode(data)) << " sibling(s).\n";
                            stop = clock();
                        }
                        catch (exception &e){
                            cout << e.what();
                        }
                        
                       	break;
                    }
                    case 8: // Find node, with data
                    {
                        string data;
                        cout << "Enter the data for the node you wish to find: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try {
                            start = clock();
                            myLinkedTree.findNode(data);
                            stop = clock();
                            
                            
                            cout << "The node containing this data was found in the tree. It is located at memory space: " << myLinkedTree.findNode(data) << endl;
                        }
                        
                        catch (exception &e){
                            stop = clock();
                            cout << e.what();
                        }
                        
                       	break;
                    }
                    case 9: // print preorder
                    {
                        if(!myLinkedTree.empty()){
                            cout << "Printing the tree in preorder...\n";
                            
                            start = clock();
                            myLinkedTree.preorder();
                            stop = clock();
                            
                            
                        } else {
                            cout << "The tree is empty. There is nothing to print.\n";
                        }
                        
                        break;
                    }
                    case 10: // print postorder
                    {
                        if(!myLinkedTree.empty()){
                            cout << "Printing the tree in postorder...\n";
                            
                            start = clock();
                            myLinkedTree.postorder();
                            stop = clock();
                            
                        } else {
                            cout << "The tree is empty. There is nothing to print.\n";
                        }
                        
                        break;
                    }
                    case 11: // print inorder
                    {
                        if(!myLinkedTree.empty()){
                            cout << "Printing the tree in order...\n";
                            
                            start = clock();
                            myLinkedTree.inorder();
                            stop = clock();
                            
                        } else {
                            cout << "The tree is empty. There is nothing to print.\n";
                        }
                        
                        break;
                    }
                    case 12: // clear tree
                    {
                        start = clock();
                        myLinkedTree.clear();
                        stop = clock();
                        
                        cout << "The tree was cleared.\n";
                        
                        break;
                    }
                    case 13: // Insert data
                    {
               
                        string data;
                        
                        cout << "Enter data that you wish to insert into the tree: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        start = clock();
                        myLinkedTree.insert(data);
                        stop = clock();
                        
                        break;
                    }
                    case 14: // Delete data
                    {
                        string data;
                        
                        cout << "Enter data that you wish to delete from the tree: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try{
                            
                            start = clock();
                            myLinkedTree.del(data);
                            stop = clock();
                            
                            cout << "\"" << data << "\" was deleted from the tree.\n";
                        }
                        
                        catch (exception &e){
                            stop = clock();
                            cout << e.what();
                        }
                        
                        
                        break;
                    }
                    case 15: // Exit
                    {
                        cout << "Exit succesful." << endl;
                       	return 0;
                    }
                    default:
                    {
                        cout << "Invalid code." << endl;
                    }
                } // end of code-switch statement
                
                // cout << "\nTime: " << (stop - start)/double(CLOCKS_PER_SEC)*1000 << " ms.\n";
                cout << endl;
                
            } // end of for(;;) statement
            break;
        } // end of general tree
            
        case 'a':
        {
            
            cout << "1. Return root\n"
            "2. Return size\n"
            "3. Return height\n"
            "4. Return height (node)\n"
            "5. Is tree empty?\n"
            "6. Return number of leaves\n"
            "7. Return number of siblings (node)\n"
            "8. Find node (data)\n"
            "9. Print preorder\n"
            "10. Print postorder\n"
            "11. Print inorder\n"
            "12. Clear tree\n"
            "13. Insert (data)\n"
            "14. Delete (data)\n"
            "15. Exit\n\n";
            
            
            
            
            AVL<string> myAVL;
            
            for (;;) {
                
                cout << "Enter operation code: ";
                cin >> code;
                
                
                
                switch (code) {
                        
                    case 1: // root value
                    {
                        try{
                            start = clock();
                            cout << myAVL.getRoot();
                            stop = clock();
                            
                        }
                        catch (exception &e){
                            cout << e.what();
                        }
                       	break;
                    }
                    case 2: // size
                    {
                        start = clock();
                       	cout << "There are " <<  myAVL.getSize() << " items in your tree." << endl;
                        stop = clock();
                        
                       	break;
                    }
                    case 3: // height
                    {
                        try {
                            start = clock();
                            myAVL.getHeight();
                            stop = clock();
                            
                            cout << "The height of the tree is: " << myAVL.getHeight() << endl;
                        }
                        catch (exception &e){
                            cout << e.what();
                        }
                       	break;
                    }
                    case 4: // height of a node
                    {
                        string data;
                        cout << "Enter data to identify which node you wish to know the height of: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try{
                            // This is called before necessary for output, so that only the exception prints if the data is not found.
                            myAVL.findNode(data);
                            
                            start = clock();
                            cout << "The height of the node containing \"" << data << "\" is: "
                            << myAVL.getHeight(myAVL.findNode(data)) << endl;
                            stop = clock();
                        }
                        catch (exception &e){
                            cout << e.what();
                        }
                        
                       	break;
                    }
                    case 5: // empty?
                    {
                        start = clock();
                        bool yes = myAVL.empty();
                        stop = clock();
                        
                        cout << "The tree is " << (yes?"empty.\n":"not empty.\n") << endl;
                        
                       	break;
                    }
                    case 6: // number of  leaves
                    {
                        start = clock();
                        cout << "The tree has " << myAVL.leaves() << " leaves.\n";
                        stop = clock();
                       	break;
                    }
                    case 7: // number of siblings of a node
                    {
                        string data;
                        cout << "Enter data to identify for which node you wish to know the number of siblings: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try{
                            // This is called before necessary for output, so that only the exception prints if the data is not found.
                            myAVL.findNode(data);
                            
                            start = clock();
                            cout << "The node containing \"" << data << "\" has "
                            << myAVL.siblings(myAVL.findNode(data)) << " sibling(s).\n";
                            stop = clock();
                        }
                        catch (exception &e){
                            cout << e.what();
                        }

                       	break;
                    }
                    case 8: // Find node, with data
                    {
                        string data;
                        cout << "Enter the data for the node you wish to find: ";
                        
                        cin.ignore();
                        getline(cin, data);

                        try {
                            myAVL.findNode(data);
                            start = clock();
                            cout << "The node containing this data was found in the tree. It is located at memory space: " << myAVL.findNode(data) << endl;
                            stop = clock();
                        }
                        
                        catch (exception &e){
                            cout << e.what();
                        }
                        
                       	break;
                    }
                    case 9: // print preorder
                    {
                        if(!myAVL.empty()){
                            cout << "Printing the tree in preorder...\n";
                            
                            start = clock();
                            myAVL.preorder();
                            stop = clock();
                            
                        } else {
                            cout << "The tree is empty. There is nothing to print.\n";
                        }
                        
                        break;
                    }
                    case 10: // print postorder
                    {
                        if(!myAVL.empty()){
                            cout << "Printing the tree in postorder...\n";
                            
                            start = clock();
                            myAVL.postorder();
                            stop = clock();
                            
                        } else {
                            cout << "The tree is empty. There is nothing to print.\n";
                        }
                        
                        break;
                    }
                    case 11: // print inorder
                    {
                        if(!myAVL.empty()){
                            cout << "Printing the tree in order...\n";
                        
                            start = clock();
                            myAVL.inorder();
                            stop = clock();
                            
                        } else {
                            cout << "The tree is empty. There is nothing to print.\n";
                        }
                        
                        break;
                    }
                    case 12: // clear tree
                    {
                        start = clock();
                        myAVL.clear();
                        stop = clock();
    
                        cout << "The tree was cleared\n";
                        
                        break;
                    }
                    case 13: // Insert data
                    {
                        string data;
                        
                        cout << "Enter data that you wish to insert into the tree: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        start = clock();
                        myAVL.insert(data);
                        stop = clock();
                        
                        break;
                    }
                    case 14: // Delete data
                    {
                        string data;
                        
                        cout << "Enter data that you wish to delete from the tree: ";
                        
                        cin.ignore();
                        getline(cin, data);
                        
                        try{
                            start = clock();
                            myAVL.del(data);
                            stop = clock();
                        
                            cout << "\"" << data << "\" was deleted from the tree.\n";
                        }
                        
                        catch (exception &e){
                            stop = clock();
                            cout << e.what();
                        }

                        
                        break;
                    }
                    case 15: // Exit
                    {
                        cout << "Exit succesful." << endl;
                       	return 0;
                    }
                    default:
                    {
                        cout << "Invalid code." << endl;
                    }
                } // end of code-switch statement
                
                //cout << "\nTime: " << (stop - start)/double(CLOCKS_PER_SEC)*1000 << " ms.\n";
                
                cout << endl;
                
            } // end of for(;;) statement
            break;
            
        } // end of AVL tree
        
        case 'h':
        {
            //int code;
            int initSize = 1;
            
            bool incorrectInput = true;
            
            while (incorrectInput) {
                cout << "Enter the initial size of the heap: ";
                cin >> initSize;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid size.\n";
                }
                else {
                    incorrectInput = false;
                }
            }
            
            
            cout << "1. Return root\n"
            "2. Return size\n"
            "3. Return height\n"
            "4. Is tree empty?\n"
            "5. Return number of leaves\n"
            "6. Print\n"
            "7. Clear tree\n"
            "8. Insert (key, data)\n"
            "9. Delete\n"
            "10. Exit\n\n";
            
            
            
            MaxHeapTree<string> heap(initSize);
            
            for (;;) {
                cout << "Enter operation code: ";
                cin >> code;
                
                switch (code) {
                        
                    case 1:
                    {
                        try {
                            start = clock();
                            heap.getMax();
                            stop = clock();
                        }
                        catch (const exception& e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 2:
                    {
                        start = clock();
                        cout << "Number of items in the tree: " << heap.getSize() << endl;
                        stop = clock();
                        
                        break;
                    }
                    case 3:
                    {
                        try {
                            start = clock();
                            cout << "Height of the tree: " << heap.getHeight() << endl;
                            stop = clock();
                        }
                        catch (const exception& e) {
                            stop = clock();
                            cout << e.what();
                            
                        }
                        break;
                    }
                    case 4:
                    {
                        start = clock();
                        cout << "Is tree empty? true = 1, false = 0: " << heap.empty() << endl;
                        stop = clock();
                        break;
                    }
                    case 5:
                    {
                        start = clock();
                        cout << "Number of leaves: " << heap.leaves() << endl;
                        stop = clock();
                        break;
                    }
                    case 6:
                    {
                        try {
                            start = clock();
                            heap.print();
                            stop = clock();
                            
                        }
                        catch (const exception& e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 7:
                    {
                        start = clock();
                        heap.clear();
                        stop = clock();
                        
                        cout << "Clear Succesful.\n";
                        break;
                    }
                    case 8:
                    {
                        int key1;
                        string item;
                        cout << "Enter the key to add to the heap: ";
                        cin >> key1;
                        
                        cout << "Enter the value to add to the heap: ";
                        cin.ignore();
                        getline(cin, item);
                        
                        start = clock();
                        heap.insert(key1, item);
                        stop = clock();
                        
                        break;
                        
                    }
                    case 9:
                    {
                        try {
                            start = clock();
                            heap.delMax();
                            stop = clock();
                            cout << "The root has been deleted." << endl;
                        }
                        catch (const exception& e) {
                            stop = clock();
                            cout << e.what();
                        }
                        break;
                    }
                    case 10:
                    {
                        cout << "Exit succesful." << endl;
                        return 0;
                    }
                    default: 
                    {
                        cout << "Invalid code." << endl;
                    }
                } // end of code switch
                
                //cout << "\nTime: " << (stop - start)/double(CLOCKS_PER_SEC)*1000 << " ms.\n";

                cout << endl;
                
            }// end of for(;;)
            
            break;
        } // end of maxHeap
        
        default:
            cout << "Invalid code." << endl;
            
   	} // end of tree selection switch
    
   	return 0;
    
};
