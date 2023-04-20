#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#pragma warning (disable:4996)

char* IDGen(char* ID, const char* name)
{
	int i = 0, j = 0;
	char temp[11] = { 0 };
	for (i = 0; i < 3; i++)
		temp[i] = toupper(name[i]);
	for (i = 3; i < 6; i++)
		temp[i] = rand() % 10 + 48;
	for (i = 6; i < 10; i++)
		temp[i] = rand() % 26 + 65;
	strcpy(ID, temp);
	return ID; // 3 letters of name + 3 random numbers + 5 random letters
}

void generateLog(const char* context, const char* by_who, const int level)
{
	FILE* f = fopen("syslog.txt", "a");
	if (f == NULL)
	{
		return; //silent
	}
	char level_str[15];
	strcpy(level_str, level == 0 ? "[INFO] - " : level == 1 ? "[WARNING] - " : "[ERROR] - ");

	char f_context[256] = { 0 };
	strcat(f_context, level_str);
	strcat(f_context, by_who);
	strcat(f_context, " : ");
	strcat(f_context, context);
	fprintf(f, "%s\n", f_context);
	fclose(f);
}

typedef struct
{
	int day;
	int month;
	int year;
}Date;

typedef struct {
	char staff_id[11];
	char name[50];
	char gender;
	char password[17];
	char email[50];
	char phone_number[20];
	char address[100];
	float salary;
	Date birth;
} Staff;

typedef struct {
	char member_id[11];
	char name[31];
	char gender;
	char password[17];
	char email[31];
	char phone_number[20];
	char address[100];
	float balance;
	char status[16];
	Date birth;
} Member;

typedef struct {
	int stock_id;
	char name[50];
	char description[100];
	int quantity;
	float price;
	Date import_date;
} Stock;