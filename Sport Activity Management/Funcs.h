/**
 * @file Funcs.h
 * @author Thiago Yabuki de Araujo
 * @date 2022
 * @brief File with all the functions used in the project
 */

/**
 * @brief Checks if the entered hour and minute are valid.
 * 
 * @param Hour 
 * @param Min 
 * @return 0 if the hour and minute are valid, 1 if they are not.
 */
int getValidHour(int Hour, int Min) {												
	if (Hour < 0 || Hour > 23) {													
		return 1;															
	}
	if (Min < 0 || Min > 59) {													
		return 1;																
	}

	return 0;																		
}

/**
 * @brief Checks if the entered date is valid.
 * 
 * @param Day 
 * @param Month 
 * @return 0 if the date is valid, 1 if it is not.
 */
int getValidData(int Day, int Month) {												
	if (Month < 1 || Month > 12) {
		return 1;
	}


	if (Day < 1) {
		return 1;
	}														

	int DayM;																		
	if (Month == 2)
	{
		DayM = 28;
	}
	else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
	{
		DayM = 30;
	}
	else {
		DayM = 31;
	}


	if (Day > DayM) {
		return 1;
	}													


	return 0;																	
}

/**
 * @brief Checks if the entered name is valid.
 * 
 * @return char 
 */
char getValidChar() {
	char c;
	do {
		c = getchar();
	} while (c != 'y' && c != 'n');
	return c;
}

/**
 * @brief Checks if the entered string is valid.
 * 
 * @param str 
 */
void getValidStr(char str[]) {
	do {
		gets(str);
	} while (strlen(str) == 0);
}

/**
 * @brief This function prints the data of the client in the file "TabelaDiaD.txt".
 * 
 * @param c 
 */
void printDiaD(Dados c) {
	FILE *f = fopen("TabelaDiaD.txt", "a");
	
	fprintf(f, "|%04d\t|%-15s\t|%-10s\t|%-10d%s\t|%10s\t|%02d/%02d/%04d\t|%02d/%02d/%04d\t|  %d %s \t| \n",
		c.InfoNumbers.NumberClient, c.name, c.Activity1, c.InfoNumbers.Size1, c.measure1, c.Activity,c.InfoNumbers.DayI, c.InfoNumbers.MonthI, c.InfoNumbers.YearI,
		c.InfoNumbers.DayF, c.InfoNumbers.MonthF, c.InfoNumbers.YearF, c.InfoNumbers.Size, c.measure
	);
	fprintf(f, "+---------------+---------------+-----------------------+-----------------------+---------------+---------------+-----------------------+----------------+\n");
	fclose(f);

	printf("|\t%d\t|\t%s\t|\t%d/%d/%d\t|\t%d/%d/%d\t|\t%dKm\t|\t%d\t|\t\t%02d/%02d/%02d\t\t|\n",
		c.InfoNumbers.NumberClient, c.name, c.InfoNumbers.DayI, c.InfoNumbers.MonthI, c.InfoNumbers.YearI,
		c.InfoNumbers.DayF, c.InfoNumbers.MonthF, c.InfoNumbers.YearF, c.InfoNumbers.totaldistance, c.InfoNumbers.totalTime,
		c.InfoNumbers.DayI2, c.InfoNumbers.MonthI2, c.InfoNumbers.YearI2);
	printf("+---------------+---------------+-----------------------+-----------------------+---------------+---------------+-----------------------+---------------+\n");
}

/**
 * @brief This function prints the practitioner's data and his day of greatest effort (Day D) in a table.
 * 
 * @param y 
 * @param certs2 
 * @param numCerts 
 */
