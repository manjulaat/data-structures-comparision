#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;

//template for generic type 
template<typename K, typename V> 

//Hashnode class 
class HashNode {
	public: 
	V value;
	K key;
	
	//Constructor of hashnode 
	HashNode(K key, V value) {

		this->value = value;
		this->key = key;
	}
};

//template for generic type 
template<typename K, typename V> 

//Our own Hashmap class 
class HashMap {
	//hash element array 
	HashNode<K,V> **arr;
	int capacity;
	//current size 
	int size;
	//dummy node 
	HashNode<K,V> *dummy;

	public: 
	HashMap() {

		//Initial capacity of hash array 
		capacity = 22000;
		size= 22000 * 8;
		arr = new HashNode<K,V>*[capacity];
		
		//Initialise all elements of array as NULL 
		for(int i=0 ; i < capacity ; i++) 
			arr[i] = NULL;
		
		//dummy node with value and key -1 
		dummy = new HashNode<K,V>("", "");
	}
	// This implements hash function to find index 
	// for a key 
	unsigned long int hashCode(K key) {

    unsigned long int hash = 0;
    for (int i = 0; i < key.length(); i++)
    	hash = 37*hash + key[i];
  	return hash % capacity;
	}
	
	//Function to add key value pair 
	void insertNode(K key, V value) {

		HashNode<K,V> *temp = new HashNode<K,V>(key, value);
		
		// Apply hash function to find index for given key 
		unsigned long int hashIndex = hashCode(key);
		
		//find next free space 
		while(arr[hashIndex] != NULL && arr[hashIndex]->key != key 
			&& arr[hashIndex]->key != "") {
			hashIndex++;
			hashIndex %= capacity;
		}
		size += key.size();
		arr[hashIndex] = temp;
	}
	
	//Function to delete a key value pair 
	V deleteNode(string key) {

		// Apply hash function to find index for given key 
		unsigned long int hashIndex = hashCode(key);
		
		//finding the node with given key 
		while(arr[hashIndex] != NULL) {
			//if node found 
			if(arr[hashIndex]->key == key) 
			{
				HashNode<K,V> *temp = arr[hashIndex];
				
				//Insert dummy node here for further use 
				arr[hashIndex] = dummy;
				
				// Reduce size 
				size--;
				return temp->value;
			}
			hashIndex++;
			hashIndex %= capacity;

		}
		
		//If not found return null 
		return 0;
	}
	
	//Function to search the value for a given key 
	bool search(string key) {

		// Apply hash function to find index for given key 
		unsigned long int hashIndex = hashCode(key);
		int counter=0;
		//finding the node with given key 
		while(arr[hashIndex] != NULL) { int counter =0;
			if(counter++>capacity) //to avoid infinite loop 
				return false;		 
			//if node found return its value 
			if(arr[hashIndex]->key == key) 
				return true;
			hashIndex++;
			hashIndex %= capacity;
		}
		
		//If not found return null 
		return false;
	}
	
	//Return current size 
	int sizeofMap() {

		return size;
	}
	
	//Return true if size is 0 
	bool isEmpty() {

		return size == 0;
	}
};

//Driver method to test map class 
int main() {
	int choice, num, numberOfSearches;
  bool isFound;
  string line;
  int val;
  string searchName, tempName;
	HashMap<string, string> *h = new HashMap<string, string>;
  ifstream dataInputFile("../../input/universities_followers.csv");
  ifstream searchStoredInput("../../input/stored_names.csv");
  ifstream searchNotStoredInput("../../input/not_stored_names.csv");
  ofstream timeFile("../../output/userName/hashClosedTime.txt");
	ofstream whateverFile("../../whatever.csv");
  ofstream sizeFile("../../output/userName/hashClosedSize.txt");
  // To read the header line
  getline(dataInputFile, line);
  // Read data, line by line
  int lineCount = 0;
  clock_t begin_time, end_time;
  begin_time = clock();
  timeFile << "Time for insertions\n";
  while (getline(dataInputFile, line)) {
    lineCount++;
    // Create a stringstream of the current line
    stringstream ss(line);
    string placeholderString;
		getline(ss, placeholderString, ',');
    getline(ss, placeholderString, ',');
		getline(ss, tempName, ',');
		
		h->insertNode(tempName,tempName);
    if (lineCount == 1000 || lineCount == 5000 || lineCount == 10000 || lineCount == 15000 || lineCount == 20000) {
      end_time = clock();
      timeFile << "\n" << lineCount << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
			whateverFile << float( end_time - begin_time ) / CLOCKS_PER_SEC << ",";
    }
  }
	
	whateverFile << "\n";
	// Close file
  dataInputFile.close();
  sizeFile << "size: " << h->sizeofMap() << "bytes" << endl;
	
	timeFile << "Search stored entries" << endl;
  while (getline(searchStoredInput, line)) {
    // Create a stringstream of the current line
    stringstream ss(line);
    ss >> numberOfSearches;
		ss.ignore();
    begin_time = clock();
    for (int i = 0; i < numberOfSearches; i++) {
      getline(ss, searchName, ',');
			isFound = h -> search(searchName);
      if (!isFound)
      {
        cout << "warning: name not found " << searchName << endl;
      }
    }
    end_time = clock();
    timeFile << "\n" << numberOfSearches << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
		whateverFile << float( end_time - begin_time ) /  CLOCKS_PER_SEC << ",";
  }
  
  whateverFile << "\n";
  timeFile << "search NOT stored entries" << endl;
  while (getline(searchNotStoredInput, line)) {
    // Create a stringstream of the current line
    stringstream ss(line);
    ss >> numberOfSearches;
		ss.ignore();
    begin_time = clock();
    for (int i = 0; i < numberOfSearches; i++) {
      getline(ss, searchName, ',');
      isFound = h -> search(searchName);
      if (isFound)
      {
        cout << "warning: number found" << endl;
      }
    }
    end_time = clock();
    timeFile << "\n" << numberOfSearches << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
		whateverFile << float( end_time - begin_time ) /  CLOCKS_PER_SEC << ",";
  }

	return 0;
}
