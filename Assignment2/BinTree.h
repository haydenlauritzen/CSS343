#pragma once

#include<iostream>
#include"nodedata.h"

class BinTree {

private:

    NodeData *left, *right; // Pointers to NodeData

public:

    /* Constructors */
    /**
     * @brief Creates an empty binary tree.
     * 
     */
    BinTree();
    /**
     * @brief Copy Constructor
     * Creates a Deep Copy
     */
    BinTree(const BinTree&);

    /* Overloaded Operators */

    // Assignment
    /**
     * @brief Assigns the BST.
     * @param bst
     * @return BinTree* 
     */
    BinTree* operator=(const BinTree&);

    // Equivalence 
    /**
     * @brief Checks for BST Equivelance.
     * @param bst
     * @return true If 'bst' is equivalent to this tree.
     * @return false If 'bst' is not equivalent to this tree.
     */
    bool operator==(const BinTree&) const;
    /**
     * @brief Checks for BST Inequivelance
     * Returns the negation of operator==()
     * @param bst 
     * @return true If 'bst' is not equivalent to this tree.
     * @return false If 'bst' is equivalent to this tree.0
     */
    bool operator!=(const BinTree&) const;
    
    /* Accessors */

    /**
     * @brief Prints the BST.
     * 
     * @return ostream& 
     */
    friend ostream& operator<<(ostream&, const BinTree&);
    /**
     * @brief Returns a pointer by reference of a specific value in the tree.
     * Searchs the BST for a specific value and returns a pointer by reference to that value.
     * If the value is not found, false is returned.
     * @param value - Value to search for in tree.
     * @param ptr - Pointer to 'value'.
     * @post If false is returned 'ptr' is a nullptr.
     * @return true If the value is in the tree
     * @return false If the value is not in the tree.
     */
    bool retrieve(const NodeData&, NodeData*&);
    /**
     * @brief Returns the height of a specific value in the tree.
     * 
     * @return int 
     */
    int getHeight(const NodeData&) const;

    /* Mutators */

    /**
     * @brief Fills an array with BST data and empties the tree.
     * @param data - Array of Data values from tree.
     */
    void bstreeToArray(NodeData*[]);
    /**
     * @brief Fills a BST with array data and empties the array.
     * @param data - Array of Data values to insert.
     * @pre 'data' is not empty.
     */
    void arrayToBSTree(NodeData*[]);

};


