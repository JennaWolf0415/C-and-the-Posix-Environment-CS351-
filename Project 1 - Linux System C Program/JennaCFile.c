/*Assignment: Project 1 Linux C Program
Creator: Jenna Wolf
Program Name: JennaCFile.cpp
Creation date: 3/16/2024
Version: 3.16.24
Revision: 1
Notes:
- https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program   Used to get the current time and date (edits made)
- https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/   Used to get the host name (edits made to fit my program)
- https://dextutor.com/how-to-get-os-version-in-c/#:~:text=How%20it%20works%3F,version%20of%20the%20operating%20system.  Used to get release and kernal version
- https://stackoverflow.com/questions/4586405/how-to-get-the-number-of-cpus-in-linux-using-c   Used to find how to get the number of cpus
- https://www.quora.com/What-is-the-C-programming-code-that-tells-you-how-much-RAM-your-computer-has  Used to get the total memory left
- https://stackoverflow.com/questions/25500329/allow-only-numbers-to-continue-using-while-scanf   Used to fix error checking and make sure proper input is made
- ChatGPT used for various erros (help with a lot of error checking, help with all proceses, looks for overall problems in program)
*/
//all packages needed to run this program
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>

int main(void) {
    int choice; //holds the choice data

    //used for date
    time_t timeNow;
    struct tm *tm;

    //used for hostname
    char host[256]; 

    //used for release and kernal
    struct utsname data;
    uname(&data);

    //used for finding the amount of cpu's
    long nop = sysconf(_SC_NPROCESSORS_ONLN);

    //used for find the total amount of RAM
    long totalmem = (sysconf(_SC_PHYS_PAGES)) * (sysconf(_SC_PAGE_SIZE)) / (1024 * 1024);

    //says hello to the user
    puts("Hello! Welcome to the program!");
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
        puts("7.Exit");

        //takes in the users input. Makes sure it is an integer betwwen 1 and 7
        if(scanf("%d", &choice) != 1 || choice > 7 || choice < 1 ) {
            printf("ERROR: Please enter a proper number!");
            for ( int ch; (ch = getchar()) != EOF && ch != '\n'; ) { }
            choice = 0;
        }
        puts("");

        //enters and dispalys the right information based on the users input
        if(choice == 1) {   //displays the time and date

            timeNow = time(NULL);   //sets timeNow to the current date and time

            //makes sure timeNow actually recieved the correct data
            if(timeNow == -1)
                printf("Error: time was not recieved correctly");
            else {
                tm = localtime(&timeNow);   //sets tm to the readable version of timeNow

                //makes sure tm was set to the correct format before outputing the current date and time
                if(tm == NULL)
                    printf("Error: time was not recieved correctly");
                else
                    printf("Current data and time: %s", asctime(tm));
            }

        }
        else if(choice == 2) {  //displays the hosts name

            int hostName = gethostname(host, sizeof(host)); //sets hostName to the hosts name using the gethostname function
            
            //makes sure hostName was set to the correct data before outputing the host name
            if(hostName == -1)
                printf("Error: hostname not recieved");
            else
                printf("System's host name: %s\n", host);

        }
        else if(choice == 3) {  //displays the release information

            //makes sure that the uname function worked and the correct data was returned when geting data.release
            //outputs the release data if the correct information is returned
            if(uname(&data) != 0 || data.release == NULL)
                printf("Error: release data not recieved");
            else
                printf("System's release information: %s\n", data.release);

        }
        else if(choice == 4) {  //displays the version information

            //makes sure that the uname function worked and the correct data was returned when geting data.version
            //outputs the version data if the correct information is returned
            if(uname(&data) != 0 || data.version == NULL)
                printf("Error: kernal version not recieved");
            else
                printf("System's kernal version: %s\n", data.version);

        }
        else if(choice == 5) {  //dispalys the number of cpus and processing cores

            //makes sure nop was set to at least 1 cpu (you need at least one to run a computer)
            //outputs the CPu data if the correct information is returned
            if(nop < 1)
                printf("Error: Number of CPU/Cores not recieved");
            else
                printf("Number of CPU and processing cores: %lu\n", nop);

        }
        else if(choice == 6) {  //displays the system memory left

            //makes sure both values used had correct data returned before outputing the memory data
            if( (sysconf(_SC_PHYS_PAGES)) == -1 || (sysconf(_SC_PAGE_SIZE)) == -1)
                printf("Error: Total System Memory not recieved");
            else
                printf("Total System Memory (RAM):  %ld MB\n", totalmem);

        }
        puts("");
        sleep(1);
    }while(choice != 7);

    return 0;
}
