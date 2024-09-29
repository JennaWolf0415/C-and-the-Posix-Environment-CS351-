/*Assignment: Project 3 C Program
Creator: Jenna Wolf
Program Name: JennaCFileV3.c
Creation date: 3/16/2024
Version: 4.02.24
Revision: 4
Notes:
- https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program   Used to get the current time and date (edits made)
- https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/   Used to get the host name (edits made to fit my program)
- https://dextutor.com/how-to-get-os-version-in-c/#:~:text=How%20it%20works%3F,version%20of%20the%20operating%20system.  Used to get release and kernal version
- https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c   Used to find how to get the number of cpus
- https://www.quora.com/What-is-the-C-programming-code-that-tells-you-how-much-RAM-your-computer-has  Used to get the total memory left
- https://stackoverflow.com/questions/25500329/allow-only-numbers-to-continue-using-while-scanf   Used to fix error checking and make sure proper input is made
- ChatGPT used for various erros (help with a lot of error checking, help with all proceses, looks for overall problems in program)
- MORE ChatGpt was used for opening and reading/saving data from file. Those functions are pretty much from chat gpt as I was struggling on figuring out how
- to read/write to a file.
- ChatGPT also used to find out how to find the exact line in a file to extract (for modifying the bash script) and how to put it back together
*/

//all packages needed to run this program
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <string.h>

char systemInfo[5][6][256]; //global array variable that holds the systemInfo data

void getTime(int set) {

    //used for date
    time_t timeNow;
    struct tm *tm;

    timeNow = time(NULL);   //sets timeNow to the current date and time

    //makes sure timeNow actually recieved the correct data
    if(timeNow == -1)
        printf("Error: time was not recieved correctly");
    else {
        tm = localtime(&timeNow);   //sets tm to the readable version of timeNow

        //makes sure tm was set to the correct format before outputing the current date and time
        if(tm == NULL)
            printf("Error: time was not recieved correctly");
        else if(set < 0)    //outputs the data if set is less than 0. Otherwise sets it to the correct arary slot.
            printf("Current date and time: %s", asctime(tm));
        else {
            strcpy(systemInfo[set][0], asctime(tm));
            systemInfo[set][0][strcspn(systemInfo[set][0], "\n")] = '\0';
        }
    }
}

void getHost(int set) {

    //used for hostname
    char host[256]; 

    int hostName = gethostname(host, sizeof(host)); //sets hostName to the hosts name using the gethostname function
            
    //makes sure hostName was set to the correct data before outputing the host name
    if(hostName == -1)
        printf("Error: hostname not recieved");
    else if(set < 0)    //outputs the data if set is less than 0. Otherwise sets it to the correct arary slot.
        printf("System's host name: %s\n", host);
    else
        strcpy(systemInfo[set][1], host);
}

void getRelease(int set) {

    //used for release and kernal
    struct utsname data;
    uname(&data);

    //makes sure that the uname function worked and the correct data was returned when geting data.release
    //outputs the release data if the correct information is returned
    if(uname(&data) != 0 || data.release == NULL)
        printf("Error: release data not recieved");
    else if(set < 0)    //outputs the data if set is less than 0. Otherwise sets it to the correct arary slot.
        printf("System's release information: %s\n", data.release);
    else
        strcpy(systemInfo[set][2], data.release);
}

void getKernal(int set) {

    //used for release and kernal
    struct utsname data;
    uname(&data);

    //makes sure that the uname function worked and the correct data was returned when geting data.version
    //outputs the version data if the correct information is returned
    if(uname(&data) != 0 || data.version == NULL)
        printf("Error: kernal version not recieved");
    else if(set < 0)    //outputs the data if set is less than 0. Otherwise sets it to the correct arary slot.
        printf("System's kernal version: %s\n", data.version);
    else
        strcpy(systemInfo[set][3], data.version);
}

void getCPU(int set) {

    //used for finding the amount of cpu's
    long nop = sysconf(_SC_NPROCESSORS_ONLN);

    //makes sure nop was set to at least 1 cpu (you need at least one to run a computer)
    //outputs the CPu data if the correct information is returned
    if(nop < 1)
        printf("Error: Number of CPU/Cores not recieved");
    else if(set < 0)    //outputs the data if set is less than 0. Otherwise sets it to the correct arary slot.
        printf("Number of CPU and processing cores: %lu\n", nop);
    else
        snprintf(systemInfo[set][4], 256, "%lu", nop);

}

void getMemory(int set) {

    //used for find the total amount of RAM
    long totalmem = (sysconf(_SC_PHYS_PAGES)) * (sysconf(_SC_PAGE_SIZE)) / (1024 * 1024);

    //makes sure both values used had correct data returned before outputing the memory data
    if( (sysconf(_SC_PHYS_PAGES)) == -1 || (sysconf(_SC_PAGE_SIZE)) == -1)
        printf("Error: Total System Memory not recieved");
    else if(set < 0)    //outputs the data if set is less than 0. Otherwise sets it to the correct arary slot.
        printf("Total System Memory (RAM):  %ld MB\n", totalmem);
    else
        snprintf(systemInfo[set][5], 256, "%ld", totalmem);
}

