
#include<stdio.h>
#include "dlist.h"
#include<string.h>
#include"cardprocessing.h"
#include"stringprocessing.h"
#include"output.h"
int main(int argc, char* argv[]) {
	// declare the three link list
	DList list;
	DList string;
	DList card;
	DListConstruct(&list);// creat the list 
	DListConstruct(&card);
	DListConstruct(&string);
	inputcardfromfile(&card, argv[1]);// read the valid card from the file 
	readstring(&string, argv[2]);// read the valid strings from the file 
    processingcard(&list, &card, &string);// process each valid card and string 
	output(&list, argv[3]);// output the valid strings.
	DListDestruct(&list);// free all the memory
	DListDestruct(&string);
	DListDestruct(&card);
	return 0;
}