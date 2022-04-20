/**
 * @file BinTree.cpp
 * @author haydenlauritzen@gmail.com
 * @brief Implementation file for BinTree
 * @date 2022-04-04
 * @copyright Copyright (c) 2022
 */

#include"bintree.h"

/*** Constructors ***/

BinTree::BinTree() {
    this->root = nullptr;
}    

BinTree::BinTree(const BinTree& bst) {
    this->root = nullptr;
    this->operator=(bst);  
}   

BinTree::~BinTree() {
    this->makeEmpty();
}

/* Overloaded Operators */

BinTree& BinTree::operator=(const BinTree& bst) {
    // If tree is empty, makeEmpty() will immediately return.
    this->makeEmpty();
    auto h_assign = [](BinNode* lhs, const BinNode* rhs, auto&& h_assign) {
        if(rhs == nullptr) return; // Base Case
        // Traverse in Pre-Order and assign. 
        BinNode* newNode = new BinNode();
        newNode->data = rhs->data;
        lhs = newNode;
        h_assign(lhs->left, rhs->left, h_assign);
        h_assign(lhs->right, rhs->right, h_assign);
    };
    // Begin recursion.
    h_assign(this->root, bst.root, h_assign);
    return *this;
}

bool BinTree::operator==(const BinTree& bst) const {
    auto h_equivalence = [](const BinNode* lhs, const BinNode* rhs, auto&& h_equivalence) -> bool {
        if(lhs == nullptr || rhs == nullptr) { // Base Case
            // If only one Node is a nullptr, the BSTs are not equivalent
            // If both nodes are nullptr, we have reached a leaf node's branches.
            if(lhs == rhs) return true;
            else return false;
        }
        return (lhs->data == rhs->data // If all nodes are equivalant, will return true.
        && h_equivalence(lhs->left, rhs->left, h_equivalence))
        && h_equivalence(lhs->right, rhs->right, h_equivalence);
    };
    return h_equivalence(this->root, bst.root, h_equivalence);
}

// bool BinTree::h_equivalence(const BinNode* lhs, const BinNode* rhs) const {
//     return (lhs->data == rhs->data) 
//     && h_equivalence(lhs->left, rhs->left) 
//     && h_equivalence(lhs->right, rhs->right);
// } 

bool BinTree::operator!=(const BinTree& bst) const {
    return !(this->operator==(bst));
}

/* Accessors */

bool BinTree::retrieve(const NodeData& nd, NodeData*& out) {
    BinNode* temp = findNode(nd);
    // If search fails, nullptr is returned
    if(temp == nullptr) return false;
    out = temp->data;
    // Returns true if the found node == nd
    return (nd == *out); 
}

/* Mutators */

bool BinTree::insert(NodeData* nd) {
    // If tree is empty
    if(this->isEmpty()) {
        BinNode* newNode = new BinNode();
        newNode->data = nd;
        this->root = newNode;
        return true;
    }
    BinNode* cur = this->root;
    bool success = 0;
    auto h_insert = [&](auto&& h_insert) mutable {
        // Data to insert is larger -> go right
        if(*nd > *(cur->data)) {
            // If right is empty, insert node and end recursion
            if(cur->right == nullptr) {
                BinNode* newNode = new BinNode();
                newNode->data = nd;
                cur->right = newNode;
                success = true;
                return;
            }
            // Otherwise traverse to the right
            else {
                cur = cur->right;
                h_insert(h_insert);
            }
        }
        // Data to insert is smaller -> go left
        else if(*nd < *(cur->data)) {
            // If left is empty, insert node and end recursion
            if(cur->left == nullptr) {
                BinNode* newNode = new BinNode();
                newNode->data = nd;
                cur->left = newNode;
                success = true;
                return;
            }
            // Otherwise traverse to the left
            else { 
                cur = cur->left;
                h_insert(h_insert);
            }
        }
        else {
            // Duplicate value
            return;             
        }
    };
    h_insert(h_insert);
    return success;
}

/* Auxilary Functions */

std::ostream& operator<<(ostream& os, const BinTree& bst) {
    return os;
}

