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
    if(*this == bst) return *this;
    // If tree is empty, makeEmpty() will immediately return.
    this->makeEmpty();
    auto h_assign = [this](BinNode*& lhs, const BinNode* rhs, auto&& h_assign) mutable {
        if(rhs == nullptr) return; // Base Case
        NodeData* newData = new NodeData(*rhs->data);
        setNode(lhs, newData);
        h_assign(lhs->left, rhs->left, h_assign);
        h_assign(lhs->right, rhs->right, h_assign);
    };
    // Begin recursion.
    h_assign(this->root, bst.root, h_assign);
    return *this;
}

bool BinTree::operator==(const BinTree& bst) const {
    auto h_equivalence = [&](const BinNode* lhs, const BinNode* rhs, auto&& h_equivalence) {
        // If both nodes are nullptr, we have reached a leaf node's branches.
        if(lhs == nullptr && rhs == nullptr) return true;
        // If only one Node is a nullptr, the BSTs are not equivalent
        else if(lhs == nullptr || rhs == nullptr) return false;
        return (*(lhs->data) == *(rhs->data)) 
            && h_equivalence(lhs->left, rhs->left, h_equivalence)
            && h_equivalence(lhs->right, rhs->right, h_equivalence);
    };
    return h_equivalence(this->root, bst.root, h_equivalence);
}

bool BinTree::operator!=(const BinTree& bst) const {
    return !(this->operator==(bst));
}

/* Accessors */

bool BinTree::retrieve(const NodeData& nd, NodeData*& out) {
    BinNode* temp = findNode(nd);
    // If search fails, nullptr is returned
    if(temp == nullptr) return false;
    out = temp->data;
    // Returns true if found node == nd
    return (nd == *out); 
}

/* Mutators */

bool BinTree::insert(NodeData* nd) {
    auto h_insert = [&](BinNode*& cur, auto&& h_insert) mutable {
        if(cur == nullptr) {
            setNode(cur, nd);
            return true;
        }
        // Data to insert is larger -> go right
        else if(*nd > *(cur->data)) {
            return h_insert(cur->right, h_insert);
        }
        // Data to insert is smaller -> go left
        else if(*nd < *(cur->data)) {
            return h_insert(cur->left, h_insert);
        }
        // Otherwise node is a duplicate, function will return
        return false;
    };
    return h_insert(this->root, h_insert);
}

/* Auxilary Functions */

std::ostream& operator<<(ostream& os, const BinTree& bst) {
    bool first = true;
    auto h_operatoros = [&](BinTree::BinNode* cur, auto&& h_operatoros) {
        if(cur == nullptr) return;
        h_operatoros(cur->left, h_operatoros);
        if(!first) {
            os << " ";
        }
        else {
            first = false;
        }
        os << *cur->data; 
        h_operatoros(cur->right, h_operatoros);
    };
    h_operatoros(bst.root, h_operatoros);
    os << std::endl;
    return os;
}

BinTree::BinNode* BinTree::findNode(const NodeData& nd) const {
    auto h_findNode = [&](BinNode* cur, auto&& h_findNode) -> BinNode* {
        if(cur == nullptr) return cur; // Base Case
        if(nd == *(cur->data)) { // Node matches NodeData, end recursion
            return cur;
        }
        else if(nd < *(cur->data)) {
            return h_findNode(cur->left, h_findNode);
        }
        else if(nd > *(cur->data)) {
            return h_findNode(cur->right, h_findNode);
        }
        // Otherwise Node was not found, return nullptr
        else return nullptr;
    };
    return h_findNode(this->root, h_findNode);
}

void BinTree::setNode(BinNode*& node, NodeData* nd) {
    if(nd == nullptr) return;
    node = new BinNode();
    node->data = nd;
}

