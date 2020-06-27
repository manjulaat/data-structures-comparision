#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;

//template for generic type 
template<typename K, typename V> 

//Node class 
class Node {
	public: 
	V value;
	K key;
	
	//Constructor of Node 
	Node(K key, V value) {
		this->value = value;
		this->key = key;
	}
};

//template for generic type 
template<typename K, typename V> 

//Our own Hashmap class 
class HashMap {
	//hash element array 
	Node<K,V> **arr;
	int capacity;
	//current size 
	int size;
	//dummy node 
	Node<K,V> *dummy;

	public: 
	HashMap() {

		//Initial capacity of hash array 
		capacity = 22000;
		size=0;
		arr = new Node<K,V>*[capacity];
		
		//Initialise all elements of array as NULL 
		for(int i=0 ; i < capacity ; i++) 
			arr[i] = NULL;
		
		//dummy node with value and key -1 
		dummy = new Node<K,V>(-1, -1);
	}
	// This implements hash function to find index 
	// for a key 
	int hashCode(unsigned long long key) {

		return key % capacity;
	}
	
	//Function to add key value pair 
	void insertNode(K key, V value) {

		Node<K,V> *temp = new Node<K,V>(key, value);
		
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);
		
		//find next free space 
		while(arr[hashIndex] != NULL && arr[hashIndex]->key != key 
			&& arr[hashIndex]->key != -1) {
			hashIndex++;
			hashIndex %= capacity;
		}
		size++;
		arr[hashIndex] = temp;
	}
	
	//Function to search the value for a given key 
	V search(unsigned long long key) {

		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);
		int counter=0;
		//finding the node with given key 
		while(arr[hashIndex] != NULL) {
			int counter =0;
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
  unsigned long long searchNum, tempNum;
	HashMap<unsigned long long, unsigned long long> *h = new HashMap<unsigned long long, unsigned long long>;
  ifstream dataInputFile("../../input/universities_followers.csv");
  ifstream searchStoredInput("../../input/stored_user_ids.csv");
  ifstream searchNotStoredInput("../../input/not_stored_user_ids.csv");
  ofstream timeFile("../../output/userId/hashClosedTime.txt");
	ofstream whateverFile("../../whatever.csv");
  ofstream sizeFile("../../output/userId/hashClosedSize.txt");
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
    
		ss >> tempNum;
		
		h->insertNode(tempNum,tempNum);
    if (lineCount == 1000 || lineCount == 5000 || lineCount == 10000 || lineCount == 15000 || lineCount == 20000) {
      end_time = clock();
      timeFile << "\n" << lineCount << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
			whateverFile << float( end_time - begin_time ) / CLOCKS_PER_SEC << ",";
    }
  }
	whateverFile << "\n";
	// Close file
  dataInputFile.close();
  sizeFile << "size: " << h->sizeofMap() << endl;
	
	timeFile << "Search stored entries" << endl;
  while (getline(searchStoredInput, line)) {
    // Create a stringstream of the current line
    stringstream ss(line);
    ss >> numberOfSearches;
    begin_time = clock();
    for (int i = 0; i < numberOfSearches; i++) {
      ss.ignore();
      ss >> searchNum;
      isFound = h -> search(searchNum);
      if (!isFound)
      {
        cout << "warning: number not found" << endl;
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
    begin_time = clock();
    for (int i = 0; i < numberOfSearches; i++) {
      ss.ignore();
      ss >> searchNum;
      isFound = h -> search(searchNum);
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
