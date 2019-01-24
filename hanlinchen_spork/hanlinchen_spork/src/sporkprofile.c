/**************************************************************************************************/

/*
 * File: sporkprofile.c
 * Author: Hanlin Chen
 * NetID: Hanlin@email.arizona.edu
 * Date:Feb 1 2016
 *
 * Description: Function definitions for reading, processing, and writing Spork profiles.
 *
 */

 /**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include "sporkprofile.h"
# define max 1024
/**************************************************************************************************/

/* Reads up to maxProfiles Spork profiles from an input file specified by fileName. Functions reads
 * the input file line-by-line using the format:
 *
 *    BusinessName X.XX Y.YY R.RR A
 *
 * BusinessName is the name of the restauarant/business. The buseiness name will not include any
 * whitespace characters
 *
 * X.XX represents the X location in miles using a Cartesian coodinate system
 *
 * Y.YY represents the Y location in miles using a Cartesian coodinate system
 *
 * R.RR represents the average rating for the business
 *
 * A is the advertising level, which should 0, 1, or 2
 *
 * Alpha submission: ReadSporkDataFromFile() function should initialize isNearby and isGood
 *                   to true and initialize distMiles to 0.0 for all profile entries.
 *                   Note: This requirement is different for the final project submission.
 *
 * Project submission: ReadSporkDataFromFile() function should initialize isNearby and isGood
 *                     to false for all profile entries.
 *                     Note: This requirement is different for the alpha project submission.
 *
 * Returns: The number of Spork profiles read from the file. If the input file could not be opened,
 *          the function returns -1.
 *
 */
int ReadSporkDataFromFile(SporkProfile sporkProfiles[], int maxProfiles, char *fileName) { 
	int i = 0; int j = 0; FILE* inputfile = NULL; int result = 0; char a[100];
	char line[max];
	for (i = 0; i < maxProfiles; i++) {
		sporkProfiles[i].isNearby = false;
		sporkProfiles[i].isGood = false;
		sporkProfiles[i].distMiles = 0;
		sporkProfiles[i].avgRating = 0;
		sporkProfiles[i].adLevel = 0;
		sporkProfiles[i].locX = 0;
		sporkProfiles[i].locY= 0;
	}
	inputfile = fopen(fileName, "r");
	if (inputfile == NULL) {
		return -1;
	}
	while (!feof(inputfile) && j < maxProfiles) {
		fgets(line, max, inputfile); // read each line into a string 
	
		 if(sscanf(line, "%s %lf %lf %lf %d %s", &sporkProfiles[j].businessName, &sporkProfiles[j].locX, &sporkProfiles[j].locY, &sporkProfiles[j].avgRating, &sporkProfiles[j].adLevel,a)!=5) {// copy the data from the string into varible if it read wrong skip to nexline 
			 fgets(line, max, inputfile);
			 sscanf(line, "%s %lf %lf %lf %d %s", &sporkProfiles[j].businessName, &sporkProfiles[j].locX, &sporkProfiles[j].locY, &sporkProfiles[j].avgRating, &sporkProfiles[j].adLevel, a);
			 
		 }
			j++;
		
	}
	fclose(inputfile);
	return j;
}

/**************************************************************************************************/

/*
 * Determines if each business is nearby the user,  sets the Spork profile's isNearby flag to
 * true (is nearby) or false (not nearby), and stores the distance in miles in the Spork profile.
 *
 * userLocX, userLocY: Indicates the x and y coordiante of the user's location
 * maxDist: Indicates the maxmimum distance between the user and a nearby business
 *
 */
void FindNearbyBusinesses(SporkProfile sporkProfiles[], int numProfiles,double userLocX, double userLocY, double maxDist) {
	int i = 0;
	for (i = 0; i < numProfiles; i++) {
		sporkProfiles[i].distMiles = sqrt(pow((sporkProfiles[i].locX-userLocX), 2) + pow((sporkProfiles[i].locY-userLocY), 2));
		if (sporkProfiles[i].distMiles <=maxDist) {// if the distmies is less than max dist then assign the true to isNearby varible 
			sporkProfiles[i].isNearby = true;
		}
	}
}


/**************************************************************************************************/

