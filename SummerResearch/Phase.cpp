#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

#include"Phase.h"

Phase::Phase() {
	baseCache_miss_rate = 0;
	testCache_miss_rate = 0;
}
double Phase::normalization() {
	return testCache_miss_rate / baseCache_miss_rate;
}
CacheConfig Phase::getBaseCache() {
	return baseCache;
}
void Phase::process_baseCachefile(char* filename) {
	string a; double b=0; 
	ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		cout << "cannot open base Cache file" << endl;
	}
	while (file.good()) {
		if (!(file>> a))
			break;
		if (a == "system.cpu0.dcache.overall_miss_rate::total") {
			file >> b;
			baseCache_miss_rate = b;
		}
	}
	file.close();
}

void Phase::process_testCachefile(char* filename) {
	string a; double b=0;
	ifstream file;
	file.open(filename);
	if (!file.is_open()) {
		cout << "cannot open test Cache file" << endl;
	}
	while (file.good()) {
		if (!(file >> a)) 
			break;
		
		if (a == "system.cpu0.dcache.overall_miss_rate::total")
			file >> b;
			testCache_miss_rate = b;
	}
	file.close();
}

void Phase::process_baseCache_configfile(char* filename) {
	ifstream file; string line; double b = 0; string a;  int i = 0; string buffer; int flag = 0;
	file.open(filename);
	if (!file.is_open()) {
		cout << "cannot open base Cache configfile" << endl;
	}
	while (file.good()) {
	   file>>line;
	   a = "";
	   buffer = "";
	   if (line == "[system.cpu.dcache]") {
		   flag = 1;
		   file >> line;
	   }
	   if (flag == 1) {
		   for (i = 0; i < static_cast<int>(line.length()); i++) {
			   if (line[i] != '=') {
				   buffer += line[i];
			   }
			   else {
				   i++;
				   while (i < static_cast<int>(line.length())) {
					   a += line[i];
					   i++;
				   }
				   if (buffer == "size") {
					   istringstream c(a);
					   c >> b;
					   baseCache.setCache_size(b);
				   }
				   if (buffer == "block_size") {
					   istringstream c(a);
					   c >> b;
					   baseCache.setLine_size(b);
				   }
				   if (buffer == "assoc") {
					   istringstream c(a);
					   c >> b;
					   baseCache.setAssociativity(b);
				   }
			   }
		   }
	   }
	   if ((baseCache.getAssociativity() != 0 && baseCache.getCache_size() != 0 && baseCache.getLine_size() != 0))
		   break;
	}
	file.close();
}

void Phase::systemprintout() {
	cout << "########################### Configuration Estmiation ###########################" << endl<<endl;
	cout << "the base dCache Size:" << baseCache.getCache_size() <<" bytes"<< endl;
	cout << "the base Line size:" << baseCache.getLine_size() <<" bytes"<< endl;
	cout << "the base Associativity:" << baseCache.getAssociativity() << endl<<endl;

	cout << " the base dCache overall miss rate:" << baseCache_miss_rate << endl;
	cout << " the test dCache overall miss rate:" << testCache_miss_rate << endl<<endl;
}