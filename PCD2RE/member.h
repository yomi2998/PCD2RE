#include "necessaryIncludes.h"
#pragma warning (disable:4033)

int printMenu()
{
	printf
	(
		"-----------------------------|\n"
		"|  Member Information Module |\n"
		"|----------------------------|\n"
		"|1. Display member list      |\n"
		"|2. Search members           |\n"
		"|3. Edit members             |\n"
		"|4. Delete members           |\n"
		"|5. Add members	          |\n"
		"|6. Update member status     |\n"
		"|7. Back                     |\n"
		" ----------------------------\n"
		"Enter your choice: "
	);
	int selection;
	scanf(" %d", &selection);
	while (selection < 1 || selection > 7)
	{
		printf("Invalid input. Please try again: ");
		scanf(" %d", &selection);
	}
	return selection;
}

void displayMember()
{
	FILE* f = fopen("member.txt", "r");
	if (f == NULL)
	{
		printf("Error: Cannot open file\n");
		system("pause");
		return;
	}
	printf("");
	Member member;
	char hundred_line[101];
	memset(hundred_line, '-' ,100);
	hundred_line[100] = '\0';
	int count = 0;
	printf
	(
		"%s\n%-15s%-30s%-8s%-17s%-30s%-15s%-17s%-10s%-15s%-100s\n%s\n", 
		hundred_line, 
		"Member ID",
		"Member name",
		"Gender", 
		"Password", 
		"Email",
		"Phone number",
		"Status",
		"Balance", 
		"Birth Date", 
		"Address",
		hundred_line
	);
	while
		(
			fscanf
			(
				f,
				"%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%d-%d-%d\n",
				member.member_id,
				member.name,
				&member.gender,
				member.password,
				member.email,
				member.phone_number,
				member.address,
				member.status,
				&member.balance,
				&member.birth.day,
				&member.birth.month,
				&member.birth.year
			) != EOF
		)
	{
		++count;
		printf
		(
			"%-15s%-30s%-8s%-17s%-30s%-15s%-17s%-10s%-15s%-100s\n",
			member.member_id,
			member.name,
			member.gender,
			member.password,
			member.email,
			member.phone_number,
			member.status,
			member.balance,
			member.birth.day,
			member.birth.month,
			member.birth.year,
			member.address
		);
	}
	fclose(f);
	printf("%s\n", hundred_line);
	printf("Total: %d members\n", count);
	system("pause");
}

void member()
{
	while (1)
	{
		system("cls");
		int selection = printMenu(); // 1-7
		switch (selection)
		{
		case 1:
			displayMember();
			break;
		case 2:
			searchMember();
			break;
		case 3:
			editMember();
			break;
		case 4:
			deleteMember();
			break;
		case 5:
			addMember();
			break;
		case 6:
			updateMemberStatus();
			break;
		case 7:
			return;
			break;
		}
	}
}