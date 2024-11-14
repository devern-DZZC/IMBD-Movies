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



BTNode * insertBST (BTNode * root, Movie data) {
	
	return NULL;
}



BTNode * containsBST (BTNode * root, string key) {

	return NULL;
}



BTNode * minimumBST (BTNode * root) {

	return NULL;
}



BTNode * maximumBST (BTNode * root) {

	return NULL;
}



BTNode * inOrderSuccessor (BTNode * node) {

	return NULL;	
}



void rangeBST (BTNode * root, string lowerID, string upperID) {
	
	return;
}
	


void statisticsBST (BTNode * root) {
	return;
		
}



bool isIsomorphic (BTNode * root1, BTNode * root2) {
		
	return false;
}



BTNode * deleteBST (BTNode * root, string key) {

	return root; 

}

