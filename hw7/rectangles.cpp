#include <iostream>

using namespace std;

//prototypes

void createBoard(string line);
//void printBoard(int** board);
bool isValid(int len, int height, int** board);
void Tiles();
void TileHelper(int len, int height, int** board);
void verify();

struct Rectangle
{
	int ID;
	int length;
	int height;
};

//Global Variables
int tot_len;
int tot_height;
int tot_tiles;

//Instantiate RedBlackTree
RedBlackTree<int, Rectangle*> potential_tree;
RedBlackTree<int, pair<int, int> > solution_tree; 

int main(int argc, char *argv[])
{
	//Parse Time!
	if(argc < 3)
	{
		cerr << "Wrong format: ./rectangles input.txt output.txt" << endl;
	}

	ifstream inputfile;
	inputfile.open(argv[1]);

	string input;
	stringstream ss;
	getline(inputfile, input);

	//converting into variables
	ss << input;
	ss >> tot_len;
	ss >> tot_height;
	ss >> tot_tiles;

	string buffer;
	//reading file
	while(!inputfile.eof())
	{
		getline(inputfile, buffer);
		createBoard(buffer);
	}

	inputfile.close();
	return 0;
}

void createBoard(string line)
{
	Rectangle *rect = new Rectangle;

	int length;
	int height;
	int ID;

	stringstream ss;

	ss << line;
	ss >> ID;
	ss >> length;
	ss >> height;


	//create 2D Array board
	int **board = new int*[tot_height];

	for(int i=0; i<tot_height; i++)
	{
		board[i] = new int[tot_len];
	}

	//initialize board with -1 to mark as not visited

	for(int i=0; i<tot_height; i++)
	{
		for(int j=0; j<tot_len; j++)
		{
			board[i][j] = -1;
		}
	}

	//still need to write valid moves for placing board
}

bool Sudoku::isValid(int length, int height, int** board) 
{


  int value = board[row][col];

  for (int i=0; i<9; i++) {
    if (i == length) {
    continue;
    }
    
    int temp = board[i][height];
    if (temp == value) {
      return false;
    }
  }
  
  for (int i=0; i<9; i++) {
      if (i == height) {
      continue;
    }
    
    int temp = board[length][i];
    if (temp == value) {
      return false;
    }
  }
  
  int box_length = length / 3; 
  int box_height = height / 3; 
  
  for (int i=box_length * 3; i < box_length * 3 + 3; i++) {
    for (int j=box_height * 3; j < box_height * 3 + 3; j++) {
      if (i == length && j == height) {
        continue;
      }
      
      int temp = board[i][j];
      if (temp == value) {
        return false;
      }
    }
  } 
  return true;
}

void verify() 
{
  for(int i = 0; i < 9; i++) 
  {
    for(int j = 0; j < 9; j++) 
    {
      if(!isValid(i, j)) 
      {
        cout << "INVALID TILE" << endl;
        return;
      }
    }
  }
  cout << "VALID TILE" << endl;
}



