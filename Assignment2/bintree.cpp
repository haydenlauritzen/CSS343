/**
 * @file BinTree.cpp
 * @author haydenlauritzen@gmail.com
 * @brief Implementation file for BinTree
 * @date 2022-04-04
 * @copyright Copyright (c) 2022
 */

#include"bintree.h"

/* Constructors */

BinTree::BinTree() : root(nullptr){}

BinTree::BinTree(const BinTree& bst) {
    h_assignment(this->root, bst.root);    
}   

BinTree::~BinTree() {
    this->makeEmpty();
}

/* Overloaded Operators */

BinTree& BinTree::operator=(const BinTree& bst) {
    this->makeEmpty();
    h_assignment(this->root, bst.root);    
}


void BinTree::h_assignment(BinNode* rootNode, const BinNode* newNode) {
    if(newNode == nullptr) return;
    rootNode->data = newNode->data;
    h_assignment(rootNode->left, newNode->left);
    h_assignment(rootNode->right, newNode->right);
}

bool BinTree::operator==(const BinTree& bst) const {
    return h_equivalence(this->root, bst.root);
}

bool BinTree::h_equivalence(const BinNode* lhs, const BinNode* rhs) const {
    return (lhs->data == rhs->data) 
    && h_equivalence(lhs->left, rhs->left) 
    && h_equivalence(lhs->right, rhs->right);
} 

bool BinTree::operator!=(const BinTree& bst) const {
    return !(this->operator==(bst));
}

/* Accessors */

bool BinTree::retrieve(const NodeData& nd, NodeData*& out) {
    BinNode* temp;
    getBinNode(this->root, nd, temp);
    out = temp->data;
    return (nd == *(temp->data));
}

/* Auxilary Functions */

void BinTree::getBinNode(BinNode* cur, const NodeData& nd, BinNode* out) const {
    if(cur == nullptr) return;
    if(*(cur->data) == nd) {
        out = cur;
        return;
    }
    getBinNode(cur, nd, out);
}

// int BinTree::getDepth(const NodeData& nd) {
//     int depth = 0;
//     NodeData* cur;
//     retrieve(nd, cur);
//     findDepth(cur, 0, depth);
//     return depth;
// }

// void BinTree::findDepth(const BinNode* cur, int depth, int& nodeDepth) {
//     ++depth;
//    if((*(cur->data) != nullptr) && depth > nodeDepth) {
//        nodeDepth = depth;
//    } 
// } 

int BinTree::getHeight(const NodeData& nd) const {
    BinNode *cur, *out;
    int height = 0;
    getBinNode(cur, nd, out);
    h_height(out, 0, height);
    return height;
}

void BinTree::h_height(BinNode* cur, int depth, int& height) const {
    if(cur == nullptr) return;
    if(depth > height) {
        height = depth;
        h_height(cur->left, depth+1, height);
        h_height(cur->right, depth+1, height);
    }
}

// bool BinTree::insert(NodeData*) {
    
// }

void BinTree::bstreeToArray(NodeData*[]) {
    
}

void BinTree::arrayToBSTree(NodeData*[]) {
    
}

bool BinTree::isEmpty() const {
    return this->root == nullptr;
}

void BinTree::makeEmpty() {
    
}

void BinTree::h_makeEmpty(BinNode* cur) {
    if(cur != nullptr) {
        h_makeEmpty(cur->left);
        h_makeEmpty(cur->right);
        cur->data == nullptr;
    }
    delete cur;
}

void BinTree::displaySideways() const {
	h_sideways(root, 0);
}

void BinTree::h_sideways(BinNode* current, int level) const {
	if (current != NULL) {
		level++;
		h_sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		h_sideways(current->left, level);
	}
}