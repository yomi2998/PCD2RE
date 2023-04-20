#include "necessaryIncludes.h"
#pragma warning (disable:4033)

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
	dprintf(100);
	int count = 0;
	printf
	(
		" %-15s%-30s%-8s%-17s%-30s%-15s%-17s%-10s%-15s%-100s\n",
		"Member ID",
		"Member name",
		"Gender",
		"Password",
		"Email",
		"Phone number",
		"Status",
		"Balance",
		"Birth Date",
		"Address"
	);
	dprintf(100);
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
		++count;
		printf
		(
			" %-15s%-30s%-8c%-17s%-30s%-15s%-17sRM %-7.2f%02d-%02d%-9d%-100s\n",
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
	dprintf(100);
	printf("Total members: %d\n", count);
	system("pause");
}

void searchMember()
{
	while (1)
	{
		int found = -1;
		Member member;
		char member_id[11];
		system("cls");
		FILE* f = fopen("member.txt", "r");
		if (f == NULL)
		{
			printf("Error: Cannot open file\n");
			system("pause");
			return;
		}
		printf("Enter member ID to search (-1 to stop): ");
		scanf(" %[^\n]", member_id);
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
			"Member balance: %lf\n"
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
		system("cls");
		FILE* fp, * temp;
		Member member;
		char line[256];
		memset(line, 0, sizeof(line));
		char id_to_edit[11];
		int found = 0;
		displayMember();
		fp = fopen("member.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}

		temp = fopen("temp.txt", "w");
		if (temp == NULL) {
			printf("Error creating temporary file\n");
			system("pause");
			return;
		}

		printf("Enter the ID of the member to edit (-1 to cancel): ");
		scanf(" %s", id_to_edit);

		if (checkSentinent(id_to_edit)) {
			fclose(fp);
			fclose(temp);
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

			if (strcmp(member.member_id, id_to_edit) == 0) {
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
					"8. Member balance: %lf\n"
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
						fclose(temp);
						return;
					}
					int choice_int = atoi(choice);
					while (choice_int < 1 || choice_int > 9) {
						printf("Invalid choice! Please enter again: ");
						scanf(" %s", choice);
						if (checkSentinent(choice)) {
							fclose(fp);
							fclose(temp);
							return;
						}
						choice_int = atoi(choice);
					}
					switch (choice_int) {
					case 1:
						printf("Enter new name: ");
						scanf(" %[^\n]", member.name);
						break;
					case 2:
						printf("Enter new gender:");
						scanf(" %c", &member.gender);
						break;
					case 3:
						printf("Enter new password: ");
						scanf(" %s", member.password);
						break;
					case 4:
						printf("Enter new email: ");
						scanf(" %s", member.email);
						break;
					case 5:
						printf("Enter new phone number: ");
						scanf(" %s", member.phone_number);
						break;
					case 6:
						printf("Enter new address: ");
						scanf(" %s", member.address);
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
						printf("Enter new birth date: ");
						scanf(" %d-%d-%d", &member.birth.day, &member.birth.month, &member.birth.year);
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
						"8. Member balance: %lf\n"
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
					temp,
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
				fprintf(temp, "%s", line);
			}
		}

		fclose(fp);
		fclose(temp);

		if (!found) {
			printf("Member not found! Please try again\n");
			remove("temp.txt");
		}
		else
		{
			remove("member.txt");
			rename("temp.txt", "member.txt");

			printf("Member information updated successfully!\n");
		}
		system("pause");
	}
}

void deleteMember()
{
	while (1)
	{
		system("cls");
		FILE* fp, * temp;
		Member member;
		char line[256];
		memset(line, 0, sizeof(line));
		char id_to_delete[11];
		int found = 0;
		displayMember();
		Sleep(100);
		fp = fopen("member.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}

		temp = fopen("temp.txt", "w");
		if (temp == NULL) {
			printf("Error creating temporary file\n");
			system("pause");
			return;
		}

		printf("Enter the ID of the member to delete (-1 to cancel): ");
		scanf(" %s", id_to_delete);

		if (checkSentinent(id_to_delete)) {
			fclose(fp);
			fclose(temp);
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

			if (strcmp(member.member_id, id_to_delete) == 0) {
				found = 1;
			}
			else {
				fprintf(temp, "%s", line);
			}
		}

		fclose(fp);
		fclose(temp);

		if (!found) {
			printf("Member not found! Please try again\n");
			remove("temp.txt");
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
				if (rename("temp.txt", "member.txt") != 0) {
					printf("Error renaming file\n");
					remove("temp.txt");
					system("pause");
					return;
				}
				printf("Member deleted successfully!\n");
			}
			else {
				remove("temp.txt");
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
		printf("Enter member name (-1 to stop): ");
		scanf(" %[^\n]", member.name);
		if (checkSentinent(member.name))
		{
			fclose(fp);
			return;
		}
		printf("Enter member gender (f/m): ");
		char gender;
		scanf(" %c", &gender);
		member.gender = toupper(gender);
		printf("Enter member password: ");
		scanf(" %s", member.password);
		printf("Enter member email: ");
		scanf(" %s", member.email);
		printf("Enter member address: ");
		scanf(" %[^\n]", member.address);
		printf("Enter member phone number: ");
		scanf(" %s", member.phone_number);
		printf("Enter member balance: ");
		scanf(" %f", &member.balance);
		printf("Enter member status: ");
		scanf(" %[^\n]", member.status);
		printf("Enter member birth date (format: dd-mm-yyyy): ");
		scanf(" %d-%d-%d", &member.birth.day, &member.birth.month, &member.birth.year);
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
				printf("Enter new name: ");
				scanf(" %[^\n]", member.name);
				break;
			case 2:
				printf("Enter new gender:");
				scanf(" %c", &member.gender);
				break;
			case 3:
				printf("Enter new password: ");
				scanf(" %s", member.password);
				break;
			case 4:
				printf("Enter new email: ");
				scanf(" %s", member.email);
				break;
			case 5:
				printf("Enter new phone number: ");
				scanf(" %s", member.phone_number);
				break;
			case 6:
				printf("Enter new address: ");
				scanf(" %s", member.address);
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
				printf("Enter new birth date (format: dd/mm/yyyy): ");
				scanf(" %d-%d-%d", &member.birth.day, &member.birth.month, &member.birth.year);
				break;
			}
		}
		fprintf
		(
			fp,
			" %s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
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
	FILE* f = fopen("member.txt", "r");
	if (f == NULL)
	{
		printf("Error: Cannot open file\n");
		system("pause");
		return;
	}
	printf("");
	Member member;
	dprintf(70);
	printf
	(
		" %-15s%-30s%-17s\n",
		"Member ID",
		"Member name",
		"Status"
	);
	dprintf(70);
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
			" %-15s%-30s%-17s\n",
			member.member_id,
			member.name,
			member.status
		);
	}
	fclose(f);
	dprintf(70);
}

void updateMemberStatus()
{
	while (1)
	{
		system("cls");
		FILE* fp, * temp;
		Member member;
		char line[256];
		char id_to_edit[11];
		int found = 0;
		displayMemberStatus();
		fp = fopen("member.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}
		printf("Enter the ID of the member to edit (-1 to cancel): ");
		scanf(" %s", id_to_edit);
		if (checkSentinent(id_to_edit)) {
			fclose(fp);
			return;
		}
		temp = fopen("temp.txt", "w");
		if (temp == NULL) {
			printf("Error creating temporary file\n");
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

			if (strcmp(member.member_id, id_to_edit) == 0) {
				found = 1;
				system("cls");
				printf
				(
					"Member ID: %s\n"
					"Member name: %s\n"
					"Member status: %s\n"
					"\nEnter new status: ",
					member.member_id,
					member.name,
					member.status
				);

				scanf(" %s", member.status);
			}
			fprintf(temp, "%s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
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
		fclose(temp);
		remove("member.txt");
		rename("temp.txt", "member.txt");
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