#include <ctype.h>
#define MaxR 5000
#define MaxNL 20

//___________________________________________________STRUCTS____________________________________________________
typedef struct
{
	char fName[MaxNL + 1];
	char lName[MaxNL + 1];
	char pNum[10];
} RType, *Record;

typedef struct
{
	Record phoneRec[MaxR];
	int recIndex;
} PRType, *PhoneRec;

void mainMenu();
void sort(PhoneRec pr);
void addRecord(PhoneRec pr);
void load(PhoneRec pr);

//_____________________________________________________FUNCTIONS___________________________________________________

//creates an empty collection of records
PhoneRec initPhoneRec(void)
{
	PhoneRec pr = (PhoneRec)malloc(sizeof(PRType));
	pr->recIndex = 0;
	return pr;
}

//Goes through array and return 1 if phone number found and 0 if not.
int checkDupNum(PhoneRec pr, char *input)
{
	for (int i = 0; i < pr->recIndex; i++)
	{
		if (strcmp(input, pr->phoneRec[i]->pNum) == 0)
		{
			return 1;
		}
	}
	return 0;
}

// sort: display all records in ascending order based on a particular field
void swap(Record list[], int i, int j)
{
	//swap list[i] and list[j]
	Record hold = list[i];
	list[i] = list[j];
	list[j] = hold;
} //end swap

//splitting part of quicksort
int partition(Record A[], int lo, int hi, char ans)
{
	//partition A[lo] to A[hi] using A[lo] as the pivot
	Record pivot = A[lo];
	int lastSmall = lo;
	int cmp = 0;
	for (int h = lo + 1; h <= hi; h++)
	{
		if (ans == 'f')
			cmp = strcmp(A[h]->fName, pivot->fName);
		else if (ans == 'l')
			cmp = strcmp(A[h]->lName, pivot->lName);
		else
			cmp = strcmp(A[h]->pNum, pivot->pNum);

		if (cmp < 0)
		{
			++lastSmall;
			swap(A, lastSmall, h);
		}
	}
	swap(A, lo, lastSmall);
	return lastSmall; //return the division point
} //end partition

//Divide and conquer, recursive algorithm, which calls partition
void quicksort(Record A[], int lo, int hi, char ans)
{
	//sorts A[lo] to A[hi] in ascending order
	if (lo < hi)
	{
		int dp = partition(A, lo, hi, ans);
		quicksort(A, lo, dp - 1, ans);
		quicksort(A, dp + 1, hi, ans);
	}
} //end quicksort

// capitalize first word
char *firstCap(char *s)
{
	int length = strlen(s);

	for (int i = 0; i < length; i++)
	{
		if (isalpha(s[0]))
		{
			s[0] = toupper(s[0]);
		}
		if (isalpha(s[i]) && i != 0)
		{
			s[i] = tolower(s[i]);
		}
	}
	return s;
}

// print all records in phone book
int cleanInput(void)
{
	while (getchar() != '\n')
	return 1;
}

void printRec(PhoneRec pr)
{
	printf("  NO.          FIRST NAME          LAST NAME          PHONE NUMBER\n");
	printf("____________________________________________________________________\n\n");
	for (int i = 0; i < pr->recIndex; i++)
	{

		printf("%4d.%20s%19s%22s\n", i + 1, pr->phoneRec[i]->fName, pr->phoneRec[i]->lName,
			   pr->phoneRec[i]->pNum);
	}
	printf("\n");
}

// add a new record
void addRec(PhoneRec pr, Record r)
{
	if (!checkDupNum(pr, r->pNum))
	{
		pr->phoneRec[pr->recIndex] = r;
		pr->recIndex++;
	}
}

// creates an empty record and returns the record struct
Record initRec(char *fName, char *lName, char *pNum)
{
	Record r = (Record)malloc(sizeof(RType));
	strncpy(r->fName, fName, MaxNL);
	r->fName[MaxNL] = '\0';
	strncpy(r->lName, lName, MaxNL);
	r->lName[MaxNL] = '\0';
	strncpy(r->pNum, pNum, 10);
	r->pNum[MaxNL] = '\0';
	return r;
}

// retrieve: display a record that contains a particular attribute value
void retrieveRec(PhoneRec pr)
{
	char *attr = (char *)malloc(MaxNL + 1);
	int found = 0;
	int count = 1;
	printf("\nEnter first name, last name, or phone number to look for:\n");
	scanf("%s", attr);

	printf("  NO.          FIRST NAME          LAST NAME          PHONE NUMBER\n");
	printf("____________________________________________________________________\n\n");

	for (int i = 0; i < pr->recIndex; i++)
	{
		if (strcmp(firstCap(attr), pr->phoneRec[i]->fName) == 0 ||
			strcmp(firstCap(attr), pr->phoneRec[i]->lName) == 0 ||
			strcmp(attr, pr->phoneRec[i]->pNum) == 0)
		{
			printf("%4d.%20s%19s%22s\n", count, pr->phoneRec[i]->fName, pr->phoneRec[i]->lName,
				   pr->phoneRec[i]->pNum);
			count++;
			found = 1;
		}
	}

	if (found == 0)
	{
		printf("\nRecord not found\n");
	}

	printf("\n");
}

