#include "puzzle_move.h"

using namespace std;

PuzzleMove::PuzzleMove(Board* board)
{
	b = board;
	prev = NULL;
	g = 0;


}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
	b = board;
	prev = parent;
	g = parent->g+1;
}

PuzzleMove::~PuzzleMove()
{

}