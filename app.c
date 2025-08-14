#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//<stdlib.h> contains a function system() we can run other code's exe files
// through it

// console colors
// collected from https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

int main()
{
    printf(YELLOW "[*] CSE Assignment by BITTO SAHA (2403142)" RESET "\n\nSELECT AN USER:\n\t1. Admin\n\t2. User\n\t3. Exit\n\n");
    while (1)
    {
        printf("[APP] Enter your choice: ");
        int op;
        scanf("%d", &op);

        if (op == 1)
        {
            // admin page
            printf("Enter Admin password: ");
            int password;
            scanf("%d", &password);
            if (password == 61770)
            {
                // logged in
                printf("\n" GREEN "Success!" RESET "\n");
                system("admin.exe");
                printf("\n" GREEN "Getting back to menu..." RESET "\n");
            }
            else
            {

                printf(RED "Sorry authentication failed!\nRestart the app.exe or (Press enter)\n" RESET);
                getch();
            }
        }
        else if (op == 2)
        {
            // client side
            system("client.exe");
            printf("\n" GREEN "Getting back to menu..." RESET "\n");
        }
        else if (op == 3)
        {
            printf("\n\tThanks for using.Press any key to close :)\n\n");
            getch();
        }
        else
        {
            printf(RED "Sorry That option does not exist. Try again later" RESET "\n\n");
        }
    }

    return 0;
}