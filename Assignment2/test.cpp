#if 0

#include"bintree.h"

using namespace std;

const static int ARRAYSIZE = 100;

void buildTree(BinTree&, ifstream&); 
void initArray(NodeData*[]); 

/* 
 * $$ Empty Tree
 * a $$ Tree Size 1
 * b a c b a c $$ Tree Size > 1; Duplicate Values
 * c b a $$ Tree Size > 1
 * a a a b b b c c c $$ Tree Size > 1 Duplicate Values
 */ 

int main() {
	BinTree tree, empty, root; // Test Default Constructor
	tree.isEmpty() ? cerr << "Default Constructor Test Passed\n" : cerr << "Default Constructor Test Failed\n"; 
	NodeData* rootVal = new NodeData("root");
	root.insert(rootVal);
	cout << "---------------------------------------------------------------\n"; 
	// Test Self Equivalence 
	empty == empty ? cerr << "Empty Self Equivalence Test Passed\n" : cerr << "Empty Self Equivalence Test Failed\n"; 
	root == root ? cerr << "Single Value Self Equivalence Test Passed\n" : cerr << "Single Value Self Equivalence Test Failed\n"; 
	// This is false
	root == empty ? cerr << "Single Value = Empty Equivalence Test Failed\n" : cerr << "Single Value = Empty Self Equivale Passed\n"; 
	cout << "---------------------------------------------------------------\n"; 
	// Test Self Inequivalence 
	// This is false
	empty != empty ? cerr << "Empty Self Equivalence Test Failed\n" : cerr << "Empty Self Equivalence Test Passed\n"; 
	// This is false
	root != root ? cerr << "Single Value Self Equivalence Test Failed\n" : cerr << "Single Value Self Equivalence Test Passed\n"; 
	root != empty ? cerr << "Single Value != Empty Equivalence Test Passed\n" : cerr << "Single Value != Empty Self Equivalence Test Failed\n"; 
	cout << "---------------------------------------------------------------\n"; 	// Test Assignemnt Bounds
	BinTree copyAE = empty;
	copyAE == empty ? cerr << "Assign to Empty Test Passed\n" : cerr << "Assign to Empty Test Failed\n"; 
	BinTree copyAR = root;
	copyAR == root ? cerr << "Assign to Single Value Test Passed\n" : cerr << "Assign to Single Value Test Failed\n";
	root = root;
	root == root ? cerr << "Assign to Self Test Passed\n" : cerr << "Assign to Self Test Failed\n"; 
	cout << "---------------------------------------------------------------\n"; 	// Test Assignemnt Bounds
	// Test Copy Construction Bounds
	BinTree copyCR(empty);
	copyCR == empty ? cerr << "Copy to Empty Test Passed\n" : cerr << "Copy to Empty Test Failed\n"; 
	BinTree copyCE(root);
	copyCE == root ? cerr << "Copy to Single Value Test Passed\n" : cerr << "Copy to Single Value Test Failed\n";
	cout << "---------------------------------------------------------------\n"; 	// Test Assignemnt Bounds
	ifstream infile("testData.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	NodeData nd_a("a");
	NodeData nd_b("b");
	NodeData nd_c("c");
	NodeData nd_d("d");
	// Test all Tree Edge Cases (Size 0, Size 1, Size >1, Duplicate Values)
	while(!infile.eof()) {
		cout << "---------------------------------------------------------------\n"; 
		cout << "Inital Tree Values: " << endl;
		buildTree(tree, infile);
		cerr << "\nTrying operator<<:" << '\n' << tree;
		cerr << "Trying displaySideways:" << '\n';
		tree.displaySideways();
		cout << endl;
		// Test Copy and Assignment Construction 
		tree.isEmpty() ? cerr << "Tree is Empty\n" : cerr << "Tree is not Empty\n"; 
		BinTree copy(tree);
		copy == tree ? cerr << "Copy Constructor Test Passed\n" : cerr << "Copy Constructor Test Failed\n";
		BinTree copy2 = tree;
		copy2 == tree ? cerr << "Assignment Test Passed\n" : cerr << "Assignment Test Failed\n";
	 	tree == tree ? cerr << "Multiple Value Self Equivalence Test Passed\n" : cerr << "Multiple Value Self Equivalence Test Failed\n"; 
		tree != tree ? cerr << "Multiple Value Self Inequivalence Test Failed\n " : cerr << "Multiple Value Self Inequivalence Test Passed\n"; 
		NodeData* out;
		tree.retrieve(nd_a, out) ? cerr << "\"A\" is in this tree\n" : cerr << "\"A\" is not in this tree\n"; 
	 	tree.retrieve(nd_b, out) ? cerr << "\"B\" is in this tree\n" : cerr << "\"B\" is not in this tree\n"; 
	 	tree.retrieve(nd_c, out) ? cerr << "\"C\" is in this tree\n" : cerr << "\"C\" is not in this tree\n"; 
	 	tree.retrieve(nd_d, out) ? cerr << "\"D\" is in this tree\n" : cerr << "\"D\" is not in this tree\n"; 
		cerr << "Height of \"a\" is: " << tree.getHeight(nd_a) << '\n'; 
		cerr << "Height of \"b\" is: " << tree.getHeight(nd_b) << '\n'; 
		cerr << "Height of \"c\" is: " << tree.getHeight(nd_c) << '\n'; 
		cerr << "Height of \"d\" is: " << tree.getHeight(nd_d) << '\n'; 
		cerr << "Testing BST-->Array" << endl;
		tree.bstreeToArray(ndArray);
		cerr << "Array is now:" << endl;
		for(int i = 0; i < ARRAYSIZE; i++) {
			if(ndArray[i] == nullptr) break;
			cerr << *ndArray[i] << ' ';
		}
		cerr << "\nTree is now:\n";
		tree.displaySideways();
		cerr << endl;
		cerr << "Testing BST-->Array\n";
		tree.arrayToBSTree(ndArray);
		cerr << "Array is now:" << endl;
		for(int i = 0; i < ARRAYSIZE; i++) {
			if(ndArray[i] == nullptr) break;
			cerr << *ndArray[i] << ' ';
		}
		cerr << "\nTree is now:\n";
		tree.displaySideways();
		cerr << endl;
		tree.makeEmpty();
		tree == empty ? cerr << "makeEmpty() Test Passed\n " : cerr << "makeEmpty() Test Failed\n"; 
	}
	cout << "---------------------------------------------------------------\n"; 
}


void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
		// would do a setData if there were more than a string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}

void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}

#endif
