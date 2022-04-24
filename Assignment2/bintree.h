/**
 * @file BinTree.h
 * @author haydenlauritzen@gmail.com
 * @brief Header file for BinTree
 * @date 2022-04-04
 * @copyright Copyright (c) 2022
 */

#pragma once

#include<iostream>
#include"nodedata.h"

class BinTree {

    /**
     * @brief Prints the BST.
     * @return ostream& 
     */
    friend std::ostream& operator<<(std::ostream&, const BinTree&);

private:

    struct BinNode {
        BinNode *left, *right;
        NodeData *data;
    };

    BinNode* root;

    /**
     * @brief Gets the BinNode that contains a specific NodeData
     * @param nd NodeData to search for.
     * @return nullptr if value not found
     * @return BinNode* Pointer to BinNode containing NodeData
     */
    BinNode* findNode(const NodeData&) const;
    /**
     * @brief Sets the BinNode's and makes a copy of the NodeData
     * @param node Node to set NodeData to
     * @param nd NodeData to make a copy of.
     */
    void setNode(BinNode*&, const NodeData*);

public:

    /* Constructors */
    /**
     * @brief Creates an empty binary tree.
     */
    BinTree();
    /**
     * @brief Creates a Deep Copy
     */
    BinTree(const BinTree&);
    /**
     * @brief Destroys the BST.
     */
    ~BinTree();

    /* Overloaded Operators */

    // Assignment
    /**
     * @brief Assigns the BST.
     * @param bst BST to assign.
     * @return A reference to this BST. 
     */
    BinTree& operator=(const BinTree&);

    // Equivalence 
    /**
     * @brief Checks for BST Equivalence.
     * @param bst BST to assign.
     * @return true If 'bst' is equivalent to this tree.
     * @return false If 'bst' is not equivalent to this tree.
     */
    bool operator==(const BinTree&) const;
    /**
     * @brief Checks for BST Inequivelance
     * @details Returns the negation of operator==()
     * @param bst BST to assign.
     * @return true If 'bst' is not equivalent to this tree.
     * @return false If 'bst' is equivalent to this tree.
     */
    bool operator!=(const BinTree&) const;
    
    /* Accessors */

    /**
     * @brief Returns a pointer by reference of a specific value in the tree.
     * 
     * @details 
     * Searchs the BST for a specific value and returns a pointer by reference to that value.
     * If the value is not found, false is returned.
     * 
     * @param value - Value to search for in tree.
     * @param ptr - Pointer to 'value'.
     * @post If false is returned 'ptr' is a nullptr.
     * @return true If the value is in the tree
     * @return false If the value is not in the tree.
     */
    bool retrieve(const NodeData&, NodeData*&);

    /* Mutators */

    /**
     * @brief Inserts a Node into the BST.
     * @pre NodeData is dynamically allocated.
     * @return true If node was successfully inserted into the Tree.
     * @return false If the node was not successfully inserted into the tree (duplicate value)
     */
    bool insert(NodeData*);
    /**
     * @brief Fills an array with BST data and empties the tree.
     * @param data Array of Data values from tree.
     * @post BST is empty. 
     */
    void bstreeToArray(NodeData*[]);
    /**
     * @brief Fills a BST with array data and empties the array.
     * @param data Array of Data values to insert.
     * @pre 'data' is not empty.
     */
    void arrayToBSTree(NodeData*[]);
    /**
     * @brief Empties the BST.
     * @post isEmpty() == true
     */
    void makeEmpty();

    /* Auxilary Functions */

   /**
     * @brief Returns the height of a specific value in the tree.
     * 
     * @return int 
     */
    int getHeight(const NodeData&) const;
    // int getDepth(const NodeData&) const; // OPTIONAL
    /**
     * @brief Determines if the BST is empty.
     * @return true If root == nullptr
     * @return false If root != nullptr
     */
    bool isEmpty() const;
    /**
     * @brief Displays a sideways diagram of the tree to the console.
     */
    void displaySideways() const;

};