void tabelaDiaD(Dados y, Dados* certs2, int numCerts) {
	Dados activityData[100] = { 0 };
	int numActivityData = 0;


	for (int i = 0; i < numCerts; i++) {

		Dados activity = certs2[i];

		if (PractList(activity, y)) {

			int j;
			for (j = 0; j < numActivityData; j++) {

				if (activityData[j].InfoNumbers.NumberClient == activity.InfoNumbers.NumberClient && strcmp(activityData[j].Activity, activity.Activity) == 0) {
					break;
				}
			}

			if (activityData[j].InfoNumbers.Size < activity.InfoNumbers.Size) {
				activityData[j].InfoNumbers.Size = activity.InfoNumbers.Size;
				activityData[j].InfoNumbers.DayI2 = activity.InfoNumbers.DayI2;
				activityData[j].InfoNumbers.MonthI2 = activity.InfoNumbers.MonthI2;
				activityData[j].InfoNumbers.YearI2 = activity.InfoNumbers.YearI2;
			}

			if (j == numActivityData) {
				activityData[numActivityData].InfoNumbers.NumberClient = activity.InfoNumbers.NumberClient;
				strcpy(activityData[numActivityData].Activity, activity.Activity);
				numActivityData++;
			}

			activityData[j].InfoNumbers.totalTime += activity.InfoNumbers.DurationM;
			activityData[j].InfoNumbers.totaldistance += activity.InfoNumbers.Size;
			activityData[j].InfoNumbers.numActivities++;
		}
	}

	Dados certs[100], certs4[100];
	int i, d = 0;

	i = scanDataPract(certs);

	FILE* f = fopen("TabelaDiaD.txt", "w");
	if (f == NULL)
	{
		printf("Error opening the file! \n");
		return;
	}
	
	fprintf(f, "+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
	fprintf(f, "|Number\t|Name\t\t\t|Activity\t|Distance\t|Activity\t|Start Date\t|End Date\t|Distance \t| \n");
	fprintf(f, "+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
	
	fclose(f);

	printf("+---------------+---------------+-----------------------+-----------------------+---------------+---------------+-----------------------+---------------+\n");
	printf("|\tNumber\t|\tName\t|\tStart\t\t|\tEnd\t\t|\tTotal\t|\tTime\t|\tDay with more effort\t\t|\n");
	printf("+---------------+---------------+-----------------------+-----------------------+---------------+---------------+-----------------------+---------------+\n");


	for (int a = 0; a < i; a++) {
		for (int e = 0; e < numActivityData; e++) {
			if (certs[a].InfoNumbers.NumberClient == activityData[e].InfoNumbers.NumberClient) {
				certs4[d].InfoNumbers.NumberClient = certs[a].InfoNumbers.NumberClient;
				strcpy(certs4[d].name, certs[a].name);
				certs4[d].InfoNumbers.totaldistance = activityData[e].InfoNumbers.totaldistance;
				certs4[d].InfoNumbers.totalTime = activityData[e].InfoNumbers.totalTime;
				certs4[d].InfoNumbers.DayI2 = activityData[e].InfoNumbers.DayI2;
				certs4[d].InfoNumbers.MonthI2 = activityData[e].InfoNumbers.MonthI2;
				certs4[d].InfoNumbers.YearI2 = activityData[e].InfoNumbers.YearI2;
				certs4[d].InfoNumbers.DayI = y.InfoNumbers.DayI;
				certs4[d].InfoNumbers.MonthI = y.InfoNumbers.MonthI;
				certs4[d].InfoNumbers.YearI = y.InfoNumbers.YearI;
				certs4[d].InfoNumbers.DayF = y.InfoNumbers.DayF;
				certs4[d].InfoNumbers.MonthF = y.InfoNumbers.MonthF;
				certs4[d].InfoNumbers.YearF = y.InfoNumbers.YearF;
				d++;
			}
		}
	}

	for (--d; d >= 0; d--) {
		printDiaD(certs4[d]);
	}

	char str[100];
	FILE *f3 = fopen("TabelaDiaD.bin", "wb");
	FILE *f2 = fopen("TabelaDiaD.txt", "r");

	if (f2 == NULL) {
		printf("Error opening the file! \n");
	}

	while (fgets(str, 100, f2) != NULL) {
    	size_t str_size = strlen(str);
		fwrite(str, 1, str_size, f3);
	}

	fclose(f2);
	fclose(f3);
}


/**
 * @brief This function prints the practitioner's data on the console.
 * 
 * @param c 
 */
void printPractList(Dados c) {
	printf(" %d;%d-%d-%d;%d:%d;%s;%d;%d;%s;\n", c.InfoNumbers.NumberClient, c.InfoNumbers.DayI2, c.InfoNumbers.MonthI2,
	c.InfoNumbers.YearI2, c.InfoNumbers.HourI, c.InfoNumbers.MinI, c.Activity, c.InfoNumbers.DurationM, c.InfoNumbers.Size, c.measure);
}


/**
 * @brief This function reads data from the DataPract.txt file.
 * 
 * @param certs 
 * @return int
 */
int scanDataPract(Dados* certs) {
	Dados c;
	char str[100];
	int i = 0;
	
	
	FILE* fp = fopen("DataPract.txt", "r");

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return;
	}

	
	while (fgets(str, 100, fp) != NULL) {
		sscanf(str, "%d;%[^;];%d;%d", &c.InfoNumbers.NumberClient, &c.name, &c.InfoNumbers.Telefone, &c.InfoNumbers.Age);
		certs[i++] = c;
	}


	fclose(fp);
	return i;
}


/**
 * @brief This function reads data from the InfoActiv.txt file.
 * 
 * @param certs 
 * @return int
 */
int scanInfoActiv(Dados* certs) {

	Dados c;
	char str[100];
	int i = 0;
	FILE* fp = fopen("InfoActiv.txt", "r");

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return;
	}

	while (fgets(str, 100, fp) != NULL) {

		sscanf(str, "%d;%d-%d-%d;%d:%d;%[^;];%d;%d;%[^;];", &c.InfoNumbers.NumberClient, &c.InfoNumbers.DayI2, &c.InfoNumbers.MonthI2,
			&c.InfoNumbers.YearI2, &c.InfoNumbers.HourI, &c.InfoNumbers.MinI, &c.Activity, &c.InfoNumbers.DurationM, &c.InfoNumbers.Size, &c.measure);

		certs[i++] = c;
	}


	fclose(fp);
	return i;
}


