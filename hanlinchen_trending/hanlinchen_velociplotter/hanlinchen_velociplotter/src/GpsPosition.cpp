#include<iostream>
#include<cmath>
using namespace std;
#include"GpsPosition.h"
// this file has the definition of each function from GpsPosition.h 
// defualt constructor 
GpsPosition::GpsPosition() {
	 latitude=0;
	longitude=0;
	timeSeconds = 0;
}
// custom constructor 
GpsPosition::GpsPosition(double latitude, double longitude, unsigned long timeSeconds) {
	this->latitude = latitude;
	this->longitude = longitude;
	this->timeSeconds = timeSeconds;	
}
// getter for the latitude 
double GpsPosition::GetLatitude() {
	return latitude;
}
// getter fot thee lingitude 
double GpsPosition::GetLongitude() {
	return longitude;
}
// getter for the time 
long unsigned GpsPosition::GetTime() {
	return timeSeconds;
}
// setter for the latitude
void GpsPosition::SetLatitude(double latitude) {
	this->latitude = latitude;
}
// setter for the longitude
void GpsPosition::SetLongitude(double longitude) {
	this->longitude = longitude;
}
// setter for the time 
void GpsPosition::SetTime(double timeSeconds) {
	this->timeSeconds = timeSeconds;
}
// calculate the distance between each time point 
double GpsPosition::CalcDistanceKmTo(GpsPosition toPosition) {
	const double EarthRadiusKm = 6371.0;
	const double PI = 3.14159265358979323846;

	double fromLatitudeRad;
	double fromLongitudeRad;
	double toLatitudeRad;
	double toLongitudeRad;
	double deltaLatitude;
	double deltaLongitude;
	double a;
	double c;

	// Convert to radians
	fromLatitudeRad = PI * this->GetLatitude() / 180.0;
	fromLongitudeRad = PI * this->GetLongitude() / 180.0;

	toLatitudeRad = PI * toPosition.GetLatitude() / 180.0;
	toLongitudeRad = PI * toPosition.GetLongitude() / 180.0;

	// Calculate delta for latituce and longitude
	deltaLatitude = toLatitudeRad - fromLatitudeRad;
	deltaLongitude = toLongitudeRad - fromLongitudeRad;

	// Calculate great-circle distance using haversine formula
	a = (sin(deltaLatitude / 2) * sin(deltaLatitude / 2)) +
		(sin(deltaLongitude / 2) * sin(deltaLongitude / 2) *
			cos(fromLatitudeRad) * cos(toLatitudeRad));
	c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return EarthRadiusKm * c;

}