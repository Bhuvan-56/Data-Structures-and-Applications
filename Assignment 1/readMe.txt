Suppose that your program uses a header file myheader.h and a corresponding C file,
myheader.c

First compile with
gcc -c myheader.c
This creates myheader.o, which is an object file.

Then compile your main file with
gcc main.c myheader.o -o out

Note: If myheader.h or myheader.c changes, then you need to compile both;
when you make changes only to the main.c file, you only need to do the second compilation.