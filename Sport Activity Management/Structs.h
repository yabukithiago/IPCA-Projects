/**
 * @file Structs.h
 * @author Thiago Yabuki de Araujo
 * @date 2022
 * @brief File with all the structs used in the project
 */

typedef struct Numbers {
	int NumberClient; /* Number of client*/
	int Telefone; /* Phone number of client*/
	int Age; /* Age of client*/
	int DayI; /* Initial day of activity*/
	int MonthI; /* Initial month of activity*/
	int YearI; /* Initial year of activity*/
	int DayI2; /* Initial day of activity 2*/
	int MonthI2; /* Initial month of activity 2*/
	int YearI2; /* Initial year of activity 2*/
	int DayF; /* Final day of activity*/
	int MonthF; /* Final month of activity*/
	int YearF; /* Final year of activity*/
	int DayD; /* Day of activity*/
	int MonthD; /* Month of activity*/
	int YearD; /* Year of activity*/
	int HourI; /* Initial hour of activity*/
	int MinI; /* Initial hour of activity*/
	int HourI2; /* Initial hour of activity 2*/
	int MinI2; /* Initial hour of activity 2*/
	int HourF; /* Final hour of activity*/
	int MinF; /* Final hour of activity*/
	int DurationM; /* Duration of activity in minutes*/
	int Distance; /* Distance of activity*/
	int Size; /* Size of activity*/
	int Size1; /* Size of activity 2*/
	int totalTime; /* Total time of activity*/
	int numActivities; /* Number of activities*/
	int totaldistance; /* Total distance of activity*/
}Numbers;


typedef struct Dados {
	char name[100]; /* Name of practitioner*/
	char Activity[100]; /* Name of activity*/
	char Activity1[100]; 
	char measure[10]; /* Measure of activity*/
	char measure1[10]; 
	Numbers InfoNumbers; /* Struct with all the numbers*/
}Dados;