#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>	
#include <string.h>
#include <stdlib.h>	
#include <time.h>	
#include <math.h>
#include <stddef.h>
#include "Structs.h"
#include "Funcs.h"

/**
 * @brief This function is the main part of the code that allows the user to access all sports activities management functions.
 * 
 */
void main() {
	int x;
	char o;
	char name[50];

	printf("Please, insert your name: ");
	scanf("%s", name);
	system("CLS");
	printf("Hello %s!\nWelcome to Activities Management!\n\n", name);
	do {
		printf(" M E N U\n");
		printf(" Please, select an option:\n 1. Practitioner Data \n 2. Information on each activity performed by each practitioner \n 3. Activity Plan Data\n ");
		printf("4. List of practitioners in a given period in descending order \n 5. List of practitioners in a given period \n 6. Calculation of total times and time averages\n ");
		printf("7. Table of planned activities\n 8. Practitioner's Table with the day with more physical effort \n 9. Read binary file \n 10. Read binary file with the day with more physical effort\n 0. Quit \n");
		printf(" Option: ");
		scanf("%d", &x);
		system("CLS");

		switch (x) {
		case(1):
			DataPract();
			break;
		case(2):
			InfoActiv();
			break;
		case(3):
			PlanActiv();
			break;
		case(4):
			ordemDec();
			break;
		case(5):
			listAtividades();
			break;
		case(6):
			calcMedia();
			break;
		case(7):
			table();
			break;
		case(8):
			diaUser();
			break;
		case(9):
			lerficheirobin();
			break;
		case(10):
			lerficheirobin2();
			break;
		case(0):
			printf("Thank you for using the program!\n");
			exit(0);
			break;
		default:
			printf("Invalid value! \n Please, enter a value between 1 and 10.\n");
			break;
		}

		printf("Intends to end the program (y/n)? ");
		o = getValidChar();

		system("CLS");

	} while (o == 'n');


	return 0;
}