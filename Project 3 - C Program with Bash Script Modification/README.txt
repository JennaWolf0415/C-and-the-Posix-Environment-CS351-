Name: Jenna Wolf
Assignment: Project 3 C Program
Bash script: bashScript.sh
Program Name: JennaCFileV3.c
Creation date: 3/16/2024
Version: 4.02.24
Revision number: 4

Notes:
1. https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program                                                                        Used to get the current time and date (edits made)
2. https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/             Used to get the host name (edits made to fit my program)
3. https://dextutor.com/how-to-get-os-version-in-cC/#:~:text=How%20it%20works%3F,version%20of%20the%20operating%20system.               Used to get release and kernal version
4. https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c                                                                            Used to find how to get the number of cpus
5. https://www.quora.com/What-is-the-C-programming-code-that-tells-you-how-much-RAM-your-computer-has                                                                   Used to get the total memory left
6. https://stackoverflow.com/questions/25500329/allow-only-numbers-to-continue-using-while-scanf                                                                        Used to fix error checking and make sure proper input is made
7. ChatGPT used for various erros (help with error checking, help with all proceses, looks for overall problems in program)
8.MORE ChatGpt was used for opening and reading/saving data from file. Those functions are pretty much from chat gpt as I was struggling on figuring out how to read/write to a file.
9. ChatGPT also used to find out how to find the exact line in a file to extract (for modifying the bash script) and how to put it back together

purpose: This program works to display system information to the user using the c programing language. It also includes an array and a bash script that both deal with system information or manipulation.

functionality: This program has 11 options to choose from
1. Retrieve the current date and time and dispaly it
2. Retrieve the host name and dispaly it
3. Retrieve the system's release information and display it
4. Retrieve the system's kernal version and dispaly it
5. Retrieve the number of cpu's/cores on the system and dispaly it
6. Retrieve the total system memory (RAM) and display it
7. Run the bash script. Also used to edit the speed parameter in the bash script.
8. save all system information to a "save slot" on the array
9. display all system information from a slot in the array
10. erase all system information from a slot in the array
11. Exit the program
This program also uses error checking to take in proper inputs and display error messages when code doesn't work
The array works to keep all system information saved to it both inside and outside the program. Array information is saved to a text file when program ends and retrieves that information again when program is started.
The 7th option on the menu allows you to edit the bash script. This works by opening and reading in the information from the script, making the edit based on the users input, and then writing back to the bash script. This program allows the user to edit the speed at which a ping runs on the script.

The bash script has 5 options on its menu
1. Add a ping (allow user to see connection to internet)
2. Remove a ping (stop a ping that is currently going on)
3. View all pings currently going on
4. View the last line of a ping textfile (all pings are saved to textfiles for users use)
5. end the program

important information:
Debian Linux - This script is to be ran on a linux distributor. It should be able to run on most Debian based ones.

How To Start:
1. unzip your file into the directory/folder you wish to use (Suggested folder would be documents)
2. Open your terminal
3. use the cd and ls commands to enter the directory with the file (ex: cd Documents) (use ls to see if the file is in your current directory. if the file JennaCFile.cpp is not there, then you are not in the correct directory).
4. type in the command " gcc JennaCFileV3.c -o JennaCFile " to create a runnable c program. You can also name it something else if you wish to run it another way.
5. type in ./JennaCFile (or ./name you gave the code) to run the program

IF THE C CODE RETURNS PERMISION DENIED WHEN TRYING TO RUN IT
1. exit the program if it is still running
2. enter "chmod +x bashScript.sh"
3. Start the script again like above