BinTree::BinNode* BinTree::findNode(const NodeData& nd) const {
    BinNode* result = nullptr;
    auto h_findNode = [&](BinNode* cur, auto&& h_findNode) {
        if(cur == nullptr) return; // Base Case
        if(*(cur->data) == nd) { // Node matches NodeData, end recursion
            result = cur;
            return;
        }
        // Otherwise, continue recursion.
        h_findNode(cur->left, h_findNode);
        h_findNode(cur->right, h_findNode);
    };
    h_findNode(this->root, h_findNode);
    return result;
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
    BinNode* node = findNode(nd); // Finds the node with 'nd'
    if(node == nullptr) return 0;  
    int height = 1;
    int depth = 1;
    auto h_getHeight = [&](BinNode* cur, int depth, auto&& h_getHeight) mutable {
        if(cur == nullptr) return;
        if(depth > height) {
            height = depth;
        }
        h_getHeight(cur->left, depth++, h_getHeight);
        h_getHeight(cur->right, depth++, h_getHeight);
    };
    h_getHeight(node, depth, h_getHeight);
    return height;
    // BinNode* cur = findNode(nd);
    // h_height(out, 0, height);
    // return height;
}

// void BinTree::h_height(BinNode* cur, int depth, int& height) const {
//     if(cur == nullptr) return;
//     if(depth > height) {
//         height = depth;
//         h_height(cur->left, depth+1, height);
//         h_height(cur->right, depth+1, height);
//     }
// }

void BinTree::bstreeToArray(NodeData* nd[]) {
    int index = 0;
    auto h_bstreeToArray = [&](BinNode* cur, auto&& h_bstreeToArray) mutable {
        if(cur == nullptr) return;
        h_bstreeToArray(cur->left, h_bstreeToArray);
        nd[++index] = cur->data;
        h_bstreeToArray(cur->right, h_bstreeToArray);
    };
    h_bstreeToArray(this->root, h_bstreeToArray);
}

// void BinTree::h_bstreeToArray(NodeData* nd[], BinNode* cur, int& index) {
//     if(cur == nullptr) return;
//     h_bstreeToArray(nd, cur->left, index);
//     nd[index] = cur->data;
//     ++index;
//     h_bstreeToArray(nd, cur->right, index);
// }

void BinTree::arrayToBSTree(NodeData* nd[]) {
    int index = 0;  
    auto h_arrayToBSTree = [&](BinNode* cur, auto&& h_arrayToBSTree) mutable {
        if(cur == nullptr) return;
        // In-Order Traversal
        h_arrayToBSTree(cur->left, h_arrayToBSTree);
        cur->data = nd[++index];
        h_arrayToBSTree(cur->right, h_arrayToBSTree);
    };
    h_arrayToBSTree(this->root, h_arrayToBSTree);
}

// void BinTree::h_arrayToBSTree(NodeData* nd[], BinNode* cur, int& index) {
//     if(cur == nullptr) return;
//     h_arrayToBSTree(nd, cur->left, index);
//     cur->data = nd[index];
//     ++index;
//     h_arrayToBSTree(nd, cur->right, index);
// }

bool BinTree::isEmpty() const {
    return this->root == nullptr;
}

void BinTree::makeEmpty() {
    auto h_makeEmpty = [&](BinNode* cur, auto&& h_makeEmpty) mutable {
        if(cur == nullptr) return;
        h_makeEmpty(cur->right, h_makeEmpty);
        h_makeEmpty(cur->left, h_makeEmpty);
        delete cur->data;
        cur->data = nullptr;
        delete cur;
        cur = nullptr;
    };
    h_makeEmpty(this->root, h_makeEmpty);
}

void BinTree::displaySideways() const { 
    auto h_sideways = [](BinNode* cur, int level, auto&& h_sideways) -> void {
        if (cur != nullptr) {
            level++;
            h_sideways(cur->right, level, h_sideways);
            // indent for readability, 4 spaces per depth level 
            for (int i = level; i >= 0; i--) {
                cout << "    ";
            }
            cout << *cur->data << endl;        // display information of object
            h_sideways(cur->left, level, h_sideways);
	    }
    };
	h_sideways(this->root, 0, h_sideways);
}

// void BinTree::h_sideways(BinNode* current, int level) const {
// 	if (current != NULL) {
// 		level++;
// 		h_sideways(current->right, level);

// 		// indent for readability, 4 spaces per depth level 
// 		for (int i = level; i >= 0; i--) {
// 			cout << "    ";
// 		}

// 		cout << *current->data << endl;        // display information of object
// 		h_sideways(current->left, level);
// 	}
// }