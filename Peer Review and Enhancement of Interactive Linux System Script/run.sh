#! /bin/bash

#Sources for checking if package is installed:
#Ask Ubuntu: https://askubuntu.com/questions/1133749/how-to-check-if-a-package-is-installed-from-bash
#LinuxConfig.org: https://linuxconfig.org/how-to-test-for-installed-package-using-shell-script-on-ubuntu-and-debian
#
#
#Checking user input:
#StackExchange: https://unix.stackexchange.com/questions/175496/read-command-how-to-verify-user-has-typed-something
#
#
#Using user input:
#LinuxCapable: https://www.linuxcapable.com/read-command-in-linux/
#LinuxIze: https://linuxize.com/post/bash-read/
#
#
#Validating user input:
#StackExchange: https://unix.stackexchange.com/questions/375887/unix-shell-script-using-case-to-validate-users-input


#Exit code 1 = fail; 0 = success
dpkg -s $1 sysstat &> /dev/null


#This judges the output (exit code) of the above command and checks if it is 1.
if [ $? -eq  1 ]; then
	echo "Sysstat not found. Installing in 5 seconds. Please hit Tab, then Enter when prompted to restart services."
	sleep 5
	sudo apt install sysstat -y
else
	echo "sysstat found. Continuing."
fi

#asks if user would like to make a directory if y is entered, takes in
#users name and makes a directory
echo "Would you like to make a directory? y or n"
read -r -p ": " choice
while [[ $choice != y && $choice != n ]]; do
            echo "Please enter y or n!"
            read -r -p ": " choice
done

#if yes is entered, takes in a name (error checking on name) can creates a directory
if [ $choice = y ]; then
	echo "enter the name of your file"
	read -r -p ": " name
	while [[ ! "$name" =~ ^[[:alnum:]]+$ ]]; do
		echo "Please enter a name of only letters and numbers!"
		read -r -p ": " name
	done
	mkdir "$name"
	cd "$name"
fi

#creates the UserInput variable
UserInput=0

#loop repeats until user decides to exit
while [ ! $UserInput == 3 ]; do
	echo "Which list would you like to see?"
	echo "(1): All running processes"
	echo "(2): CPU and Memory usage"
	echo "(3): Exit"

	#-r disables backslash escaping; -p denotes this as a user prompt
	read -r -p ": " UserInput


	#This validates the user input as 1 or 2
	if [[ $UserInput == "1" ]] || [[ $UserInput == "2" ]];
	then

		#This supplies the commands to be run depending on the user's input. 
		case $UserInput in
			[1]* ) ps aux
					data=$(ps -e aux);;
			[2]* ) free -h; mpstat
					data=$(free -h; mpstat);;
		esac

		#asks the user if they would like to export their data
		echo "Would you like to export this information to a file? (y and n)"
		read -r -p ": " choice
		while [[ $choice != y && $choice != n ]]; do
            echo "Please enter y or n!"
            read -r -p ": " choice
		done

		#exports the data to a text file if y is entered. makes sure name is only
		#letters or numbers
		if [ $choice = y ]; then
			echo "enter the name of your file"
			read -r -p ": " name
			while [[ ! "$name" =~ ^[[:alnum:]]+$ ]]; do
				echo "Please enter a name of only letters and numbers!"
				read -r -p ": " name
			done
			echo -e $data > $name.txt
		fi
	elif [ $UserInput != 3 ]; 
	then
		#error message if user input is incorrect
		echo "Incorrect input, please try running the program again"
	fi
done
