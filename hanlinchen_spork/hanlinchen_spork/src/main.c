/**************************************************************************************************/

/*
 * File: main.c
 * Author: Hanlin Chen 
 * NetID:Hanlinchen@email.arizona.edu
 * Date:Feb 1 2016 
 *
 * Description: Spork program finds nearby and good restaurants/businesses.
 *
 */

/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sporkprofile.h"

/**************************************************************************************************/

#define MAX_SPORK_PROFILES 500

/**************************************************************************************************/

int main(int argc, char *argv[]) {
   SporkProfile sporkProfiles[MAX_SPORK_PROFILES];
   int numProfiles = 0;
   int maxSponsorIndex = -1;
   double userLocX = 0.0;
   double userLocY = 0.0;
   double maxDistMiles = 0.0;
   double minAvgRating = 0.0;
   
   /*
    * Check for the correct number of command line arguments. If incorrect
    * provide a usage message to the assist the user.
    *
    */
   if( argc != 7 ) {
      printf("Usage: FIXME\n");
      return EXIT_FAILURE;
   }
   
   // Read Spork profiles from input file and store the number of profiles read.
   numProfiles  = ReadSporkDataFromFile(sporkProfiles, MAX_SPORK_PROFILES, argv[1]);
   if( numProfiles == -1 ) {
      printf("Could not read input file %s\n", argv[1]);
      return EXIT_FAILURE;
   }

   // FIXME: Convert command line arguments for user's x and y location, maximum distance, and
   // minimum rating to variables userLocX, userLocY, maxDist, and minRating.
   // minimum rating to variables userLocX, userLocY, maxDist, and minRating.
   sscanf(argv[3], "%lf", &userLocX);
   sscanf(argv[4], "%lf", &userLocY);
   sscanf(argv[5], "%lf", &maxDistMiles);
   sscanf(argv[6], "%lf", &minAvgRating);
   FindNearbyBusinesses(sporkProfiles, numProfiles, userLocX, userLocY, maxDistMiles);
   FindGoodBusinesses(sporkProfiles, numProfiles, minAvgRating);
   maxSponsorIndex = GetIndexMaxSponsor(sporkProfiles, numProfiles);

   // Write nearby and good Spork profiles to the output file.
   if( WriteSporkResultsToFile(sporkProfiles, numProfiles, maxSponsorIndex, argv[2]) == -1 ) {
      printf("Could not write output file %s\n", argv[2]);
      return EXIT_FAILURE;
   }
   
   return EXIT_SUCCESS;
}

/**************************************************************************************************/
