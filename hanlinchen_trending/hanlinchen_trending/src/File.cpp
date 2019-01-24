#include <iostream>
#include<sstream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
#include "File.h"
/* this class include two private varible such as endfile and starfile and my program process endfile fisrt and load all hashtag 
into the enfile varible and starfile so on. after all the hashtag has been loaded into these two varible, my programm start to count
number of samehashtag has used in the file.  and then print out the trending of each hashtag in from start file to end file 
*/

File::File() {

}

// setter 
void File::setFile(vector<Hashtag> a) {
	starfile = a;
}


// getter 
vector<Hashtag> File::getFile() const {
	return starfile;  
}
// this function is to print out the difference of rank from start file to endfile.
string File::RD(Hashtag a) {
	ostringstream t;  string p;
	if (a.getStartRank() == 0) { // if there is a tied of rank 
		t<< "(new)"<<endl;
	}
	else {  
		if (a.getStartRank() -a.getEndRank() > 0) {// if the strat rank is greater than the end rank and printout the plus sign 
			t << "(" << "+" << a.getStartRank() - a.getEndRank() << ")" << endl;
		}
		else if (a.getStartRank() -a.getEndRank() == 0) {// if the rank keep same ,print out +0
			t<< "(+0)" << endl;
		}
		else if (a.getStartRank() - a.getEndRank()<0) {
			t << "(" <<a.getStartRank() - a.getEndRank() << ")" << endl;
		}
	}
	p = t.str();  // return the string 
	return p;
}
// this function is to print out the all ranked hashtag 
void File::print(char *filename) {
	ofstream file; 
	file.open(filename);
	if (!file.is_open()) {
		cout << "failed" << endl;
	}
	int i = 0;
	for (i = 0; i < static_cast<int>(endfile.size()); i++) {
		if (i != 0 && i != static_cast<int>(endfile.size()-1) && (endfile.at(i).getEndRank() == endfile.at(i + 1).getEndRank() || endfile.at(i).getEndRank() == endfile.at(i - 1).getEndRank())) {
			file << "T" << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}
		if (i != 0 && i != static_cast<int>(endfile.size() - 1)&& (endfile.at(i).getEndRank() != endfile.at(i + 1).getEndRank() && endfile.at(i).getEndRank() != endfile.at(i - 1).getEndRank())) {
			file << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}
		if (i == 0&&static_cast<int>(endfile.size())>1&&endfile.at(i).getEndRank() == endfile.at(i + 1).getEndRank()) {
			file << "T" << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}
		if (i == 0 && static_cast<int>(endfile.size())>1&&endfile.at(i).getEndRank() != endfile.at(i + 1).getEndRank()) {
			file << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}

		if (i == static_cast<int>(endfile.size() - 1)&& static_cast<int>(endfile.size())>1&& endfile.at(i).getEndRank() == endfile.at(i - 1).getEndRank()) {
			file << "T" << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}
		if (i == static_cast<int>(endfile.size() - 1)&& static_cast<int>(endfile.size())>1&&endfile.at(i).getEndRank() != endfile.at(i - 1).getEndRank()) {
			file << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}
		if (static_cast<int>(endfile.size()) == 1) {
			file << endfile.at(i).getEndRank() << ":" << " " << endfile.at(i).getWord() << " ";
			file << RD(endfile.at(i));
		}
	}
}


// this function is to conver all letter to lower case.
string File::convert(string a) {
	int i = 0;
	string convert;
	for (i = 0; i < static_cast<int>(a.length()); i++) { // start from the very begning of string 
		convert+=tolower(a[i]);// convert all letter to lower case 
	}
	return convert; // return the string 
}

// this function is to process the end file firt and load all hashtag into private varible  endfile .
void File::processendfile(char* filename) {
	ifstream file; string k;int i = 0; vector<string> linebuffer; int endcount = 0; int rank = 1; 
	file.open(filename);
	if (!file.is_open()) {
		cout << "faile" << endl;
	}
	while (file.good()) {
		if (!(file >> k)) {
			break;
		}
		
	    linebuffer.push_back(convert(k)); // read all the hashtag infile into a string vector linebuffer
	}
	file.close();
	sort(linebuffer.begin(), linebuffer.end());// sort the linebuffer for counting each identical hashtag 
	for (i = 0; i < static_cast<int>(linebuffer.size()); i++) {// this forloop is to count number of each hashtag and load it into the endfile private variable 
		endcount++;
		if (i != static_cast<int>(linebuffer.size() - 1 )&& linebuffer.at(i) != linebuffer.at(i + 1)) {
			endfile.push_back(Hashtag(linebuffer.at(i), 0, endcount));
			endcount = 0;
		}
		else if (i == static_cast<int>(linebuffer.size() - 1)) {
			endfile.push_back(Hashtag(linebuffer.at(i), 0, endcount));
		}
	}
	sort(endfile.begin(), endfile.end()); // after counting each hashtag , sort endfile varibl for ranking 
	for (i = 0; i < static_cast<int>(endfile.size()); i++) { // ranking each hashtag from top to bottom
		endfile.at(i).setEndRank(rank);
		endfile.at(i).setStartRank(0);
		if (i != static_cast<int>(endfile.size() - 1 )&& endfile.at(i).getEndCount() != endfile.at(i + 1).getEndCount())
			rank++;
	}
}
// this function is to process the start file firt and load all hashtag into private varible  starfile .
void File::processstarfile(char *filename) {
	ifstream file;  string k; int i = 0; int count = 0; int rank=1; vector<string> linebuffer;
	file.open(filename);
	if (!file.is_open()) {
		cout << "faile" << endl;
	}
	while (file.good()) {
		if(!(file>> k)){
			break;
		}
		linebuffer.push_back(convert(k));// sort the linebuffer for counting each identical hashtag 
	}
	sort(linebuffer.begin(), linebuffer.end()); //this forloop is to count number of each hashtag and load it into the starfile private variable
	// this forloop is to count number of each hashtag and load it into the starfile private variable 
	for (i = 0; i <static_cast<int>( linebuffer.size()); i++) {
		count++;
		if (i != static_cast<int>(linebuffer.size() - 1 )&& linebuffer.at(i) != linebuffer.at(i + 1)) {
			starfile.push_back(Hashtag(linebuffer.at(i),count));
			count = 0;
		}
		else if (i == static_cast<int>(linebuffer.size() - 1)) {
			starfile.push_back(Hashtag(linebuffer.at(i),count));
		}
	}
	sort(starfile.begin(), starfile.end());
	for (i = 0; i < static_cast<int>(starfile.size()); i++) {// ranking each hashtag from top to bottom
		starfile.at(i).setStartRank(rank);
		if (i != static_cast<int>(starfile.size() - 1) && starfile.at(i).getStartCount() != starfile.at(i + 1).getStartCount())
			rank++;
	}
}
// this function is to combine information which it is start rank and end ranks into the endfile varible 
void File::combine() {
	int i = 0; int j = 0;
	for (i = 0; i < static_cast<int>(starfile.size()); i++) {
		for (j = 0; j < static_cast<int>(endfile.size()); j++) {
			if (starfile.at(i).getWord() == endfile.at(j).getWord()) {
				endfile.at(j).setStartRank(starfile.at(i).getStartRank());
				break;
			}
		}
	}
}

