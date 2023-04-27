#include "necessaryIncludes.h"
// Tan Jun Xian
void displayMember()
{
	system("cls");
	FILE* f = fopen("member.txt", "r");
	if (f == NULL)
	{
		printf("Error: Cannot open file\n");
		system("pause");
		return;
	}
	Member member;
	dprintf(107);
	int count = 0;
	printf
	(
		"|%-15s|%-30s|%-8s|%-15s|%-17s|%-15s|\n",
		"Member ID",
		"Member name",
		"Gender",
		"Phone number",
		"Status",
		"Balance"
	);
	dprintf(107);
	while
		(
			fscanf
			(
				f,
				"%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
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
			"|%-15s|%-30s|%-8c|%-15s|%-17s|RM %-12.2f|\n",
			member.member_id,
			member.name,
			member.gender,
			member.phone_number,
			member.status,
			member.balance
		);
	}
	fclose(f);
	dprintf(107);
	printf("Total members: %d\n", count);
	system("pause");
}

void searchMember()
{
	while (1)
	{
		int found = -1;
		Member member;
		displayMember();
		FILE* f = fopen("member.txt", "r");
		if (f == NULL)
		{
			printf("Error: Cannot open file\n");
			system("pause");
			return;
		}
		char member_id[11];
		IDGet(member_id, "member", "display");
		if (checkSentinent(member_id))
		{
			fclose(f);
			return;
		}
		while
			(
				fscanf
				(
					f,
					"%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
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
			if (strcmp(member.member_id, member_id) == 0)
			{
				found = 1;
				break;
			}
		}
		fclose(f);
		if (found == -1)
		{
			printf("Member with ID %s not found!\n", member_id);
			system("pause");
			continue;
		}
		dprintf(50);
		printf
		(
			"Member found! Here are the details:\n"
			"Member ID: %s\n"
			"Member name: %s\n"
			"Member gender: %c\n"
			"Member password: %s\n"
			"Member email: %s\n"
			"Member phone number: %s\n"
			"Member address: %s\n"
			"Member status: %s\n"
			"Member balance: RM %.2f\n"
			"Member birth date: %d-%d-%d\n",
			member.member_id,
			member.name,
			member.gender,
			member.password,
			member.email,
			member.phone_number,
			member.address,
			member.status,
			member.balance,
			member.birth.day,
			member.birth.month,
			member.birth.year
		);
		dprintf(50);
		system("pause");
	}
}

void editMember()
{
	while (1)
	{
		FILE* fp, * new_fp;
		Member member;
		char line[256];
		memset(line, 0, sizeof(line));
		int found = 0;
		displayMember();
		fp = fopen("member.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}

		new_fp = fopen("new_member.txt", "w");
		if (new_fp == NULL) {
			printf("Error creating new_member.txt file\n");
			system("pause");
			return;
		}

		char member_id[11];
		IDGet(member_id, "member", "edit");

		if (checkSentinent(member_id)) {
			fclose(fp);
			fclose(new_fp);
			remove("new_member.txt");
			return;
		}

		while (fgets(line, sizeof(line), fp)) {
			sscanf
			(
				line,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
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
			);

			if (strcmp(member.member_id, member_id) == 0) {
				found = 1;
				printf
				(
					"Member found! Here are the details:\n"
					"   Member ID: %s\n"
					"1. Member name: %s\n"
					"2. Member gender: %c\n"
					"3. Member password: %s\n"
					"4. Member email: %s\n"
					"5. Member phone number: %s\n"
					"6. Member address: %s\n"
					"7. Member status: %s\n"
					"8. Member balance: RM %.2f\n"
					"9. Member birth date: %d-%d-%d\n",
					member.member_id,
					member.name,
					member.gender,
					member.password,
					member.email,
					member.phone_number,
					member.address,
					member.status,
					member.balance,
					member.birth.day,
					member.birth.month,
					member.birth.year
				);
				while (1)
				{
					printf("Which to edit? (1-9, -1 to cancel): ");
					char choice[3];
					scanf(" %s", choice);
					if (checkSentinent(choice)) {
						fclose(fp);
						fclose(new_fp);
						remove("new_member.txt");
						return;
					}
					int choice_int = atoi(choice);
					while (choice_int < 1 || choice_int > 9) {
						printf("Invalid choice! Please enter again: ");
						scanf(" %s", choice);
						if (checkSentinent(choice)) {
							fclose(fp);
							fclose(new_fp);
							remove("new_member.txt");
							return;
						}
						choice_int = atoi(choice);
					}
					switch (choice_int) {
					case 1:
						do
						{
							memset(member.name, 0, sizeof(member.name));
							printf("Enter new member name (-1 to cancel): ");
							scanf(" %[^\n]", member.name);
							if (checkSentinent(member.name))
							{
								fclose(fp);
								return;
							}
							if (!validationName(member.name))
							{
								printf("Incorrect name format! Please try again.\n");
							}
						} while (!validationName(member.name));
						break;
					case 2:
						do
						{
							printf("Enter new gender (f/m): ");
							char gender;
							scanf(" %c", &gender);
							member.gender = toupper(gender);
							if (member.gender != 'F' && member.gender != 'M')
							{
								printf("Invalid gender type! Please try again.\n");
							}
						} while (member.gender != 'F' && member.gender != 'M');
						break;
					case 3:
						do
						{
							memset(member.password, 0, sizeof(member.password));
							printf("Enter new password (-1 to cancel): ");
							scanf(" %s", member.password);
							if (checkSentinent(member.password))
							{
								fclose(fp);
								return;
							}
							if (!validationPassword(member.password))
							{
								printf("Password must consist of between 8 to 16 characters, alphanumeric, lower/uppercase, and a special character. Please try again.\n");
							}
						} while (!validationPassword(member.password));
						break;
					case 4:
						do
						{
							memset(member.email, 0, sizeof(member.email));
							printf("Enter member email (-1 to cancel): ");
							scanf(" %s", member.email);
							if (checkSentinent(member.email))
							{
								fclose(fp);
								return;
							}
							if (!validationEmail(member.email))
							{
								printf("Incorrect email format! Example of email format: john@mail.com. Please try again.\n");
							}
						} while (!validationEmail(member.email));
						break;
					case 5:
						do
						{
							memset(member.phone_number, 0, sizeof(member.phone_number));
							printf("Enter new phone number (No need to put '-', -1 to cancel): ");
							scanf(" %[^\n]", member.phone_number);
							if (checkSentinent(member.phone_number))
							{
								fclose(fp);
								return;
							}
							if (!validationPhone(member.phone_number))
							{
								printf("Incorrect phone number format! Please try again.\n");
							}
						} while (!validationPhone(member.phone_number));
						break;
					case 6:
						do
						{
							memset(member.address, 0, sizeof(member.address));
							printf("Enter new address (-1 to cancel): ");
							scanf(" %[^\n]", member.address);
							if (checkSentinent(member.address))
							{
								fclose(fp);
								return;
							}
							if (!validationAddress(member.address))
							{
								printf("Incorrect address format! Please try again.\n");
							}
						} while (!validationAddress(member.address));
						break;
					case 7:
						printf("Enter new status: ");
						scanf(" %s", member.status);
						break;
					case 8:
						printf("Enter new balance: ");
						scanf(" %f", &member.balance);
						break;
					case 9:
						do
						{
							memset(&member.birth, 0, sizeof(member.birth));
							printf("Enter member birth date (format: dd-mm-yyyy): ");
							scanf(" %d-%d-%d", &member.birth.day, &member.birth.month, &member.birth.year);
							if (!validationBirth(member.birth))
							{
								printf("Incorrect birth date format! Please try again (Note: Must at least 18 years old to register).\n");
							}
						} while (!validationBirth(member.birth));
						break;
					}
					system("cls");
					dprintf(50);
					printf
					(
						"Updated member info:\n"
						"   Member ID: %s\n"
						"1. Member name: %s\n"
						"2. Member gender: %c\n"
						"3. Member password: %s\n"
						"4. Member email: %s\n"
						"5. Member phone number: %s\n"
						"6. Member address: %s\n"
						"7. Member status: %s\n"
						"8. Member balance: RM %.2f\n"
						"9. Member birth date: %d-%d-%d\n",
						member.member_id,
						member.name,
						member.gender,
						member.password,
						member.email,
						member.phone_number,
						member.address,
						member.status,
						member.balance,
						member.birth.day,
						member.birth.month,
						member.birth.year
					);
					dprintf(50);
					printf("Looks good? (y/n): ");
					char select;
					scanf(" %c", &select);
					select = tolower(select);
					while (select != 'y' && select != 'n') {
						printf("Invalid choice! Please enter again: ");
						scanf(" %c", &select);
					}
					if (select == 'y')
					{
						break;
					}
				}
				fprintf
				(
					new_fp,
					"%s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
					member.member_id,
					member.name,
					member.gender,
					member.password,
					member.email,
					member.phone_number,
					member.address,
					member.status,
					member.balance,
					member.birth.day,
					member.birth.month,
					member.birth.year
				);
			}
			else {
				fprintf(new_fp, "%s", line);
			}
		}

		fclose(fp);
		fclose(new_fp);

		if (!found) {
			printf("Member not found! Please try again\n");
			remove("new_member.txt");
		}
		else
		{
			remove("member.txt");
			rename("new_member.txt", "member.txt");

			printf("Member information updated successfully!\n");
		}
		system("pause");
	}
}

void deleteMember()
{
	while (1)
	{
		FILE* fp, * new_fp;
		Member member;
		char line[256];
		memset(line, 0, sizeof(line));
		int found = 0;
		displayMember();
		Sleep(100);
		fp = fopen("member.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}

		new_fp = fopen("new_member.txt", "w");
		if (new_fp == NULL) {
			printf("Error creating new_member.txt file\n");
			system("pause");
			return;
		}

		char member_id[11];
		IDGet(member_id, "member", "delete");

		if (checkSentinent(member_id)) {
			fclose(fp);
			fclose(new_fp);
			remove("new_member.txt");
			return;
		}

		while (fgets(line, sizeof(line), fp)) {
			sscanf
			(
				line,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
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
			);

			if (strcmp(member.member_id, member_id) == 0) {
				found = 1;
			}
			else {
				fprintf(new_fp, "%s", line);
			}
		}

		fclose(fp);
		fclose(new_fp);

		if (!found) {
			printf("Member not found! Please try again\n");
			remove("new_member.txt");
		}
		else
		{
			// Confirm with the user before deleting the member
			printf("Are you sure you want to delete this member? (y/n): ");
			char confirm;
			scanf(" %c", &confirm);
			if (confirm == 'y' || confirm == 'Y') {
				if (remove("member.txt") != 0) {
					printf("Error deleting file\n");
					system("pause");
					return;
				}
				if (rename("new_member.txt", "member.txt") != 0) {
					printf("Error renaming file\n");
					remove("new_member.txt");
					system("pause");
					return;
				}
				printf("Member deleted successfully!\n");
			}
			else {
				remove("new_member.txt");
				printf("Deletion canceled\n");
			}
		}
		system("pause");
	}
}

void addMember()
{
	while (1)
	{
		system("cls");
		FILE* fp = fopen("member.txt", "a");
		if (fp == NULL)
		{
			printf("Error opening member.txt!\n");
			system("pause");
			return;
		}
		dprintf(25);
		printf("Member registration\n");
		dprintf(25);

		Member member;
		IDGen(member.member_id, "MEMBER");
		printf("Member ID: %s\n", member.member_id);
		do
		{
			memset(member.name, 0, sizeof(member.name));
			printf("Enter member name (-1 to cancel): ");
			scanf(" %[^\n]", member.name);
			if (checkSentinent(member.name))
			{
				fclose(fp);
				return;
			}
			if (!validationName(member.name))
			{
				printf("Incorrect name format! Please try again.\n");
			}
		} while (!validationName(member.name));
		do
		{
			printf("Enter member gender (f/m): ");
			char gender;
			scanf(" %c", &gender);
			member.gender = toupper(gender);
			if (member.gender != 'F' && member.gender != 'M')
			{
				printf("Invalid gender type! Please try again.\n");
			}
		} while (member.gender != 'F' && member.gender != 'M');
		do
		{
			memset(member.password, 0, sizeof(member.password));
			printf("Enter member password (-1 to cancel): ");
			scanf(" %s", member.password);
			if (checkSentinent(member.password))
			{
				fclose(fp);
				return;
			}
			if (!validationPassword(member.password))
			{
				printf("Password must consist of between 8 to 16 characters, alphanumeric, lower/uppercase, and a special character. Please try again.\n");
			}
		} while (!validationPassword(member.password));
		do
		{
			memset(member.email, 0, sizeof(member.email));
			printf("Enter member email (-1 to cancel): ");
			scanf(" %s", member.email);
			if (checkSentinent(member.email))
			{
				fclose(fp);
				return;
			}
			if (!validationEmail(member.email))
			{
				printf("Incorrect email format! Example of email format: john@mail.com. Please try again.\n");
			}
		} while (!validationEmail(member.email));
		do
		{
			memset(member.address, 0, sizeof(member.address));
			printf("Enter member address (-1 to cancel): ");
			scanf(" %[^\n]", member.address);
			if (checkSentinent(member.address))
			{
				fclose(fp);
				return;
			}
			if (!validationAddress(member.address))
			{
				printf("Incorrect address format! Please try again.\n");
			}
		} while (!validationAddress(member.address));
		do
		{
			memset(member.phone_number, 0, sizeof(member.phone_number));
			printf("Enter member phone number (No need to put '-', -1 to cancel): ");
			scanf(" %[^\n]", member.phone_number);
			if (checkSentinent(member.phone_number))
			{
				fclose(fp);
				return;
			}
			if (!validationPhone(member.phone_number))
			{
				printf("Incorrect phone number format! Please try again.\n");
			}
		} while (!validationPhone(member.phone_number));
		printf("Enter member balance: ");
		scanf(" %f", &member.balance);
		printf("Enter member status: ");
		scanf(" %[^\n]", member.status);
		do
		{
			memset(&member.birth, 0, sizeof(member.birth));
			printf("Enter member birth date (format: dd-mm-yyyy): ");
			scanf(" %d-%d-%d", &member.birth.day, &member.birth.month, &member.birth.year);
			if (!validationBirth(member.birth))
			{
				printf("Incorrect birth date format! Please try again (Note: Must at least 18 years old to register).\n");
			}
		} while (!validationBirth(member.birth));
		while (1)
		{
			system("cls");
			dprintf(100);
			printf
			(
				"Current member info:\n"
				"   Member ID: %s\n"
				"1. Member name: %s\n"
				"2. Member gender: %c\n"
				"3. Member password: %s\n"
				"4. Member email: %s\n"
				"5. Member phone number: %s\n"
				"6. Member address: %s\n"
				"7. Member status: %s\n"
				"8. Member balance: RM %.2f\n"
				"9. Member birth date: %d-%d-%d\n",
				member.member_id,
				member.name,
				member.gender,
				member.password,
				member.email,
				member.phone_number,
				member.address,
				member.status,
				member.balance,
				member.birth.day,
				member.birth.month,
				member.birth.year
			);
			dprintf(100);
			printf("Confirm register? (y/n): ");
			char select;
			scanf(" %c", &select);
			select = tolower(select);
			while (select != 'y' && select != 'n') {
				printf("Invalid choice! Please enter again: ");
				scanf(" %c", &select);
			}
			if (select == 'y')
			{
				break;
			}
			printf("Which to edit? (1-9, -1 to cancel): ");
			char choice[3];
			scanf(" %s", choice);
			if (checkSentinent(choice)) {
				fclose(fp);
				return;
			}
			int choice_int = atoi(choice);
			while (choice_int < 1 || choice_int > 9) {
				printf("Invalid choice! Please enter again: ");
				scanf(" %s", choice);
				if (checkSentinent(choice)) {
					fclose(fp);
					return;
				}
				choice_int = atoi(choice);
			}
			switch (choice_int) {
			case 1:
				do
				{
					memset(member.name, 0, sizeof(member.name));
					printf("Enter new member name (-1 to cancel): ");
					scanf(" %[^\n]", member.name);
					if (checkSentinent(member.name))
					{
						fclose(fp);
						return;
					}
					if (!validationName(member.name))
					{
						printf("Incorrect name format! Please try again.\n");
					}
				} while (!validationName(member.name));
				break;
			case 2:
				do
				{
					printf("Enter new gender (f/m): ");
					char gender;
					scanf(" %c", &gender);
					member.gender = toupper(gender);
					if (member.gender != 'F' && member.gender != 'M')
					{
						printf("Invalid gender type! Please try again.\n");
					}
				} while (member.gender != 'F' && member.gender != 'M');
				break;
			case 3:
				do
				{
					memset(member.password, 0, sizeof(member.password));
					printf("Enter new password (-1 to cancel): ");
					scanf(" %s", member.password);
					if (checkSentinent(member.password))
					{
						fclose(fp);
						return;
					}
					if (!validationPassword(member.password))
					{
						printf("Password must consist of between 8 to 16 characters, alphanumeric, lower/uppercase, and a special character. Please try again.\n");
					}
				} while (!validationPassword(member.password));
				break;
			case 4:
				do
				{
					memset(member.email, 0, sizeof(member.email));
					printf("Enter member email (-1 to cancel): ");
					scanf(" %s", member.email);
					if (checkSentinent(member.email))
					{
						fclose(fp);
						return;
					}
					if (!validationEmail(member.email))
					{
						printf("Incorrect email format! Example of email format: john@mail.com. Please try again.\n");
					}
				} while (!validationEmail(member.email));
				break;
			case 5:
				do
				{
					memset(member.phone_number, 0, sizeof(member.phone_number));
					printf("Enter new phone number (No need to put '-', -1 to cancel): ");
					scanf(" %[^\n]", member.phone_number);
					if (checkSentinent(member.phone_number))
					{
						fclose(fp);
						return;
					}
					if (!validationPhone(member.phone_number))
					{
						printf("Incorrect phone number format! Please try again.\n");
					}
				} while (!validationPhone(member.phone_number));
				break;
			case 6:
				do
				{
					memset(member.address, 0, sizeof(member.address));
					printf("Enter new address (-1 to cancel): ");
					scanf(" %[^\n]", member.address);
					if (checkSentinent(member.address))
					{
						fclose(fp);
						return;
					}
					if (!validationAddress(member.address))
					{
						printf("Incorrect address format! Please try again.\n");
					}
				} while (!validationAddress(member.address));
				break;
			case 7:
				printf("Enter new status: ");
				scanf(" %s", member.status);
				break;
			case 8:
				printf("Enter new balance: ");
				scanf(" %f", &member.balance);
				break;
			case 9:
				do
				{
					memset(&member.birth, 0, sizeof(member.birth));
					printf("Enter member birth date (format: dd-mm-yyyy): ");
					scanf(" %d-%d-%d", &member.birth.day, &member.birth.month, &member.birth.year);
					if (!validationBirth(member.birth))
					{
						printf("Incorrect birth date format! Please try again (Note: Must at least 18 years old to register).\n");
					}
				} while (!validationBirth(member.birth));
				break;
			}
		}
		fprintf
		(
			fp,
			"%s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
			member.member_id,
			member.name,
			member.gender,
			member.password,
			member.email,
			member.phone_number,
			member.address,
			member.status,
			member.balance,
			member.birth.day,
			member.birth.month,
			member.birth.year
		);
		fclose(fp);
		printf("Member registered successfully!\n");
		system("pause");
	}
}

void displayMemberStatus()
{
	system("cls");
	FILE* f = fopen("member.txt", "r");
	if (f == NULL)
	{
		printf("Error: Cannot open file\n");
		system("pause");
		return;
	}
	Member member;
	dprintf(66);
	printf
	(
		"|%-15s|%-30s|%-17s|\n",
		"Member ID",
		"Member name",
		"Status"
	);
	dprintf(66);
	while
		(
			fscanf
			(
				f,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
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
		printf
		(
			"|%-15s|%-30s|%-17s|\n",
			member.member_id,
			member.name,
			member.status
		);
	}
	fclose(f);
	dprintf(66);
}

void updateMemberStatus()
{
	while (1)
	{
		FILE* fp, * new_fp;
		Member member;
		char line[256];
		int found = 0;
		displayMemberStatus();
		fp = fopen("member.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}
		char member_id[11];
		IDGet(member_id, "member", "update");
		if (checkSentinent(member_id)) {
			fclose(fp);
			return;
		}
		new_fp = fopen("new_member.txt", "w");
		if (new_fp == NULL) {
			printf("Error creating new_member.txt file\n");
			fclose(fp);
			system("pause");
			return;
		}
		while (fgets(line, sizeof(line), fp)) {
			sscanf
			(
				line,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
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
			);

			if (strcmp(member.member_id, member_id) == 0) {
				found = 1;
				system("cls");
				printf
				(
					"Member ID: %s\n"
					"Member name: %s\n"
					"Member status: %s\n"
					"\nEnter new status (-1 to cancel): ",
					member.member_id,
					member.name,
					member.status
				);

				scanf(" %s", member.status);

				if (checkSentinent(member.status))
				{
					fclose(fp);
					fclose(new_fp);
					remove("new_member.txt");
					return;
				}
			}
			fprintf(new_fp, "%s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
				member.member_id,
				member.name,
				member.gender,
				member.password,
				member.email,
				member.phone_number,
				member.address,
				member.status,
				member.balance,
				member.birth.day,
				member.birth.month,
				member.birth.year);
			if (found)break;
		}
		fclose(fp);
		fclose(new_fp);
		remove("member.txt");
		rename("new_member.txt", "member.txt");
		if (!found) {
			printf("Member not found! Please try again\n");
		}
		else {
			printf("Member status updated successfully!\n");
		}
		system("pause");
	}
}


int printMemberMenu()
{
	printf
	(
		"------------------------------\n"
		"|  Member Information Module |\n"
		"|----------------------------|\n"
		"|1. Display member list      |\n"
		"|2. Search members           |\n"
		"|3. Edit members             |\n"
		"|4. Delete members           |\n"
		"|5. Add members	             |\n"
		"|6. Update member status     |\n"
		"|7. Back                     |\n"
		"------------------------------\n"
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

void member()
{
	FILE* cr8file = fopen("member.txt", "a"); // create file if not exist
	fclose(cr8file);
	while (1)
	{
		system("cls");
		int selection = printMemberMenu(); // 1-7
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