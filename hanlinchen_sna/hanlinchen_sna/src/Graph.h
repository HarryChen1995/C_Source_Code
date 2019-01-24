#ifndef GRAPH_H
#define GRAPH_H
#include"User.h"
#include<fstream>
#include<algorithm>
#include<queue>
/////////////////////////////////////////////////
/* this file contain the basic graph structure and declaration of each fucntiion performs requried functionality 
*/
////////////////////////////////////////////////
class Graph {
private:vector<User*> netUser; // this variable store the entire graph structure 
		vector<User*> User_depth3;// this varible store the all the user node within depth 3
		vector<User*>  depth2_3; // this varibel sorte the all the user node from depth 2 to the depth 3 
		User* rootuser; // the varible store the root user 
public:
	Graph(); // default construtor 
	User* search(string _name); // esearch the user by user name 
	bool Readinputfile(char* filename); // the prcosseed input file 
	void BTS(char* rootname); // implemeting the breadth first search 
	void Writeoutputfile(char* filename); // read the result to the output file 

};
#endif
