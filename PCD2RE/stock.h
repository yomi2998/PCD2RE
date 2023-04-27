#include "necessaryIncludes.h"
// Siew Jun Hong
void displayStock()
{
	system("cls");
	int count = 0;
	FILE* fp = fopen("stock.bin", "rb");
	if (fp == NULL)
	{
		printf("Fail to open stock.bin\n");
		system("pause");
		return;
	}
	Stock stock;
	dprintf(107);
	printf
	(
		"|%-15s|%-30s|%-20s|%-10s|%-10s|%-15s|\n",
		"Stock ID",
		"Name",
		"Category",
		"Quantity",
		"For sale?",
		"Price"
	);
	dprintf(107);
	while (fread(&stock, sizeof(stock), 1, fp) == 1)
	{
		++count;
		printf
		(
			"|%-15s|%-30s|%-20s|%-10d|%-10c|RM %-12.2F|\n",
			stock.stock_id,
			stock.name,
			stock.category,
			stock.quantity,
			stock.forSale,
			stock.price
		);
	}
	dprintf(107);
	printf("Total stocks: %d\n", count);

	fclose(fp);
	system("pause");
}

void searchStock()
{
	while (1)
	{
		displayStock();
		FILE* fp = fopen("stock.bin", "rb");
		if (fp == NULL)
		{
			printf("Fail to open stock.bin\n");
			system("pause");
			return;
		}
		Stock stock;
		char stock_id[11];
		IDGet(stock_id, "stock", "display");
		int found = 0;
		if (checkSentinent(stock_id))
		{
			fclose(fp);
			return;
		}
		while (fread(&stock, sizeof(stock), 1, fp) == 1)
		{
			if (strcmp(stock.stock_id, stock_id) == 0)
			{
				system("cls");
				found = 1;
				printf("\nStock found! Here are the details:\n\n");
				printf("Stock ID: %s\n", stock.stock_id);
				printf("Stock name: %s\n", stock.name);
				printf("Stock category: %s\n", stock.category);
				printf("Stock description: %s\n", stock.description);
				printf("Stock quantity: %d\n", stock.quantity);
				printf("Stock price: RM %.2f\n", stock.price);
				printf("Stock for sale: %c\n", stock.forSale);
				printf("Stock import date: %d-%d-%d\n", stock.import_date.day, stock.import_date.month, stock.import_date.year);
			}
		}
		fclose(fp);
		if (!found)
			printf("Stock item not found! Please try again.\n");
		system("pause");
	}
}

