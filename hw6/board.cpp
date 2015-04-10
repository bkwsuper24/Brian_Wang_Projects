#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(const Board& bd)
{
  _tiles = new int[bd.size()];
  _size = bd.size();

  for(int i=0; i<bd.size(); i++)
  {
    _tiles[i] = bd[i];
  }
}

Board::~Board()
{
  delete [] _tiles;


}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> possboard;
  int blankrow;
  int blankcol;
  int dimension = dim();

  int j=-1;
  while(_tiles[++j] != 0)
  {
    blankcol = j % dimension;
    blankrow = j/dimension;
  }

  int north, south, east, west;

  //west
  if(blankcol-1 >=0)
  {
    west = j-1;
    Board* westboard = new Board(*this);
    westboard->move(_tiles[west]);
    possboard.insert(make_pair(_tiles[west], westboard));
  }
  //east
  else if(blankcol+1 <= dimension-1)
  {
    east = j+1;
    Board* eastboard = new Board(*this);
    eastboard->move(_tiles[east]);
    possboard.insert(make_pair(_tiles[east], eastboard));
  }
  //north
  else if(blankrow-1 >=0)
  {
    north = j-1;
    Board* northboard = new Board(*this);
    northboard->move(_tiles[north]);
    possboard.insert(make_pair(_tiles[north], northboard));
  }
  //south
  else if(blankrow+1 <= dimension-1)
  {
    south = j+1;
    Board* southboard = new Board(*this);
    southboard->move(_tiles[south]);
    possboard.insert(make_pair(_tiles[south], southboard));
  }

  return possboard;  
}

ostream& operator<<(ostream &os, const Board &b)
{
  int dimension = b.dim();
  for(int i=0; i<dimension; i++)
  {
    b.printRowBanner(os);
    for(int j=0; j<dimension; j++)
    {
      os<<"|";
      if(b[i*dimension+j] != 0)
      {
        os <<" "<< b[i*dimension+j];
      }
      else
      {
        os << "  ";
      }
    }
    os<<"|";
    os << endl;
  }
  b.printRowBanner(os);
  return os;
}

bool Board::operator<(const Board& rhs) const
{
  for(int i=0; i<_size; i++)
  {
    if(rhs[i] < _tiles[i])
    {
      return false;
    }
    else if(_tiles[i] < rhs[i])
    {
      return true;
    }
    else
    {
      continue;
    }
  }
  return false;
}


bool Board::solved() const
{
  int counter = 0;
  for(int i=0; i < _size; i++)
  {
    if(_tiles[i] == i)
    {
      counter++;
    }
  }

  if(counter == _size)
  {
    return true;
  }
  
  return false;
}


const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
