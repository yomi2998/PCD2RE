#include "necessaryIncludes.h"
// Eugene Lim Wei Han
void displayStaff()
{
	system("cls");
	FILE* f = fopen("staff.txt", "r");
	if (f == NULL)
	{
		printf("Error: Cannot open file\n");
		system("pause");
		return;
	}
	Staff staff;
	dprintf(102);
	int count = 0;
	printf
	(
		"|%-15s|%-30s|%-8s|%-15s|%-17s|%-10s|\n",
		"Staff ID",
		"Staff name",
		"Gender",
		"Phone number",
		"Position",
		"Salary"
	);
	dprintf(102);
	while
		(
			fscanf
			(
				f,
				"%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
				staff.staff_id,
				staff.name,
				&staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				&staff.salary,
				&staff.birth.day,
				&staff.birth.month,
				&staff.birth.year
			) != EOF
			)
	{
		++count;
		printf
		(
			"|%-15s|%-30s|%-8c|%-15s|%-17s|RM %-7.2f|\n",
			staff.staff_id,
			staff.name,
			staff.gender,
			staff.phone_number,
			staff.position,
			staff.salary
		);
	}
	fclose(f);
	dprintf(102);
	printf("Total staffs : %d\n", count);
	system("pause");
}

void searchStaff()
{
	while (1)
	{
		int found = -1;
		Staff staff;
		displayStaff();
		FILE* f = fopen("staff.txt", "r");
		if (f == NULL)
		{
			printf("Error: Cannot open file\n");
			system("pause");
			return;
		}
		char staff_id[11];
		IDGet(staff_id, "staff", "display");
		if (checkSentinent(staff_id))
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
					staff.staff_id,
					staff.name,
					&staff.gender,
					staff.password,
					staff.email,
					staff.phone_number,
					staff.address,
					staff.position,
					&staff.salary,
					&staff.birth.day,
					&staff.birth.month,
					&staff.birth.year
				) != EOF
				)
		{
			if (strcmp(staff.staff_id, staff_id) == 0)
			{
				found = 1;
				break;
			}
		}
		fclose(f);
		if (found == -1)
		{
			printf("Staff with ID %s not found!\n", staff_id);
			system("pause");
			continue;
		}
		dprintf(50);
		printf
		(
			"Staff found! Here are the details:\n"
			"Staff ID: %s\n"
			"Staff name: %s\n"
			"Staff gender: %c\n"
			"Staff password: %s\n"
			"Staff email: %s\n"
			"Staff phone number: %s\n"
			"Staff address: %s\n"
			"Staff position: %s\n"
			"Staff salary: RM %.2f\n"
			"Staff birth date: %d-%d-%d\n",
			staff.staff_id,
			staff.name,
			staff.gender,
			staff.password,
			staff.email,
			staff.phone_number,
			staff.address,
			staff.position,
			staff.salary,
			staff.birth.day,
			staff.birth.month,
			staff.birth.year
		);
		dprintf(50);
		system("pause");
	}
}

