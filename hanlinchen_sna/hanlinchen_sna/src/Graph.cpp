#include<iostream>
using namespace std;
#include"Graph.h"
//////////////////////////////////////
/* this file contain the all the implementation of fucntion from  the Graph.cpp
*/
/////////////////////////////////////
Graph::Graph() { // defualt constructor 

}
// this function can traverse the newUser vector and conduct linear search to find and return the match user node 
User* Graph::search(string _name) { 
	int i = 0;
	for (i = 0; i < static_cast<int>(netUser.size()); i++) {
		if ((netUser.at(i))->getname() == _name)
			return netUser.at(i);
	}
	return NULL;
}
////////////////////////////////////
/* this function is to process the inputfule and construc the entire graph structure of all the user node 
and return the true if file has been process sucssefully 
*/
////////////////////////////////
bool Graph::Readinputfile(char* filename) {
	ifstream file;  User *person1; User *person2;
	string name1; string name2; int i = 0; rootuser = NULL;
	file.open(filename); // open the file  
	if (!file.is_open()) { // if file cannot open and printout the errror message 
		cout << "can not open the input file" << endl;
		return false;
	}
	while (file.good()) {
		if (!(file >> name1 >> name2))
			break;
		if (name1.length() > 15 || name2.length() > 15) // if each user node is longer than 15 character and end readiing file 
			return false;
		for (i = 0; i < static_cast<int>(name1.length()); i++) {  // check the every user has only letter,number and underscore  
			if (!((name1[i] >= 'a'&&name1[i] <= 'z' )||( name1[i] >= 'A'&&name1[i] <= 'Z' )||( name1[i] == '_')|| (name1[i] >= '0'&&name1[i] <= '9')))
				return false;
		}
		for (i = 0; i < static_cast<int>(name2.length()); i++) {
			if (!((name2[i] >= 'a'&&name2[i] <= 'z')||(name2[i] >= 'A'&&name2[i] <= 'Z')|| (name2[i] == '_')|| (name2[i] >= '0'&&name2[i] <= '9')))
				return false;
		}
		person1 = search(name1); // search the netUser vector and see if it exsit in the vector 
		person2 = search(name2); // search the netUser vector and see if it exsit in the vector 
		if (person1 == NULL) { // if the user node doesnot exsit 
			person1 = new User(name1); // initialized the user node by default constructor 
			netUser.push_back(person1); // add the user node to the netsure node User vector 
		}
		if (person2 == NULL) { // same as above for user Node in the second colum 
			person2 = new User(name2);
			netUser.push_back(person2);
		}
		person1->addfollower(person2); // add the the second user to the first user the followers vector 
		person2->addfollowing(person1); // add the fisrt user to the second user following vector
	}
	file.close(); // close the file  and return the true 
	return true;
}
/////////////////////////////////////////////////////
/* this  function implement the BTS search only till the depth 3 
*/
//////////////////////////////////////////////////////
void Graph::BTS(char* rootname) {
	string root = rootname; 
	User* start=search(root); // find the root user first in the newUser vector add assign it to the root user 
	rootuser = start;
	User* current;
	int size = 0;
	queue<User*>  frontier; // initialize the queue 
	if (rootuser != NULL) { // if the root user exsit  in the vector 
		frontier.push(start);
		User_depth3.push_back(start);
		start->setVisit(true);
		int node = 0; // this varible is to check if the all the root user'following is pop out the queue 
		int i = 0;
		while (!frontier.empty() && node < static_cast<int>(start->getfollowing().size() + 1)) {// if start node and all the root user pop out the queue, all the user within depth 2 will be stored in the Userdpth3
			current = frontier.front();
			frontier.pop();
			node++;
			for (i = 0; i < static_cast<int>(current->getfollowing().size()); i++) {
				if (!(current->getfollowing().at(i)->getVisit())) {
					current->getfollowing().at(i)->setVisit(true); // assign the visit variable as true ans indicate it is already traversed 
					frontier.push(current->getfollowing().at(i));
					User_depth3.push_back(current->getfollowing().at(i));
				}
			}
		}
		int j = 0;
		start = User_depth3.at(0); // now starting add all the userd node in the  depth 3
		size = static_cast<int>(User_depth3.size()); // start from the end of this vector and search the all user node in depth 3
		for (i = size - 1; i >= static_cast<int>(start->getfollowing().size() + 1); i--) {
			current = User_depth3.at(i);
			for (j = 0; j < static_cast<int>(current->getfollowing().size()); j++) {
				if (!(current->getfollowing().at(j)->getVisit())) { 
					current->getfollowing().at(j)->setVisit(true);
					User_depth3.push_back(current->getfollowing().at(j));
				}
			}
		}
		start = User_depth3.at(0);
		size = User_depth3.size(); 
		for (i = size - 1; i >= static_cast<int>(start->getfollowing().size() + 1); i--) { // extract all the user node in depth 2 and 3 to the userdepth2_3 vector 
			depth2_3.push_back(User_depth3.at(i));
		}
	}
}
///////////////////////////////////////////
/* this function can conver all uppercase letter to the lower case 
and return  the lower case string
*/
//////////////////////////////////////////
string convert(string name) {
	string afterconvert; int i = 0;
	for (i = 0; i<static_cast<int>(name.length()); i++) { // go throgh the each character insed the string 
		afterconvert +=tolower(name[i]);
	}
	return afterconvert; // and return the string after converted
}
/////////////////////////////////////////////////
/* this function is to comapre the to user node for buil-in sort function inside algrithm libary and return true if user a > user b
*/
/////////////////////////////////////////
bool compare(User* a, User* b) { 
if (a->getfollowers().size()>b->getfollowers().size()) {  // if the user a has more followers than user b and return true 

		return true;
	}
	if (a->getfollowers().size() == b->getfollowers().size()) { // if they all has the same followers and compare the user name nore : case insensitice 
		if (convert(a->getname())<convert(b->getname()))  // conver them into the lower case and compare 
			return true;
	}
	
	return false;	
}
////////////////////////////////////////
/* this function is to wire the sorted result to output file 
*/
//////////////////////////////////////
void Graph::Writeoutputfile(char* filename) {
	int i = 0; ofstream file;
		file.open(filename);
	if (!file.is_open()) {// if file cannot open and printout the error message 
		cout << "can not open file ";
	}
	if (rootuser!= NULL) {
		sort(depth2_3.begin(), depth2_3.end(), compare); // sort the all the user within depth 2 and 3 in descend order 
		file << "Looking for new accounts for " << rootuser->getname() << "(" << static_cast<int>(rootuser->getfollowers().size()) << ")" << " to follow" << endl;// print the fisr line with root user as required 
		for (i = 0; i < static_cast<int>(depth2_3.size()); i++) { // print each single sorted used node inside the vector 
			file<< depth2_3.at(i)->getname() << " " <<"("<< static_cast<int>(depth2_3.at(i)->getfollowers().size()) <<")"<<endl;
		}
	}
	file.close(); // close the file 
}