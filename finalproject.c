#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
// Author:Hanlin Chen and Holden Cheng
// this program is to simulate the Battleship
typedef struct ship_name {// create the ship varible 
	char shiptype[20];
	char shipsymbol;
	char shipp;
	int shipsize;
	int *X_Location;
	int *Y_Location;
	int *X_Hit;
	int *Y_Hit;
	int size;
	int mark;
	struct ship *pt;
}ship;

void checkdeleteship(ship **a, int *num, int *flag, int *m) {// delete the ship after player and computer take shoot
	int i = 0; int sum = 0; int stop = 0, j = 0;
	ship *curr = NULL; ship **temp = a; ship *target = NULL;
	curr = *a;
	if (*num == 1) {
		j = 0;
		while (j < curr->shipsize) {
			if (curr->X_Location[j] - curr->X_Hit[j] == 0 && curr->Y_Location[j] - curr->Y_Hit[j] == 0 && curr->mark == *m) {
				stop = 1;
				curr->size = curr->size - 1;
				break;
			}
			j++;
		}
		if (curr->size == 0) {
			target = curr;
			while ((*temp) != target)
			{
				temp = &(*temp)->pt; // locating the address of the previous element
			}
			if (target == *a) // if first element must be deleted
				*a = target->pt; // make head point to the next element
			*temp = target->pt;  // skip element to be deleted
			free(target); // free the memory
			*flag = 1;
		}
	}
	else {
		while (i < *num && stop == 0) {
			//a->size = a->shipsize;
			j = 0;
			while (j < curr->shipsize) {
				if (curr->X_Location[j] - curr->X_Hit[j] == 0 && curr->Y_Location[j] - curr->Y_Hit[j] == 0 && curr->mark == *m) {
					curr->size = curr->size - 1;
					stop = 1;
					break;
				}
				j++;
			}
			if (curr->size == 0) {
				target = curr;
				while ((*temp) != target)
				{
					temp = &(*temp)->pt; // locating the address of the previous element
				}
				if (target == *a) // if first element must be deleted
					*a = target->pt; // make head point to the next element
				*temp = target->pt;  // skip element to be deleted
				free(target); // free the memory
				*num = *num - 1;
				break;
			}

			curr = curr->pt;
			i++;
		}
	}
}

