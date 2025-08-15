#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// console colors
// collected from https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

int totalTransactions = 0;
int trans40 = 0;
int trans60 = 0;
int trans100 = 0;

int _CARD_SIZE = 32;
int _LINE_SIZE = 42;
int _PHONE_SIZE = 12;
int _TIME_SIZE = 20;

// command 404 master reset
void _RESET(char path[], char val)
{
    FILE *fptr = fopen(path, "w");
    if (isdigit(val))
    {
        fprintf(fptr, "%d", 0);
    }
    fclose(fptr);
}
void _MASTER_RESET()
{
    // setting all files as 0
    _RESET("user/number.txt", '0');
    _RESET("admin/balance.txt", '0');
    _RESET("admin/blocked.txt", '0');
    _RESET("admin/sold/40.txt", '0');
    _RESET("admin/sold/60.txt", '0');
    _RESET("admin/sold/100.txt", '0');
    // setting all files empty
    _RESET("FreshCards/40.txt", 'e');
    _RESET("FreshCards/60.txt", 'e');
    _RESET("FreshCards/100.txt", 'e');
    _RESET("UsedCards/40.txt", 'e');
    _RESET("UsedCards/60.txt", 'e');
    _RESET("UsedCards/100.txt", 'e');

#ifdef _WIN32
    system("del /Q user\\pack\\*"); // Windows
    system("del /Q user\\pass\\*"); // Windows
#else
    system("rm -f user/pack/*"); // Linux/macOS
    system("rm -f user/pass/*"); // Linux/macOS
#endif

    printf("\n" GREEN "Successfully cleared all data." RESET "\n");
}

void generateCardAndAppend(int type)
{
    /*
    This function generates 20 random numbers to form a card.
    Then based on the card type 40 minutes,60 minutes, 100 minutes.
    It appends generated card to the specified folder

    */
    int card_number[20];
    int firstNum = (rand() % (9 - 2 + 1)) + 2; //  2-9 random number
    card_number[0] = firstNum;
    for (int i = 1; i < 20; i++)
    {
        card_number[i] = (rand() % (9 - 0 + 1)) + 0; // random number 0-9
    }
    char filename[6];
    sprintf(filename, "%d", type);
    char filepath[100] = "FreshCards/"; // parent folder
    strcat(filepath, filename);         // the card type
    strcat(filepath, ".txt");
    // printf("%s", filepath);

    FILE *fptr = fopen(filepath, "a");
    for (int i = 0; i < 20; i++)
    {
        fprintf(fptr, "%d", card_number[i]);
    }
    fprintf(fptr, "\n"); // card ended
    fclose(fptr);
}

void cardDialog()
{

    printf("Enter the amount of cards: ");
    int amount;
    int typop1 = scanf("%d", &amount);
    if (typop1 == 0)
    {
        printf("\n" RED "Sorry please enter an integer type data" RESET "\n");
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        amount = 0;
    }

    printf("\n Enter the type of card (40/60/100): ");
    int type;
    int typop2 = scanf("%d", &type);
    if (typop2 == 0)
    {
        printf("\n" RED "Sorry please enter an integer type data" RESET "\n");
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        type = 40;
    }

    for (int i = 0; i < amount; i++)
    {
        generateCardAndAppend(type);
    }
    printf("\n\n\t" GREEN "Successfully Created %d cards of %d mins" RESET "\n\n", amount, type);
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

void deleteCard(int min)
{
    printf("Enter card number: ");
    char entered_card[_CARD_SIZE];
    getchar();
    fgets(entered_card, _CARD_SIZE, stdin);
    entered_card[strcspn(entered_card, "\n")] = 0;

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

        if (strcmp(entered_card, real_card) == 0)
        {
            printf(GREEN "Card Found! at line %d" RESET "\n", lineNum + 1);

            // remove the card
            found = 1;
            break;
        }
        lineNum++;
    }

    if (!found)
    {
        printf(RED "Card does not exist!" RESET "\n");
        return;
    }

    fclose(fptr);
    removeCard(min, lineNum + 1);
    printf(GREEN "Card Deleted successfully" RESET "\n");
}
void deleteDialog()
{
    printf("What type of card do you want to delete?\n\t1. 40min\n\t2. 60min\n\t3. 100min\n\nEnter an option: ");
    int op;
    int typop = scanf("%d", &op);
    if (typop == 0)
    {
        printf("\n" RED "Sorry please enter an integer type data" RESET "\n");
        char ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ; // clear buffer
    }
    if (op == 1)
    {
        deleteCard(40);
    }
    else if (op == 2)
    {
        deleteCard(60);
    }
    else if (op == 3)
    {
        deleteCard(100);
    }
    else
    {
        printf(RED "Invalid Selection" RESET "\n");
    }
}

