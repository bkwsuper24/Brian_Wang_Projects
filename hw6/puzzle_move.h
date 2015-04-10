#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include "board.h"

using namespace std;

struct PuzzleMove
{
  // Data members can be public
  int tileMove;  // tile moved to reach the Board b
  Board *b;      // Pointer to a board representing the updated state
  int g;         // distance from the start board
  int h;         // heuristic distance to the goal
  PuzzleMove *prev;  // Pointer to parent PuzzleMove


  // Constructor for starting Board (i.e. initial move)
  PuzzleMove(Board* board);

  // Constructor for subsequent search boards 
  // (i.e. those returned by Board::potentialMoves() )
  PuzzleMove(int tile, Board* board, PuzzleMove *parent);

  // Destructor
  ~PuzzleMove();

};


struct PuzzleMoveScoreComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    int tot1 = (m1->g) + (m1->h);
    int tot2 = (m2->g) + (m2->h);
    if(tot1 < tot2)
    {
      return true;
    }
    else if(tot1 == tot2)
    {
      if(m1->h < m2->h)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    return false;
    // Add code to check if m1's f-score is less than m2's
    // If both have the same f-score, break ties by using 
    // the checking if m1's h-score is less than m2's
  }
};

struct PuzzleMoveBoardComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    Board* b1;
    Board* b2;
    b1 = m1->b;
    b2 = m2->b;

    // Add code to check if m1's board is "less-than" m2's board by 
    // using the Board class' operator<()
    if(*b1 < *b2)
    {
      return true;
    }
    return false;
  }
};

#endif
