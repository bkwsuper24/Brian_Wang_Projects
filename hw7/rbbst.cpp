#include "rbbst.h"

int main(){
	RedBlackTree <double, double> *test = new RedBlackTree<double, double>();
	RedBlackNode<double, double> *rootrbn;
	rootrbn = NULL;
	if(rootrbn == NULL){
		std::cout << "empty node" << std::endl;
	}
	test->insert(std::make_pair (12, 3));
	test->insert(std::make_pair (5, 10));
	test->insert(std::make_pair (15, 56));
	test->insert(std::make_pair (3, 11));
	
	test->insert(std::make_pair (10, 5));
	test->insert(std::make_pair (13, 8));
	test->insert(std::make_pair (17, 12));
	test->insert(std::make_pair (4, 54));
	test->insert(std::make_pair (7, 17));
	test->insert(std::make_pair (11, 8));
	test->insert(std::make_pair (14, 8));
	test->insert(std::make_pair (6, 8));
	test->insert(std::make_pair (8, 8));
	test->insert(std::make_pair (1, 19));
	test->insert(std::make_pair(13.5, 100));
	test->insert(std::make_pair(14.5, 200));
	test->insert(std::make_pair(9, 700));
	




	test->print();
}