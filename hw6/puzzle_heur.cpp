#include "puzzle_heur.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "board.h"

using namespace std;


int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int total = 0;

	int wrongr;
	int wrongc;
	int rightr;
	int rightc;

	for(int i=0; i<b.size(); i++)
	{
		//not blank tile
		if(b[i] !=0)
		{
			int dimension = b.dim();
			wrongr = i/dimension;
			wrongc = i%dimension;
			rightr = b[i]/dimension;
			rightc = b[i]%dimension;
		}
	}

	total += abs(rightr - wrongr) + abs(rightc - wrongc);
	return total;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int ofp_val = 0;

	for(int i=0; i<b.size(); i++)
	{
		if(b[i] != 0 && b[i] != i)
		{
			ofp_val++;
		}
	}
	return ofp_val;
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}