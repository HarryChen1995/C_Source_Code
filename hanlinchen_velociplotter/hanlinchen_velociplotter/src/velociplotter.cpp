#include<fstream>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
//this file has the definition of each function for class velociplotter 
#include"velociplotter.h"
// default constuctor
velociplotter::velociplotter() {

}
// setter for the private variable  Position 
void velociplotter::setPosition(vector<GpsPosition> Position) {
	this->Position = Position;
}
// getter for the private variable 
vector<GpsPosition> velociplotter::getPosition() const {
	return Position;
}
// convert the time varible in term of seconds 
unsigned long velociplotter::converttimetosecond(long unsigned  time) {
	double hour = 0; double minute = 0; double second = 0;
	hour = 3600 * (time / 10000);
	time = time % 10000;
	minute = 60 * (time / 100);
	time = time % 100;
	second = time;
	return second + hour + minute;
	
}
// convert the latitude and longitude into the radians 
double velociplotter::convertlatitudetodegree(double latitude) {
	double degree = 0; double minute = 0; 
	degree = static_cast<int>(latitude)/ 100;
	latitude = latitude - 100 * degree;
	minute = latitude*(1.0 / 60.0);
	
	return minute+degree;
}
// this function is to read the input file 
void velociplotter :: processGpslogfile(char* filename) {
	ifstream file;    string NMEA;  string time; string latitude; string longitude; string p; 
	string s; string t; string line;
	long unsigned time1 = 0; double latitude1 = 0.0; double longitude1 = 0.0;
	file.open(filename);// open th file 
	if (!file.is_open()) {// if file cannot open 
		cout<< "could not open the file"<<endl;
	}
	while (file.good()) {  
		if (!getline(file, line)) {
			continue;
		}
		istringstream linebuffer(line);
		if (linebuffer.fail()) {
			continue;
		}
		
		// read untilt reach the end of this file 
	if (!getline(linebuffer, NMEA, ',')) // read the data format of each sentence 
			continue;
		if (!getline(linebuffer, time, ','))// read the time varaible 
			continue;
		if (!getline(linebuffer, latitude, ','))// read the latitude
			continue;
		if (!getline(linebuffer,p , ','))
			continue;
		if (!getline(linebuffer, longitude, ','))// read the longitude
			continue;
		if (!getline(linebuffer,s,'\n'))// throw rest of string a away 
			continue;
		istringstream a(time);
		if (NMEA == "$GPGGA"&&a>>time1&&(time1/10000)<=24&&((time1%10000)/100)<=60&&((time1%10000)%100)<=60) { // check if it is right sentence format 
		time1 = converttimetosecond(time1); // conver it into the seconds
		istringstream b(latitude);
		    b >> latitude1; //convert it into the radians 
			latitude1 = convertlatitudetodegree(latitude1);
	   istringstream c(longitude);
		    c>>longitude1;
			longitude1 = convertlatitudetodegree(longitude1);// convert it into the radians 

				Position.push_back(GpsPosition(latitude1, longitude1, time1));
			
        }
	}
	file.close();
}
// this function is to check if the each data is invalid base on the time variable 
bool velociplotter::checkvalid() {
	int i = 0;  
	for (i = 0; i < static_cast<int>(Position.size()); i++) {
		if (i != static_cast<int>(Position.size()) - 1 && Position.at(i).GetTime() >= Position.at(i + 1).GetTime()) {// if the previous time varible is larger or equal to the current time varible return false 
			return false;
		}
	}
	return true;
}
// this function is to write the ouput into file  
void velociplotter::outputtimespeed(char* filename) {
	ofstream file; int i = 0;  int j = 0; int a = 0;
	file.open(filename);// open the file 
	if (!file.is_open()) {// if file cannot open 
		file<< "could not open the file" << endl;
	}
	for (i = 1; i < static_cast<int>(Position.size()); i++) {// if each time varibles have no disconnection and just print it out in order already stored in the vector 
		if (Position.at(i).GetTime() - Position.at(i-1).GetTime() == 1) {
			file<< Position.at(i).GetTime() << " ";
			file<< (Position.at(i - 1).CalcDistanceKmTo(Position.at(i))) / ((Position.at(i).GetTime() - Position.at(i - 1).GetTime()) / 3600.0) << endl;
		}
		if(Position.at(i).GetTime() - Position.at(i - 1).GetTime()>1) {
			a = 0;
			for (j = 0; j <static_cast<int>(Position.at(i).GetTime() - Position.at(i - 1).GetTime()-1);j++) {
				a++;
				// if there is a disconnection then fill out the disconnection 
				file << Position.at(i-1).GetTime()+a<< " " << (Position.at(i - 1).CalcDistanceKmTo(Position.at(i))) / ((Position.at(i).GetTime() - Position.at(i - 1).GetTime()) / 3600.0) << endl;
				
			}
			file<< Position.at(i).GetTime() << " ";
			file<< (Position.at(i - 1).CalcDistanceKmTo(Position.at(i))) / ((Position.at(i).GetTime() - Position.at(i - 1).GetTime()) / 3600.0) << endl;
		}
	}
	file.close();// close the file
}