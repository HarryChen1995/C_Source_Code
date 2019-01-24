
#include<stdio.h>
#include<string.h>
#include"stringprocessing.h"
#include<stdlib.h>
/*
* this function is to read the valid string from file into the string the list
*
*/
 void readstring(DList* list,char* filename) {
	FILE* input = NULL; DListNode* a = NULL; char line[1024];
	input=fopen(filename, "r");
	while (!feof(input)) {
		if ( fscanf(input,"%s",line)==0 ) {// the list return 0  and end the reading process.
			break;
}
		if (strlen(line)>=3) {
			a = NULL;
			a = (DListNode*)malloc(sizeof(DListNode));
			a->str = (char*)malloc((strlen(line) + 1)*sizeof(char));
			strtok(line, "\n");
            strtok(line,"\r");
			strcpy(a->str, line);
			a->blankLength = strlen(line);
			a->blankIndex = -1;
			DListInsertAfter(list, list->tail, a);
		}
	}
	fclose(input);
}
