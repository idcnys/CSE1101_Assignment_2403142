#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

// console colors
// collected from https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

int unsuccessful_attempts = 0;

int _CARD_SIZE = 32;
int _LINE_SIZE = 42;
int _PHONE_SIZE = 12;
int _TIME_SIZE = 20;
void resetCurrentNumber()
{
    FILE *fptr2 = fopen("user/number.txt", "w");
    fprintf(fptr2, "%d", 0);
    fclose(fptr2);
}
void updateSold(int min)
{
    // sold name
    char filename[6];
    sprintf(filename, "%d", min);
    char filepath[100] = "admin/sold/"; // parent folder
    strcat(filepath, filename);         // the card type
    strcat(filepath, ".txt");

    FILE *fptr = fopen(filepath, "r+");
    char count[11];
    fscanf(fptr, "%10s", count);

    int sold = atoi(count);
    int final = sold + 1;
    char finalsold[20];
    sprintf(finalsold, "%d", final);

    fseek(fptr, 0, SEEK_SET);
    fprintf(fptr, "%s", finalsold);
    fclose(fptr);
}
void updateAdminBalance(int val)
{
    FILE *fptr = fopen("admin/balance.txt", "r+");
    char bal[11];
    fscanf(fptr, "%10s", bal);

    int balance = atoi(bal);
    int final = balance + val;
    char finalBalance[20];
    sprintf(finalBalance, "%d", final);

    fseek(fptr, 0, SEEK_SET);
    fprintf(fptr, "%s", finalBalance);
    fclose(fptr);
}
void showMinutes()
{
    printf("\n\tAvailable Minutes: ");
    // Reading pack details
    char filepathofuser[100] = "user/pack/";
    FILE *unp = fopen("user/number.txt", "r");
    char cur_user_num[25];
    fscanf(unp, "%11s", cur_user_num);
    strcat(filepathofuser, cur_user_num);
    strcat(filepathofuser, ".txt");

    FILE *fptr2 = fopen(filepathofuser, "r");
    if (!fptr2)
    {
        printf("0 minutes\n\n");
        return;
    }
    // if not exists then the value is 0 else the  value
    char bal[20];
    if (fscanf(fptr2, "%19s", bal) != 1)
    {
        printf("0 minutes\n");
        fclose(fptr2);
        return;
    }
    fclose(fptr2);

    printf("%s minutes\n\n", bal);
}
void removeCard(int type, int lineNum)
{
    char filename[6];
    sprintf(filename, "%d", type);
    char filepath[100] = "FreshCards/"; // parent folder
    strcat(filepath, filename);         // the card type
    strcat(filepath, ".txt");

    FILE *realfile = fopen(filepath, "r");
    FILE *tmpfile = fopen("FreshCards/temp.txt", "w");

    char real_card[_CARD_SIZE];
    int check_line = 1;

    while (fgets(real_card, _CARD_SIZE, realfile) != NULL)
    {
        if (strlen(real_card) <= 1)
            continue;
        real_card[strcspn(real_card, "\n")] = 0;

        if (check_line != lineNum)
        {
            fprintf(tmpfile, "%s\n", real_card);
        }
        check_line++;
        // copy lines to tempfile
        // except that lineNum;
        // delete the realfile
        // rename the temp file to realfilename
    }
    fclose(realfile);
    fclose(tmpfile);

    if (remove(filepath) != 0)
    {
        perror("Error deleting original file");
        return;
    }

    // Rename temp file
    if (rename("FreshCards/temp.txt", filepath) != 0)
    {
        perror("Error renaming temp file");
        return;
    }
}

