/**
 * @file BinTree.cpp
 * @author haydenlauritzen@gmail.com
 * @brief Implementation file for BinTree
 * @date 2022-04-04
 * @copyright Copyright (c) 2022
 */

#include"bintree.h"

BinTree::BinTree() : root(nullptr){}

BinTree::BinTree(const BinTree& bst) {
    assignment(this->root, bst.root);    
}   

BinTree::~BinTree() {
    this->makeEmpty();
}

BinTree& BinTree::operator=(const BinTree& bst) {
    this->makeEmpty();
    assignment(this->root, bst.root);    
}

bool BinTree::operator==(const BinTree&) const {
    
}

bool BinTree::operator!=(const BinTree&) const {
    
}

bool BinTree::retrieve(const NodeData&, NodeData*&) {
    
}

int BinTree::getHeight(const NodeData&) const {
    
}

bool BinTree::insert(NodeData*) {
    
}

void BinTree::bstreeToArray(NodeData*[]) {
    
}

void BinTree::arrayToBSTree(NodeData*[]) {
    
}

bool BinTree::isEmpty() const {
    
}

void BinTree::makeEmpty() {
    
}

void BinTree::displaySideways() const {
    
}

void BinTree::sideways(BinNode*, int) const {
    
}

void BinTree::assignment(BinNode* rootNode, const BinNode* newNode) {
    if(newNode == nullptr) return;
    rootNode->data = newNode->data;
    assignment(rootNode->left, newNode->left);
    assignment(rootNode->right, newNode->right);
}