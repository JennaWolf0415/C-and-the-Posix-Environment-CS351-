Name: Jenna Wolf
Assignment: Project 1 Linux C Program
Program Name: JennaCFile.cpp
Creation date: 3/16/2024
Version: 3.16.24
Revision number: 1

Notes:
1. https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program                                                                        Used to get the current time and date (edits made)
2. https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/             Used to get the host name (edits made to fit my program)
3. https://dextutor.com/how-to-get-os-version-in-cC/#:~:text=How%20it%20works%3F,version%20of%20the%20operating%20system.               Used to get release and kernal version
4. https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c                                                                            Used to find how to get the number of cpus
5. https://www.quora.com/What-is-the-C-programming-code-that-tells-you-how-much-RAM-your-computer-has                                                                   Used to get the total memory left
6. https://stackoverflow.com/questions/25500329/allow-only-numbers-to-continue-using-while-scanf                                                                        Used to fix error checking and make sure proper input is made
7. ChatGPT used for various erros (help with error checking, help with all proceses, looks for overall problems in program)

purpose: This program works to display system information to the user using the c programing language.

functionality: This program has 7 options to choose from
1. Retrieve the current date and time and dispaly it
2. Retrieve the host name and dispaly it
3. Retrieve the system's release information and display it
4. Retrieve the system's kernal version and dispaly it
5. Retrieve the number of cpu's/cores on the system and dispaly it
6. Retrieve the total system memory (RAM) and display it
7. Exit the program
This program also uses error checking to take in proper inputs and display error messages when code doesn't work

important information:
Debian Linux - This script is to be ran on a linux distributor. It should be able to run on most Debian based ones.

How To Start:
1. unzip your file into the directory/folder you wish to use (Suggested folder would be documents)
2. Open your terminal
3. use the cd and ls commands to enter the directory with the file (ex: cd Documents) (use ls to see if the file is in your current directory. if the file JennaCFile.cpp is not there, then you are not in the correct directory).
4. type in the command " gcc JennaCFile.c -o JennaCFile " to create a runnable c program.
5. type in ./JennaCFile to run the program
