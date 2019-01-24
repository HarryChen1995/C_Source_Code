
#include<stdio.h>
#include"output.h"
/*this function is to output the processed string into output file
*/
void output(DList* list, char* filename) {
	FILE* output = NULL; DListNode* curr = NULL;
	output = fopen(filename, "w");
	curr = list->head;
	while (curr != NULL) {
		fprintf(output, "%s\n", curr->str);
		curr = curr->next;
	}
	fclose(output);
}