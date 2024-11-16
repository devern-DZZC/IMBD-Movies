#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "HashTable.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "Data.h"
using namespace std;

#define QUIT 99


int main () {

	char fileName [25] = "Movies.txt";
	
	cout << "Creating hash table ...\n->  ";
	HashTable * ht = initHashTable(23);
	ht = initHashTableFromFile(23, fileName);
	
	cout << "\nCreating BST ...\n->  ";
	BTNode * root = initBSTFromFile(fileName);
	cout << "Root of BST created with "<<root->data.ID<<endl;
	
	cout << "\nProcessing commands from commands file ... "<<endl;
	char commandsFile [25] = "Commands.txt";
	ifstream inputFile;
	inputFile.open(commandsFile);
	if(!inputFile.is_open())
	{
		cout << "Error opening file...\n";
		exit(1);
	}
	
	int command;
	string id, genre, title, upperID, file;
	int year, duration;
	inputFile >> command;
	while(command != QUIT)
	{
		
		cout << "\nCOMMAND "<<command<<":\n\n";
		if(command == 10)
		{
			inputFile >> id >> year >> duration >> genre >> ws;
			getline (inputFile, title);
			Movie movie;
			movie.ID = id;
			movie.duration = duration;
			movie.yearReleased = year;
			movie.genre = genre;
			movie.title = title;
			
			displayMovie(movie);
			if(containsHT(ht, id) == -1 || containsBST(root, id) == NULL)
			{
				insertHT(ht, movie);
				root = insertBST(root, movie);
				cout << "--> Movie "<< movie.ID <<" inserted in hash table and BST.\n";

			}
			else
				cout << "--> Movie "<< movie.ID <<" already in hash table and BST.\n";
				
		}
		if(command == 11)
		{
			inputFile >> id;
			if(containsHT(ht, id) != -1)
			{
				cout << "--> The movie "<<id<<" is in the hash table.\n";
				displayMovieHT(ht, id);
			}
			else
				cout << "--> The movie "<<id<<" is NOT in the hashtable.\n";
			
			if(containsBST(root, id) != NULL)
			{
				cout << "--> The movie "<<id<<" is in the BST.\n";
				BTNode * node = containsBST(root, id);
				displayMovie(node->data);
			}
			else
				cout << "--> The movie "<<id<<" is NOT in the BST.\n";
		}
		if(command == 12)
		{
			inputFile >> id;
			if(containsHT(ht, id) == -1)
				cout << "--> Movie "<<id<<" is NOT in the hash table.\n";
			else
			{
				deleteHT(ht, id);
				if(containsHT(ht, id) == -1)
					cout << "--> Movie "<<id<<" deleted from hash table.\n";
				else
					cout << "--> Movie "<<id<<" NOT deleted from hash table.\n";
			}
				
			BTNode * node = deleteBST(root, id);
			if(node==NULL)
				cout << "--> The movie "<<id<<" is NOT in the BST.\n";
			else
				cout <<"--> Movie "<<id<<" deleted from BST.\n";
		}
		if(command == 13)
		{
			statisticsHT (ht);
			cout << endl;
			statisticsBST (root);
			cout << endl;
		}
		if(command == 20)
		{
			cout << "Inorder traversal of BST:\n\n";
			inOrder(root);
			cout << endl;
		}
		if(command==21)
		{
			cout << "Level Order traversal of BST:\n\n";
			levelOrder(root);
			cout << endl;
		}
		if(command == 22)
		{
			inputFile >> id >> upperID;
			cout << "Displaying all keys in the BST between "<<id<<" and "<<upperID<<":\n\n";
			rangeBST(root, id, upperID);
			cout << endl;
		}
		if(command == 23)
		{
			inputFile >> file;
			
			char newFile[25];
			int i=0;
			while (i<file.length())
			{
				newFile[i] = file[i];
				i++;
			}
			newFile[i]='\0';
			cout << "Creating BST ...\n->  ";
			BTNode * newTree = initBSTFromFile(newFile);
			cout << "Root of BST created with "<<newTree->data.ID<<endl;
			cout << "\nLevel Order traversal of BST:\n\n";
			levelOrder(root);
			cout << endl;
			if(isIsomorphic(root, newTree))
				cout << "--> BSTs are isomorphic.\n";
			else
				cout << "--> BSTs are NOT isomorphic.\n";
			clearBT(newTree);
		}
		inputFile >> command;
	}
	
	return 0;
}