// delete: delete an existing record given a specific attribute of that record
void deleteRec(PhoneRec pr)
{
	int found = 0;
	char *attr = (char *)malloc(MaxNL + 1);
	int count = 0;

	printf("\nEnter first name, last name, or phone number to delete:\n");
	scanf("%s", attr);
	printf("\n");

	printf("  NO.          FIRST NAME          LAST NAME          PHONE NUMBER\n");
	printf("____________________________________________________________________\n\n");

	for (int i = 0; i < pr->recIndex; i++)
	{
		if (strcmp(firstCap(attr), pr->phoneRec[i]->fName) == 0 ||
			strcmp(firstCap(attr), pr->phoneRec[i]->lName) == 0 ||
			strcmp(attr, pr->phoneRec[i]->pNum) == 0)
		{
			printf("%4d.%20s%19s%22s\n", count + 1, pr->phoneRec[i]->fName, pr->phoneRec[i]->lName,
				   pr->phoneRec[i]->pNum);
			count++;
		}
	}

	int recNum = 1;
	char newLine;
	if (count > 1)
	{
		do
		{
			printf("\nWhich record do you want to to delete from the above list?\n");
		} while (((scanf("%d%c", &recNum, &newLine) != 2 || newLine != '\n') &&
				  cleanInput()) ||
				 recNum < 1 || recNum > count);
	}

	for (int i = 0; i < pr->recIndex; i++)
	{

		if (strcmp(attr, pr->phoneRec[i]->fName) == 0 ||
			strcmp(attr, pr->phoneRec[i]->lName) == 0 ||
			strcmp(attr, pr->phoneRec[i]->pNum) == 0)
		{
			found = 1;
			if (recNum == 1)
			{
				// move all elements right of index to left by one position
				for (int j = i; j < pr->recIndex - 1; j++)
				{
					pr->phoneRec[j] = pr->phoneRec[j + 1];
				}
				pr->recIndex--;
				printf("\nThis record was successfully deleted.\n\n");
			}
			else
				recNum--;
		}
	}

	if (found == 0)
		printf("\nNo record match found to delete.\n\n");

	//printRec(pr);
}

// load: read data from a file which contains data of the phone book
void loadRec(PhoneRec pr)
{
	char fName[MaxNL + 1];
	char lName[MaxNL + 1];
	char pNum[11];
	FILE *rFile = fopen("Records.txt", "r"); // opens a file for reading

	if (rFile == NULL) // file does not exist
		printf("File not found.\n\n");
	else
	{
		while (!feof(rFile))
		{
			fscanf(rFile, "%s %s %s", fName, lName, pNum);

			if (feof(rFile))
			{
				break;
			}
			else
			{
				Record r = initRec(fName, lName, pNum);

				addRec(pr, r);
			}
		}
	}

	printf("\n");
	quicksort(pr->phoneRec, 0, pr->recIndex - 1, 'f');
	fclose(rFile);
}

// save: write data of phone book to a file
void saveRec(PhoneRec pr)
{
	FILE *wFile = fopen("Records.txt", "w"); // opens a new file for writing

	if (wFile == NULL)
	{
		printf("File not found.\n\n");
	}

	for (int i = 0; i < pr->recIndex; i++)
	{
		fprintf(wFile, "%s %s %s\n", pr->phoneRec[i]->fName, pr->phoneRec[i]->lName, pr->phoneRec[i]->pNum);
	}

	fclose(wFile);
}

//Function for checking if string contains anything other than characters
int isChar(char *input)
{
	int len = strlen(input);

	for (int i = 0; i < len; i++)
	{
		if (!isalpha(input[i]))
		{
			printf("Must be characters only\n");
			return 0;
		}
	}
	return 1;
}
//Function for checking if string contains anything other than numbers
int isNum(char *input)
{
	int len = strlen(input);

	for (int i = 0; i < len; i++)
	{
		if (isalpha(input[i]))
		{
			return 0;
		}
	}
	return 1;
}