void tractscore(ship*a, ship *b, char x[][10], char p[][10], int num, int num2, int *computersunk, int *playersunk) {// tract the score 
	int playerhit = 0; int computerhit = 0; int playermiss = 0; int computermiss = 0;  int sum1 = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (x[i][j] == 'H') {
				playerhit++;
			}
			else if (x[i][j] == 'X') {
				playermiss++;
			}
		}
	}
	for (int i = 0; i < num2; i++) {
		sum1 = 0;
		for (int j = 0; j < a->shipsize; j++) {
			if (a->X_Location[j] - a->X_Hit[j] == 0 && a->Y_Location[j] - a->Y_Hit[j] == 0) {
				sum1++;
			}
		}
		if (sum1 == a->shipsize) {
			*playersunk = *playersunk + 1;
		}
		a = a->pt;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (p[i][j] == 'H') {
				computerhit++;
			}
			else if (p[i][j] == 'X') {
				computermiss++;
			}
		}
	}
	for (int i = 0; i < num; i++) {
		sum1 = 0;
		for (int j = 0; j < b->shipsize; j++) {
			if (b->X_Location[j] - b->X_Hit[j] == 0 && b->Y_Location[j] - b->Y_Hit[j] == 0) {
				sum1++;
			}
		}
		if (sum1 == b->shipsize) {
			*computersunk = *computersunk + 1;
		}
		b = b->pt;
	}
	printf("your score:\n");
	printf("Hit: %d\n", playerhit);
	printf("Miss: %d\n", playermiss);
	printf("Sunk: %d\n", *playersunk);
	printf("computer score:\n");
	printf("Hit: %d\n", computerhit);
	printf("Miss: %d\n", computermiss);
	printf("Sunk: %d\n", *computersunk);

}
void creatint(ship *a, int num) {
	for (int i = 0; i < num; i++) {
		a->X_Hit = (int*)malloc(a->shipsize*sizeof(int));
		a->Y_Hit = (int*)malloc(a->shipsize*sizeof(int));
		a = a->pt;
	}
}
void computershoot(ship *a, char p[][10], int num, int *m) {// computer take shot
	int y = 0; int x = 0;
	y = rand() % 10;
	x = rand() % 10;
	while (p[y][x] == 'H' || p[y][x] == 'x') {
		y = rand() % 10;
		x = rand() % 10;
	}
	if (p[y][x] != ' ') {
		for (int i = 0; i < num; i++) {
			if (a->shipsymbol == p[y][x]) {
				for (int j = 0; j < a->shipsize; j++) {
					if (a->Y_Location[j] == y&&a->X_Location[j] == x) {
						a->Y_Hit[j] = y;
						a->X_Hit[j] = x;
						*m = *m + 1;
						a->mark = *m;
					}
				}
			}
			a = a->pt;
		}
		p[y][x] = 'H';
	}
	else {
		p[y][x] = 'X';
	}
}
void Playershoot(ship *a, char c[][10], char p[][10], int num, int *m) {// player take shoot
	int y = 0; char x = ' ';
	printf("please take a shoot and enter row number:\n");
	scanf("%d", &y);
	printf("please take a shoot and enter column letter(capital case):\n");
	scanf(" %c", &x);
	while (y - 1 < 0 || y - 1 > 9) {
		printf("renter row number:\n");
		scanf("%d", &y);
	}
	while (x - 'A' < 0 || x - 'A'>9) {
		printf("renter column letter(capital case):\n");
		scanf(" %c", &x);
	}
	while (c[y - 1][x - 'A'] == 'H' || c[y - 1][x - 'A'] == 'X') {
		printf("you cannot take shoot right here");
		printf("please take a shoot and enter row number:\n");
		scanf("%d", &y);
		printf("please take a shoot and enter column letter(capital case):\n");
		scanf(" %c", &x);
	}
	if (c[y - 1][x - 'A'] != ' ') {
		for (int i = 0; i < num; i++) {
			if (a->shipsymbol == c[y - 1][x - 'A']) {
				for (int j = 0; j < a->shipsize; j++) {
					if (a->Y_Location[j] == y - 1 && a->X_Location[j] == x - 'A') {
						a->Y_Hit[j] = y - 1;
						a->X_Hit[j] = x - 'A';
						*m = *m + 1;
						a->mark = *m;
					}
				}
			}
			a = a->pt;
		}
		c[y - 1][x - 'A'] = 'H';
		p[y - 1][x - 'A'] = 'H';
	}
	else {
		c[y - 1][x - 'A'] = 'X';
		p[y - 1][x - 'A'] = 'X';
	}

}
int checkline2(ship *a) {// check ship's configuration
	int sum = 0; int i = 0;
	if ((strcmp(a->shiptype, "Kayak") == 0) || (strcmp(a->shiptype, "Row boat") == 0)) {
		return 0;
	}
	if (a->shipp == 'h') {
		for (i = 0; i < a->shipsize - 1; i++) {
			if ((a->X_Location[i + 1] - a->X_Location[i] == 1) && (a->Y_Location[i + 1] - a->Y_Location[i] == 0) || (a->X_Location[i + 1] - a->X_Location[i] == -1) && (a->Y_Location[i + 1] - a->Y_Location[i] == 0)) {
				sum = sum + 1;
			}
		}
	}
	else if (a->shipp == 'v') {
		for (i = 0; i < a->shipsize - 1; i++) {
			if ((a->Y_Location[i + 1] - a->Y_Location[i] == 1) && (a->X_Location[i + 1] - a->X_Location[i] == 0) || (a->Y_Location[i + 1] - a->Y_Location[i] == -1) && (a->X_Location[i + 1] - a->X_Location[i] == 0)) {
				sum = sum + 1;
			}
		}
	}
	else if (a->shipp == 'd') {
		for (i = 0; i < a->shipsize - 1; i++) {
			if ((a->X_Location[i + 1] - a->X_Location[i] == 1) && (a->Y_Location[i + 1] - a->Y_Location[i] == 1)) {
				sum = sum + 1;
			}
		}
	}
	return sum;
}
int checkline(ship *a) {
	int sum1 = 0; int i = 0;
	if ((strcmp(a->shiptype, "Kayak") == 0) || (strcmp(a->shiptype, "Row boat") == 0)) {
		return 0;
	}
	if (a->shipp == 'h') {
		for (i = 0; i < a->shipsize - 1; i++) {
			if ((a->X_Location[i + 1] - a->X_Location[i] == 1) && (a->Y_Location[i + 1] - a->Y_Location[i] == 0)) {
				sum1 = sum1 + 1;
			}
		}
	}
	else if (a->shipp == 'v') {
		for (i = 0; i < a->shipsize - 1; i++) {
			if ((a->Y_Location[i + 1] - a->Y_Location[i] == 1) && (a->X_Location[i + 1] - a->X_Location[i] == 0)) {
				sum1 = sum1 + 1;
			}
		}
	}
	else if (a->shipp == 'd') {
		for (i = 0; i < a->shipsize - 1; i++) {
			if ((a->X_Location[i + 1] - a->X_Location[i] == 1) && (a->Y_Location[i + 1] - a->Y_Location[i] == 1)) {
				sum1 = sum1 + 1;
			}
		}
	}
	if (sum1 = a->shipsize - 1) {
		return 0;
	}
	else {
		return 1;
	}
}
void Playerselectlocation(ship *a, char p[][10]) {// player select location 
	char y = ' ';  int u = 0; int g = 0; int l = 0;
	a->X_Location = (ship*)malloc(a->shipsize*sizeof(ship));
	a->Y_Location = (ship*)malloc(a->shipsize*sizeof(ship));
	printf("select the ship %s location(ship size %d) vertical or horizontal/digonal(v/h/d):\n", a->shiptype, a->shipsize);
	scanf(" %c", &a->shipp);
	if (a->shipp == 'h') {
		printf("please enter the row number:\n");
		scanf("%d", &u);
		while (u - 1 > 9 || u - 1 < 0) {
			printf("please reenter the row number:\n");
			scanf("%d", &u);
		}
		for (int i = 0; i < a->shipsize; i++) {
			printf("please enter the %dth column letter(captial case)!!:\n", i + 1);
			scanf(" %c", &y);
			a->X_Location[i] = y - 'A';
			while (a->X_Location[i] > 9 || a->X_Location < 0) {
				printf("please reenter the %dth Column letter(capital case)!!:\n", i + 1);
				scanf(" %c", &y);
				a->X_Location[i] = y - 'A';
			}
			a->Y_Location[i] = u - 1;
			while (p[a->Y_Location[i]][a->X_Location[i]] != ' ') {
				printf("spot is not avalibale!! please reenter!!\n");
				printf("please enter the column letter(captial case)!!starting from %dth spot:\n", i + 1);
				scanf(" %c", &y);
				a->X_Location[i] = y - 'A';
			}
			p[a->Y_Location[i]][a->X_Location[i]] = a->shipsymbol;
		}
	}
	else if (a->shipp == 'v') {
		printf("please enter the column letter(capital case)!!:\n");
		scanf(" %c", &y);
		while (y - 'A' > 9 || y - 'A' < 0) {
			printf("please reenter the column letter(capital case)!!:\n");
			scanf(" %c", &y);
		}
		for (int i = 0; i < a->shipsize; i++) {
			printf("please enter the %dth row number:\n", i + 1);
			scanf("%d", &u);
			while (u - 1 < 0 || u - 1 > 9) {
				printf("please enter the %dth row number:\n", i + 1);
				scanf("%d", &u);
			}
			a->X_Location[i] = y - 'A';
			a->Y_Location[i] = u - 1;
			while (p[a->Y_Location[i]][a->X_Location[i]] != ' ') {
				printf("spot is not avalibale!! please reenter!!\n");
				printf("please enter the row number starting from %dth spot:\n", i + 1);
				scanf("%d", &u);
				a->Y_Location[i] = u - 1;
			}
			p[a->Y_Location[i]][a->X_Location[i]] = a->shipsymbol;
		}
	}
	else if (a->shipp == 'd') {
		for (int i = 0; i < a->shipsize; i++) {
			printf("please enter the %dth column letter (captial case)!!:\n", i + 1);
			scanf(" %c", &y);
			while (y - 'A' > 9 || y - 'A' < 0) {
				printf("please reenter the column letter(capital case)!!:\n");
				scanf(" %c", &y);
			}
			a->X_Location[i] = y - 'A';
			printf("please enter the %dth row number:\n", i + 1);
			scanf("%d", &u);
			while (u - 1 < 0 || u - 1 > 9) {
				printf("please enter the %dth row number:\n", i + 1);
				scanf("%d", &u);
			}
			a->Y_Location[i] = u - 1;
			while (p[a->Y_Location[i]][a->X_Location[i]] != ' ') {
				printf("spot is not avalibale!! please reenter!!\n");
				printf("please enter the column letter (captial case) starting from %dth spot!!:\n", i + 1);
				scanf(" %c", &y);
				a->X_Location[i] = y - 'A';
				printf("please enter the row number starting from %dth spot:\n");
				scanf("%d", &u);
				a->Y_Location[i] = u - 1;
			}
			p[a->Y_Location[i]][a->X_Location[i]] = a->shipsymbol;
		}
	}
}
void computerselect(ship *a, char c[][10]) {// computer select location 
	a->X_Location = (ship*)malloc(a->shipsize*sizeof(ship));
	a->Y_Location = (ship*)malloc(a->shipsize*sizeof(ship));
	int l = 0; int p = 0; int y = 0;
	l = rand() % 3;
	if (l == 0) {
		a->shipp == 'h';
		p = rand() % 10;
		y = rand() % 5;
		for (int i = 0; i < a->shipsize; i++) {
			a->Y_Location[i] = p;
			a->X_Location[i] = y + i;
			while (c[a->Y_Location[i]][a->X_Location[i]] != ' ') {
				p = rand() % 10; y = rand() % 5;
				a->Y_Location[i] = p;
				a->X_Location[i] = y + i;
			}
			c[a->Y_Location[i]][a->X_Location[i]] = a->shipsymbol;
		}
	}
	if (l == 1) {
		a->shipp == 'v';
		p = rand() % 10;
		y = rand() % 5;
		for (int i = 0; i < a->shipsize; i++) {
			a->Y_Location[i] = y + i;
			a->X_Location[i] = p;
			while (c[a->Y_Location[i]][a->X_Location[i]] != ' ') {
				p = rand() % 10; y = rand() % 5;
				a->Y_Location[i] = y + i;
				a->X_Location[i] = p;
			}
			c[a->Y_Location[i]][a->X_Location[i]] = a->shipsymbol;
		}
	}
	if (l == 2) {
		a->shipp == 'd';
		p = rand() % 5;
		y = rand() % 5;
		for (int i = 0; i < a->shipsize; i++) {
			a->Y_Location[i] = y + i;
			a->X_Location[i] = p + i;
			while (c[a->Y_Location[i]][a->X_Location[i]] != ' ') {
				p = rand() % 5; y = rand() % 5;
				a->Y_Location[i] = y + i;
				a->X_Location[i] = p + i;
			}
			c[a->Y_Location[i]][a->X_Location[i]] = a->shipsymbol;
		}
	}
}
void shipSetting(ship *headplayer) {
	printf("please enter the ship option name:\n");
	fgets(headplayer->shiptype, 20, stdin);
	headplayer->shiptype[strlen(headplayer->shiptype) - 1] = '\0';
	if (strcmp(headplayer->shiptype, "Aircraft Carrier") == 0) {
		headplayer->shipsize = 5; headplayer->size = 5; headplayer->shipsymbol = 'A';
	}
	if (strcmp(headplayer->shiptype, "Battleship") == 0) {
		headplayer->shipsize = 4; headplayer->size = 4; headplayer->shipsymbol = 'B';
	}
	if (strcmp(headplayer->shiptype, "Cruiser") == 0) {
		headplayer->shipsize = 3; headplayer->size = 3; headplayer->shipsymbol = 'C';
	}
	if (strcmp(headplayer->shiptype, "Submarine") == 0) {
		headplayer->shipsize = 3; headplayer->size = 3; headplayer->shipsymbol = 'S';
	}
	if (strcmp(headplayer->shiptype, "Patrol Boat") == 0) {
		headplayer->shipsize = 2; headplayer->size = 2; headplayer->shipsymbol = 'P';
	}
	if (strcmp(headplayer->shiptype, "Kayak") == 0) {
		headplayer->shipsize = 1; headplayer->size = 1; headplayer->shipsymbol = 'K';
	}
	if (strcmp(headplayer->shiptype, "Row boat") == 0) {
		headplayer->shipsize = 1; headplayer->size = 1; headplayer->shipsymbol = 'R';
	}
}
void creat_gameboard(char x[][10], char y[][10], char z[][10]) {
	int i = 0; int j = 0;
	for (i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			x[i][j] = ' '; y[i][j] = ' '; z[i][j] = ' ';
		}
	}
}
void print_gameboardmajor(char x[][10]) {
	printf("    %c   %c   %c   %c   %c   %c   %c   %c   %c   %c  \n", 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J');
	printf("  -----------------------------------------\n");
	for (int i = 0; i < 10; i++) {
		if (i == 9) {
			printf("  |   |   |   |   |   |   |   |   |   |   |\n");
			printf("%d| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", i + 1, x[i][0], x[i][1], x[i][2], x[i][3], x[i][4], x[i][5], x[i][6], x[i][7], x[i][8], x[i][9]);
			printf("  |   |   |   |   |   |   |   |   |   |   |\n");
			printf("  -----------------------------------------\n");
		}
		else {
			printf("  |   |   |   |   |   |   |   |   |   |   |\n");
			printf("%d | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", i + 1, x[i][0], x[i][1], x[i][2], x[i][3], x[i][4], x[i][5], x[i][6], x[i][7], x[i][8], x[i][9]);
			printf("  |   |   |   |   |   |   |   |   |   |   |\n");
			printf("  -----------------------------------------\n");
		}
	}
}
void print_gameboardminor(char x[][10]) {
	printf("    %c   %c   %c   %c   %c   %c   %c   %c   %c   %c  \n", 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J');
	printf("  -----------------------------------------\n");
	for (int i = 0; i < 10; i++) {
		if (i == 9) {
			printf("%d| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", i + 1, x[i][0], x[i][1], x[i][2], x[i][3], x[i][4], x[i][5], x[i][6], x[i][7], x[i][8], x[i][9]);
			printf("  -----------------------------------------\n");
		}
		else {
			printf("%d | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", i + 1, x[i][0], x[i][1], x[i][2], x[i][3], x[i][4], x[i][5], x[i][6], x[i][7], x[i][8], x[i][9]);
			printf("  -----------------------------------------\n");
		}
	}
}
int main(void) {
	int marking = 0, marking1 = 0;
	int numShip = 0; ship *headplayer = NULL; ship *headcomputer = NULL; char num[20]; int num1 = 0; srand(time(NULL));
	char gameboardmajor[10][10]; char gameboardminor[10][10]; char gameboardmajor2[10][10];	int j = 0;
	int computersunk = 0;
	int playersunk = 0;
	int flag = 0;
	printf("welocme to battleship!!!!!!!!!!\n");
	printf("Please enter number of ship:\n");
	fgets(num, "%s", stdin);
	num1 = atoi(num);
	while (num1 > 7) {
		printf("Please reenter number of ship and maximun is 7:\n");
		fgets(num, "%s", stdin);
		num1 = atoi(num);
	}
	printf("Ship Option\tBoard Symbol Ship Size:\n");
	printf("Aircraft Carrier\tA\t%d\n", 5); printf("Battleship\t\tB\t%d\n", 4); printf("Cruiser\t\t\tC\t%d\n", 3);
	printf("Submarine\t\tS\t%d\n", 3); printf("Patrol Boat\t\tP\t%d\n", 2); printf("Kayak\t\t\tC\t%d\n", 1); printf("Row boat\t\tR\t%d\n", 1);
	int i = 0; ship *curr = NULL; ship *last = NULL; ship *curr2 = NULL; ship *last2 = NULL;
	creat_gameboard(gameboardmajor, gameboardmajor2, gameboardminor);
	for (i = 0; i < num1; i++) {
		curr = (ship*)malloc(sizeof(ship));
		shipSetting(curr);
		if (headplayer == NULL) {
			headplayer = curr;
		}
		else {
			last->pt = curr;
		}
		last = curr;
		curr->pt = NULL;
	}
	curr->pt = headplayer;
	//curr = NULL; last = NULL;
	for (i = 0; i < num1; i++) {
		curr2 = (ship*)malloc(sizeof(ship));
		if (headcomputer == NULL) {
			headcomputer = curr2;
		}
		else {
			last2->pt = curr2;
		}
		last2 = curr2;
		curr2->pt = NULL;
	}
	curr2->pt = headcomputer;
	for (i = 0; i < num1; i++) {
		strcpy(headcomputer->shiptype, headplayer->shiptype);
		headcomputer->shipsize = headplayer->shipsize;
		headcomputer->size = headplayer->size;
		headcomputer->shipsymbol = headplayer->shipsymbol;
		headplayer = headplayer->pt; headcomputer = headcomputer->pt;
	}
	for (i = 0; i < num1; i++) {
		Playerselectlocation(headplayer, gameboardmajor);
		while (checkline2(headplayer) != headplayer->shipsize - 1) {
			for (j = 0; j < headplayer->shipsize; j++) {
				gameboardmajor[headplayer->Y_Location[j]][headplayer->X_Location[j]] = ' ';
			}
			printf("Cannot deploy ship here please reenter:\n");
			Playerselectlocation(headplayer, gameboardmajor);
		}
		headplayer = headplayer->pt;
	}
	for (i = 0; i < num1; i++) {
		computerselect(headcomputer, gameboardmajor2);
		while (checkline(headcomputer) != 0) {
			for (j = 0; j < headcomputer->shipsize; j++) {
				gameboardmajor2[headcomputer->Y_Location[j]][headcomputer->X_Location[j]] = ' ';
			}
			srand(time(NULL));
			computerselect(headcomputer, gameboardmajor2);
		}
		headcomputer = headcomputer->pt;
	} 
	printf("your major board:\n");
	print_gameboardmajor(gameboardmajor);
	creatint(headplayer, num1);
	creatint(headcomputer, num1);
	int num2 = num1;
	while (flag != 1) {

		Playershoot(headcomputer, gameboardmajor2, gameboardminor, num2, &marking1);
		computershoot(headplayer, gameboardmajor, num1, &marking);
		printf("your minor board:\n");
		print_gameboardminor(gameboardminor);
		printf("your major board:\n");
		print_gameboardmajor(gameboardmajor);
		tractscore(headplayer, headcomputer, gameboardmajor2, gameboardmajor, num2, num1, &computersunk, &playersunk);
		checkdeleteship(&headplayer, &num1, &flag, &marking);
		checkdeleteship(&headcomputer, &num2, &flag, &marking1);
	}
	printf("game Over!!!!\n");
	if (computersunk > playersunk) {
		printf("you win!!!\n");
	}
	else {
		printf("you lost!!!\n");
	}
	printf("your major board:\n");
	print_gameboardmajor(gameboardmajor);
	printf("computer's major board:\n");
	print_gameboardmajor(gameboardmajor2);
	return 0;
}
