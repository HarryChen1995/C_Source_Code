
#ifndef CACHECONFIG_H
#define CACHECONFIG_H

class CacheConfig {
	private: double Cache_size;
			 double Line_size;
			 double Associativity;
	public: CacheConfig();
			CacheConfig(double Cache_size, double Line_size, double Associativity);
			void setCache_size(double Cache_size);
			void setLine_size(double Line_size);
			void setAssociativity(double Associativity);
			double getCache_size()const;
			double getLine_size()const;
			double getAssociativity()const;
};




#endif 
