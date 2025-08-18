## CSE 1101 Assignment (1-1)

## How to use?
- `demo.mp4` explains the user interface. [See video](https://youtu.be/2giGPSrm0A0?si=aHWQkktIDZWQXa1A)
- just compile and run `app.c`
- Admin password is `61770`

## Resources

- I used some ANSI COLORS to style the terminal output.
  `#define RED "\x1b[31m"` `...` `#define RESET "\x1b[0m"`
  It's very simple to use `printf("\n" GREEN "Colored String" RESET "\n ")`. [Source](https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c)

## Folder structure
- It should exactly look like this to make the programs work properly.
- `404` command will `automatically erase/update` the files. We don't need to manually clear them.
- <img width="283" height="761" alt="Image" src="https://github.com/user-attachments/assets/06eca625-c1fe-4243-acfa-f84b92a66128" />

## User Interface
### - `App`<br><img width="390" height="154" alt="Image" src="https://github.com/user-attachments/assets/3c178156-1a21-449b-a009-1e4211a1177a" /><br>
---
### -`Admin Panel`<br><img width="418" height="440" alt="Image" src="https://github.com/user-attachments/assets/0b7433ba-c172-44cd-8e9d-d87f7a6e3cb6" /><br>
   - `0. Menu`<br><img width="415" height="284" alt="Image" src="https://github.com/user-attachments/assets/64d363c9-ae55-4664-8eff-7b77ed15d154" /><br>
   - `1. New Card`<br><img width="677" height="181" alt="Image" src="https://github.com/user-attachments/assets/28aee457-2ed7-40ae-98ca-50892191a8e3" /><br>
   - `2. Delete Card`<br><img width="617" height="270" alt="Image" src="https://github.com/user-attachments/assets/b902704c-a90a-4822-9654-a8b0bfa5c26b" /><br>
   - `3. Unblock Account`<br><img width="564" height="264" alt="Image" src="https://github.com/user-attachments/assets/6ac18dcd-5cbc-4d8d-8cf7-7a056a71b37c" /><br>
   - `4. History`<br><img width="952" height="927" alt="Image" src="https://github.com/user-attachments/assets/ef468735-a0c3-44a7-b025-f72e380ddc91" /><br>
   - `5. Statistics`<br><img width="984" height="193" alt="Image" src="https://github.com/user-attachments/assets/83063a0f-135c-4a78-b068-7c87cca91319" /><br>
   - `6. Search User`<br><img width="695" height="475" alt="Image" src="https://github.com/user-attachments/assets/93761ae2-581d-45e5-b8ea-52364a4a3041" /><br>
   - `7. Exit`<br> will exit the program.
---
### - `User panel`
  - `registration`<br><img width="979" height="414" alt="Image" src="https://github.com/user-attachments/assets/a96871c4-154a-4d13-b05a-fd572ed44a44" /><br>
    - `log in`<br><img width="749" height="488" alt="Image" src="https://github.com/user-attachments/assets/bfcc7c24-8fd1-422e-9fe8-f69ab40b31a8" /><br>
    - `recharge`<br><img width="620" height="309" alt="Image" src="https://github.com/user-attachments/assets/fedf5e90-216d-4a76-9995-d8e6eaa2a6fa" /><br>
     ---
  This project is for educational purpose only.


  # Function Explanations

## Core System Functions
- `_SETUP()`  
  Creates directories and files. Initializes default values. First-time setup.

## Card Management
- `generateCardAndAppend()`  
  Generates random card numbers. Saves to appropriate file.
- `removeCard()`  
  Deletes specific card from FreshCards.
- `deleteCard()`  
  Finds and removes card by number.
- `deleteDialog()`  
  UI for card deletion options.

## Admin Functions
- `unblock()`  
  Removes number from blocked list.
- `showBlockList()`  
  Displays all blocked numbers.
- `unlockAccount()`  
  Unblocks user account.
- `showStatistics()`  
  Displays sales and stock data.
- `showHistory()`  
  Shows all transactions.
- `searchUserTransaction()`  
  Finds transactions by phone number.

## Transaction Processing
- `updateSold()`  
  Increments sold card count.
- `updateAdminBalance()`  
  Updates admin's balance.
- `commitRecharge()`  
  Validates and processes card recharge.

## User Functions
- `showMinutes()`  
  Displays user's remaining minutes.
- `updateBalance()`  
  Updates user's minute balance.
- `isBlocked()`  
  Checks if user is blocked.
- `logOut()`  
  Clears current session.
- `clientPanel()`  
  Main user interface handler.

## Utilities
- `formatDate()`  
  Converts timestamp to readable format.
- `resetCurrentNumber()`  
  Clears current user session.
- `checkIfBlocked()`  
  Verifies if current user is blocked.

## Main Interfaces
- `adminPanel()`  
  Admin control interface.
- `showDialog()`  
  User menu interface.
- `main()`  
  Entry point with role selection.

  

     
