int BinTree::getHeight(const NodeData& nd) const {
    // Tree is not assumed to be a BST
    // BinNode* node = findNode(nd); // Finds the node with 'nd'
    // Therefore this function above is not used
    auto h_findNode = [&](BinNode* cur, auto&& h_findNode) -> BinNode* {
        if(cur == nullptr) return cur; // Base Case
        if(nd == *(cur->data)) return cur;  // Node matches NodeData, end recursion
        BinNode* left = h_findNode(cur->left, h_findNode);
        BinNode* right = h_findNode(cur->right, h_findNode);
        // Return the pointer that is not nullptr
        // If both are nullptr, nullptr gets returned
        return left == nullptr ? right : left;
    };
    BinNode* node = h_findNode(this->root, h_findNode);
    if(node == nullptr) return 0;  
    int height = 1;
    int depth = 1;
    auto h_getHeight = [&](BinNode* cur, int depth, auto&& h_getHeight) mutable {
        if(cur == nullptr) return;
        if(depth > height) {
            height = depth;
        }
        h_getHeight(cur->left, depth+1, h_getHeight);
        h_getHeight(cur->right, depth+1, h_getHeight);
    };
    h_getHeight(node, depth, h_getHeight);
    return height;
}

void BinTree::bstreeToArray(NodeData* nd[]) {
    if(this->isEmpty()) return;
    int index = 0;
    auto h_bstreeToArray = [&](BinNode* cur, auto&& h_bstreeToArray) mutable {
        if(cur == nullptr) return;
        h_bstreeToArray(cur->left, h_bstreeToArray);
        // Array is assumed to handle ownership of values
        NodeData* newData = new NodeData(*(cur->data));
        nd[index++] = newData;
        h_bstreeToArray(cur->right, h_bstreeToArray);
    };
    h_bstreeToArray(this->root, h_bstreeToArray);
    this->makeEmpty(); // Tree should be empty; deallocates memory for tree
}

void BinTree::arrayToBSTree(NodeData* nd[]) {
    if(nd[0] == nullptr) return;
    const int ARRAYSIZE = 100; //Array is fixed to 100 elements
    int numElements = 0;
    for(int i = 0; i < ARRAYSIZE; i++) { 
        if(nd[i] == nullptr) break; // Rest of array is nullptr 
        ++numElements;
    }
    if(numElements == 0) return;
    auto h_arrayToBSTree = [&](BinNode*& cur, int left, int right, auto&& h_arrayToBSTree) mutable {
        if(left > right) return;
        int median = (left+right)/2;
        // Set median to current root node
        // BST will handle deallocation.
        NodeData* newData = new NodeData(*nd[median]);
        setNode(cur, newData);
        // Values left of root get inserted left of the root
        h_arrayToBSTree(cur->left, left, median - 1, h_arrayToBSTree);
        // Values left of root get inserted right of the root
        h_arrayToBSTree(cur->right, median + 1, right, h_arrayToBSTree);
    };
    h_arrayToBSTree(this->root, 0, numElements-1, h_arrayToBSTree);
    // Delete values in array.
    for(int i = 0; i < ARRAYSIZE; i++) { 
        if(nd[i] == nullptr) break; // Rest of array is nullptr
        delete nd[i];   
        nd[i] = nullptr;
    }
}

bool BinTree::isEmpty() const {
    return this->root == nullptr || this->root->data == nullptr;
}

void BinTree::makeEmpty() {
    if(this->root == nullptr) return;
    auto h_makeEmpty = [](BinNode*& cur, auto&& h_makeEmpty) mutable {
        if(cur == nullptr) return;
        h_makeEmpty(cur->left, h_makeEmpty);
        h_makeEmpty(cur->right, h_makeEmpty);
        delete cur->data;
        cur->data = nullptr;
        delete cur;
        cur = nullptr;
    };
    h_makeEmpty(this->root, h_makeEmpty);
}

void BinTree::displaySideways() const { 
    if(this->root == nullptr) return;
    auto h_sideways = [](BinNode* cur, int level, auto&& h_sideways) -> void {
        if (cur == nullptr) return;
        level++;
        h_sideways(cur->right, level, h_sideways);
        // indent for readability, 4 spaces per depth level 
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }
        cout << *cur->data << endl;        // display information of object
        h_sideways(cur->left, level, h_sideways);
    };
	h_sideways(this->root, 0, h_sideways);
}