void editStock()
{
	while (1)
	{
		displayStock();
		FILE* fp = fopen("stock.bin", "rb");
		FILE* new_fp = fopen("new_stock.bin", "wb");
		if (fp == NULL || new_fp == NULL)
		{
			printf("Fail to open stock.bin\n");
			system("pause");
			return;
		}
		Stock stock;
		char stock_id[11];
		IDGet(stock_id, "stock", "edit");
		int found = 0;
		char yN;
		if (checkSentinent(stock_id))
		{
			fclose(fp);
			fclose(new_fp);
			remove("new_stock.bin");
			return;
		}
		while (fread(&stock, sizeof(stock), 1, fp) == 1)
		{
			if (strcmp(stock.stock_id, stock_id) == 0)
			{
				found = 1;
				while (1)
				{
					system("cls");
					printf(
						"\nHere are the details:\n\n"
						"   Stock ID: %s\n"
						"1. Stock name: %s\n"
						"2. Stock category: %s\n"
						"3. Stock description: %s\n"
						"4. Stock quantity: %d\n"
						"5. Stock price: RM %.2f\n"
						"6. Stock for sale: %c\n"
						"7. Stock import date: %d-%d-%d\n"
						"Which to edit? (1-7, -1 to cancel): ",
						stock.stock_id,
						stock.name,
						stock.category,
						stock.description,
						stock.quantity,
						stock.price,
						stock.forSale,
						stock.import_date.day,
						stock.import_date.month,
						stock.import_date.year
					);
					char choice[3];
					scanf(" %s", choice);
					if (checkSentinent(choice)) {
						fclose(fp);
						fclose(new_fp);
						remove("new_stock.bin");
						return;
					}
					int choice_int = atoi(choice);
					while (choice_int < 1 || choice_int > 7) {
						printf("Invalid choice! Please enter again: ");
						scanf(" %s", choice);
						if (checkSentinent(choice)) {
							fclose(fp);
							fclose(new_fp);
							remove("new_stock.bin");
							return;
						}
						choice_int = atoi(choice);
					}
					switch (choice_int)
					{
					case 1:
						do
						{
							memset(stock.name, 0, sizeof(stock.name));
							printf("Enter new stock name (-1 to cancel): ");
							scanf(" %[^\n]", stock.name);
							if (checkSentinent(stock.name))
							{
								fclose(fp);
								fclose(new_fp);
								remove("new_stock.bin");
								return;
							}
							if (!validationStockName(stock.name))
							{
								printf("Incorrect name format! Please try again.\n");
							}
						} while (!validationStockName(stock.name));
						break;
					case 2:
						printf("Enter new stock category (-1 to cancel): ");
						scanf(" %[^\n]", stock.category);
						if (checkSentinent(stock.category))
						{
							fclose(fp);
							fclose(new_fp);
							remove("new_stock.bin");
							return;
						}
						break;
					case 3:
						printf("Enter new stock description (-1 to cancel): ");
						scanf(" %[^\n]", stock.description);
						if (checkSentinent(stock.description))
						{
							fclose(fp);
							fclose(new_fp);
							remove("new_stock.bin");
							return;
						}
						break;
					case 4:
						do
						{
							printf("Enter new stock quantity: ");
							scanf(" %d", &stock.quantity);
							if (stock.quantity < 0)
								printf("Quantity must be 0 or more! Please try again.\n");
						} while (stock.quantity < 0);
						break;
					case 5:
						do
						{
							printf("Enter new stock price: ");
							scanf(" %f", &stock.price);
							if (stock.price < 0)
								printf("Price must be 0 or more! Please try again.\n");
						} while (stock.price < 0);
						break;
					case 6:
						if (stock.quantity == 0)
						{
							printf("The stock cannot be on sale as the quantity is 0.\n");
							system("pause");
							break;
						}
						do
						{
							printf("Change stock to %s?(Y/N): ", stock.forSale == 'Y' ? "not for sale" : "for sale");
							scanf(" %c", &yN);
							yN = toupper(yN);
							if (yN != 'Y' && yN != 'N')
							{
								printf("Invalid choice! Please try again.\n");
							}
							else if (yN == 'Y')
							{
								stock.forSale = stock.forSale == 'Y' ? 'N' : 'Y';
							}
						} while (yN != 'Y' && yN != 'N');
						break;
					case 7:
						do
						{
							memset(&stock.import_date, 0, sizeof(stock.import_date));
							printf("Enter new stock import date (format: dd-mm-yyyy): ");
							scanf(" %d-%d-%d", &stock.import_date.day, &stock.import_date.month, &stock.import_date.year);
							if (!validationStockImport(stock.import_date))
							{
								printf("Incorrect date format! Make sure you've entered correct date.\n");
							}
						} while (!validationStockImport(stock.import_date));
						break;
					}
					system("cls");
					printf(
						"\nHere are the details:\n\n"
						"   Stock ID: %s\n"
						"1. Stock name: %s\n"
						"2. Stock category: %s\n"
						"3. Stock description: %s\n"
						"4. Stock quantity: %d\n"
						"5. Stock price: RM %.2f\n"
						"6. Stock for sale: %c\n"
						"7. Stock import date: %d-%d-%d\n",
						stock.stock_id,
						stock.name,
						stock.category,
						stock.description,
						stock.quantity,
						stock.price,
						stock.forSale,
						stock.import_date.day,
						stock.import_date.month,
						stock.import_date.year
					);
					do
					{
						printf("Apply the modifications?(Y/N): ");
						scanf(" %c", &yN);
						yN = toupper(yN);
						if (yN != 'Y' && yN != 'N')
						{
							printf("Invalid choice! Please try again.\n");
						}
						else if (yN == 'Y')
						{
							break;
						}
					} while (yN != 'Y' && yN != 'N');
					if (yN == 'Y')
					{
						fwrite(&stock, sizeof(stock), 1, new_fp);
						break;
					}
					else
					{
						continue;
					}
				}
			}
			else
			{
				fwrite(&stock, sizeof(stock), 1, new_fp);
			}
		}
		fclose(fp);
		fclose(new_fp);
		if (!found)
		{
			printf("Stock item not found! Please try again.\n");
			remove("new_stock.bin");
		}
		else
		{
			remove("stock.bin");
			rename("new_stock.bin", "stock.bin");
			printf("Stock successfully updated!\n");
		}
		system("pause");
	}
}

