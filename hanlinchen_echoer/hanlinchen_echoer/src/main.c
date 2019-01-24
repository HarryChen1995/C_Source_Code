//----------------------------------------------------------------------//
// Author:         Hanlin Chen
//                 (adpated from code by Jonathan Sprinkle)
// Net ID:         hanlinchen
// Date:           22 January 2016
// Project Number: 0
// Project Name:   echoer
//
// Contains the main function.
//----------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "process.h"

int main(int argc, char* argv[]) {// pass the arugment to main function 
        


	if (argc == 2) {// if the command argument line is excalty 1 word then call the processword fucntion to echoe this argument 
			processWord(argv[1]);
		
	}
	else{// otherwise printfout usage message 
	
		printf("This program echoes a word differently, depending on the word that is passed in. Usage:\nechoer [word]\n");
          return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
