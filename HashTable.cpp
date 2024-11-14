#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include "Data.h"
#include "HashTable.h"
   using namespace std;


HashTable * initHashTable (int sizeTable) {

	return NULL;
}



HashTable * initHashTableFromFile (int sizeTable, char fileName[]) {

	ifstream inputFile;
	ofstream outputFile;

	Movie movie;
	int numMovies;
	
	HashTable * ht = initHashTable(sizeTable);	
	
	inputFile.open(fileName);
	
	if (!inputFile.is_open()) {
		cout << "Input file " << fileName << " could not be opened. Aborting ..." << endl;
		return ht;
	}
	
	numMovies = 0;
	inputFile >> movie.ID;
	
	while (movie.ID != "END") {
		inputFile >> movie.yearReleased >> movie.duration >> movie.genre >> ws;
		getline (inputFile, movie.title);
		numMovies++;

		insertHT (ht, movie);
		inputFile >> movie.ID;
	}

	inputFile.close();
	
	cout << numMovies << " movies read from " << fileName << " and stored in hash table." << endl;
	
	return ht;
}



int containsHT (HashTable * ht, string key) {
	
	return -1;
}



void displayMovie (Movie movie) {
	
	cout << "ID:              " << movie.ID << endl;
	cout << "TITLE:           " << movie.title << endl;
	cout << "YEAR RELEASED:   " << movie.yearReleased << endl;
	cout << "DURATION:        " << movie.duration << endl;
	cout << "GENRE:           " << movie.genre << endl;
	cout << endl;	
}



void displayMovieHT (HashTable * ht, string key) {

	return;
}


	
int lengthChain (HashTable * ht, int location) {
	
	return 0;
}



LLNode * createNode (Movie movie) {
	LLNode * newNode;
	
	newNode = new LLNode;
	
	newNode->data = movie;
	newNode->next = NULL;
	
	return newNode;
}



void insertHT (HashTable * ht, Movie movie) {
	
	return;	
}



void statisticsHT (HashTable * ht) {

	return;
}




void deleteHT (HashTable * ht, string key) {
	return;
}
	
