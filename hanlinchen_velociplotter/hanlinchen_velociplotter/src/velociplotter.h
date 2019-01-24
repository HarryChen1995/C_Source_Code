#include<vector>
using namespace std;
#include "GpsPosition.h"
#ifndef VELOCIPLOTTER_H
#define VELOCIPLOTTER_H
// this file defined the class which could read the input file and extract the data and convert them into to right form for calculation
// then writr the output to file as time, speed sperating by the space.
class velociplotter {
private:   vector<GpsPosition>  Position;

public: velociplotter();// constructor 
		void setPosition(vector<GpsPosition> Position);// setter
		vector<GpsPosition>getPosition()const;// getter
		void processGpslogfile(char* filename);// process the input file 
		unsigned long converttimetosecond(long unsigned time);//convert the time into seconds 
		double convertlatitudetodegree(double latitude);// convert this into the radians
		bool checkvalid();//check if the input file is valid 
		void outputtimespeed(char* filename);// write the output


};

#endif 