void mainMenu(PhoneRec pr)
{
	int input;

	printf("0. Print Phone Records\n");
	printf("1. Add Record\n");
	printf("2. Retrieve Record\n");
	printf("3. Delete Record\n");
	printf("4. Load File\n");
	printf("5. Save To File\n");
	printf("6. Sort\n");
	printf("7. Exit\n\n");

	do
	{
		printf("Choose an option: \n");
		scanf("%d", &input);
	} while ((input < 0 || input > 7) && cleanInput());

	if (input == 0)
	{
		printf("\n\n\n\nLoading");
		for (int i = 0; i < 8; i++)
		{

			printf("\n.");
			Sleep(150);
		}
		printf("\n\n\n");
		printRec(pr);
		mainMenu(pr);
	}
	else if (input == 1)
	{
		addRecord(pr);
		mainMenu(pr);
	}
	else if (input == 2)
	{
		retrieveRec(pr);
		mainMenu(pr);
	}
	else if (input == 3)
	{
		printf("\n");
		deleteRec(pr);
		mainMenu(pr);
	}
	else if (input == 4)
	{
		load(pr);
		mainMenu(pr);
	}
	else if (input == 5)
	{
		saveRec(pr);
		printf("\nState saved!\n\n");
		mainMenu(pr);
	}
	else if (input == 6)
	{
		sort(pr);
		printf("\n\n");
		mainMenu(pr);
	}
	else if (input == 7)
	{
		char in;
		do
		{
			printf("\nDo you want to save current state(y/n): ");
			scanf("%s", &in);

			if (in == 'y')
			{
				saveRec(pr);
				printf("State saved!\n");
				exit(0);
			}
			else if (in == 'n')
			{
				printf("\nExited succesfully!!!\n");
				exit(0);
			}
			else
				printf("Invalid Input!\n");

		} while (in);
	}
}

//Adds user input into records which is added to the PhoneRec array.
void addRecord(PhoneRec pr)
{

	char first[MaxNL + 1];
	char last[MaxNL + 1];
	char pnum[11];
	char in = 'y';

	while (in != 'n')
	{
		do
		{
			printf("\nEnter First Name: ");
			scanf("%s", first);
		} while (!isChar(first));

		do
		{
			printf("Enter Last Name: ");
			scanf("%s", last);
		} while (!isChar(last));
		do
		{
			printf("Enter Phone Number: ");
			scanf("%s", pnum);
			if (!isNum(pnum))
				printf("\nMust be Numbers only\n\n");
			else if (strlen(pnum) != 10)
				printf("\nPhone number must be 10 numbers long.\n\n");
			else if (checkDupNum(pr, pnum))
				printf("\nPhone number already exists.\n\n");
		} while (checkDupNum(pr, pnum) || !isNum(pnum) || strlen(pnum) != 10);

		Record r = initRec(firstCap(first), firstCap(last), pnum);
		addRec(pr, r);
		quicksort(pr->phoneRec, 0, pr->recIndex - 1, 'f');

		do
		{
			printf("\nDo you want to add another record? (y/n)");
			scanf("%s", &in);
			if (in == 'y')
				break;
			else if (in == 'n')
			{
				printf("\n");
				mainMenu(pr);
			}
			else
				printf("Enter valid input\n\n");
		} while (in);
	}
}

//Prompts user to choose a sort criteria. Calls quicksort accordingly.
void sort(PhoneRec pr)
{
	char in[11];
	do
	{
		printf("\nSort by First Name(f), Last Name(l), or Phone Number(p)?\n");
		scanf("%s", in);
		printf("\n");
		firstCap(in);
		if (!strcmp(in, "F"))
		{
			quicksort(pr->phoneRec, 0, pr->recIndex - 1, 'f');
			printf("\n\nLoading");
			for (int i = 0; i < 8; i++)
			{

				printf("\n.");
				Sleep(150);
			}
			printf("\n\n");
			printRec(pr);
			printf("Sorted by First Name\n\n");
			mainMenu(pr);
		}

		else if (!strcmp(in, "L"))
		{
			quicksort(pr->phoneRec, 0, pr->recIndex - 1, 'l');
			printf("\n\nLoading");
			for (int i = 0; i < 8; i++)
			{

				printf("\n.");
				Sleep(150);
			}
			printf("\n\n");
			printRec(pr);
			printf("Sorted by Last Name\n\n");
			mainMenu(pr);
		}
		else if (!strcmp(in, "P"))
		{
			quicksort(pr->phoneRec, 0, pr->recIndex - 1, 'p');
			printf("\n\nLoading");
			for (int i = 0; i < 8; i++)
			{

				printf("\n.");
				Sleep(150);
			}
			printf("\n\n");
			printRec(pr);
			printf("Sorted by Phone Number\n\n");
			mainMenu(pr);
		}
		else
		{
			printf("Invalid input\n");
		}
	} while ((strcmp(in, "F") || strcmp(in, "L") || strcmp(in, "P")));
}

//Calls loadRec and prints success statement.
void load(PhoneRec pr)
{

	loadRec(pr);
	printf("Load Successful\n\n");
}
