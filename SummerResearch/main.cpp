#include<iostream>
#include<fstream>
using namespace std;
#include"CacheConfig.h"
#include"Phase.h"
int main(int argc, char* argv[]) {
	Phase Cache; double C_max = 0; double C_min = 0; double A_max = 0; double A_min = 0; double L_max = 0; double L_min = 0;
	double Delta = 0;
	double C_thr = 8000;
	double A_thr = 2;
	double L_thr = 64;
	if (argc != 4) {
		cout << "Usage: base_Cache.txt  test_Cache.txt cache_config.ini" << endl;
		return 0;
	}
	cout << "Please enter C_max:";
	cin >> C_max;
	cout << "Please enter C_min:";
	cin >> C_min;
	cout << "Please enter A_max:";
	cin >> A_max;
	cout << "Please enter A_min:";
	cin >> A_min;
	cout << "Please enter L_max:";
	cin >> L_max;
	cout << "Please enter L_min:";
	cin >> L_min;
	Cache.process_baseCachefile(argv[1]);
	Cache.process_testCachefile(argv[2]);
	Cache.process_baseCache_configfile(argv[3]);
	Cache.systemprintout();
	Delta = Cache.normalization();
	double C_I = Cache.getBaseCache().getCache_size();
	double A_I = Cache.getBaseCache().getAssociativity();
	double L_I = Cache.getBaseCache().getLine_size();
	if ((Delta>0&&Delta<=0.25)||(Delta>0.25 && Delta <=0.5)||(Delta>2.5)) {
		C_I=C_thr;
	}
	else if (Delta > 0.5&&Delta <= 0.75) {
		if (Cache.getBaseCache().getCache_size() == C_min) {
			C_I = Cache.getBaseCache().getCache_size() * 2;
		}
		else {
			C_I = C_thr;
		}
		if (Cache.getBaseCache().getAssociativity() == A_min) {
			A_I = Cache.getBaseCache().getAssociativity() * 2;
		}
	}
	else if (Delta>0.75&&Delta<=1.25) {
		C_I = C_thr;
		if (Cache.getBaseCache().getAssociativity() != A_max) {
			A_I = Cache.getBaseCache().getAssociativity() * 2;
		}
		if (Cache.getBaseCache().getLine_size() != L_min) {
			L_I = Cache.getBaseCache().getLine_size() / 2;
		}
	}
	else if (Delta > 1.25&&Delta<=1.5) {
		C_I = C_thr;
		if (Cache.getBaseCache().getAssociativity() == 1) {
			A_I = A_thr;
		}
	}
	else if (Delta > 1.5&&Delta <= 2.5) {
		if (Cache.getBaseCache().getCache_size() != C_max) {
			C_I = C_max / 2;
		}
	}
	cout << "######################## Estimation Result########################" << endl<<endl;
	cout << "the adjusted dCache Size:" << C_I<< " bytes" << endl;
	cout << "the adjusted Line size:" << L_I<< " bytes" << endl;
	cout << "the adjusted Associativity:" << A_I<< endl << endl;
	return 0;
}