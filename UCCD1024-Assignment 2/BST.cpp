#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"



using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::deepestNodes()
{
	//return false if it is a empty tree
	if (root == NULL)
		return false;

	int height = getHeight(root);

	cout << "\nStudent ID of the deepest nodes:" << endl;
	deepestNodes2(root, 1, height);
	cout << "\n\n";

	return true;
}

//calculate the height of tree
int BST::getHeight(BTNode* cur)
{
	if (cur == NULL)
		return 0;

	int leftHeight = getHeight(cur->left);
	int rightHeight = getHeight(cur->right);

	return max(leftHeight, rightHeight) + 1;
}

void BST::deepestNodes2(BTNode* cur, int currentHeight, int maxHeight)
{
	if (cur == NULL)
		return;

	//print the student ID when the current height = height of tree
	if (currentHeight == maxHeight)
	{
		cout << cur->item.id;
		cout << "\t";
	}

	//tranverse to the left node
	deepestNodes2(cur->left, currentHeight + 1, maxHeight);

	//tranverse to the right node
	deepestNodes2(cur->right, currentHeight + 1, maxHeight);
}


bool BST::CloneSubtree(BST t1, type item) {
	BST t2; // Initialize t2

	if (t1.root == NULL) {
		return false; 
	}

	BTNode* cur = t1.root;
	BTNode* cur2 = NULL; 

	while (cur != NULL) {
		if (cur->item.id == item.id) {
		
			t2.root = NULL; 
			CloneSubtree2(t2, cur);
			break;
		}
		else if (cur->item.id > item.id) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	if (t2.root == NULL) {
		return false; 
	}

	cout << "\nStudents in Subtree t1: " << endl;
	t1.preOrderPrint();
	cout << "______________________________________\n\n";
	cout << "Cloned Subtree from student: " << item.id << endl;
	t2.preOrderPrint();
	return true;
}

void BST::CloneSubtree2(BST& t2, BTNode* cur) {
	if (cur == NULL) {
		return;
	}
	BTNode* cur2=new BTNode(cur->item);
	if (cur2 != NULL) {
	    cur2->item = cur->item;
		t2.insert(cur2->item);
	}
	
	
	CloneSubtree2(t2, cur->left);
	CloneSubtree2(t2, cur->right);
}




bool BST::printLevelNodes() {
	BTNode* cur;
	Queue q;
	int currentLevel = 1;
	int nodesInCurrentLevel = 1;
	int nodesInNextLevel = 0;

	if (root == NULL) return false;
	q.enqueue(root);
	while (!q.empty()) {
		cout << "Level " << currentLevel << ": ";

		for (int i = 0; i < nodesInCurrentLevel; i++) {
			
			q.dequeue(cur);

			cout << cur->item.id << " ";

			if (cur->left != NULL) {
				q.enqueue(cur->left);
				nodesInNextLevel++;
			}

			if (cur->right != NULL) {
				q.enqueue(cur->right);
				nodesInNextLevel++;
			}
		}

		cout << endl;
		currentLevel++;
		nodesInCurrentLevel = nodesInNextLevel;
		nodesInNextLevel = 0;
	}

	return true;
}
