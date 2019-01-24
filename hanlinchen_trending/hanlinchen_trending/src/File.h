
#ifndef FILE_H
#define FILE_H
#include <vector>
using namespace  std;
#include "Hashtag.h"
class File {
private:
	vector <Hashtag>  starfile;
	vector<Hashtag> endfile;
public :
	string convert(string a);
	void processstarfile(char* filename);
	void  processendfile(char*filename);
	     File();
	void setFile(vector<Hashtag> a);
    vector<Hashtag> getFile() const;
    void combine();
    string RD(Hashtag a);
	void print(char *filename);
};
#endif 

