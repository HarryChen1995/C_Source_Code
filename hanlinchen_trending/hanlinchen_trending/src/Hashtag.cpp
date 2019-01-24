#include <iostream>
using namespace std;
#include  "Hashtag.h"

Hashtag::Hashtag(string word) {
	this->word = word;
	 startCount=0;   // Number of occurrences in start file
	 endCount=0;     // Number of occurrences in end file
	 startRank=0;    // Rank in start file
	 endRank=0;
}
Hashtag::Hashtag(string word, int startCount, int endCount) {
	this->word = word;
    this->startCount=startCount;    // Rank in start file
	this->endCount = endCount;
}
string Hashtag::getWord() const {
	return word;
}
int Hashtag::getStartCount() const {
	return startCount;
}
int Hashtag::getEndCount() const {
	return endCount;
}
int Hashtag::getStartRank() const {
	return startRank;
}
int Hashtag:: getEndRank() const {
	return endRank;
}
void Hashtag::setStartRank(int rank) {
	startRank = rank;
}
void Hashtag::setStartCount(int startCount) {
	this->startCount = startCount;
}
void Hashtag::setEndRank(int rank) {
	endRank = rank;
}
void Hashtag::IncrementStartCount() {
	this->startCount++;
}
void Hashtag::IncrementEndCount() {
	this->endCount++;
}
bool Hashtag::operator<(const Hashtag& rhs) const {
	if ((rhs.endCount)<(this->endCount)) {
		return true;
	}
	  if ((rhs.endCount==this->endCount)&&(rhs.endCount!=0)&&(this->endCount!=0)&&((this->word)<rhs.word)) {
		return true;
	}
	if ((rhs.startCount<( this->startCount)) && (rhs.endCount==0) && (this->endCount== 0)) {
		return true;
	}
	if ((rhs.startCount == this->startCount) && (rhs.endCount == 0) && (this->endCount == 0) && ((this->word) < rhs.word)) {
		return true;
	}
	
	return false;
}