void deleteStock()
{
	while (1)
	{
		displayStock();
		FILE* fp = fopen("stock.bin", "rb");
		FILE* new_fp = fopen("new_stock.bin", "wb");
		if (fp == NULL || new_fp == NULL)
		{
			printf("Fail to open stock.bin\n");
			system("pause");
			return;
		}
		Stock stock;
		char stock_id[11];
		IDGet(stock_id, "stock", "delete");
		int found = 0;
		char yN;
		if (checkSentinent(stock_id))
		{
			fclose(fp);
			fclose(new_fp);
			remove("new_stock.bin");
			return;
		}
		while (fread(&stock, sizeof(stock), 1, fp) == 1)
		{
			if (strcmp(stock.stock_id, stock_id) == 0)
			{
				system("cls");
				found = 1;
				printf(
					"\nStock found! Here are the details:\n\n"
					"   Stock ID: %s\n"
					"1. Stock name: %s\n"
					"2. Stock category: %s\n"
					"3. Stock description: %s\n"
					"4. Stock quantity: %d\n"
					"5. Stock price: RM %.2f\n"
					"6. Stock for sale: %c\n"
					"7. Stock import date: %d-%d-%d\n",
					stock.stock_id,
					stock.name,
					stock.category,
					stock.description,
					stock.quantity,
					stock.price,
					stock.forSale,
					stock.import_date.day,
					stock.import_date.month,
					stock.import_date.year
				);
				do
				{
					printf("Confirm delete?(Y/N): ");
					scanf(" %c", &yN);
					yN = toupper(yN);
					if (yN != 'Y' && yN != 'N')
					{
						printf("Invalid choice! Please try again.\n");
					}
					else if (yN == 'Y')
					{
						break;
					}
				} while (yN != 'Y' && yN != 'N');
				if (yN == 'N')
				{
					fwrite(&stock, sizeof(stock), 1, new_fp);
				}
			}
			else
			{
				fwrite(&stock, sizeof(stock), 1, new_fp);
			}
		}
		fclose(fp);
		fclose(new_fp);
		if (!found)
		{
			printf("Stock item not found! Please try again.\n");
			remove("new_stock.bin");
		}
		else if (yN == 'Y')
		{
			remove("stock.bin");
			rename("new_stock.bin", "stock.bin");
			printf("Stock deleted successfully!\n");
		}
		system("pause");
	}
}

