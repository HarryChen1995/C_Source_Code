#include<iostream>
#include<fstream>
using namespace std;
#include"GpsPosition.h"
#include "velociplotter.h"
int main(int argc, char* argv[]) {
	ofstream file;
	velociplotter GPS; // declare the velciplotter class
	if (argc != 3) {// check the number of argument 
		cout << "Usage: velociplotter gpsLogFile gpsPlotDataFile" << endl;
	}
	GPS.processGpslogfile(argv[1]);// process the input file 
if (!GPS.checkvalid()) {
	file.open(argv[2]);
	return 0;
	}
	GPS.outputtimespeed(argv[2]);
	return 0;

}