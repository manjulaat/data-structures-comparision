// CPP program to implement hashing with chaining 
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;

class Hash {
	int BUCKET; // No. of buckets 
  int length;

	// Pointer to an array containing buckets 
	list<unsigned long long> *table;
public: 
	Hash(int V); // Constructor 

	// inserts a key into hash table 
	void insertItem(unsigned long long x);

	// deletes a key from hash table 
	bool search(unsigned long long key);

  int size() {
    return length * 8;
  }

	// hash function to map values to key 
	int hashFunction(unsigned long long x) {
		return (x % BUCKET);
	}

};

Hash::Hash(int b) {
	this->BUCKET = b;
  this -> length = 0;
	table = new list<unsigned long long>[BUCKET];
}

void Hash::insertItem(unsigned long long key) {
	int index = hashFunction(key);
  length++;
	table[index].push_back(key);
}

bool Hash::search(unsigned long long key) {
	// get the hash index of key 
	int index = hashFunction(key);

	// find the key in (inex)th list 
	list <unsigned long long> :: iterator i;
	for (i = table[index].begin();
			i != table[index].end(); i++) {
		if (*i == key) 
		break;
	}

	// if key is found in hash table, remove it 
	if (i != table[index].end()) 
		return true;
	return false;
}

int main() {

  int choice, num, numberOfSearches;
  bool isFound;
  string line;
  int val;
  unsigned long long searchNum, tempNum;
	Hash h(1000);

  ifstream dataInputFile("../../input/universities_followers.csv");
  ifstream searchStoredInput("../../input/stored_user_ids.csv");
  ifstream searchNotStoredInput("../../input/not_stored_user_ids.csv");
  ofstream timeFile("../../output/userId/hashOpenTime.txt");
	ofstream whateverFile("../../whatever.csv");
  ofstream sizeFile("../../output/userId/hashOpenSize.txt");
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
    
		h.insertItem(tempNum);
    if (lineCount == 1000 || lineCount == 5000 || lineCount == 10000 || lineCount == 15000 || lineCount == 20000) {
      end_time = clock();
      timeFile << "\n" << lineCount << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
			whateverFile << float( end_time - begin_time ) / CLOCKS_PER_SEC << ",";
    }
	}


  
	whateverFile << "\n";
	// Close file
  dataInputFile.close();
  sizeFile << "size: " << h.size() << "bytes" << endl;


  timeFile << "Search stored entries" << endl;
  while (getline(searchStoredInput, line)) {
    // Create a stringstream of the current line
    stringstream ss(line);
    ss >> numberOfSearches;
    begin_time = clock();
    for (int i = 0; i < numberOfSearches; i++) {
      ss.ignore();
      ss >> searchNum;
      isFound = h.search(searchNum);
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
      isFound = h.search(searchNum);
      if (isFound)
      {
        cout << "warning: number found" << endl;
      }
    }
    end_time = clock();
    timeFile << "\n" << numberOfSearches << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
		whateverFile << float( end_time - begin_time ) /  CLOCKS_PER_SEC << ",";
  }
}