void bash() {
    char edit = '\0';   //creates the edit character and sets it to NULL

    //asks for input from the user on weather they want to edit the bash script or not.
    //makes sure that a proper input is made for this
    for ( int ch; (ch = getchar()) != '\n' && ch != EOF; ) { }
    puts("Would you like to edit the speed of the pings in the bash script? (y or n): ");
    while(scanf(" %c", &edit) != 1 || (edit != 'y' && edit != 'n')) {
            printf("ERROR: You made a wrong input. Please enter a proper character. Either 'y' or 'n': ");
            char t;
            while ((t = getchar()) != '\n' && t != EOF);
            edit = '\0';
    }
    puts("");

    //enters the if statement if the user selected yes
    if(edit == 'y') {
        int speed = 0;          //holds the speed data. This is the varaible that will change the bash script
        char temp[8000];        //holds the temp data. This variable holds the file data when opened
        char remaining[6000];   //holds the remaining data. This vairable holds the remaining data after speed is changed
        char before[10];        //holds the before data. This variable holds the data before it is changed
        char after[10];         //holds the after data. This variable holds the data after it is changed

        //creates the file and opens the bash script in a readble format. errors out if the file fails to open
        FILE *file;
        file = fopen("bashScript.sh", "r");
        if(file == NULL) {
            printf("ERROR: File was unable to open. Please try again!\n");
            return;
        }

        //reads in the information from the file before closing it
        fread(temp, sizeof(char), sizeof(temp), file);
        fclose(file);

        //creates the position character pointer that finds and holds the position of the variable being changed.
        //errors out if the variable isn't found.
        char *position = strstr(temp, "speed=");
        if(position == NULL) {
            printf("ERROR: position came back null. Line in script not found. Please try again!\n");
            return;
        }

        strcpy(before, position);               //makes a copy of the current speed variable before the change
        before[strlen("speed=") + 2] = '\0';    //sets the end of the array to a NULL character
        position += strlen("speed=");           //adds the length of speed to position so the value of speed can be changed

        //tells the user what they must enter
        printf("Enter the speed you want the pings to run at in the bash script\n");
        printf("(must be between 20 and 99):\n");

        //takes in the speed value. Error checking in place to make sure a proper input is made
        while(scanf("%d", &speed) != 1 || speed > 99 || speed < 20 ) {
                printf("ERROR: You made a wrong input. Please enter a proper number. It should be between 20 and 99: ");
                for ( int ch; (ch = getchar()) != '\n' && ch != EOF; ) { }
        }
        puts("");

        strcpy(remaining, (position + 2));      //copies the remaining information after speed is changed into the remaining array
        sprintf(position, "%d", speed);         //sets the speed into the position pointer
        strcpy(after, position - strlen("speed=")); //makes a copy of the new speed variable after the change

        //creates the positionTwo pointer that finds and holds the position of the final line of code in the script.
        //errors out if the line isn't found.
        char *positionTwo = strstr(remaining, "final goodbye to the user");
        if(positionTwo == NULL) {
            printf("ERROR: position came back null. Line in script not found. Please try again!\n");
            return;
        }
        positionTwo += strlen("final goodbye to the user"); //adds the length of the string to positionTwo 
        int index = (int)(positionTwo - remaining);         //sets index to the second part of the array
        for(int i = index; i < 6000; i++)                   //empties out all remaining characters in the array (in case of werid characters)
            remaining[i] = '\0';
        
        //opens the file again in a writeable format. Errors out if there is a problem opening it.
        file = fopen("bashScript.sh", "w");
        if(file == NULL) {
           printf("ERROR: File was unable to open. Please try again!\n");
            return;
        }

        //writes temp and remaining (the new bash script) into the file before closing it
        fwrite(temp, sizeof(char), strlen(temp), file);
        fwrite(remaining, sizeof(char), strlen(remaining), file);
        fclose(file);

        //resets edit before asking the user if they would like to see the changes to the speed variable in the script.
        //error checking in place to make sure a proper input is made
        edit = '\0';
        printf("Would you like to see the changes in the script? (y or n): ");
        while(scanf(" %c", &edit) != 1 || (edit != 'y' && edit != 'n')) {
            printf("ERROR: You made a wrong input. Please enter a proper character. Either 'y' or 'n': ");
            char t;
            while ((t = getchar()) != '\n' && t != EOF);
            edit = '\0';
        }
        puts("");

        //outputs the information if the user asked for it
        if(edit == 'y') {
            printf("Before: %s \n", before);
            sleep(1);
            printf("After: %s \n", after);
            sleep(1);
        }

    }

    system("./bashScript.sh");  //runs the bash script
}