void editStaff()
{
	while (1)
	{
		FILE* fp, * temp;
		Staff staff;
		char line[256];
		memset(line, 0, sizeof(line));
		int found = 0;
		displayStaff();
		fp = fopen("staff.txt", "r");
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
		char staff_id[11];
		IDGet(staff_id, "staff", "edit");
		if (checkSentinent(staff_id)) {
			fclose(fp);
			fclose(temp);
			remove("temp.txt");
			return;
		}

		while (fgets(line, sizeof(line), fp)) {
			sscanf
			(
				line,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
				staff.staff_id,
				staff.name,
				&staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				&staff.salary,
				&staff.birth.day,
				&staff.birth.month,
				&staff.birth.year
			);

			if (strcmp(staff.staff_id, staff_id) == 0) {
				found = 1;
				printf
				(
					"Staff found! Here are the details:\n"
					"   Staff ID: %s\n"
					"1. Staff name: %s\n"
					"2. Staff gender: %c\n"
					"3. Staff password: %s\n"
					"4. Staff email: %s\n"
					"5. Staff phone number: %s\n"
					"6. Staff address: %s\n"
					"7. Staff position: %s\n"
					"8. Staff salary : RM %.2f\n"
					"9. Staff birth date: %d-%d-%d\n",
					staff.staff_id,
					staff.name,
					staff.gender,
					staff.password,
					staff.email,
					staff.phone_number,
					staff.address,
					staff.position,
					staff.salary,
					staff.birth.day,
					staff.birth.month,
					staff.birth.year
				);
				while (1)
				{
					printf("Which to edit? (1-9, -1 to cancel): ");
					char choice[3];
					scanf(" %s", choice);
					if (checkSentinent(choice)) {
						fclose(fp);
						fclose(temp);
						remove("temp.txt");
						return;
					}
					int choice_int = atoi(choice);
					while (choice_int < 1 || choice_int > 9) {
						printf("Invalid choice! Please enter again: ");
						scanf(" %s", choice);
						if (checkSentinent(choice)) {
							fclose(fp);
							fclose(temp);
							remove("temp.txt");
							return;
						}
						choice_int = atoi(choice);
					}
					switch (choice_int) {
					case 1:
						do
						{
							memset(staff.name, 0, sizeof(staff.name));
							printf("Enter new staff name (-1 to cancel): ");
							scanf(" %[^\n]", staff.name);
							if (checkSentinent(staff.name))
							{
								fclose(fp);
								return;
							}
							if (!validationName(staff.name))
							{
								printf("Incorrect name format! Please try again.\n");
							}
						} while (!validationName(staff.name));
						break;
					case 2:
						do
						{
							printf("Enter new gender (f/m): ");
							char gender;
							scanf(" %c", &gender);
							staff.gender = toupper(gender);
							if (staff.gender != 'F' && staff.gender != 'M')
							{
								printf("Invalid gender type! Please try again.\n");
							}
						} while (staff.gender != 'F' && staff.gender != 'M');
						break;
					case 3:
						do
						{
							memset(staff.password, 0, sizeof(staff.password));
							printf("Enter new password (-1 to cancel): ");
							scanf(" %s", staff.password);
							if (checkSentinent(staff.password))
							{
								fclose(fp);
								return;
							}
							if (!validationPassword(staff.password))
							{
								printf("Password must consist of between 8 to 16 characters, alphanumeric, lower/uppercase, and a special character. Please try again.\n");
							}
						} while (!validationPassword(staff.password));
						break;
					case 4:
						do
						{
							memset(staff.email, 0, sizeof(staff.email));
							printf("Enter staff email (-1 to cancel): ");
							scanf(" %s", staff.email);
							if (checkSentinent(staff.email))
							{
								fclose(fp);
								return;
							}
							if (!validationEmail(staff.email))
							{
								printf("Incorrect email format! Example of email format: john@mail.com. Please try again.\n");
							}
						} while (!validationEmail(staff.email));
						break;
					case 5:
						do
						{
							memset(staff.phone_number, 0, sizeof(staff.phone_number));
							printf("Enter new phone number (No need to put '-', -1 to cancel): ");
							scanf(" %[^\n]", staff.phone_number);
							if (checkSentinent(staff.phone_number))
							{
								fclose(fp);
								return;
							}
							if (!validationPhone(staff.phone_number))
							{
								printf("Incorrect phone number format! Please try again.\n");
							}
						} while (!validationPhone(staff.phone_number));
						break;
					case 6:
						do
						{
							memset(staff.address, 0, sizeof(staff.address));
							printf("Enter new address (-1 to cancel): ");
							scanf(" %[^\n]", staff.address);
							if (checkSentinent(staff.address))
							{
								fclose(fp);
								return;
							}
							if (!validationAddress(staff.address))
							{
								printf("Incorrect address format! Please try again.\n");
							}
						} while (!validationAddress(staff.address));
						break;
					case 7:
						printf("Enter new position: ");
						scanf(" %s", staff.position);
						break;
					case 8:
						printf("Enter new salary: ");
						scanf(" %f", &staff.salary);
						break;
					case 9:
						do
						{
							memset(&staff.birth, 0, sizeof(staff.birth));
							printf("Enter staff birth date (format: dd-mm-yyyy): ");
							scanf(" %d-%d-%d", &staff.birth.day, &staff.birth.month, &staff.birth.year);
							if (!validationBirth(staff.birth))
							{
								printf("Incorrect birth date format! Please try again (Note: Must at least 18 years old to register).\n");
							}
						} while (!validationBirth(staff.birth));
						break;
					}
					system("cls");
					dprintf(50);
					printf
					(
						"Updated staff info:\n"
						"   Staff ID: %s\n"
						"1. Staff name: %s\n"
						"2. Staff gender: %c\n"
						"3. Staff password: %s\n"
						"4. Staff email: %s\n"
						"5. Staff phone number: %s\n"
						"6. Staff address: %s\n"
						"7. Staff position: %s\n"
						"8. Staff salary : RM %.2f\n"
						"9. Staff birth date: %d-%d-%d\n",
						staff.staff_id,
						staff.name,
						staff.gender,
						staff.password,
						staff.email,
						staff.phone_number,
						staff.address,
						staff.position,
						staff.salary,
						staff.birth.day,
						staff.birth.month,
						staff.birth.year
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
					staff.staff_id,
					staff.name,
					staff.gender,
					staff.password,
					staff.email,
					staff.phone_number,
					staff.address,
					staff.position,
					staff.salary,
					staff.birth.day,
					staff.birth.month,
					staff.birth.year
				);
			}
			else {
				fprintf(temp, "%s", line);
			}
		}

		fclose(fp);
		fclose(temp);

		if (!found) {
			printf("Staff not found! Please try again\n");
			remove("temp.txt");
		}
		else
		{
			remove("staff.txt");
			rename("temp.txt", "staff.txt");

			printf("Staff information updated successfully!\n");
		}
		system("pause");
	}
}

void deleteStaff()
{
	while (1)
	{
		FILE* fp, * temp;
		Staff staff;
		char line[256];
		memset(line, 0, sizeof(line));
		int found = 0;
		displayStaff();
		Sleep(100);
		fp = fopen("staff.txt", "r");
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
		char staff_id[11];
		IDGet(staff_id, "staff", "delete");
		if (checkSentinent(staff_id)) {
			fclose(fp);
			fclose(temp);
			remove("temp.txt");
			return;
		}

		while (fgets(line, sizeof(line), fp)) {
			sscanf
			(
				line,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
				staff.staff_id,
				staff.name,
				&staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				&staff.salary,
				&staff.birth.day,
				&staff.birth.month,
				&staff.birth.year
			);

			if (strcmp(staff.staff_id, staff_id) == 0) {
				found = 1;
			}
			else {
				fprintf(temp, "%s", line);
			}
		}

		fclose(fp);
		fclose(temp);

		if (!found) {
			printf("Staff not found! Please try again\n");
			remove("temp.txt");
		}
		else
		{
			printf("Are you sure you want to delete this staff? (y/n): ");
			char confirm;
			scanf(" %c", &confirm);
			if (confirm == 'y' || confirm == 'Y') {
				if (remove("staff.txt") != 0) {
					printf("Error deleting file\n");
					system("pause");
					return;
				}
				if (rename("temp.txt", "staff.txt") != 0) {
					printf("Error renaming file\n");
					remove("temp.txt");
					system("pause");
					return;
				}
				printf("Staff deleted successfully!\n");
			}
			else {
				remove("temp.txt");
				printf("Deletion canceled\n");
			}
		}
		system("pause");
	}
}

void addStaff()
{
	while (1)
	{
		system("cls");
		FILE* fp = fopen("staff.txt", "a");
		if (fp == NULL)
		{
			printf("Error opening staff.txt!\n");
			system("pause");
			return;
		}
		dprintf(25);
		printf("Staff registration\n");
		dprintf(25);

		Staff staff;
		IDGen(staff.staff_id, "STAFF");
		printf("Staff ID: %s", staff.staff_id);
		do
		{
			memset(staff.name, 0, sizeof(staff.name));
			printf("Enter staff name (-1 to cancel): ");
			scanf(" %[^\n]", staff.name);
			if (checkSentinent(staff.name))
			{
				fclose(fp);
				return;
			}
			if (!validationName(staff.name))
			{
				printf("Incorrect name format! Please try again.\n");
			}
		} while (!validationName(staff.name));
		do
		{
			printf("Enter staff gender (f/m): ");
			char gender;
			scanf(" %c", &gender);
			staff.gender = toupper(gender);
			if (staff.gender != 'F' && staff.gender != 'M')
			{
				printf("Invalid gender type! Please try again.\n");
			}
		} while (staff.gender != 'F' && staff.gender != 'M');
		do
		{
			memset(staff.password, 0, sizeof(staff.password));
			printf("Enter staff password (-1 to cancel): ");
			scanf(" %s", staff.password);
			if (checkSentinent(staff.password))
			{
				fclose(fp);
				return;
			}
			if (!validationPassword(staff.password))
			{
				printf("Password must consist of between 8 to 16 characters, alphanumeric, lower/uppercase, and a special character. Please try again.\n");
			}
		} while (!validationPassword(staff.password));
		do
		{
			memset(staff.email, 0, sizeof(staff.email));
			printf("Enter staff email (-1 to cancel): ");
			scanf(" %s", staff.email);
			if (checkSentinent(staff.email))
			{
				fclose(fp);
				return;
			}
			if (!validationEmail(staff.email))
			{
				printf("Incorrect email format! Example of email format: john@mail.com. Please try again.\n");
			}
		} while (!validationEmail(staff.email));
		do
		{
			memset(staff.address, 0, sizeof(staff.address));
			printf("Enter staff address (-1 to cancel): ");
			scanf(" %[^\n]", staff.address);
			if (checkSentinent(staff.address))
			{
				fclose(fp);
				return;
			}
			if (!validationAddress(staff.address))
			{
				printf("Incorrect address format! Please try again.\n");
			}
		} while (!validationAddress(staff.address));
		do
		{
			memset(staff.phone_number, 0, sizeof(staff.phone_number));
			printf("Enter staff phone number (No need to put '-', -1 to cancel): ");
			scanf(" %[^\n]", staff.phone_number);
			if (checkSentinent(staff.phone_number))
			{
				fclose(fp);
				return;
			}
			if (!validationPhone(staff.phone_number))
			{
				printf("Incorrect phone number format! Please try again.\n");
			}
		} while (!validationPhone(staff.phone_number));
		printf("Enter staff salary: ");
		scanf(" %f", &staff.salary);
		printf("Enter staff position: ");
		scanf(" %[^\n]", staff.position);
		do
		{
			memset(&staff.birth, 0, sizeof(staff.birth));
			printf("Enter staff birth date (format: dd-mm-yyyy): ");
			scanf(" %d-%d-%d", &staff.birth.day, &staff.birth.month, &staff.birth.year);
			if (!validationBirth(staff.birth))
			{
				printf("Incorrect birth date format! Please try again (Note: Must at least 18 years old to register).\n");
			}
		} while (!validationBirth(staff.birth));
		while (1)
		{
			system("cls");
			dprintf(100);
			printf
			(
				"Current staff info:\n"
				"   Staff ID: %s\n"
				"1. Staff name: %s\n"
				"2. Staff gender: %c\n"
				"3. Staff password: %s\n"
				"4. Staff email: %s\n"
				"5. Staff phone number: %s\n"
				"6. Staff address: %s\n"
				"7. Staff position: %s\n"
				"8. Staff salary: RM %.2f\n"
				"9. Staff birth date: %d-%d-%d\n",
				staff.staff_id,
				staff.name,
				staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				staff.salary,
				staff.birth.day,
				staff.birth.month,
				staff.birth.year
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
					memset(staff.name, 0, sizeof(staff.name));
					printf("Enter new staff name (-1 to cancel): ");
					scanf(" %[^\n]", staff.name);
					if (checkSentinent(staff.name))
					{
						fclose(fp);
						return;
					}
					if (!validationName(staff.name))
					{
						printf("Incorrect name format! Please try again.\n");
					}
				} while (!validationName(staff.name));
				break;
			case 2:
				do
				{
					printf("Enter new gender (f/m): ");
					char gender;
					scanf(" %c", &gender);
					staff.gender = toupper(gender);
					if (staff.gender != 'F' && staff.gender != 'M')
					{
						printf("Invalid gender type! Please try again.\n");
					}
				} while (staff.gender != 'F' && staff.gender != 'M');
				break;
			case 3:
				do
				{
					memset(staff.password, 0, sizeof(staff.password));
					printf("Enter new password (-1 to cancel): ");
					scanf(" %s", staff.password);
					if (checkSentinent(staff.password))
					{
						fclose(fp);
						return;
					}
					if (!validationPassword(staff.password))
					{
						printf("Password must consist of between 8 to 16 characters, alphanumeric, lower/uppercase, and a special character. Please try again.\n");
					}
				} while (!validationPassword(staff.password));
				break;
			case 4:
				do
				{
					memset(staff.email, 0, sizeof(staff.email));
					printf("Enter staff email (-1 to cancel): ");
					scanf(" %s", staff.email);
					if (checkSentinent(staff.email))
					{
						fclose(fp);
						return;
					}
					if (!validationEmail(staff.email))
					{
						printf("Incorrect email format! Example of email format: john@mail.com. Please try again.\n");
					}
				} while (!validationEmail(staff.email));
				break;
			case 5:
				do
				{
					memset(staff.phone_number, 0, sizeof(staff.phone_number));
					printf("Enter new phone number (No need to put '-', -1 to cancel): ");
					scanf(" %[^\n]", staff.phone_number);
					if (checkSentinent(staff.phone_number))
					{
						fclose(fp);
						return;
					}
					if (!validationPhone(staff.phone_number))
					{
						printf("Incorrect phone number format! Please try again.\n");
					}
				} while (!validationPhone(staff.phone_number));
				break;
			case 6:
				do
				{
					memset(staff.address, 0, sizeof(staff.address));
					printf("Enter new address (-1 to cancel): ");
					scanf(" %[^\n]", staff.address);
					if (checkSentinent(staff.address))
					{
						fclose(fp);
						return;
					}
					if (!validationAddress(staff.address))
					{
						printf("Incorrect address format! Please try again.\n");
					}
				} while (!validationAddress(staff.address));
				break;
			case 7:
				printf("Enter new position: ");
				scanf(" %s", staff.position);
				break;
			case 8:
				printf("Enter new salary: ");
				scanf(" %f", &staff.salary);
				break;
			case 9:
				do
				{
					memset(&staff.birth, 0, sizeof(staff.birth));
					printf("Enter staff birth date (format: dd-mm-yyyy): ");
					scanf(" %d-%d-%d", &staff.birth.day, &staff.birth.month, &staff.birth.year);
					if (!validationBirth(staff.birth))
					{
						printf("Incorrect birth date format! Please try again (Note: Must at least 18 years old to register).\n");
					}
				} while (!validationBirth(staff.birth));
				break;
			}
		}
		fprintf
		(
			fp,
			"%s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
			staff.staff_id,
			staff.name,
			staff.gender,
			staff.password,
			staff.email,
			staff.phone_number,
			staff.address,
			staff.position,
			staff.salary,
			staff.birth.day,
			staff.birth.month,
			staff.birth.year
		);
		fclose(fp);
		printf("Staff registered successfully!\n");
		system("pause");
	}
}

