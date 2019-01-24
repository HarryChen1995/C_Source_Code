#include<iostream>
using namespace std;
#include"User.h"
#include "Graph.h"
int main(int argc, char* argv[]) {
	if (argc != 4) { // check the command line argument 
		cout << "Usage: sna inputFile userName outputFile" << endl; // print out the usage message 
		return 0;
	}
	Graph a; // initializes the graph varible 
	if (a.Readinputfile(argv[1])) {// if process the input file successfully then implementing the BTS algrithm 
		a.BTS(argv[2]);
	}
	a.Writeoutputfile(argv[3]); // write the output to outputfile 
	return 0;
}