Creator: Jenna Wolf
Script Name: EnhanceLab.sh
Version: 02172024
Date last edited: 2/25/2024
Class: C and the posix enviorment
Instructor: Robbie Davis

Purpose: This program was made for the Enhanced Linux Interaction Script. This is a simple script that allows the user to start processes/ping, kill those processes/ping, see what jobs they are currently running, and view the last line of a ping file (show last ping). It is simple for now, as it can only do 2 types of ping, but it works to do process management and is focused on user interaction/error checking

functionality:
1. Start process: This section allows user to start a process (in this case, a ping) and store the information of that ping into a text file. It makes sure to check to see if a text file of that name does not already exist before making it/overiding it if the user wishes to do so.
2. kill process: This allows the usr to pick a process to kill from the job list. It displays the job and allows them to pick a PID before terminating that job
3. View jobs: This simply shows the user the jobs list, which tells them what they are currently running.
4: Look at last line of ping file: The allows the user to view the last line of a textfile within the pingData folder. When pings are made, this is the folder their text data automatically goes into. If a wrong name is entered, it tells the user

requirements: 
Debian Linux - This script is to be ran on a linux distributor. It should be able to run on most Debian based ones.

to use:
1. unzip the file into any directory/file you wish to user (I suggest Documents)
2. Open up your command line interface
3. cd into the directory the script is located in. To make sure you are in the right directory, type in ls and the script should be listed there (EnhanceLab.sh). Example: cd Documents/JWEnhanceLab
3. type in " sudo chmod +x EnhanceLab.sh ". Type in your password if prompted. If this does not work, try " chmod +x EnhanceLab.sh ". Make sure you are in the correct directory.
5. To start the program, type in " bash EnhanceLab.sh " (this is currently the only way for it to run, as ./EnhanceLab.sh is not currently working).
