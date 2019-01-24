#ifndef HASHTAG_H
#define HASHTAG_H
class Hashtag {
private:
	string word;      // The hashtag itself
	int startCount;   // Number of occurrences in start file
	int endCount;     // Number of occurrences in end file
	int startRank;    // Rank in start file
	int endRank;      // Rank in end file

public:
	Hashtag(string word); // Default constructor
	Hashtag(string word, int startCount, int endCount=0);

	// Getter and setter functions for hashtag word, counts, and ranks
	void setStartCount(int startCount);
	string getWord() const;
	int getStartCount() const;
	int getEndCount() const;
	int getStartRank() const;
	int getEndRank() const;
	void setStartRank(int rank);
	void setEndRank(int rank);

	// Functions to increment start or end counts
	void IncrementStartCount();
	void IncrementEndCount();

	// Overloaded < operator for Hashtag objects
	bool operator<(const Hashtag& rhs) const;
};

#endif 

