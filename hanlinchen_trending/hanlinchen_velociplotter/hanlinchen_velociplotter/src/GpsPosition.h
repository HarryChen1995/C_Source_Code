#ifndef GPSPOSITION_H
#define GPSPOSITION_H
// this file include given class declareation from the website 
class GpsPosition {

private: // private varible 
	double latitude;
	double longitude;
	unsigned long timeSeconds;

public:
	GpsPosition();// defualt constructor 
	GpsPosition(double latitude, double longitude, unsigned long timeSeconds);// constum constructor 

	double GetLatitude();// getter for the latitude 
	double GetLongitude();// getter for the longitude  
	unsigned long GetTime();// getter for the time varible 

	void SetLatitude(double latitude);// setter for lattitude 
	void SetLongitude(double longitude);// setter for longitude 
	void SetTime(double timeSeconds);// setter fot time 

	double CalcDistanceKmTo(GpsPosition toPosition);// calulate the ditstance between each two point 
};





#endif 