void displayStaffPosition()
{
	system("cls");
	FILE* f = fopen("staff.txt", "r");
	if (f == NULL)
	{
		printf("Error: Cannot open file\n");
		system("pause");
		return;
	}
	Staff staff;
	dprintf(66);
	printf
	(
		"|%-15s|%-30s|%-17s|\n",
		"Staff ID",
		"Staff name",
		"Position"
	);
	dprintf(66);
	while
		(
			fscanf
			(
				f,
				" %[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d-%d-%d\n",
				staff.staff_id,
				staff.name,
				&staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				&staff.salary,
				&staff.birth.day,
				&staff.birth.month,
				&staff.birth.year
			) != EOF
			)
	{
		printf
		(
			"|%-15s|%-30s|%-17s|\n",
			staff.staff_id,
			staff.name,
			staff.position
		);
	}
	fclose(f);
	dprintf(66);
}

void updateStaffPosition()
{
	while (1)
	{
		FILE* fp, * temp;
		Staff staff;
		char line[256];
		int found = 0;
		displayStaffPosition();
		fp = fopen("staff.txt", "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			system("pause");
			return;
		}
		char staff_id[11];
		IDGet(staff_id, "staff", "update");
		if (checkSentinent(staff_id)) {
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
				staff.staff_id,
				staff.name,
				&staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				&staff.salary,
				&staff.birth.day,
				&staff.birth.month,
				&staff.birth.year
			);

			if (strcmp(staff.staff_id, staff_id) == 0) {
				found = 1;
				system("cls");
				printf
				(
					"Staff ID: %s\n"
					"Staff name: %s\n"
					"Staff position: %s\n"
					"\nEnter new position (-1 to cancel): ",
					staff.staff_id,
					staff.name,
					staff.position
				);

				scanf(" %s", staff.position);

				if (checkSentinent(staff.position))
				{
					fclose(fp);
					fclose(temp);
					remove("temp.txt");
					return;
				}
			}
			fprintf(temp, "%s|%s|%c|%s|%s|%s|%s|%s|%.2lf|%d-%d-%d\n",
				staff.staff_id,
				staff.name,
				staff.gender,
				staff.password,
				staff.email,
				staff.phone_number,
				staff.address,
				staff.position,
				staff.salary,
				staff.birth.day,
				staff.birth.month,
				staff.birth.year);
			if (found)break;
		}
		fclose(fp);
		fclose(temp);
		remove("staff.txt");
		rename("temp.txt", "staff.txt");
		if (!found) {
			printf("Staff not found! Please try again\n");
		}
		else {
			printf("Staff position updated successfully!\n");
		}
		system("pause");
	}
}


int printStaffMenu()
{
	printf
	(
		"------------------------------\n"
		"|  Staff Information Module  |\n"
		"|----------------------------|\n"
		"|1. Display staff list       |\n"
		"|2. Search staffs            |\n"
		"|3. Edit staffs              |\n"
		"|4. Delete staffs            |\n"
		"|5. Add staffs 	             |\n"
		"|6. Update staff position    |\n"
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

void staff()
{
	FILE* cr8file = fopen("staff.txt", "a"); // create file if not exist
	fclose(cr8file);
	while (1)
	{
		system("cls");
		int selection = printStaffMenu(); // 1-7
		switch (selection)
		{
		case 1:
			displayStaff();
			break;
		case 2:
			searchStaff();
			break;
		case 3:
			editStaff();
			break;
		case 4:
			deleteStaff();
			break;
		case 5:
			addStaff();
			break;
		case 6:
			updateStaffPosition();
			break;
		case 7:
			return;
			break;
		}
	}
}