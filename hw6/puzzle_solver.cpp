#include <iostream>
#include "puzzle_solver.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) :
	_b(b), _ph(ph)
{
	_expansions = 0;
}

PuzzleSolver::~PuzzleSolver()
{


}

std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}

int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}


void PuzzleSolver::run()
{
	//create the puzzle Move
	PuzzleMove* pm = new PuzzleMove(&_b);
	pm->h = _ph->compute(_b);

	PuzzleMoveScoreComp mscore;
	PuzzleMoveBoardComp mboard;

	PuzzleMove* done;

	PuzzleMoveSet closedList(mboard);

	Heap<PuzzleMove*, PuzzleMoveScoreComp> openList(2, mscore);

	openList.push(pm);
	closedList.insert(pm);

	while(!openList.empty())
	{
		PuzzleMove* n = openList.top();
		openList.pop();

		if(n->b->solved())
		{
			done = n;
		}
		map<int, Board*>potentialmoves = n->b->potentialMoves();
		map<int, Board*>::iterator it;

		for(it=potentialmoves.begin(); it !=potentialmoves.end(); it++)
		{
			PuzzleMove* temp_pm = new PuzzleMove(it->first, it->second, n);
			//Heuristic calculation
			temp_pm->h = _ph->compute(*(temp_pm->b));
			temp_pm->g = n->g+1;

			PuzzleMoveSet::iterator itt = closedList.find(temp_pm);

			//Not in closed list
			if(itt == closedList.end())
			{
				//updating expansion, lists, scores
				openList.push(temp_pm);
				closedList.insert(temp_pm);
				_expansions++;
			}
			else
			{
				delete temp_pm;
			}
		}
	}

	PuzzleMove* solution = openList.top();
	while(solution->tileMove != 0)
	{
		_solution.push_front(solution->tileMove);
		solution=solution->prev;
	}

}