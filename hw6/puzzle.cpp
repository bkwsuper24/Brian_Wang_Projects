#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5)
  {
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int size = atoi(argv[1]);
  int initMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);

  Board* puzzBoard = new Board(size, initMoves, seed);

  PuzzleHeuristic *ph = NULL;
  
  if(heur == 0)
  {
  	ph = new PuzzleBFSHeuristic();
  }
  else if(heur == 1)
  {
  	ph = new PuzzleOutOfPlaceHeuristic();
  }
  else if(heur == 2)
  {
  	ph = new PuzzleManhattanHeuristic();
  }

  cout << *puzzBoard; 
  int input;

  while(!puzzBoard->solved())
  {
    cout << "Enter tile number to move or -1 for a cheat: " << endl;
    cin >> input;

    if(input > 0 && input < pow(size,2))
    {
      puzzBoard->move(input);
      cout << *puzzBoard;
    }
    else if(input == -1)
    {
      
      PuzzleSolver* solver = new PuzzleSolver(*puzzBoard, ph);
      solver->run();
      cout << "Try this sequence: ";
      deque<int> solution = solver->getSolution();
      for(unsigned int i=0; i<solution.size(); i++)
      {
        cout << solution[i] << " ";
        cout << endl; 
        cout << "(Expansions = " << solver->getNumExpansions() << ")" << endl;
        solution.pop_front();
      }
    }
    else if(input == 0)
    {
      delete puzzBoard;
      //delete solver;
      delete ph;
      break;
    }
  }
}