void unblock(int lineNum)
{

    FILE *realfile = fopen("admin/blocked.txt", "r");
    FILE *tmpfile = fopen("admin/temp.txt", "w");

    char phn[_PHONE_SIZE];
    int check_line = 1;

    while (fgets(phn, _PHONE_SIZE, realfile) != NULL)
    {
        if (strlen(phn) <= 1)
            continue;
        phn[strcspn(phn, "\n")] = 0;

        if (check_line != lineNum)
        {
            fprintf(tmpfile, "%s\n", phn);
        }
        check_line++;
    }
    fclose(realfile);
    fclose(tmpfile);

    if (remove("admin/blocked.txt") != 0)
    {
        perror("Error deleting original file");
        return;
    }

    // Rename temp file
    if (rename("admin/temp.txt", "admin/blocked.txt") != 0)
    {
        perror("Error renaming temp file");
        return;
    }
}

void showBlockList()
{
    printf(YELLOW "Block List: " RESET "\n\n");
    int count = 0;
    FILE *fptr = fopen("admin/blocked.txt", "r");
    char phn[_PHONE_SIZE];
    while (fgets(phn, _PHONE_SIZE, fptr) != NULL)
    {
        if (strlen(phn) <= 1)
            continue;
        phn[strcspn(phn, "\n")] = 0;
        printf("%s\n", phn);
        count++;
    }
    if (count > 0)
        printf(GREEN "Total %d numbers found in the list." RESET "\n", count);
    else
        printf(GREEN "List is Empty" RESET "\n");

    fclose(fptr);
}
void unlockAccount()
{

    showBlockList();

    printf("Enter user Number: ");
    char user_phn[_PHONE_SIZE];
    getchar();
    fgets(user_phn, _PHONE_SIZE, stdin);
    user_phn[strcspn(user_phn, "\n")] = 0;

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
            printf("User Found! at line %d\n", lineNum + 1);

            // remove the card
            found = 1;
            break;
        }
        lineNum++;
    }
    fclose(fptr);

    if (found)
    {
        unblock(lineNum + 1);
        printf(GREEN "User unblocked successfully" RESET "\n");
    }
    else
    {
        printf(RED "The number is not in the blocked list" RESET "\n");
    }
}

void showSoldCards(int min)
{
    char filename[6];
    sprintf(filename, "%d", min);
    char filepath[100] = "admin/sold/"; // parent folder
    strcat(filepath, filename);         // the card type
    strcat(filepath, ".txt");

    FILE *fptr = fopen(filepath, "r");

    char sold_count[6];
    fscanf(fptr, "%5s", sold_count);

    printf("\t %d Minutes: %s times\t", min, sold_count);
}
void showSoldCardsInTaka(int min)
{
    char filename[6];
    sprintf(filename, "%d", min);
    char filepath[100] = "admin/sold/"; // parent folder
    strcat(filepath, filename);         // the card type
    strcat(filepath, ".txt");

    FILE *fptr = fopen(filepath, "r");

    char sold_count[6];
    fscanf(fptr, "%5s", sold_count);
    int amount;
    if (min == 40)
        amount = 50;
    else if (min == 60)
        amount = 70;
    else
        amount = 120;

    amount *= atoi(sold_count);

    printf("\t %d Minutes: %d Taka\t", min, amount);
}