/**
 * @brief This funciont reads data from the PlanActiv.txt file.
 * 
 * @param certs 
 * @return int 
 */
int scanPlanActiv(Dados* certs) {
	Dados c;
	int i = 0;
	char str[100];

	FILE* fp = fopen("PlanActiv.txt", "r");

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return;
	}

	while (fgets(str, 100, fp) != NULL) {
		sscanf(str, "%d;%02d-%02d-%04d;%02d:%02d;%02d-%02d-%02d;%02d:%02d;%[^;]; %d;%[^;];", &c.InfoNumbers.NumberClient, &c.InfoNumbers.DayI, &c.InfoNumbers.MonthI, &c.InfoNumbers.YearI, &c.InfoNumbers.HourI, &c.InfoNumbers.MinI, &c.InfoNumbers.DayF, &c.InfoNumbers.MonthF, &c.InfoNumbers.YearF, &c.InfoNumbers.HourF, &c.InfoNumbers.MinF, &c.Activity1, &c.InfoNumbers.Size1, &c.measure1);
		certs[i++] = c;
	}

	fclose(fp);
	return i;
}


/**
 * @brief This function will compare the dates and check if it is within a period of time.
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int PractList(Dados x, Dados y) {

	if ((y.InfoNumbers.YearI < x.InfoNumbers.YearI2 || (y.InfoNumbers.YearI == x.InfoNumbers.YearI2 && y.InfoNumbers.MonthI < x.InfoNumbers.MonthI2) || (y.InfoNumbers.YearI == x.InfoNumbers.YearI2 && y.InfoNumbers.MonthI == x.InfoNumbers.MonthI2 && y.InfoNumbers.DayI <= x.InfoNumbers.DayI2)) &&
		(x.InfoNumbers.YearI2 < y.InfoNumbers.YearF || (x.InfoNumbers.YearI2 == y.InfoNumbers.YearF && x.InfoNumbers.MonthI2 < y.InfoNumbers.MonthF) || (x.InfoNumbers.YearI2 == y.InfoNumbers.YearF && x.InfoNumbers.MonthI2 == y.InfoNumbers.MonthF && x.InfoNumbers.DayI2 <= y.InfoNumbers.DayF))) {
		return 1;
	}

	else {
		return 0;
	}

}


/**
 * @brief This function sorts the array in descending order.
 * 
 * @param array 
 * @param size 
 */
void organizaArray(Dados* array, int size) {
	int i, j, max_index;
	Dados temp;
	for (i = 0; i < size - 1; i++) {
		max_index = i;
		for (j = i + 1; j < size; j++) {
			if (array[j].InfoNumbers.NumberClient > array[max_index].InfoNumbers.NumberClient) {
				max_index = j;
			}
		}
		temp = array[i];
		array[i] = array[max_index];
		array[max_index] = temp;
	}
}


/**
 * @brief This function will compare the dates and call the tabelaDiaD function. 
 *  
 */
void diaUser() {
	Dados y, certs[100];
	int i;
	do {

		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayI, &y.InfoNumbers.MonthI, &y.InfoNumbers.YearI);

	} while (getValidData(y.InfoNumbers.DayI, y.InfoNumbers.MonthI));

	do {


		printf("End date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayF, &y.InfoNumbers.MonthF, &y.InfoNumbers.YearF);
	} while (getValidData(y.InfoNumbers.DayF, y.InfoNumbers.MonthF));
	i = scanInfoActiv(certs);

	tabelaDiaD(y, certs, i);

}


/**
 * @brief This function lists the number of practitioners in descending order.
 * 
 */

