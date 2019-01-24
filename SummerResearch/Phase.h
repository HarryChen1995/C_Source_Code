#ifndef PHASE_H
#define PHASE_H
#include"CacheConfig.h"
class Phase {
    private:CacheConfig baseCache;
			double baseCache_miss_rate;
			double testCache_miss_rate;
  public:Phase();
		 void process_baseCachefile(char* filename);
		 void process_testCachefile(char* filename);
		 void process_baseCache_configfile(char* filename);
		 double normalization();
		 CacheConfig getBaseCache();
		 void systemprintout();
		 
};
#endif 