void showStock(int min)
{
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
        lineNum++;
    }

    fclose(fptr);

    printf("\t %d is available : %d\t", min, lineNum);
}
void showAdminBalance()
{
    FILE *fptr = fopen("admin/balance.txt", "r");
    char bal[12];
    fscanf(fptr, "%11s", bal);

    printf("\t " GREEN "Total balance %s Taka" RESET "\n", bal);
}
void showStatistics()
{
    printf("\n" YELLOW "Statistics: " RESET "\n");
    showSoldCards(40);
    showSoldCards(60);
    showSoldCards(100);
    printf("\n");
    showStock(40);
    showStock(60);
    showStock(100);
    printf("\n");
    showSoldCardsInTaka(40);
    showSoldCardsInTaka(60);
    showSoldCardsInTaka(100);
    printf("\n\n");
    showAdminBalance();
}

void formatDate(char stamp[])
{
    // ref https://www.epochconverter.com/
    /*

    The Unix epoch (or Unix time or POSIX time or Unix timestamp) is the number of seconds that have elapsed since January 1, 1970 (midnight UTC/GMT), not counting leap seconds (in ISO 8601: 1970-01-01T00:00:00Z).
    */
    // int stamp_int = atoi(stamp);
    // int year_passed = stamp_int / 31556926;
    // stamp_int %= 31556926;
    // int months = stamp_int / 2629743;
    // stamp_int %= 2629743;

    // int days = stamp_int / 86400;
    // stamp_int %= 86400;

    // int cur_year = 1970 + year_passed;
    // int cur_mon = 1 + months;

    // int cur_day = 1 + days;

    // int hrs = stamp_int / 3600;
    // stamp_int %= 3600;
    // int mns = stamp_int / 60;
    // stamp_int %= 60;

    // printf("%02d-%02d-%04d %02d:%02d:%02d\n", cur_day, cur_mon, cur_year, hrs, mns, stamp_int);
    // My idea has some glitch leap year and month violation 31 30 31 30,
    // using outer function
    time_t rawtime = (time_t)atol(stamp);
    rawtime += 6 * 3600; // gmt
    struct tm *timeinfo = gmtime(&rawtime);

    if (timeinfo == NULL)
    {
        printf("Invalid time conversion\n");
        return;
    }

    printf("Date: %02d-%02d-%04d \nTime: %02d:%02d:%02d\n",
           timeinfo->tm_mday,
           timeinfo->tm_mon + 1,
           timeinfo->tm_year + 1900,
           timeinfo->tm_hour,
           timeinfo->tm_min,
           timeinfo->tm_sec);
}
void showTransaction(int min)
{

    char filename[6];
    sprintf(filename, "%d", min);
    char filepath[] = "UsedCards/"; // parent folder
    strcat(filepath, filename);     // the card type
    strcat(filepath, ".txt");

    FILE *fptr = fopen(filepath, "r");
    char line[44];
    char card_num[22], timestamp_str[20], phone[12];
    int ifa = 1;
    while (fgets(line, 44, fptr) != NULL)
    {
        int n = sscanf(line, "%21s %19s %11s", card_num, timestamp_str, phone);

        if (n == 3)
        {
            if (min == 40)
                trans40++;
            else if (min == 60)
                trans60++;
            else
                trans100++;
            totalTransactions++;
            if (ifa)
            {
                printf("\n" CYAN "For %d minutes pack:" RESET " \n", min);
                ifa = 0;
            }
            printf("\n\nCard Number: ");
            for (int i = 0; i < 20; i++)
            {
                printf("%c", card_num[i]);
                if ((i + 1) % 4 == 0)
                {
                    printf(" ");
                }
            }
            printf("\n");

            formatDate(timestamp_str);
            printf("Phone: %s\n", phone);
        }
    }
}

void showHistory()
{
    printf(YELLOW "Transaction History: " RESET "\n");
    showTransaction(40);
    showTransaction(60);
    showTransaction(100);
    printf("\n");
    printf("\nTotal %02d transactions found for all packs.\t 40 mins: %02d\t 60 mins: %02d\t 100 mins: %02d\n", totalTransactions, trans40, trans60, trans100);
    totalTransactions = 0; // setting it back
    trans40 = 0;
    trans60 = 0;
    trans100 = 0;
}

