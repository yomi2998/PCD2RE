#include "necessaryIncludes.h"
#include "member.h"
#include <time.h>
int printMenu()
{
	printf
	(
		"------------------------------\n"
		"|   System for MLM Company   |\n"
		"|----------------------------|\n"
		"|1. Member information module|\n"
		"|2. Staff information module |\n"
		"|3. Stock information module |\n"
		"|4. Exit                     |\n"
		"------------------------------\n"
		"Enter your choice: "
	);
	int selection;
	scanf(" %d", &selection);
	while (selection < 1 || selection > 4)
	{
		printf("Invalid input. Please try again: ");
		scanf(" %d", &selection);
	}
	return selection;
}
void main()
{
	srand((unsigned int)time(NULL));
	while (1)
	{
		system("cls");
		int selection = printMenu();
		switch (selection)
		{
		case 1:
			member();
			break;
		case 2:
			//staff();
			break;
		case 3:
			//stock();
			break;
		case 4:
			printf("See you next time\n");
			system("pause");
			exit(0);
			break;
		}
	}
}