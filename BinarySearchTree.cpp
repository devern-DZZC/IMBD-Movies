#include <iostream>
#include <cstdlib>
#include <fstream>

#include "NodeTypes.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Data.h"
using namespace std;


BTNode * initBSTFromFile (char fileName[]) {
	
	BTNode * root = NULL;
	
	ifstream inputFile;
	Movie movie;
	int numMovies;
	
	inputFile.open(fileName);
	
	if (!inputFile.is_open()) {
		cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
		return root;
	}

	numMovies = 0;
	inputFile >> movie.ID;
		
	while (movie.ID != "END") {
		inputFile >> movie.yearReleased >> movie.duration >> movie.genre >> ws;
		getline (inputFile, movie.title);
		numMovies++;

		root = insertBST (root, movie);
		inputFile >> movie.ID;
	}

	inputFile.close();
	
	cout << numMovies << " movies read from " << fileName << " and stored in BST." << endl;
	
	return root;
}

int idConvert(string id)
{
	int number=0;
	int i = id.length()-1;
	int mult=1;
	
	while (i>1)
	{
		int n = id[i]-'0';
		number += (n*mult);
		mult *= 10;
		i--;
	}
	return number;
}




BTNode * insertBST (BTNode * root, Movie data) {
	BTNode * newNode = createBTNode(data);
	if(root==NULL)
	{
		root = newNode;
		return root;
	}
	int id = idConvert(root->data.ID);
	if(idConvert(data.ID) < id)
	{
		BTNode* leftChild = insertBST(root->left, data);
        root->left = leftChild;
        leftChild->parent = root;
	}
	else
	{
		BTNode* rightChild = insertBST(root->right, data);
        root->right = rightChild;
        rightChild->parent = root;
	}
	return root;
}



BTNode * containsBST (BTNode * root, string key) {
	if(root==NULL)
		return NULL;
	if(root->data.ID == key)
		return root;
	else if(idConvert(root->data.ID) > idConvert(key))
		return containsBST(root->left, key);
	else
		return containsBST(root->right, key);
}



BTNode * minimumBST (BTNode * root) {
	if(root==NULL)
		return NULL;
	if(root->left == NULL)
		return root;
	return minimumBST(root->left);
}



BTNode * maximumBST (BTNode * root) {
	if(root==NULL)
		return NULL;
	if(root->right == NULL)
		return root;
	return maximumBST(root->right);
}



BTNode * inOrderSuccessor (BTNode * node) {
	if(node==NULL)
		return NULL;
	if(node->right != NULL)
		return minimumBST(node->right);
	
	BTNode * parent = node->parent;	
	while(parent != NULL && node==parent->right)
	{
		node=parent;
		parent = node->parent;
	}
	return parent;
}

void inOrderRange(BTNode * root, string lowerID, string upperID, int &count) {
	if (root == NULL)
		return;

	if (idConvert(root->data.ID) > idConvert(lowerID))
		inOrderRange(root->left, lowerID, upperID, count);

	if (idConvert(root->data.ID) >= idConvert(lowerID) && idConvert(root->data.ID) <= idConvert(upperID))
	{
		cout << root->data.ID << " ";
		count++;
	}

	if (idConvert(root->data.ID) < idConvert(upperID))
		inOrderRange(root->right, lowerID, upperID, count);
}

void rangeBST(BTNode * root, string lowerID, string upperID) {
	int count=0;
	inOrderRange(root, lowerID, upperID, count);
	cout<<endl;
	if(count > 0)
		cout <<"--> "<<count<<" keys were found in the range given.\n";
	else
		cout << "--> Range not within keys of BST.\n";
}

int countNTwithOneChild(BTNode * root)
{
	if(root==NULL)
		return 0;
	if(root->left == NULL && root->right==NULL)
		return countNTwithOneChild(root->left) + countNTwithOneChild(root->right);
	if(root->left != NULL && root->right != NULL)
		return countNTwithOneChild(root->left) + countNTwithOneChild(root->right);
	return 1 + countNTwithOneChild(root->left) + countNTwithOneChild(root->right);
	
}	


void statisticsBST (BTNode * root) {
	int h = height(root);
	int ntOneChild = countNTwithOneChild(root);
	BTNode * maxNode = maximumBST(root);
	BTNode * minNode = minimumBST(root);
	
	cout << "Statistics on BST:"<<endl;
	cout << "Height of binary tree: "<<h<<endl;
	cout << "Number of non-terminal nodes with one child: "<<ntOneChild<<endl;
	cout << "Smallest key: "<<minNode->data.ID<<endl;
	cout << "Biggest Key: "<<maxNode->data.ID<<endl;
		
}

void populate(BTNode * root, int arr[], int &size)
{
	if(root==NULL)
		return;
	populate(root->left, arr, size);
	arr[size] = idConvert(root->data.ID);
	size++;
	populate(root->right, arr, size);
}

bool isIsomorphic (BTNode * root1, BTNode * root2) {
    int arr1[MAX_ELEMENTS], arr2[MAX_ELEMENTS];
    int arrSize1=0, arrSize2=0;
    populate(root1, arr1, arrSize1);
    populate(root2, arr2, arrSize2);
    
    if(arrSize1 != arrSize2)
    	return false;
    for(int i=0;i<arrSize1;i++)
    {
    	if(arr1[i] != arr2[i])
    		return false;
	}
	return true;
}


BTNode * deleteBST (BTNode * root, string key) { 
	if(root==NULL)
		return NULL;
	BTNode * node = containsBST(root, key);
	if(node==NULL)
		return NULL;
		
	if(node->left==NULL && node->right==NULL)
	{
		BTNode * parent = node->parent;
		if(parent->left == node)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
		
	if(node->left==NULL)
	{
		BTNode * parent = node->parent;
		if(parent->left == node)
			parent->left = node->right;
		else
			parent->right = node->right;
	}
		
	if(node->right==NULL)
	{
		BTNode * parent = node->parent;
		if(parent->left == node)
			parent->left = node->left;
		else
			parent->right = node->left;
	}
		
	BTNode * succ = minimumBST(node->right);
	node->data = succ->data;
	BTNode * parent = succ->parent;
	if(parent==node)
		node->right = succ->right;
	else
		parent->left = succ->right;
		
	return root;
}

