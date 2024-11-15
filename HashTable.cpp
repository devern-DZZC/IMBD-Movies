#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include "Data.h"
#include "HashTable.h"
#include "NodeTypes.h"
   using namespace std;


HashTable * initHashTable (int sizeTable) {
	
	if (sizeTable==0)
		return NULL;
	HashTable * ht = new HashTable;
	for(int i=0;i<sizeTable;i++)
		ht->elements[i] = NULL;
	ht->sizeTable = sizeTable;
	return ht;
}

//int idConvert(string id)
//{
//	int number=0;
//	int i = id.length()-1;
//	int mult=1;
//	
//	while (i>1)
//	{
//		int n = id[i]-'0';
//		number += (n*mult);
//		mult *= 10;
//		i--;
//	}
//	return number;
//}


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
	int num = idConvert(key);
	int loc = num % ht->sizeTable;
	LLNode * top = ht->elements[loc];
	LLNode * curr = top;
	
	while(curr != NULL)
	{
		if(curr->data.ID == key)
			return loc;
		curr = curr->next;
	}
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
	int loc = containsHT(ht, key);
	if(loc != -1)
	{
		LLNode * top = ht->elements[loc];
		LLNode * curr = top;
		
		while(curr != NULL)
		{
			if(curr->data.ID == key){
				displayMovie(curr->data);
				return;
			}
			curr = curr->next;
		}
	}
	return;
}


	
int lengthChain (HashTable * ht, int location) {
	LLNode * top = ht->elements[location];
	LLNode * curr = top;
	
	if(top==NULL)
		return 0;
	int count = 0;
	while (curr!=NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}



LLNode * createNode (Movie movie) {
	LLNode * newNode;
	
	newNode = new LLNode;
	
	newNode->data = movie;
	newNode->next = NULL;
	
	return newNode;
}



void insertHT (HashTable * ht, Movie movie) {
	int id = idConvert(movie.ID);
	int loc = id % ht->sizeTable;
	LLNode * top = ht->elements[loc];
	
	LLNode * newNode = createNode(movie);
	if (top==NULL)
		ht->elements[loc] = newNode;
	else
	{
		newNode->next = top;
		ht->elements[loc] = newNode;
	}
}



void statisticsHT (HashTable * ht) {
	int empty = 0;
	int longest=0;
	for(int i=0;i<ht->sizeTable;i++)
	{
		if(ht->elements[i]==NULL)
			empty++;
		else{
			int count = lengthChain(ht, i);
			if(count > longest)
				longest = count;
		}
	}
	int filled = ht->sizeTable - empty;
	
	cout << "Statistics on hash table:\n";
	cout << "There are "<<filled<<" locations."<<endl;
	cout << "There are "<<empty<<" empty locations."<<endl;
	cout << "The length of the longest chain is: "<<longest<<endl;
}




void deleteHT (HashTable * ht, string key) {
	int num = idConvert(key);
	int loc = num % ht->sizeTable;
	LLNode * top = ht->elements[loc];
	LLNode * curr = top;
	LLNode * pred = NULL;
	
	while(curr != NULL)
	{
		if(curr->data.ID == key)
		{
			if(pred==NULL)
				ht->elements[loc] = curr->next;
			else
				pred->next = curr->next;
			delete curr;
			return;	
		}
		else
		{
			pred = curr;
			curr = curr->next;
		}
	}
	cout << "The movie "<<key<<" is NOT in the hash table.\n";
	return;
}
	
