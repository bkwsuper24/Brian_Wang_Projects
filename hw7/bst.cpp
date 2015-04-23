#include <iostream>
#include "rbbst.h"

using namespace std;

int main()
{
	RedBlackTree<double, int> *rbtree = new RedBlackTree<double, int>;

	pair<int,int> test;
	test = std::make_pair(2,2);

	pair<int,int> test1;
	test1 = std::make_pair(5,5);

	pair<int,int> test2;
	test2 = std::make_pair(10,10);

	pair<int,int> test3;
	test3 = std::make_pair(3,3);

	pair<int,int> test4;
	test4 = std::make_pair(20,20);

	pair<int,int> test5;
	test5 = std::make_pair(75,75);

	pair<int,int> test6;
	test6 = std::make_pair(1,1);

	pair<int,int> test7;
	test7 = std::make_pair(11,11);

	pair<int,int> test8;
	test8 = std::make_pair(7,7);

	rbtree->insert(test);
	rbtree->insert(test1);
	rbtree->insert(test2);
	rbtree->insert(test3);
	rbtree->insert(test4);
	rbtree->insert(test5);
	rbtree->insert(test6);
	rbtree->insert(test7);
	rbtree->insert(test8);

	RedBlackTree<double, int>::iterator it(NULL);
	it = rbtree->begin();

	//test to see if begin works. This should print 1
	cout << "Test to see if begin works - Begin Key:  " << (*it).second << endl;

	//check to see if == works for iterator
	/*pair<int, int> specTest;
	specTest = std::make_pair(5,5);

	RedBlackNode<int, int> *tempRBN = new RedBlackNode<int,int>(test1.first, test1.second, NULL);
	RedBlackTree<int, int>::iterator it1(tempRBN);

	RedBlackNode<int, int> *tempRBN1 = new RedBlackNode<int, int>(specTest.first, specTest.second, NULL);
	RedBlackTree<int, int>::iterator it2(tempRBN1);

	if(it1 == it2)
	{
		cout << "Comparison worked!" << endl;
	}
	*/


	//RedBlackTree<int, int>::iterator iter(rbtree.begin());

	//printing out using iterator

	for(RedBlackTree<double, int>::iterator iter = rbtree->begin(); iter != rbtree->end(); ++iter)
	{
		cout << "KeyValue: " << (*iter).first << " " << "ValueType: " << (*iter).second << endl;
	}

	return 0;
}