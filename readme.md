## CSE 1101 Assignment (1-1)

## How to use?
- `demo.mp4` explains the user interface. [See video](https://youtu.be/2giGPSrm0A0?si=aHWQkktIDZWQXa1A)
- Make sure to compile `admin.c` `client.c` `app.c` before running their respective .exe
- `app.exe` controls the routing for the whole app.
- `system()` function that i have used for routine is OS(windows) specific.
- Or You can simply run `admin.exe` & `client.exe` manually.
- Every file is being used by the programs. `Deleting` or `Changing file` will make the program unusable.

## Resources

- In `<stdlib.h>` there is a function called `system()`. It is used to execute an operating system command specified by the string 'command' from a c/c++ program. It returns an integer status indicating the success or failure of the command execution. This function is OS-dependent. We use `system("dir")`. [Source](https://www.tutorialspoint.com/c_standard_library/c_function_system.htm)

- I used some ANSI COLORS to style the terminal output.
  `#define RED "\x1b[31m"` `...` `#define RESET "\x1b[0m"`
  It's very simple to use `printf("\n" GREEN "Colored String" RESET "\n ")`. [Source](https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c)







