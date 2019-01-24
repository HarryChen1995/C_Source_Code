#include<iostream>
using namespace std;

#include"CacheConfig.h"

CacheConfig::CacheConfig() {
	 Cache_size=0;
	 Line_size=0;
	 Associativity=0;
}

CacheConfig::CacheConfig(double Cache_size, double Line_size, double Associativity) {
	this->Cache_size = Cache_size;
	this->Line_size = Line_size;
	this->Associativity = Associativity;
}
void CacheConfig::setCache_size(double Cache_size) {
	this->Cache_size = Cache_size;
}

void CacheConfig::setLine_size(double Line_size) {
	this->Line_size = Line_size;
}

void CacheConfig::setAssociativity(double Associativity) {
	this->Associativity = Associativity;
}

double CacheConfig::getCache_size()const{
	return Cache_size;
}

double CacheConfig::getLine_size()const {
	return Line_size;
}
double CacheConfig::getAssociativity()const {
	return  Associativity;
}