void getInfo() {
    //creates the file variable and sets it to the saveData file in a read format
    FILE *file;
    file = fopen("saveData.txt", "r");

    //if the file did not open, it gives an error, creates a new textfile in a writable format, and ends the function
    if(file == NULL) {
        printf("ERROR: File was unable to open/does not exist. Creating new text file now!\n");
        file = fopen("saveData.txt", "w");
        return;
    }

    //reads all information from the text file into the global systemInfo array. Gets rid of any endline variables
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 6; j++) {
            fgets(systemInfo[i][j], 256, file);
            systemInfo[i][j][strcspn(systemInfo[i][j], "\n")] = '\0';
        }
    }
}

void saveInfo() {
    //creates the file variable and sets it to the saveData file in a write format
    FILE *file;
    file = fopen("saveData.txt", "w");

    //if the file did not open, it gives an error and ends the function
    if(file == NULL) {
        printf("ERROR: File was unable to open. Please try again!\n");
        return;
    }

    //writes all information from the global systemInfo array into the textfile.
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%s\n", systemInfo[i][j]);
        }
    }

    fclose(file);   //closes the file at the end of the program
}

int main(void) {
    int choice = 0; //holds the choice data
    int arr = 0;    //holds the arr data

    getInfo();  //calls the getInfo function

    //says hello to the user
    puts("Hello! Welcome to the program!");
    sleep(1);

    //lets the user know what slots currently have data
    for(int i = 0; i < 5; i++) {
        if(systemInfo[i][0][0])
            printf("Save slot %d currently has data.\n", i + 1);
    }
    sleep(1);

    do {
        //Menu that tells the user their options
        puts("-------------------------------------------------------------------");
        puts("Choose what data you wish to display (enter the number for your choice):");
        puts("1.Date and time");
        puts("2.System's host name");
        puts("3.System's release information");
        puts("4.System's kernal version");
        puts("5.Number of CPU and processing cores");
        puts("6.Total System Memory (RAM)");
        puts("7.Run/Edit Ping Bash Script");
        puts("8.Save current information");
        puts("9.Output saved information");
        puts("10.Clear saved information");
        puts("11.Exit");

        //takes in the users input. Makes sure it is an integer betwwen 1 and 10
        if(scanf("%d", &choice) != 1 || choice > 11 || choice < 1 ) {
            printf("ERROR: You made a wrong input. Please enter a proper number. It should be between 1 and 11.");
            for ( int ch; (ch = getchar()) != '\n' && ch != EOF; ) { }
            choice = 0;
        }

        //if the user chose 8, 9, or 10 as their option, asks for the slot the user would like to access. Makes sure it is between 1-5
        if(choice <= 10 && choice >= 8) {
            puts("Which saved data slot would you like to access? (you have 5 slots)");

            while(scanf("%d", &arr) != 1 || arr > 5 || arr < 1 ) {
                printf("ERROR: You made a wrong input. Please enter a proper number. you must choose 1-5: ");
                for ( int ch; (ch = getchar()) != '\n' && ch != EOF; ) { }
                choice = 0;
            }
                arr--;  //subtracts one from arr (array location numbering)
        }
        puts("");

        //case statement that does actions based on the users choice
        switch(choice) {
            case 1: getTime(-1); break;     //shows the user the time and date
            case 2: getHost(-1); break;     //shows the user the host name
            case 3: getRelease(-1); break;  //shows the user the release data
            case 4: getKernal(-1); break;   //shows the user the kernal information
            case 5: getCPU(-1); break;      //shows the user the cpu information
            case 6: getMemory(-1); break;   //shows the user the memory data
            case 7: bash(); break;          //calls and starts the bash script
            case 8: getTime(arr); getHost(arr);
                    getRelease(arr); getKernal(arr);        //calls each function using the save slot the user entered. Saves all data from each function.
                    getCPU(arr); getMemory(arr); break;
            case 9: if(!systemInfo[arr][0][0]) {    //makes sure there is information in the save slot before outputing data.
                        puts("There is currently no information in this save slot");
                        break;
                    }   //outputs save slot data if there is information saved to it.
                    printf("Here is the information you have saved: \n");
                    printf("Date and time: %s\n", systemInfo[arr][0]);
                    printf("System's host name: %s\n", systemInfo[arr][1]);
                    printf("System's release information: %s\n", systemInfo[arr][2]); 
                    printf("System's kernal version: %s\n", systemInfo[arr][3]); 
                    printf("Number of CPU and processing cores: %s\n", systemInfo[arr][4]);
                    printf("Total System Memory (RAM): %s MB\n", systemInfo[arr][5]); break;
            case 10: if(!systemInfo[arr][0][0]) {   //makes sure the slot is not already empty before clearing it
                        puts("This slot is already empty");
                        break;
                    }   //clears the slot if empty
                    for(int i = 0; i < 6; i++) {
                        for(int j = 0; j < 256; j++)
                            systemInfo[arr][i][j] = '\0';
                    }  
                    puts("Slot is now cleared!");
                    break;
                    
        }
        
        puts("");
        sleep(1);
    }while(choice != 11);   //loop goes until 11 (exit) is entered

    saveInfo(); //calls the saveInfo function

    return 0;
}