int printStockMenu()
{
	printf
	(
		"------------------------------\n"
		"|  Stock Information Module  |\n"
		"|----------------------------|\n"
		"|1. Display stock list       |\n"
		"|2. Search stocks            |\n"
		"|3. Edit stocks              |\n"
		"|4. Delete stocks            |\n"
		"|5. Add stocks 	             |\n"
		"|6. Change stock for sale    |\n"
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

void addStock()
{
	while (1)
	{
		system("cls");
		char yN;
		FILE* fp = fopen("stock.bin", "rb");
		if (fp == NULL)
		{
			printf("Failed to open the file.\n");
			return;
		}
		else
		{
			fclose(fp);
		}
		Stock stock;
		IDGen(stock.stock_id, "STOCK");
		printf("Stock ID: %s\n", stock.stock_id);
		do
		{
			memset(stock.name, 0, sizeof(stock.name));
			printf("Enter stock name (-1 to cancel): ");
			scanf(" %[^\n]", stock.name);
			if (checkSentinent(stock.name))
			{
				return;
			}
			if (!validationStockName(stock.name))
			{
				printf("Invalid name format! Please try again.\n");
			}
		} while (!validationStockName(stock.name));

		printf("Enter stock category (-1 to cancel): ");
		scanf(" %[^\n]", stock.category);
		if (checkSentinent(stock.category))
		{
			return;
		}

		printf("Enter stock description (-1 to cancel): ");
		scanf(" %[^\n]", stock.description);
		if (checkSentinent(stock.description))
		{
			return;
		}
		do
		{
			printf("Enter stock quantity: ");
			scanf(" %d", &stock.quantity);
			if (stock.quantity < 0)
			{
				printf("Stock quantity must be at least 0 or more! Please try again.\n");
			}
		} while (stock.quantity < 0);
		do
		{
			printf("Enter stock price (RM): ");
			scanf(" %f", &stock.price);
			if (stock.price < 0)
			{
				printf("Stock price must be at least 0 or more! Please try again.\n");
			}
		} while (stock.price < 0);
		if (stock.quantity == 0)
		{
			printf("Stock will be automatically set to 'NOT FOR SALE' as quantity of the stock is 0.\n");
		}
		else
		{
			do
			{
				printf("Enter stock for sale (Y/N) : ");
				scanf(" %c", &stock.forSale);
				stock.forSale = toupper(stock.forSale);
				if (stock.forSale != 'Y' && stock.forSale != 'N')
				{
					printf("Invalid answer! Please try again.\n");
				}
			} while (stock.forSale != 'Y' && stock.forSale != 'N');
		}
		do
		{
			printf("Enter stock import date (dd-mm-yyyy): ");
			scanf(" %d-%d-%d", &stock.import_date.day, &stock.import_date.month, &stock.import_date.year);
			if (!validationStockImport(stock.import_date))
			{
				printf("Wrong import date format! Please try again.\n");
			}
		} while (!validationStockImport(stock.import_date));
		while (1)
		{
			system("cls");
			dprintf(100);
			printf(
				"\nHere are the stock details:\n\n"
				"   Stock ID: %s\n"
				"1. Stock name: %s\n"
				"2. Stock category: %s\n"
				"3. Stock description: %s\n"
				"4. Stock quantity: %d\n"
				"5. Stock price: RM %.2f\n"
				"6. Stock for sale: %c\n"
				"7. Stock import date: %d-%d-%d\n",
				stock.stock_id,
				stock.name,
				stock.category,
				stock.description,
				stock.quantity,
				stock.price,
				stock.forSale,
				stock.import_date.day,
				stock.import_date.month,
				stock.import_date.year
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
			printf("Which to edit? (1-7, -1 to cancel): ");
			char choice[3];
			scanf(" %s", choice);
			if (checkSentinent(choice)) {
				fclose(fp);
				return;
			}
			int choice_int = atoi(choice);
			while (choice_int < 1 || choice_int > 9) {
				printf("Invalid choice! Please enter again: ");
				choice[2] = '\0';
				scanf(" %s", choice);
				if (checkSentinent(choice)) {
					fclose(fp);
					return;
				}
				choice_int = atoi(choice);
			}
			switch (choice_int)
			{
			case 1:
				do
				{
					memset(stock.name, 0, sizeof(stock.name));
					printf("Enter new stock name (-1 to cancel): ");
					scanf(" %[^\n]", stock.name);
					if (checkSentinent(stock.name))
					{
						return;
					}
					if (!validationStockName(stock.name))
					{
						printf("Incorrect name format! Please try again.\n");
					}
				} while (!validationStockName(stock.name));
				break;
			case 2:
				printf("Enter new stock category (-1 to cancel): ");
				scanf(" %[^\n]", stock.category);
				if (checkSentinent(stock.category))
				{
					return;
				}
				break;
			case 3:
				printf("Enter new stock description (-1 to cancel): ");
				scanf(" %[^\n]", stock.description);
				if (checkSentinent(stock.description))
				{
					return;
				}
				break;
			case 4:
				do
				{
					printf("Enter new stock quantity: ");
					scanf(" %d", &stock.quantity);
					if (stock.quantity < 0)
						printf("Quantity must be 0 or more! Please try again.\n");
				} while (stock.quantity < 0);
				break;
			case 5:
				do
				{
					printf("Enter new stock price: ");
					scanf(" %f", &stock.price);
					if (stock.price < 0)
						printf("Price must be 0 or more! Please try again.\n");
				} while (stock.price < 0);
				break;
			case 6:
				if (stock.quantity == 0)
				{
					printf("The stock cannot be on sale as the quantity is 0.\n");
					system("pause");
					break;
				}
				do
				{
					printf("Change stock to %s?(Y/N): ", stock.forSale == 'Y' ? "not for sale" : "for sale");
					scanf(" %c", &yN);
					yN = toupper(yN);
					if (yN != 'Y' && yN != 'N')
					{
						printf("Invalid choice! Please try again.\n");
					}
					else if (yN == 'Y')
					{
						stock.forSale = stock.forSale == 'Y' ? 'N' : 'Y';
					}
				} while (yN != 'Y' && yN != 'N');
				break;
			case 7:
				do
				{
					memset(&stock.import_date, 0, sizeof(stock.import_date));
					printf("Enter new stock import date (format: dd-mm-yyyy): ");
					scanf(" %d-%d-%d", &stock.import_date.day, &stock.import_date.month, &stock.import_date.year);
					if (!validationStockImport(stock.import_date))
					{
						printf("Incorrect date format! Make sure you've entered correct date.\n");
					}
				} while (!validationStockImport(stock.import_date));
				break;
			}
		}
		fp = fopen("stock.bin", "ab");
		fwrite(&stock, sizeof(stock), 1, fp); 
		printf("Registered sucessfully!\n");
		fclose(fp);
		system("pause");
	}
}

void displayStockSale()
{
	system("cls");
	FILE* fp = fopen("stock.bin", "rb");
	if (fp == NULL)
	{
		printf("Fail to open stock.bin\n");
		system("pause");
		return;
	}
	Stock stock;
	dprintf(59);
	printf
	(
		"|%-15s|%-30s|%-10s|\n",
		"Stock ID",
		"Name",
		"For sale?"
	);
	dprintf(59);
	while (fread(&stock, sizeof(stock), 1, fp) == 1)
	{
		printf
		(
			"|%-15s|%-30s|%-10c|\n",
			stock.stock_id,
			stock.name,
			stock.forSale
		);
	}
	dprintf(59);
	fclose(fp);
	system("pause");
}

void updateStockSale()
{
	while (1)
	{
		FILE* fp = fopen("stock.bin", "rb");
		FILE* new_fp = fopen("new_stock.bin", "wb");
		char yN;
		if (fp == NULL)
		{
			printf("Error cannot open the file.\n");
			system("pause");
			return;
		}
		displayStockSale();
		Stock stock;
		int found = 0;
		char stock_id[11];
		IDGet(stock_id, "stock", "update");
		if (checkSentinent(stock_id))
		{
			fclose(fp);
			fclose(new_fp);
			remove("new_stock.txt");
			return;
		}
		while (fread(&stock, sizeof(stock), 1, fp) == 1)
		{
			if (strcmp(stock_id, stock.stock_id) == 0)
			{
				system("cls");
				found = 1;
				printf("\nStock found! Here are the details:\n\n");
				printf("Stock ID: %s\n", stock.stock_id);
				printf("Stock name: %s\n", stock.name);
				printf("Stock for sale: %c\n", stock.forSale);
				do
				{
					printf("Update stock to %s? (Y/N):", stock.forSale == 'Y' ? "not for sale" : "for sale");
					scanf(" %c", &yN);
					yN = toupper(yN);
					if (yN != 'Y' && yN != 'N')
					{
						printf("Invalid choice, please try again.\n");
					}
					else if (yN == 'Y')
					{
						stock.forSale = stock.forSale == 'Y' ? 'N' : 'Y';
					}
					fwrite(&stock, sizeof(stock), 1, new_fp);
				} while (yN != 'Y' && yN != 'N');
			}
			else
			{
				fwrite(&stock, sizeof(stock), 1, new_fp);
			}
		}
		if (!found)
		{
			printf("Stock ID not found, please try again.\n");
			fclose(fp), fclose(new_fp);
			remove("new_stock.txt");
			system("pause");
		}
		else if (yN == 'Y')
		{
			fclose(fp), fclose(new_fp);
			remove("stock.bin");
			rename("new_stock.bin", "stock.bin");
			printf("Stock updated successfully!\n");
		}
	}
}

void stock()
{
	FILE* cr8file = fopen("stock.bin", "ab"); // create file if not exist
	fclose(cr8file);
	while (1)
	{
		system("cls");
		int selection = printStockMenu(); // 1-7
		switch (selection)
		{
		case 1:
			displayStock();
			break;
		case 2:
			searchStock();
			break;
		case 3:
			editStock();
			break;
		case 4:
			deleteStock();
			break;
		case 5:
			addStock();
			break;
		case 6:
			updateStockSale();
			break;
		case 7:
			return;
			break;
		}
	}
}