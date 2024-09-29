Author: Jenna Wolf
Original code created by: Sam Brucker
Version: 2.1
Class: C and the posix enviornment
Date: 2/11/2024
***Chat GPT was used to fix error checking on alpnum values***

This code is a simple program that interacts with the user by making a directory if specified and then displaying cpu or running process and exporting them to text files if directed. It starts by asking if a directory needs to be made or not and lets the user name the directory. Option 1 lets you see all running processes, option 2 lets you see CPU usuage. the program can ethen xport either of these two data feilds into a text file with the name the user provides. Error checking is used to only let proper inputs be made.

Requirements:
Debian Linux - this program should be ran on a linux distros. It should work on most of them based on debian.
sysstat - this package allows for data to be seen. If it is not already installed, the program will install the package automatically the first time it is ran.

How to use:
1. unzip your script into the directory/file you wish to use (Documents is suggested)
2. cd into the directory with the script by using the command " cd Directoryname " (ex: cd Documents/'JWPeerReview' )
3. type "sudo chmod +x run.sh" to get premission to run the script. Add your password if required. If this does not work, try "chmod +x run.sh"
4. type "./run.sh" and hit enter to run the script.
***Ifsysstat needs to be installed, hit tab then enter to pass the restart services screen. This pops up once the install completes***
5. interact with the program