void ordemDec() {
	
	Dados y, * certs = malloc(100 * sizeof(Dados));
	char* str = malloc(100 * sizeof(char));
	Dados* array = malloc(100 * sizeof(Dados));
	int i, a = 0, j = 0;

	printf("Activity: \n");
	getValidStr(y.Activity);
	do {
		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayI, &y.InfoNumbers.MonthI, &y.InfoNumbers.YearI);

	} while (getValidData(y.InfoNumbers.DayI, y.InfoNumbers.MonthI));

	do {
		printf("End date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayF, &y.InfoNumbers.MonthF, &y.InfoNumbers.YearF);
	} while (getValidData(y.InfoNumbers.DayF, y.InfoNumbers.MonthF));

	i = scanInfoActiv(certs);
	
	for (int j = 0; j < i; j++) {
		if (PractList(certs[j], y)) {
			if (strstr(y.Activity, certs[j].Activity) != NULL) {
				array[a++] = certs[j];
			}
		}
	}

	organizaArray(array, a);

	for (j = 0; j < a; j++) {
		printPractList(array[j]);
	}
	printf("\nTotal number of practitioners: %d\n", a);

	free(certs);
	free(str);
	free(array);
}


/**
 * @brief This function prints the data in a table.
 * 
 * @param c 
 */
void print7(Dados c) {
	printf("%d;%d-%d-%d;%d:%d;%d-%d-%d;%d:%d;%s;%d;%s;", c.InfoNumbers.NumberClient, c.InfoNumbers.DayI, c.InfoNumbers.MonthI, c.InfoNumbers.YearI, c.InfoNumbers.HourI, c.InfoNumbers.MinI, c.InfoNumbers.DayF, c.InfoNumbers.MonthF, c.InfoNumbers.YearF, c.InfoNumbers.HourF, c.InfoNumbers.MinF, c.Activity1, c.InfoNumbers.Size1, c.measure1);
}


/**
 * @brief This function will list the activities in a certain period of time and call the print7 function to print the data.
 * 
 */
void listAtividades() {
	Dados y, certs[100];
	int j;
	printf("Enter activity name: \n");
	getValidStr(y.Activity1);

	do {
		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayI, &y.InfoNumbers.MonthI, &y.InfoNumbers.YearI);
	} while (getValidData(y.InfoNumbers.DayI, y.InfoNumbers.MonthI));

	do {
		printf("End date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayF, &y.InfoNumbers.MonthF, &y.InfoNumbers.YearF);
	} while (getValidData(y.InfoNumbers.DayF, y.InfoNumbers.MonthF));

	printf("Practitioner number: \n");
	scanf("%d", &y.InfoNumbers.NumberClient);

	j = scanPlanActiv(certs);

	for (int i = 0; i < j; i++) {
		if (y.InfoNumbers.NumberClient == certs[i].InfoNumbers.NumberClient) {

			if (strcmp(certs[i].Activity1, y.Activity1) == 0) {

				if ((y.InfoNumbers.YearI > certs[i].InfoNumbers.YearI || (y.InfoNumbers.YearI == certs[i].InfoNumbers.YearI && y.InfoNumbers.MonthI > certs[i].InfoNumbers.MonthI) || (y.InfoNumbers.YearI == certs[i].InfoNumbers.YearI && y.InfoNumbers.MonthI == certs[i].InfoNumbers.MonthI && y.InfoNumbers.DayI > certs[i].InfoNumbers.DayI)) && (y.InfoNumbers.YearF < certs[i].InfoNumbers.YearF || (y.InfoNumbers.YearF == certs[i].InfoNumbers.YearF && y.InfoNumbers.MonthF < certs[i].InfoNumbers.MonthF) || (y.InfoNumbers.YearF == certs[i].InfoNumbers.YearF && y.InfoNumbers.MonthF == certs[i].InfoNumbers.MonthF && y.InfoNumbers.DayF < certs[i].InfoNumbers.DayF))) {
				}
				else {

					print7(certs[i]);
				}
			}
		}
	}
}


/**
 * @brief This function calculates the total activity time and the average spent by a practitioner.
 * 
 * @param y 
 * @param certs 
 * @param numCerts 
 */
