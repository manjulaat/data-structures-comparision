#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;
/*
 * Node Declaration
 */
struct node
{
  string userName;
  struct node * left;
  struct node *right;
}* root;
 
/*
 * Class Declaration
 */
class BST
{
  public:
    bool search(string);  
    void insert(node *, node *);
    void case_a(node *,node *);
    void case_b(node *,node *);
    void case_c(node *,node *);
    unsigned long long size(node *);
    void display(node *, int);
    BST()
    {
      root = NULL;
    }
};
/*
 * Main Contains Menu
 */
int main()
{

  int choice, num, numberOfSearches;
  BST bst;
  node *temp;
  bool isFound;
  string line;
  int val;
  string searchName;

  ifstream dataInputFile("../../input/universities_followers.csv");
  ifstream searchStoredInput("../../input/stored_names.csv");
  ifstream searchNotStoredInput("../../input/not_stored_names.csv");
  ofstream timeFile("../../output/userName/bstTime.txt");
	ofstream whateverFile("../../whatever.csv");
  ofstream sizeFile("../../output/userName/bstSize.txt");
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

    temp = new node;
    getline(ss, temp -> userName, ',');
    bst.insert(root, temp);
    if (lineCount == 1000 || lineCount == 5000 || lineCount == 10000 || lineCount == 15000 || lineCount == 20000) {
      end_time = clock();
      timeFile << "\n" << lineCount << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
			whateverFile << float( end_time - begin_time ) / CLOCKS_PER_SEC << ",";
    }
  }

  
	whateverFile << "\n";
	// Close file
  dataInputFile.close();

  sizeFile << "size: " << bst.size(root) << endl;


  timeFile << "Search stored entries" << endl;
  while (getline(searchStoredInput, line)) {
    // Create a stringstream of the current line
    stringstream ss(line);
    ss >> numberOfSearches;
		ss.ignore();
    begin_time = clock();
    for (int i = 0; i < numberOfSearches; i++) {
      getline(ss, searchName, ',');
      // ss >> searchName;
      isFound = bst.search(searchName);
      if (!isFound)
      {
        cout << "warning: name not found" << searchName << i << endl;
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
      ss >> searchName;
      isFound = bst.search(searchName);
      if (isFound)
      {
        cout << "warning: name found" << endl;
      }
    }
    end_time = clock();
    timeFile << "\n" << numberOfSearches << " entries:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
		whateverFile << float( end_time - begin_time ) /  CLOCKS_PER_SEC << ",";
  }
}
 
/*
 * search Element in the Tree
 */
bool BST::search(string item)
{
  node *ptr, *ptrsave;
  if (root == NULL)
  {
    return false;
  }
  if ((item.compare(root->userName)) == 0)
  {
    return true;
  }
  if ((item.compare(root->userName)) < 0)
    ptr = root->left;
  else
    ptr = root->right;
  ptrsave = root;
  while (ptr != NULL)
  {
    if ((item.compare(ptr->userName)) == 0)
    {
      return true;
    }
    ptrsave = ptr;
    if ((item.compare(ptr->userName)) < 0)
      ptr = ptr->left;
    else
      ptr = ptr->right;
  }
  return false;
}

unsigned long long BST::size(node* node)  {  
  if (node == NULL)  
    return 0;  
  else {
    return (size(node->left) + sizeof(node) + size(node->right));
  }
}
 
/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode)
{
  if (root == NULL)
  {
    root = new node;
    root->userName = newnode->userName;
    root->left = NULL;
    root->right = NULL;
    return;
  }
  if ((tree->userName.compare(newnode->userName)) == 0)
  {
    // cout << "warning: Duplicate entry" << endl;
    return;
  }
  if ((tree->userName.compare(newnode->userName)) > 0)
  {
    if (tree->left != NULL)
    {
      insert(tree->left, newnode);	
	}
	else
	{
      tree->left = newnode;
      (tree->left)->left = NULL;
      (tree->left)->right = NULL;
      return;
    }
  }
  else
  {
    if (tree->right != NULL)
    {
      insert(tree->right, newnode);
    }
    else
    {
      tree->right = newnode;
      (tree->right)->left = NULL;
      (tree->right)->right = NULL;
      return;
    }	
  }
}
 
/*
 * Case A
 */
void BST::case_a(node *par, node *loc )
{
  if (par == NULL)
  {
    root = NULL;
  }
  else
  {
    if (loc == par->left)
      par->left = NULL;
    else
      par->right = NULL;
  }
}
 
/*
 * Case B
 */
void BST::case_b(node *par, node *loc)
{
  node *child;
  if (loc->left != NULL)
    child = loc->left;
  else
    child = loc->right;
  if (par == NULL)
  {
    root = child;
  }
  else
  {
    if (loc == par->left)
      par->left = child;
    else
      par->right = child;
  }
}
 
/*
 * Case C
 */
void BST::case_c(node *par, node *loc)
{
  node *ptr, *ptrsave, *suc, *parsuc;
  ptrsave = loc;
  ptr = loc->right;
  while (ptr->left != NULL)
  {
    ptrsave = ptr;
    ptr = ptr->left;
  }
  suc = ptr;
  parsuc = ptrsave;
  if (suc->left == NULL && suc->right == NULL)
    case_a(parsuc, suc);
  else
    case_b(parsuc, suc);
  if (par == NULL)
  {
    root = suc;
  }
  else
  {
    if (loc == par->left)
      par->left = suc;
    else
      par->right = suc;
  }
  suc->left = loc->left;
  suc->right = loc->right;
}
