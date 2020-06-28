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
  unsigned long long userId;
  struct node * left;
  struct node *right;
}* root;
 
/*
 * Class Declaration
 */
class BST
{
  public:
    bool search(unsigned long long);  
    void insert(node *, node *);
    void case_a(node *,node *);
    void case_b(node *,node *);
    void case_c(node *,node *);
    int leftHeight(node *);
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
  unsigned long long searchNum;

  ifstream dataInputFile("../../input/universities_followers.csv");
  ifstream searchStoredInput("../../input/stored_user_ids.csv");
  ifstream searchNotStoredInput("../../input/not_stored_user_ids.csv");
  ofstream timeFile("../../output/userId/bstTime.txt");
	ofstream whateverFile("../../whatever.csv");
  ofstream sizeFile("../../output/userId/bstSize.txt");
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

    temp = new node;
    ss >> temp -> userId;
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
  
  sizeFile << "size: " << bst.size(root) * 8 << "bytes" << endl;


  timeFile << "Search stored entries" << endl;
  while (getline(searchStoredInput, line)) {
    // Create a stringstream of the current line
    stringstream ss(line);
    ss >> numberOfSearches;
    begin_time = clock();
    int count = 0;
    for (int i = 0; i < numberOfSearches; i++) {
      ss.ignore();
      ss >> searchNum;
      isFound = bst.search(searchNum);
      if (!isFound)
      {
        count++;
        cout << "warning: number not found" << count << endl;
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
      isFound = bst.search(searchNum);
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
 
/*
 * search Element in the Tree
 */
bool BST::search(unsigned long long item)
{
  node *ptr, *ptrsave;
  if (root == NULL)
  {
    return false;
  }
  if (item == root->userId)
  {
    return true;
  }
  if (item < root->userId)
    ptr = root->left;
  else
    ptr = root->right;
  ptrsave = root;
  while (ptr != NULL)
  {
    if (item == ptr->userId)
    {
      return true;
    }
    ptrsave = ptr;
    if (item < ptr->userId)
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
    return(size(node->left) + sizeof(node) + size(node->right));
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
    root->userId = newnode->userId;
    root->left = NULL;
    root->right = NULL;
    return;
  }
  if (tree->userId == newnode->userId)
  {
    return;
  }
  if (tree->userId > newnode->userId)
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

int BST::leftHeight(node *some) {
  if (some == NULL) {
    return -1;
  }
  int lefth = leftHeight(some -> left);
  int righth = leftHeight(some -> right);

  if (lefth > righth) {
      return lefth + 1;
  } else {
      return righth + 1;
  }
}

/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"Root->:  ";
        else
        {
                cout<<endl;
	}
        cout<<ptr->userId;
        display(ptr->left, level+1);
    }
}