void calcActivityTimes(Dados y, Dados* certs, int numCerts) {
	Dados activityData[100] = { 0 };
	int numActivityData = 0;


	for (int i = 0; i < numCerts - 1; i++) {

		Dados activity = certs[i];

		if (PractList(activity, y)) {

			int j;
			for (j = 0; j < numActivityData; j++) {
				if (activityData[j].InfoNumbers.NumberClient == activity.InfoNumbers.NumberClient && strcmp(activityData[j].Activity, activity.Activity) == 0) {
					break;
				}
			}

			if (j == numActivityData) {
				activityData[numActivityData].InfoNumbers.NumberClient = activity.InfoNumbers.NumberClient;
				strcpy(activityData[numActivityData].Activity, activity.Activity);
				numActivityData++;
			}

			activityData[j].InfoNumbers.totalTime += activity.InfoNumbers.DurationM;
			activityData[j].InfoNumbers.numActivities++;
		}


	}


	for (int i = 0; i < numActivityData; i++) {
		Dados data = activityData[i];
		int avgTime = data.InfoNumbers.totalTime / data.InfoNumbers.numActivities;
		printf(" %d;", data.InfoNumbers.NumberClient);
		printf("%s;", data.Activity);
		printf("Total time: %d minutes\n", data.InfoNumbers.totalTime);
		printf("Average per activity: %d minutes\n", avgTime);
	}
}


/**
 * @brief This function verifies if the client performed the activity in the period of time indicated by the user, if it is equal to the file date, the function calls calcActivityTimes.
 *
 */
void calcMedia() {
	Dados y, certs[100];
	int i;
	do {

		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayI, &y.InfoNumbers.MonthI, &y.InfoNumbers.YearI);

	} while (getValidData(y.InfoNumbers.DayI, y.InfoNumbers.MonthI));

	do {


		printf("End date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayF, &y.InfoNumbers.MonthF, &y.InfoNumbers.YearF);
	} while (getValidData(y.InfoNumbers.DayF, y.InfoNumbers.MonthF));
	i = scanInfoActiv(certs);

	calcActivityTimes(y, certs, i);
}


/**
 * @brief This function calculates the distance traveled by a practitioner.
 * 
 */
void calcDistancia() {
	Dados y, certs[100];
	int j;
	printf("Activity: \n");
	getValidStr(y.Activity1);

	do {
		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayI, &y.InfoNumbers.MonthI, &y.InfoNumbers.YearI);
	} while (getValidData(y.InfoNumbers.DayI, y.InfoNumbers.MonthI));

	do {


		printf("End date: (d-m-y) \n");
		scanf("%d-%d-%d", &y.InfoNumbers.DayF, &y.InfoNumbers.MonthF, &y.InfoNumbers.YearF);
	} while (getValidData(y.InfoNumbers.DayF, y.InfoNumbers.MonthF));

	printf("Practitioner number: \n");
	scanf("%d", &y.InfoNumbers.NumberClient);

	j = scanPlanActiv(certs);

	for (int i = 0; i < j; i++) {
		if (y.InfoNumbers.NumberClient == certs[i].InfoNumbers.NumberClient) {

			if (strcmp(certs[i].Activity1, y.Activity1) == 0) {

				if ((y.InfoNumbers.YearI > certs[i].InfoNumbers.YearI || (y.InfoNumbers.YearI == certs[i].InfoNumbers.YearI && y.InfoNumbers.MonthI > certs[i].InfoNumbers.MonthI) || (y.InfoNumbers.YearI == certs[i].InfoNumbers.YearI && y.InfoNumbers.MonthI == certs[i].InfoNumbers.MonthI && y.InfoNumbers.DayI > certs[i].InfoNumbers.DayI)) && (y.InfoNumbers.YearF < certs[i].InfoNumbers.YearF || (y.InfoNumbers.YearF == certs[i].InfoNumbers.YearF && y.InfoNumbers.MonthF < certs[i].InfoNumbers.MonthF) || (y.InfoNumbers.YearF == certs[i].InfoNumbers.YearF && y.InfoNumbers.MonthF == certs[i].InfoNumbers.MonthF && y.InfoNumbers.DayF < certs[i].InfoNumbers.DayF))) {
				}
				else {

					print7(certs[i]);
				}
			}
		}
	}
}


/**
 * @brief This function is used to print a table on the screen and also in the Tabela.txt file.
 * 
 * @param c 
 */
