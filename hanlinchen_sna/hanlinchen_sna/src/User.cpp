#include<iostream>
using namespace std;
#include "User.h"
/////////////////////////////////////////////////////////////
/* this file contain the fucntion implmentation for all public function in User.h
*/
///////////////////////////////////////////////////////////////
User::User() { // defualt constructor 
	name = ""; 
	visit = false; // initialized visit varible as false

}

User::User(string name, bool visit) { // custom constructor 
	this->name = name;
	this->visit = visit;

}

void User::setVisit(bool visit) { // setter for the visit variable 
	this->visit = visit;
}

bool User::getVisit() { // getter for the visit variable 
	return visit;
}

string User::getname() { // getter for the name 
	return name;
}

void User::addfollower(User *person) { // add the follower user to follower vector 
	this->followers.push_back(person); // push it back onto the list 
}

void User::addfollowing(User *person) {// add the following  user to follower vector 
	this->following.push_back(person); //  push it back onto the list 
}

vector<User*> User::getfollowers() { // getter of followers 
	return followers;
}

vector<User*> User::getfollowing() { // getter for following 
	return following;
}
