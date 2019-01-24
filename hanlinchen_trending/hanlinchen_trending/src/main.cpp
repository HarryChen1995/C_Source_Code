#include<iostream>
#include<string>
#include<sstream>
#include <vector>
#include <fstream>
using namespace std;
#include"Hashtag.h"
#include "File.h"
int main(int argc, char* argv[]) {
	File twitter;   
	twitter.processendfile(argv[2]); // process the start file 
	twitter.processstarfile(argv[1]);// process the endfile 
	twitter.combine(); // combine the information 
	twitter.print(argv[3]); // ouput the trending 
	return 0;
}