void updateBalance(int val)
{
    char filepathofuser[100] = "user/pack/";
    FILE *unp = fopen("user/number.txt", "r");
    char cur_user_num[25];
    fscanf(unp, "%11s", cur_user_num);
    strcat(filepathofuser, cur_user_num);
    strcat(filepathofuser, ".txt");

    FILE *fptr = fopen(filepathofuser, "r+");
    char bal[6];
    fscanf(fptr, "%5s", bal);

    int balance = atoi(bal);
    int final = balance + val;
    char finalBalance[20];
    sprintf(finalBalance, "%d", final);

    fseek(fptr, 0, SEEK_SET);
    fprintf(fptr, "%s", finalBalance);
    fclose(fptr);
}
void commitRecharge(int min, int charge)
{

    printf("Please enter the cratch card number: ");
    char user_card[_CARD_SIZE];
    getchar();
    fgets(user_card, _CARD_SIZE, stdin);
    user_card[strcspn(user_card, "\n")] = 0;

    // printf("%s\n", user_card);
    char filename[6];
    sprintf(filename, "%d", min);
    char filepath[100] = "FreshCards/"; // parent folder
    strcat(filepath, filename);         // the card type
    strcat(filepath, ".txt");

    FILE *fptr = fopen(filepath, "r");
    char real_card[_CARD_SIZE];
    int found = 0;
    int lineNum = 0;

    while (fgets(real_card, _CARD_SIZE, fptr) != NULL)
    {
        if (strlen(real_card) <= 1)
            continue;
        real_card[strcspn(real_card, "\n")] = 0;
        // printf("user card: %s\n", real_card);

        if (strcmp(user_card, real_card) == 0)
        {
            printf("Card Found! at line %d in package list\n", lineNum + 1);

            // remove the card
            // recharge the amount
            // keeping track of history
            FILE *usrnum = fopen("user/number.txt", "r");
            char usrnumber[_PHONE_SIZE];
            fscanf(usrnum, "%11s", usrnumber);
            fclose(usrnum);

            time_t currentTime;
            time(&currentTime);

            char filename2[6];
            sprintf(filename2, "%d", min);
            char filepath2[100] = "UsedCards/"; // parent folder
            strcat(filepath2, filename2);       // the card type
            strcat(filepath2, ".txt");

            FILE *fptr3 = fopen(filepath2, "a");
            fprintf(fptr3, user_card);
            fprintf(fptr3, " ");
            fprintf(fptr3, "%ld", currentTime);
            fprintf(fptr3, " ");
            fprintf(fptr3, usrnumber);
            fprintf(fptr3, "\n");
            fclose(fptr3);

            found = 1;
            break;
        }
        lineNum++;
    }

    if (!found)
    {
        unsuccessful_attempts++;
        if (unsuccessful_attempts >= 3)
        {
            FILE *fptr = fopen("admin/blocked.txt", "r");
            FILE *fptr2 = fopen("user/number.txt", "r");
            char number[_PHONE_SIZE];
            fscanf(fptr2, "%11s", number);
            fclose(fptr2);

            // now making other user login
            FILE *rst = fopen("user/number.txt", "w");
            fprintf(rst, "%d", 0);
            fclose(rst);

            int count = 0;
            int ch;

            // Read character by character until EOF
            while ((ch = fgetc(fptr)) != EOF)
            {
                count++;
            }

            if (count < 5)
            {
                // initial commit
                fclose(fptr);
                FILE *xmp = fopen("admin/blocked.txt", "w");
                fclose(xmp);
            }
            FILE *fptr3 = fopen("admin/blocked.txt", "a");
            fprintf(fptr3, number);
            fprintf(fptr3, "\n");
            fclose(fptr3);

            printf(RED "Sorry Account blocked!" RESET "\n\n");
            exit(0);
        }
        printf(RED "Invalid card!" RESET "\n");
        return;
    }

    fclose(fptr);

    updateBalance(min);
    updateAdminBalance(charge);
    updateSold(min);
    removeCard(min, lineNum + 1);
    printf("\n\n\t" GREEN "[OK] Account Recharged Successfully" RESET "\n\n");
}

