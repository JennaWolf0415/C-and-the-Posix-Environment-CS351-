#! bin/bash
#Creator: Jenna Wolf
#Version: 02172024
#Description: This program was made for the Enhanced Linux Interaction Script. This is a simple script that allows the user to start processes/ping, kill
# those processes/ping, and see what jobs they are currently running. It is simple for now, as it can only do 2 types of ping, but it works to do
# process management and is focused on user interaction/error checking
#
#Help Used:
#1. Error checking used in LabOne and PeerReview are repeated in this program
#
#2. https://www.digitalocean.com/community/tutorials/how-to-use-bash-s-job-control-to-manage-foreground-and-background-processes
#   https://www.digitalocean.com/community/tutorials/how-to-use-ps-kill-and-nice-to-manage-processes-in-linux
#   Used to learn how to manage processes (create and kill them)
#
#3. ChatGPT was used to fix increment and decrement problems.
#   was also used to fix ping hostname command issues
#   was also used for error checking on file name input and kill job loop
#   was also used a lot with help for killing jobs
#
#4. prompt style for reading in taken from peer review program
#
#5. Netacad used to help with process command

#this is the add processes function that lets the user add a process
function addProcesses {

    #menu that allows user to choose a process to start
    echo " "
    echo "What process would you like to start?"
    echo "1. ping the host IP"
    echo "2. ping web browser (google)"
    read -r -p ": " start

    #error checks to make sure a process was chosen to start
    while [[ ! "$start" =~ ^[1-2]+$ ]] || [ ${#start} != 1 ]; do
        echo "Invalid! pick a number between 1-2!"
        read -r -p ": " start
    done

    #takes in a name for the textfile that holds the ping information:
    echo " "
    echo "Please enter a name for your ping data to be stored in"
    echo "(Name can only be letters and numbers and must be less than 10 characters)"
    read -r -p ": " file

    #make sure proper name is entered
    while [[ ! "$file" =~ ^[[:alnum:]]+$ ]] || [ ${#file} -gt 10 ]; do
        echo "invalid! please entere a proper name!"
        read -r -p ": " file
    done

    #asks user if they want to make a new file if filename is the same as another one.
    if [ -f pingData/"$file.txt" ]; then

        #tells the user what is going on and gets their answer
        echo " "
        echo "A File with this name already exists. Would you like to make a new"
        echo "file with this name and overide the data or cancel the"
        echo "ping and try again? (y or n)"
        read -r -p ": " choice

        #makes sure proper input was entered
        while [ $choice != y ] && [ $choice != n ]; do
            echo "Please enter a proper answer!"
            read -r -p ": " choice
        done
        
        #removes file if y is entered
        if [ $choice = y ]; then
            rm pingData/$file.txt
        fi

        #ends start of ping if n is entered
        if [ $choice = n ]; then
            echo "Okay! cancelling ping! Going back to menu!"
        fi
    fi

    #starts a ping as long as choice is not n
    if [ $choice != n ]; then

        #starts a process based on user input
        case $start in
            1) ping -i 30 "`hostname -i`" > pingData/"$file.txt" &;;
            2) ping -i 30 google.com > pingData/"$file.txt" &;;
        esac

        echo "Ping Created" #lets user know ping was made
        ((pros++))  #adds 1 to pros
    fi

    echo " " #creates a empty line
}

#this is the remove processes function that lets the user remove a process
function remProcesses {

    #makes sure there is processes going
    if [ $pros -gt 0 ]; then
        
        #Asks user to choose a process to kill
        echo "You have $pros processes running"
        echo "Processes:"
        echo "`jobs`"
        echo "Which process would you like to kill? (type number in brackets or type 0 to cancel kill)"
        read -r -p ": " num

        #error checks to make sure a process was chosen to kill
        while [[ ! "$num" =~ ^[0-9]+$ ]]; do
            echo "Invalid! please make sure to put a number!"
            read -r -p ": " num
        done

        #kills the process entered as long as 0 is not entered and it is a proper PID (chat gpt was used to fix this line)
        if [[ $num -gt 0 ]] && kill -0 %$num > /dev/null 2>&1; then
            kill %$num
            ((pros--))
            echo "Succesfully killed!"
        elif [ $num = 0 ]; then
            echo "Kill canceled! Going back!" 
        else
            echo "Error. No proper job number was entered. Please try again."
        fi

    #outputs an error message if no processes were started       
    else
        echo "No processes to kill"
    fi

    echo " " #creates a empty line
}

#allows user to view ping file
function viewFile {

    #enters the pingData folder
    cd pingData

    if [ ! -z "$(ls)" ]; then
    #asks the user for the name of the file. lists the files in the folder
        echo " "
        echo "Enter the name of the ping file you wish to view (do not put the .txt)"
        echo "(ping file names should only consist on letters and character with a length of 10 or less)"
        echo "List of files currently in ping data folder:"
        echo "$(ls)"
        read -r -p ": " file

        #make sure proper name is entered
        while [[ ! "$file" =~ ^[[:alnum:]]+$ ]] || [ ${#file} -gt 10 ]; do
            echo "invalid! please entere a proper name!"
            read -r -p ": " file
        done

        #if the file exists in the pingData folder, than the last line is output. If not, error message is seen
        if [ -f "$file.txt" ]; then
            tail -n 1 "$file.txt"
        else
            echo "No file found with that name! Please try again!"
        fi

        echo " "
    else
        echo "no files to view" #echo line if no files are in ping data
    fi

    #goes back to the parent directory
    cd ..
}

#counts the number of processes going on
pros=0

#says hello to the user
echo "Hello there! Welcome to the program. It is currently $(date)" 
sleep 1
echo "This program allows you to start certain processes/pings, view the running"
echo "processes/pings, read the last ping from a text file, and kill those"
echo "processes/pings."
echo " "
sleep 2

#while loop that goes until 4 is entered by user
while [[ $choice != 5 ]]; do

    #menu that lets user decide what they wish to do. Error checking used
    #to make sure a proper choice is entered.
    echo "Pick one option:"
    echo "1. Add Process/Ping"
    echo "2. Remove Process/Ping"
    echo "3. View all jobs"
    echo "4. View last line of Ping textfile"
    echo "5. End Program"
    read -r -p ": " choice

    #error checking that makes sure the user enters a proper choice
    while [[ ! "$choice" =~ ^[1-5]+$ ]] || [ ${#choice} != 1 ]; do
        echo "Invalid! pick a number between 1-5 corresponding with this list!"
        read -r -p ": " choice
    done

    #case statement that goes to the correct function based the users choice
    case $choice in
        1) addProcesses;;
        2) remProcesses;;
        3) if [[ $pros = 0 ]]; then   #checks to see if processes were started before running jobs
                echo "no processes are running right now."
            else
                jobs
            fi
            echo " ";; 
        4) viewFile;;
        5) echo "Program ending. Killing all processes/pings before closing.";; #says goodbye to the user
    esac

    #waits a second before showing the menu again
    sleep 1
done

#kills the remaining jobs/pings before the program ends
pkill ping

echo "processes/pings killed. Goodbye."    #one final goodbye to the user