void showUserTransaction(char phn[], int min)
{

    char filename[6];
    sprintf(filename, "%d", min);
    char filepath[] = "Usedcards/"; // parent folder
    strcat(filepath, filename);     // the card type
    strcat(filepath, ".txt");

    FILE *fptr = fopen(filepath, "r");
    char line[44];

    char file_num[11];
    char card_num[21];
    char timestamp_str[19];
    int ifa = 1;
    while (fgets(line, 44, fptr) != NULL)
    {
        if (strlen(line) <= 1)
            continue;
        if (ifa)
        {
            printf("\n\t" CYAN "Transactions of %s for %d minutes pack:" RESET " \n", phn, min);
            ifa = 0;
        }
        line[strcspn(line, "\n")] = 0;
        // printf("user card: %s\n", real_card);

        sscanf(line, "%21s %19s %11s", card_num, timestamp_str, file_num);

        if (strcmp(file_num, phn) == 0)
        {
            // one matched transaction for that number
            totalTransactions++;
            printf("\nCard Number: ");
            for (int i = 0; i < 20; i++)
            {
                printf("%c", card_num[i]);
                if ((i + 1) % 4 == 0)
                {
                    printf(" ");
                }
            }
            printf("\n");

            formatDate(timestamp_str);
            printf("\n");
            if (min == 40)
                trans40++;
            else if (min == 60)
                trans60++;
            else
                trans100++;

            // printf("Phone: %s\n", file_num);
        }
    }

    fclose(fptr);
}
void searchUserTransaction()
{
    printf("Enter user number: ");
    char phn[_PHONE_SIZE];
    getchar();
    fgets(phn, _PHONE_SIZE, stdin);
    showUserTransaction(phn, 40);
    showUserTransaction(phn, 60);
    showUserTransaction(phn, 100);
    printf("\nTotal %02d transactions found for " GREEN "%s" RESET " for all packs\n\t 40 mins: %02d\n\t 60 mins: %02d\n\t 100 mins: %02d\n", totalTransactions, phn, trans40, trans60, trans100);

    totalTransactions = 0; // setting it back
    trans40 = 0;
    trans60 = 0;
    trans100 = 0;
}

int main()
{
    srand(time(NULL));
    printf("\nWelcome to Admin Panel!\n\n" YELLOW "The Admin Menu:" RESET "\n\t0. Menu\n\t1. New Card\n\t2. Delete Card\n\t3. Unlock Account\n\t4. History\n\t5. Statistics\n\t6. Search\n\t7. Exit\n\n");

    while (1)
    {
        printf("[" GREEN "ADMIN" RESET "] Enter your choice: ");
        int op;
        int typop = scanf("%d", &op);
        if (typop == 0)
        {
            printf("\n" RED "Sorry please enter an integer type data!" RESET "\n");
            char ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ; // clear buffer
        }
        if (op == 0)
        {
            printf("\n" YELLOW "The Admin Menu:" RESET "\n\t0. Menu\n\t1. New Card\n\t2. Delete Card\n\t3. Unlock Account\n\t4. History\n\t5. Statistics\n\t6. Search\n\t7. Exit\n\n");
        }
        else if (op == 1)
        {
            // create new cards
            cardDialog();
        }
        else if (op == 2)
        {
            // delete a card
            deleteDialog();
        }
        else if (op == 3)
        {
            // unblock user account
            unlockAccount();
        }
        else if (op == 4)
        {
            // show all packs transaction history
            showHistory();
        }
        else if (op == 5)
        {
            // show overall statistics
            showStatistics();
        }
        else if (op == 6)
        {
            searchUserTransaction();
        }
        else if (op == 7)
        {
            printf(GREEN "Program Closed\n" RESET);
            break;
        }
        else if (op == 404)
        {
            _MASTER_RESET();
            // setting all the values as default.
        }
        else
        {
            printf(RED "Invalid Selection!" RESET);
        }
    }

    return 0;
}
