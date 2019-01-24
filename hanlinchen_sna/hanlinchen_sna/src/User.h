#ifndef USER_H
#define USER_H
#include <vector>
#include <string>
using namespace std;
/////////////////////////////////////////////////////////////////////////
/*
this file contain the basic structure of user node and other public function such as setter and getter
default constructor  custom constructor.
*/
////////////////////////////////////////////////////////////
class User {
private:
	vector<User*> followers; // user the pointer vector to store followers nodes list  of each nodes
	vector<User*> following; // user the pointer vector to store following nodes list  of each nodes
	string name;// user name
	bool visit;// this varible is to check if traversed or not 
public:
	User(); // defualt constructor 
	User(string name, bool visit = false); // custom constructor 
	void setVisit(bool vist); // setter for the visit variable 
	bool getVisit(); // getter for visit varible 
	string getname(); // getter for user name 
	void addfollower(User *person); // add each user node to the follower list 
	void addfollowing(User *person); //  add  more user node to the following list 
	vector<User*> getfollowers(); // return the followers vector 
	vector<User*> getfollowing(); // return the following vector 
};
#endif