/*
 * Determines if each business is good based on the user's minimum required average rating.
 * Sets the Spork profile's isGood flag to true if the business' avgRating is greater than or
 * equal to minRating, and false otherwise.
 *
 */
void FindGoodBusinesses(SporkProfile sporkProfiles[], int numProfiles,
	double minRating) {

	int i = 0;
	for (i = 0; i < numProfiles; i++) {
	
		if (sporkProfiles[i].avgRating>=minRating) {
			sporkProfiles[i].isGood = true;// if the averagrating  is greater than  than max dist then assign the true to isgood varible 
		}
	}
}

/**************************************************************************************************/

/*
 * Returns the index of the Spork profile that is neary, good, and has the highest adLevel. If
 * there is a tie, the index of the first entry found with the highest ad level should be returned.
 * If no businesses are nearby and good, the function will return -1.
 *
 */

int GetIndexMaxSponsor(SporkProfile sporkProfiles[], int numProfiles) {
	int i = 0; int sum = 0;
	for (i = 0; i < numProfiles; i++) {
		if ((sporkProfiles[i].adLevel>sum)&& (sporkProfiles[i].isGood == true) && (sporkProfiles[i].isNearby == true)&&((sporkProfiles[i].adLevel==0)||(sporkProfiles[i].adLevel == 1)||(sporkProfiles[i].adLevel == 2))) {
			sum = sporkProfiles[i].adLevel;// fin the max index 
		}
	}

	for (i = 0; i < numProfiles; i++) {
		if ((sporkProfiles[i].isGood == true) && (sporkProfiles[i].isNearby == true)&&(sporkProfiles[i].adLevel == sum)&& ((sporkProfiles[i].adLevel == 0) || (sporkProfiles[i].adLevel == 1) || (sporkProfiles[i].adLevel == 2))) {
			return i; // retunr the dfisrt maximun index 
		}
	}
	return -1;
}

/**************************************************************************************************/

/*
 * Writes all good and nearby business to an output file specified by fileName using the format:
 *
 *    BusinessName R.RR D.DD
 *
 * R.RR is the average rating with exactly two decimal digits of precision.
 * D.DD is the distance in miles with exactly two decimal digits of precision.
 *
 * If maxSponsorIndex is not -1, the cooresponding profile entry will be output first. All other
 * nearby and good profiles will be output in the order they are stored in the sporkProfiles array.
 *
 * Each entry should be separated by a single tab character (\t), and each line should end
 * with a single newline (\n).
 *
 * Returns: -1 if the output file could not be opened, and 0 otherwise.
 *
 */
int WriteSporkResultsToFile(SporkProfile sporkProfiles[], int numProfiles, int maxSponsorIndex, char *fileName) {
	FILE* outputfile = NULL;
	int i = 0;
	outputfile = fopen(fileName, "w");
	if (outputfile == NULL) {
		return -1;
	}
	if (maxSponsorIndex == -1) {
		for (i = 0; i < numProfiles; i++) {
			if ((sporkProfiles[i].isGood == true) && (sporkProfiles[i].isNearby == true) && ((sporkProfiles[i].adLevel == 0) || (sporkProfiles[i].adLevel == 1) || (sporkProfiles[i].adLevel == 2))) {
				fprintf(outputfile, "%s\t%0.2lf\t%0.2lf\n", sporkProfiles[i].businessName, sporkProfiles[i].avgRating, sporkProfiles[i].distMiles);
			}
		}
	}
	else {
		fprintf(outputfile, "%s\t%0.2lf\t%0.2lf\n", sporkProfiles[maxSponsorIndex].businessName, sporkProfiles[maxSponsorIndex].avgRating, sporkProfiles[maxSponsorIndex].distMiles);
		for (i = 0; i < numProfiles; i++) {
			if ((i != maxSponsorIndex) && (sporkProfiles[i].isGood == true) && (sporkProfiles[i].isNearby == true) && ((sporkProfiles[i].adLevel == 0) || (sporkProfiles[i].adLevel == 1) || (sporkProfiles[i].adLevel == 2))) {
				fprintf(outputfile, "%s\t%0.2lf\t%0.2lf\n", sporkProfiles[i].businessName, sporkProfiles[i].avgRating, sporkProfiles[i].distMiles);
			}
		}
	}
	fclose(outputfile);
	return 0;
}

/**************************************************************************************************/
