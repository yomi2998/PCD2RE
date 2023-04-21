#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#pragma warning (disable:4996)
#pragma warning(disable: 6031)

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
	char position[16];
	Date birth;
} Staff;

typedef struct {
	char member_id[11];
	char name[31];
	char gender;
	char password[17];
	char email[50];
	char phone_number[20];
	char address[100];
	float balance;
	char status[16];
	Date birth;
} Member;

typedef struct {
	char stock_id[11];
	char name[31];
	char category[21];
	char description[100];
	int quantity;
	char forSale;
	float price;
	Date import_date;
} Stock;

void IDGet(char* ID, const char* Imodule, const char* action)
{
	printf("Enter %s ID to %s (-1 to cancel): ", Imodule, action);
	scanf( "%10s", ID);
	while (getchar() != '\n');
}
int checkSentinent(char* str) // check user input "-1" then will exit session
{
	return strcmp(str, "-1") == 0;
}

void dprintf(size_t n) // print n "-" to console
{
	for (size_t i = 0; i < n; i++)
		printf("-");
	printf("\n");
}

void IDGen(char* ID, const char* name) // generate ID for member and staff
{
	size_t i = 0;
	char temp[11] = { 0 };
	for (i = 0; i < 3; i++)
		temp[i] = toupper(name[i]);
	for (i = 3; i < 6; i++)
		temp[i] = rand() % 10 + 48;
	for (i = 6; i < 10; i++)
		temp[i] = rand() % 26 + 65;
	strcpy(ID, temp);
}

int validationName(const char* name)
{
	for (size_t i = 0; i < strlen(name); i++)
	{
		if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '/') // <- A/L, A/P
			return 0;
		else if (islower(name[i]))
		{
			if (i == 0)
				return 0;
			if (name[i - 1] == ' ' || name[i - 1] == '/')
				return 0;
		}
	}
	return 1;
}

int validationAddress(const char* address)
{
	int comma = 0, num = 0, space = 0;
	for (size_t i = 0; i < strlen(address); i++)
	{
		if(isalnum(address[i]))
			num++;
		else if (address[i] == ',')
			comma++;
		else if (address[i] == ' ')
			space++;
		if (islower(address[i]))
		{
			if (i == 0)
				return 0;
			if (address[i - 1] == ',')
				return 0;
		}
	}
	return comma && num && space;
}

int validationPhone(const char* phone)
{
	size_t i = 0;
	int num = 0, space = 0;
	for (i = 0; i < strlen(phone); i++)
		if (!isdigit(phone[i]))
			return 0;
		return strlen(phone) >= 10;
}

int validationPassword(const char* password)
{
	size_t i = 0;
	int upper = 0, lower = 0, digit = 0, special = 0;
	for (i = 0; i < strlen(password); i++)
	{
		if (isupper(password[i]))
			upper++;
		else if (islower(password[i]))
			lower++;
		else if (isdigit(password[i]))
			digit++;
		else if (ispunct(password[i]))
			special++;
	}
	if (upper >= 1 && lower >= 1 && digit >= 1 && special >= 1 && strlen(password) >= 8)
		return 1;
	else
		return 0;
}

int validationEmail(const char* email)
{
	size_t i = 0;
	int at = 0, dot = 0;
	for (i = 0; i < strlen(email); i++)
	{
		if (isspace(email[i])) {
			return 0;
		}
		if (email[i] == '@' && !dot)
			at++;
		else if (email[i] == '.' && at)
			dot++;
	}
	if (at && dot)
		return 1;
	else
		return 0;
}

int validationBirth(Date dob)
{
	time_t now = time(NULL);
	struct tm birthTime = { 0 };
	birthTime.tm_year = dob.year - 1900;
	birthTime.tm_mon = dob.month - 1;
	birthTime.tm_mday = dob.day;
	time_t birthTimestamp = mktime(&birthTime);
	double ageInSeconds = difftime(now, birthTimestamp);
	double ageInYears = ageInSeconds / (365.25 * 24 * 60 * 60);
	if (dob.year < 1900 || dob.year > 2023)
		return 0;
	if (dob.month < 1 || dob.month > 12)
		return 0;
	if (dob.day < 1 || dob.day > 31)
		return 0;
	if ((dob.month == 4 || dob.month == 6 || dob.month == 9 || dob.month == 11) && dob.day > 30)
		return 0;
	if (dob.month == 2) {
		int isLeapYear = ((dob.year % 4 == 0 && dob.year % 100 != 0) || dob.year % 400 == 0);
		if (isLeapYear && dob.day > 29)
			return 0;
		if (!isLeapYear && dob.day > 28)
			return 0;
	}
	if (ageInYears < 18.0)
		return 0;
	return 1;
}

int validationStockImport(Date doi)
{
	if (doi.year < 1900 || doi.year > 2023)
		return 0;
	if (doi.month < 1 || doi.month > 12)
		return 0;
	if (doi.day < 1 || doi.day > 31)
		return 0;
	if ((doi.month == 4 || doi.month == 6 || doi.month == 9 || doi.month == 11) && doi.day > 30)
		return 0;
	if (doi.month == 2) {
		int isLeapYear = ((doi.year % 4 == 0 && doi.year % 100 != 0) || doi.year % 400 == 0);
		if (isLeapYear && doi.day > 29)
			return 0;
		if (!isLeapYear && doi.day > 28)
			return 0;
	}
	return 1;
}