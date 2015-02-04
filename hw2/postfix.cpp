#include "stackdbl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

double calculate(string& expr, bool& success)
{
	//create instance of StackDbl
	StackDbl stack; 
	stringstream ss;
	ss << expr;
	double finalnumber;
	//to keep track of stack size
	int counter = 0;
	
	while (!ss.eof())
	{
		int input;
		//stringstream ss;
		ss >> input; 
		stack.push(input);
		counter++;
		
		if (ss.fail())
		{
			char operand;
			ss >> operand;
			if (stack.empty() == false)
			{
				success = false;
				break;
			}
	
			if (operand == '+' && counter>=2)
			{
				double firstnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				double secondnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				finalnumber = firstnumber + secondnumber;
			}
			else if (operand == '-' && counter>=2)
			{
				double firstnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				double secondnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				finalnumber = secondnumber - firstnumber;
			}
			else if (operand == '*' && counter>=2)
			{
				double firstnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				double secondnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				finalnumber = firstnumber * secondnumber;
			}
			else if (operand == '/' && counter>=2)
			{
				double firstnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				double secondnumber = stack.top();
				stack.pop();
				//decrement counter
				counter--;
				finalnumber = secondnumber / firstnumber;
			}
			stack.push(finalnumber);
			//increment counter
			counter++;
		}
	}
	if(counter == 1)
	{
		success = true;
	}
	else
	{
		success = false;
	}
			
	//stack.pop(); 

	return finalnumber;
}

int main(int argc, char* argv[])
{
	bool success;
	
	if(argc < 3)
	{
		cout << "Not enough arguments provided." << endl;
		return -1;
	}

	ifstream inputfile;
	//opening input file
	inputfile.open(argv[1]);
	//reading to output file
	ofstream outputfile(argv[2]);

	while (!inputfile.fail())
	{
		string temp; 
		getline(inputfile, temp);

		double total_value = calculate(temp, success);

		if(success == false)
		{
			outputfile << "invalid" << endl;
		}

		else if (success == true)
		{
			outputfile << total_value << endl;
		}
	}

	return 0;
}


