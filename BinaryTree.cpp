#include <iostream>
#include <cstdlib>
#include "BinaryTree.h"
#include "Queue.h"
#include "Data.h"

using namespace std;



BTNode * createBTNode (Movie data) {
	BTNode * newNode; 
   
	newNode = new BTNode;
   
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
   
	return newNode;
}



void preOrder (BTNode * root) {
	
	if (root == NULL)
		return;
		
	cout << root->data.ID << " ";

	preOrder (root->left);
	preOrder (root->right);
}



void inOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	inOrder (root->left);
	
	cout << root->data.ID << " ";
	
	inOrder (root->right);
}



void postOrder (BTNode * root) {
	
	if (root == NULL)
		return;

	postOrder (root->left);
	postOrder (root->right);
	
	cout << root->data.ID << " ";
}



int moment (BTNode * root) {

	if (root == NULL)
		return 0;
		
	return (1 + moment (root->left) + moment (root->right));
}



int numOneChild (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 0;

	if (root->left == NULL)
		return 1 + numOneChild (root->right);
	else
	if (root->right == NULL)
		return 1 + numOneChild (root->left);
	else
		return (numOneChild (root->left) + numOneChild (root->right));
}



int numTerminal (BTNode * root) {

	if (root == NULL)
		return 0;
		
	if (root->left == NULL && root->right == NULL)
		return 1;
		
	return (numTerminal (root->left) + numTerminal (root->right));
}



int nodeDepth (BTNode * node) {
	int branch;
	
	branch = 0;
	
	if (node == NULL)
		return -1;
		
	while (node->parent != NULL) {
		node = node->parent;
		branch++;
	}
	
	return branch;
}



int height (BTNode * root) {
	if(root==NULL)
		return 0;
	int left = height(root->left);
	int right = height(root->right);
	if(left > right)
		return 1+left;
	else
		return 1+right;
}



void levelOrder (BTNode * root) {
	Queue * q = initQueue(10);
	enqueue(q, root);
	int levelNum=0;
	
	while(!isEmptyQueue(q))
	{
		int numNodes = sizeQueue(q);
		cout <<numNodes<<" nodes at Level "<<levelNum<<": ";
		for(int i=1;i<=numNodes;i++)
		{
			BTNode * p = dequeue(q);
			cout << p->data.ID << " ";
			if(p->left != NULL)
				enqueue(q, p->left);
			if(p->right != NULL)
				enqueue(q, p->right);
		}
		levelNum++;
		cout << endl;
	}
}



void clearBT (BTNode * root) {
	if(root==NULL)
		return;
	clearBT(root->left);
	clearBT(root->right);
	delete root;
	root=NULL;
}