void prinTabela(Dados c) {
	FILE *f = fopen("Tabela.txt", "a");
	
	fprintf(f, "|%04d\t|%-15s\t|%-10s\t|%-10d%s\t|%10s\t|%02d/%02d/%04d\t|%02d/%02d/%04d\t|  %d %s \t| \n",
		c.InfoNumbers.NumberClient, c.name, c.Activity1, c.InfoNumbers.Size1, c.measure1, c.Activity,c.InfoNumbers.DayI, c.InfoNumbers.MonthI, c.InfoNumbers.YearI,
		c.InfoNumbers.DayF, c.InfoNumbers.MonthF, c.InfoNumbers.YearF, c.InfoNumbers.Size, c.measure
	);
	fprintf(f, "+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
	
	fclose(f);

	printf("|%04d\t|%-15s\t|%-10s\t|%-10d%s\t|%10s\t|%02d/%02d/%04d\t|%02d/%02d/%04d\t|  %d %s \t| \n",
		c.InfoNumbers.NumberClient, c.name, c.Activity1, c.InfoNumbers.Size1, c.measure1, c.Activity,c.InfoNumbers.DayI, c.InfoNumbers.MonthI, c.InfoNumbers.YearI,
		c.InfoNumbers.DayF, c.InfoNumbers.MonthF, c.InfoNumbers.YearF, c.InfoNumbers.Size, c.measure
	);
	printf("+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
}

/**
 * @brief This function is used to read data and print it in a table on the screen and also in the Tabela.txt file.
 * 
 */
void table() {
	
	Dados certs[100], certs2[100], certs3[100], certs4[100];
	int i, j, l, d = 0;


	i = scanDataPract(certs);
	j = scanInfoActiv(certs2);
	l = scanPlanActiv(certs3);

	FILE* f = fopen("Tabela.txt", "w");
	if (f == NULL)
	{
		printf("Error opening the file! \n");
		return;
	}
	
	fprintf(f, "+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
	fprintf(f, "|Number\t|Name\t\t\t|Activity\t|Distance\t|Activity\t|Start date\t|End date\t|Distance \t| \n");
	fprintf(f, "+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
	
	fclose(f);


	printf("+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
	printf("|Number\t|Name\t\t\t|Activity\t|Distance\t|Activity\t|Start date\t|End date\t|Distance \t| \n");
	printf("+-------+-----------------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");

	for (int a = 0; a < i; a++) {
		for (int b = 0; b < j; b++) {
			for (int c = 0; c < l; c++) {
				if (certs[a].InfoNumbers.NumberClient == certs3[c].InfoNumbers.NumberClient && certs2[b].InfoNumbers.NumberClient == certs[a].InfoNumbers.NumberClient) {
					certs4[d].InfoNumbers.NumberClient = certs[a].InfoNumbers.NumberClient;
					strcpy(certs4[d].name, certs[a].name);
					strcpy(certs4[d].Activity, certs2[b].Activity);
					strcpy(certs4[d].measure, certs2[b].measure);
					certs4[d].InfoNumbers.Size = certs2[b].InfoNumbers.Size;
					certs4[d].InfoNumbers.DayI = certs3[c].InfoNumbers.DayI;
					certs4[d].InfoNumbers.MonthI = certs3[c].InfoNumbers.MonthI;
					certs4[d].InfoNumbers.YearI = certs3[c].InfoNumbers.YearI;
					certs4[d].InfoNumbers.DayF = certs3[c].InfoNumbers.DayF;
					certs4[d].InfoNumbers.MonthF = certs3[c].InfoNumbers.MonthF;
					certs4[d].InfoNumbers.YearF = certs3[c].InfoNumbers.YearF;
					certs4[d].InfoNumbers.Size1 = certs3[c].InfoNumbers.Size1;
					strcpy(certs4[d].Activity1, certs3[c].Activity1);
					strcpy(certs4[d].measure1, certs3[c].measure1);
					d++;
				}
			}

		}
	}

	for (--d; d >= 0; d--) {
		prinTabela(certs4[d]);
	}

	char str[100];
	FILE *f3 = fopen("Tabela.bin", "wb");
	FILE *f2 = fopen("Tabela.txt", "r");

	if (f2 == NULL) {
		printf("Error opening the file! \n");
	}

	while (fgets(str, 100, f2) != NULL) {
    	size_t str_size = strlen(str);
		fwrite(str, 1, str_size, f3);
	}

	fclose(f2);
	fclose(f3);
}


/**
 * @brief This function is used to define the data of practitioners.
 * 
 * @return Dados 
 */
Dados defDataPract() {
	Dados x;																	
	printf("Enter practitioner name: \n");
	getValidStr(x.name);

	printf("Phone number: \n");
	scanf("%d", &x.InfoNumbers.Telefone);

	printf("Practitioner's age: \n");
	scanf("%d", &x.InfoNumbers.Age);

	printf("Practitioner number: \n");
	scanf("%d", &x.InfoNumbers.NumberClient);

	system("CLS");

	return x;
}


/**
 * @brief This function is used to define the data of activity.
 * 
 * @return Dados 
 */
Dados defInfoActiv() {
	Dados x;


	printf("Practitioner number: \n");
	scanf("%d", &x.InfoNumbers.NumberClient);


	do {
		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &x.InfoNumbers.DayI2, &x.InfoNumbers.MonthI2, &x.InfoNumbers.YearI2);

	} while (getValidData(x.InfoNumbers.DayI2, x.InfoNumbers.MonthI2));


	do {
		printf("Start time: (h:m) \n");
		scanf("%d:%d", &x.InfoNumbers.HourI2, &x.InfoNumbers.MinI2);

	} while (getValidHour(x.InfoNumbers.HourI2, x.InfoNumbers.MinI2));


	printf("Enter the name of the activity: \n");
	getValidStr(x.Activity);

	printf("Duration time: (min) \n");
	scanf("%d", &x.InfoNumbers.DurationM);


	printf("Distance: \n");
	scanf("%d", &x.InfoNumbers.Distance);


	printf("Enter the distance measurement\n");
	printf("0 - Km\n");
	printf("1 - Dm\n");
	printf("2 - m\n");
	printf("3 - cm\n");
	printf("4 - dm\n");
	printf("5 - nm\n");
	printf("Option: \n");
	scanf("%d", &x.InfoNumbers.Size);


	system("CLS");

	return x;
}


/**
 * @brief This function is used to define the plan data.
 * 
 * @return Dados 
 */
Dados defPlanActiv() {
	struct Dados x;
	char str[100];
	int a;
	printf("Practitioner number: \n");
	scanf("%d", &x.InfoNumbers.NumberClient);

	do {

		printf("Start date: (d-m-y) \n");
		scanf("%d-%d-%d", &x.InfoNumbers.DayI, &x.InfoNumbers.MonthI, &x.InfoNumbers.YearI);



	} while (getValidData(x.InfoNumbers.DayI, x.InfoNumbers.MonthI));

	do {
		printf("Start time: (h:m) \n");
		scanf("%d:%d", &x.InfoNumbers.HourI, &x.InfoNumbers.MinI);


	} while (getValidHour(x.InfoNumbers.HourI, x.InfoNumbers.MinI));


	do {

		printf("End date: (d-m-y) \n");
		scanf("%d-%d-%d", &x.InfoNumbers.DayF, &x.InfoNumbers.MonthF, &x.InfoNumbers.YearF);


	} while (getValidData(x.InfoNumbers.DayF, x.InfoNumbers.MonthF));

	do {
		printf("End time: (h:m) \n");
		scanf("%d:%d", &x.InfoNumbers.HourF, &x.InfoNumbers.MinF);


	} while (getValidHour(x.InfoNumbers.HourF, x.InfoNumbers.MinF));


	printf("Enter the name of the activity: \n");
	getValidStr(x.Activity);

	printf("Distance: \n");
	scanf("%d", &x.InfoNumbers.Distance);

	printf("Enter the distance measurement\n");
	printf("0 - Km\n");
	printf("1 - Dm\n");
	printf("2 - m\n");
	printf("3 - cm\n");
	printf("4 - dm\n");
	printf("5 - nm\n");
	printf("Option:\n");
	scanf("%d", &x.InfoNumbers.Size);
	system("CLS");

	return x;
}


/**
 * @brief This function is used to print the data of the practitioners in the DataPract.txt file.
 * 
 * @param c 
 */
void printDataPract(Dados c) {
	FILE* fp;

	fp = fopen("DataPract.txt", "a");

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return 0;
	}
	fprintf(fp, "%4d", c.InfoNumbers.NumberClient);
	fprintf(fp, ";%s", c.name);
	fprintf(fp, ";%9d", c.InfoNumbers.Telefone);
	fprintf(fp, ";%2d;\n", c.InfoNumbers.Age);
	fclose(fp);


}


/**
 * @brief This function is used to print the activities in the InfoActiv.txt file.
 * 
 * @param c 
 */
void printInfoActiv(Dados c) {												
	FILE* fp;																	

	fp = fopen("InfoActiv.txt", "a");										

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return 0;
	}															
	fprintf(fp, "%4d;", c.InfoNumbers.NumberClient);							
	fprintf(fp, "%2d-%2d-%4d; ", c.InfoNumbers.DayI2, c.InfoNumbers.MonthI2, c.InfoNumbers.YearI2);
	fprintf(fp, "%2d:%2d", c.InfoNumbers.HourI2, c.InfoNumbers.MinI2);			
	fprintf(fp, ";%s", c.Activity);											
	fprintf(fp, ";%2d", c.InfoNumbers.DurationM);								
	fprintf(fp, ";%3d", c.InfoNumbers.Distance);								
	switch (c.InfoNumbers.Size) {														
	case 0:
		fprintf(fp, ";Km;\n");
		break;
	case 1:
		fprintf(fp, ";Dm;\n");
		break;
	case 2:
		fprintf(fp, ";m;\n");
		break;
	case 3:
		fprintf(fp, ";dm;\n");
		break;
	case 4:
		fprintf(fp, ";cm;\n");
		break;
	case 5:
		fprintf(fp, ";nm;\n");
		break;
	default:
		fprintf(fp, ";No Distance;\n");											
	}
	fclose(fp);																	

}


/**
 * @brief This function is used to print the activitys plans in the PlanActiv.txt file.
 * 
 * @param c 
 */
void printPlanActiv(Dados c) {												
	FILE* fp;																		


	fp = fopen("PlanActiv.txt", "a");												
	if (fp == NULL) {
		printf("Error opening the file! \n");
		return 0;
	}															
	fprintf(fp, "%d;", c.InfoNumbers.NumberClient);							
	fprintf(fp, "%02d-%02d-%04d;", c.InfoNumbers.DayI, c.InfoNumbers.MonthI, c.InfoNumbers.YearI); 
	fprintf(fp, "%02d:%02d;", c.InfoNumbers.HourI, c.InfoNumbers.MinI);			
	fprintf(fp, "%02d-%02d-%04d;", c.InfoNumbers.DayF, c.InfoNumbers.MonthF, c.InfoNumbers.YearF); 
	fprintf(fp, "%02d:%02d", c.InfoNumbers.HourF, c.InfoNumbers.MinF);			
	fprintf(fp, ";%s", c.Activity);												
	fprintf(fp, ";%3d", c.InfoNumbers.Distance);							
	switch (c.InfoNumbers.Size) {															
	case 0:
		fprintf(fp, ";Km;\n");
		break;
	case 1:
		fprintf(fp, ";Dm;\n");
		break;
	case 2:
		fprintf(fp, ";m;\n");
		break;
	case 3:
		fprintf(fp, ";dm;\n");
		break;
	case 4:
		fprintf(fp, ";cm;\n");
		break;
	case 5:
		fprintf(fp, ";nm;\n");
		break;
	default:
		fprintf(fp, ";No Distance;\n");										
		fclose(fp);															
	}
}


/**
 * @brief This function defines the user information and calls the printDataPract function.
 * 
 */
void DataPract() {

	Dados certs[100], c;
	char o;
	int i = 0;

	do {
		c = defDataPract();
		certs[i++] = c;

		printf("Do you want to add more practitioners? (y/n) \n");
		o = getValidChar();

		system("CLS");

	} while (o == 'y');


	for (--i; i >= 0; i--) {
		printDataPract(certs[i]);
	}
}


/**
 * @brief This function sets user activity information and calls the printInfoActiv function.
 * 
 */
void InfoActiv() {

	Dados certs[100], c;
	char o;
	int i = 0;

	do {
		c = defInfoActiv();
		certs[i++] = c;

		printf("Do you want to add more practitioners? (y/n) \n");
		o = getValidChar();

		system("CLS");

	} while (o == 'y');


	for (--i; i >= 0; i--) {
		printInfoActiv(certs[i]);
	}
}


/**
 * @brief This function defines the users activity plan and calls the printPlanActiv function.
 * 
 */
void PlanActiv() {

	Dados certs[100], c;
	char o;
	int i = 0;

	do {
		c = defPlanActiv();
		certs[i++] = c;

		printf("Do you want to add more practitioners? (y/n) \n");
		o = getValidChar();

		system("CLS");

	} while (o == 'y');

	for (--i; i >= 0; i--) {
		printPlanActiv(certs[i]);
	}
}



/**
 * @brief This function reads the binary file Table.bin and prints its contents.
 * 
 */
void lerficheirobin(){
	FILE *fp = fopen("Tabela.bin", "rb");
	char str[100];

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return 0;
	}

	size_t result;
    while ((result = fread(&str, sizeof(char), 1, fp)) > 0) {
        printf("%s", str);
    }
	fclose(fp);
}


/**
 * @brief This function reads the binary file TableDiaD.bin and prints its content.
 * 
 */
void lerficheirobin2(){
	FILE *fp = fopen("TabelaDiaD.bin", "rb");
	char str[100];

	if (fp == NULL) {
		printf("Error opening the file! \n");
		return 0;
	}

	size_t result;
    while ((result = fread(&str, sizeof(char), 1, fp)) > 0) {
        printf("%s", str);
    }
	fclose(fp);
}
