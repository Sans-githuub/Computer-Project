//_______________________________________________________Header Files____________________________________________
#include "login.h"
#include "phonebook.h"

//------------First Create a Blank User_Input.txt and Records.txt File in the same application Directory --------------

// This system can store up to 20 number of users Data.

int main()
{
    system("color e");
    printf("\n\nLoading");
    for (int i = 0; i < 8; i++)
    {
        printf(".");
        Sleep(370);
    }
    FILE *fp = fopen(filename, "r");
    int i = 0, Num, Num1;
    User u;
    if (NULL == fp)
    {
        printf("\nFILE NOT FOUND");
        exit(1);
    }
    for (i = 0; i < USER_MAX; i++)
    {
        char User_Name[100];
        char User_Password[10];
        fscanf(fp, "%s%s", User_Name, User_Password);
        strcpy(list[i].name, User_Name);
        strcpy(list[i].password, User_Password);
    }
    int choice = Start_Options();
    switch (choice)
    {

        // This Case is for login

    case 1:
        system("cls");
        u = login();
        if (1 == exist(u))
        {

            // More Main Codes to include.
            printf("\n\nLoading");
            for (int i = 0; i < 8; i++)
            {
                printf(".");
                Sleep(370);
            }
            

            system("cls");
            
            printf("\n\n\n\n\t\t\t\t\t\tHello,%s Welcome to the Program.", Confirmed_User.name);
            printf("\n\nLoading");
            for (int i = 0; i < 8; i++)
            {
                printf(".");
                Sleep(250);
            }
            system("cls");
            PhoneRec pr = initPhoneRec();
            loadRec(pr);
            printf("Welcome to Our TELEPHONE DIRECTORY\n\n");
            mainMenu(pr);
        }
        else
        {
            printf("\nWRONG USERNAME OR PASS\n");
            printf("\n 1 --> Retry \n 0 --> Exit\n\n   Your choice --> ");
            scanf("%d", &Num);
            switch (Num)
            {
            case 1:
                system("cls");
                main();
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("\nWrong Input Do you Want to Try again");
                printf("\n 1 --> Retry \n 0 --> Exit\n\n   Your choice --> ");
                scanf("%d", &Num1);
                switch (Num1)
                {
                case 1:
                    system("cls");
                    main();
                    break;
                case 0:
                    exit(0);
                    break;
                default:
                    system("cls");
                    printf("\n\nAgain, the input is Wrong........");
                    main();
                    break;
                }
            }
        }
        break;

        // This Case is for Registration

    case 2:
        system("cls");
        registerUser();
        main();
        break;

        // This Case is to Exit

    case 0:
        exit(0);
        break;

        // This Case is for the Default if any wrong key is Pressed except 0,1 and 2

    default:
        printf("\nWrong Input Do you Want to Try again");
        printf("\n 1 --> Retry \n 0 --> Exit\n\n   Your choice --> ");
        scanf("%d", &Num);
        switch (Num)
        {
        case 1:
            system("cls");
            main();
            break;
        case 0:
            exit(0);
            break;
        default:
            system("cls");
            printf("\n\nAgain, the input is Wrong..........");
            main();
            break;
        }
    }
}