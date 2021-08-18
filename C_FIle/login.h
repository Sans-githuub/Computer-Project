// Header Files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define USER_MAX 20

// Declaration of Global Variable

char User_Name[100];

//Defining Structure having Name and Password as its Member

typedef struct
{
    char name[100];
    char password[10];
} User;

// define a global array, type User, size is USER_MAX

User list[USER_MAX];
User Confirmed_User;


// user.txt needs to br created your application directory before Running the prgram

char *filename = "User_Input.txt";


// ________________________Funciton Starts____________________

// Login Function

User login()
{
    char name[100];
    char password[10];
    printf("\nEnter Username : ");
    scanf("%s", name);
    strcpy(Confirmed_User.name, name);
    printf("\nEnter Password : ");
    scanf("%s", password);
    strcpy(Confirmed_User.password, password);
    return Confirmed_User;
}

// Funcitn for Appending the name and Password of the user

void writeToFile(User u)
{
    FILE *fw = fopen(filename, "a+");
    fprintf(fw, u.name);
    fprintf(fw, "\t\t");
    fprintf(fw, u.password);
    fprintf(fw, "\n");
    fclose(fw);
}

// Funciton to determine whether the user exists

int exist(User u)
{
    int i;
    for (i = 0; i < USER_MAX; i++)
    {
        if (0 == strcmp(list[i].name, u.name) && 0 == strcmp(list[i].password, u.password))
        {
            return 1;
        }
    }
    return -1;
}

//Funciton to Register the user

void registerUser()
{
    char name[100];
    char password[10];
    User user;
    int i;

    printf("\nEnter your name:");
    scanf("%s", name);
    strcpy(user.name, name);

    // determine whether there has been a registered user
    for (i = 0; i < USER_MAX; i++)
    {
        if (strcmp(list[i].name, name) == 0)
        {
            printf("\nUserName Already Taken.\n");
            printf("\nRegistration Failed :(\n");

            return;
        }
    }
    printf("\nEnter your password:");
    scanf("%s", password);
    printf("\nRegistration Successful :)\n");
    strcpy(user.password, password);
    writeToFile(user);
}

// Function for Showing the Options at First

int Start_Options()
{
    system("cls");
    int choice;
    printf("\n1--> Login\n");
    printf("2--> Register\n");
    printf("0--> Exit\n");
    printf("\nEnter your Choice: ");
    scanf("%d", &choice);
    return choice;
}