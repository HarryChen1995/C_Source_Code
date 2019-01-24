//----------------------------------------------------------------------//
// Author:         Roman Lysecky, Ming Li
//                 (adpated from code by Jonathan Sprinkle)
// Net ID:         rlysecky
// Date:           06 January 2016
// Project Number: 0
// Project Name:   echoer
//
// Contains the implementation for the principal logic of the
// program, which is the processWord function.
//----------------------------------------------------------------------//

#include "process.h" // get the function signature for what we implement
#include <string.h>  // need to include string.h in order to have strcmp

//----------------------------------------------------------------------//
//
// processWord
//
// This function performs the principal logic of the program, by
// echoing differently, depending on whether the word matches "Ping"
//
// If the word matches "Ping" then the echoed line will be
//
//   Give me a Ping. One Ping only, please.
//
// Otherwise, the echoed line should just be the passed in word
// with no quotes.
//
//----------------------------------------------------------------------//

void processWord(char *inputWord) {
   char pingStr[] = "Ping";  // word we want to match
   
   // if we are passed a NULL pointer, then bad things will happen.
   if (inputWord == NULL) {
      printf("Error! Received a NULL pointer.\n");
      return;
   }
   
   // match for Ping
   if (strcmp(pingStr, inputWord) == 0) {
      printf("Give me a Ping. One Ping only, please.\n");
   }
   else {
      printf("%s\n", inputWord);
   }
   
   return;
}