void makeRecharge()
{
    printf("Recharge Menu\n\n\t1. 40 min at Tk 50\n\t2. 60 min at Tk. 70\n\t3. 100 min at Tk. 120\n\n");
    int rch;
    printf("Select an option: ");
    scanf("%d", &rch);

    if (rch == 1)
    {
        // 40 mins tk 50;
        commitRecharge(40, 50);
    }
    else if (rch == 2)
    {
        commitRecharge(60, 70);
    }
    else if (rch == 3)
    {
        commitRecharge(100, 120);
    }
    else
    {
        printf(RED "Invalid selection" RESET "\n");
    }
}
void showNumber()
{
    FILE *fptr = fopen("user/number.txt", "r+");
    char number[_PHONE_SIZE];
    fscanf(fptr, "%11s", number);
    printf("\n\nCurrent User: ");
    printf("%s\n\n", number);
    fclose(fptr);
}
int isBlocked(char user_phn[])
{
    FILE *fptr = fopen("admin/blocked.txt", "r");
    char phn[_PHONE_SIZE];
    int found = 0;
    int lineNum = 0;

    while (fgets(phn, _PHONE_SIZE, fptr) != NULL)
    {
        if (strlen(phn) <= 1)
            continue;
        phn[strcspn(phn, "\n")] = 0;
        // printf("user card: %s\n", real_card);

        if (strcmp(user_phn, phn) == 0)
        {
            printf("Card Found! at line %d\n", lineNum + 1);

            // remove the card
            found = 1;
            break;
        }
        lineNum++;
    }
    fclose(fptr);

    if (found)
    {
        return 1;
    }
    else
        return 0;
}
int checkifblocked()
{
    FILE *fptr = fopen("user/number.txt", "r");
    char number[_PHONE_SIZE];
    fscanf(fptr, "%11s", number);

    if (isBlocked(number))
    {
        resetCurrentNumber(); // allowing other users log in
        printf(RED "Sorry your account is blocked" RESET "\n\n");
        return 1;
    }
    else
    {
        return 0;
    }
}
void logOut()
{
    resetCurrentNumber();
    printf("\n" GREEN "Logged out." RESET "\n");
}
void showDialog()
{
    showNumber();

    printf(YELLOW "User Menu:" RESET "\n\t1. Check Balance\n\t2. Recharge\n\t3. Log out\n\t4. Exit\n\n");

    while (1)
    {
        printf("[" MAGENTA "USER" RESET "] Enter your choice: ");
        int select;
        scanf("%d", &select);
        if (select == 0)
        {
            printf(YELLOW "User Menu:" RESET "\n\t1. Check Balance\n\t2. Recharge\n\t3. Log out\n\t4. Exit\n\n");
        }
        else if (select == 1)
        {
            showMinutes();
        }
        else if (select == 2)
        {
            makeRecharge();
        }
        else if (select == 3)
        {
            logOut();
            exit(0);
        }
        else if (select == 4)
        {
            printf(GREEN "Program Closed" RESET "\n");
            exit(0);
        }
        else
        {
            printf(RED "Invalid selection! Please try again later." RESET "\n");
        }
    }
}
int main()
{

    FILE *fptr = fopen("user/number.txt", "r+");
    char number[_PHONE_SIZE];
    fscanf(fptr, "%11s", number);
    if (strcmp(number, "0") == 0)
    {
        // not registered
        printf(YELLOW "Client Side" RESET "\nYou have to register or log in first. Enter phone Number: ");
        char phn[_PHONE_SIZE];
        fgets(phn, _PHONE_SIZE, stdin);
        phn[strcspn(phn, "\n")] = 0;
        if (strlen(phn) != 11)
        {

            printf("%d" RED " Invalid phone number" RESET, strlen(phn));
            return 0;
        }
        fseek(fptr, 0, SEEK_SET);
        fprintf(fptr, "%s", phn);
        fclose(fptr);

        char filepathofuser[100] = "user/pack/";
        strcat(filepathofuser, phn);
        strcat(filepathofuser, ".txt");
        FILE *user_pack = fopen(filepathofuser, "r+");

        if (!user_pack)
        {
            fclose(user_pack);
            FILE *tmpup = fopen(filepathofuser, "w");
            fprintf(user_pack, "%d", 0);
            fclose(user_pack);
            printf("\n\n" GREEN " Registration Successful." RESET "\n\n");
        }
        else
        {
            if (checkifblocked())
            {
                return 0;
            }
            else
            {
                printf("\n\n" GREEN " Welcome back! Logged in successfully." RESET "\n\n");
            }
        }
        // registered now
        showDialog();
    }
    // previous user

    if (checkifblocked())
    {
        return 0;
    }
    else
    {
        showDialog();
    }
}
