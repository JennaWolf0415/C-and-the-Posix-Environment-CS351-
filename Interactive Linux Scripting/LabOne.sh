#!/bin/bash

out=0
card=0
date=$(date)

echo "hello! whats your name?"
read name
echo "hello $name! I am Jenna! Welcome to the library! We have many books!"
echo "today is $date"
echo " "

while [ "$choice" != 6 ]; do
    echo "What would you like to do?"
    echo "1. See list of books"
    echo "2. Choose a book and read it"
    echo "3. Take a book home"
    echo "4. Return a book"
    echo "5. Wordcount List"
    echo "6. Leave"
    read choice
    while [[ ! "$choice" =~ ^[1-6]+$ ]] || [ ${#choice} != 1 ]; do
        echo "Invalid! pick a number between 1-6 corresponding with this list!"
        read choice
    done

    echo " "
    if [ $choice == 1 ]; then
        echo "alright! here are our books that we currently have!"
        if [ $out != 1 ]; then
            echo "Computer Facts"
        fi
        if [ $out != 2 ]; then
            echo "Twinkle Twinkle Little Star"
        fi
        if [ $out != 3 ]; then
            echo "Dangerously Yours"
        fi
        if [ $out != 4 ]; then
            echo "Scary Story"
        fi
    elif [ $choice == 2 ]; then
        echo "what book do you want? (choose 1-4)"
        read currentBook
        while [[ ! "$currentBook" =~ ^[1-4]+$ ]] || [ ${#currentBook} != 1 ]; do
            echo "Invalid! pick a number between 1-4!"
            read currentBook
        done
        if [ $currentBook == $out ]; then
            echo "That book is currently out! Please try again"
        elif [ $currentBook == 1 ]; then
            book=$(< ComputerFacts)
            echo -e $book
        elif [  $currentBook == 2 ]; then
            book=$(< TwinkleTwinkleLittleStar)
            echo -e $book
        elif [ $currentBook == 3 ]; then
            book=$(< DangerouslyYours)
            echo -e $book
        elif [ $currentBook == 4 ]; then
            book=$(< ScaryStory)
            echo -e $book
        fi
    elif [ $choice == 3 ]; then
        if [ $out != 0 ]; then
            echo "you already have a book! please return that one first!"
        else
            echo "which book would you like? (1-4)"
            read out
            while [[ ! "$out" =~ ^[1-4]+$ ]] || [ ${#out} != 1 ]; do
                echo "Invalid! Please pick a book 1-4!"
                read out
            done
            if [ $out == 1 ]; then
                mv ComputerFacts ~/bashScript/Out
            elif [ $out == 2 ]; then
                mv TwinkleTwinkleLittleStar ~/bashScript/Out
            elif [ $out == 3 ]; then
                mv DangerouslyYours ~/bashScript/Out
            else
                mv ScaryStory ~/bashScript/Out
            fi
        fi
    elif [ $choice == 4 ]; then
        if [ $out == 0 ]; then
            echo "you currently don't have a book out!"
        else
            echo "Thank you for returning your book! Pick out another if you would like!"
            if [ $out == 1 ]; then
                mv Out/ComputerFacts ~/bashScript
            elif [ $out == 2 ]; then
                mv Out/TwinkleTwinkleLittleStar ~/bashScript
            elif [ $out == 3 ]; then
                mv Out/DangerouslyYours ~/bashScript
            else
                mv Out/ScaryStory ~/bashScript
            fi
            out=0
        fi
    elif [ $choice == 5 ]; then
        memory="$(wc ComputerFacts) \n$(wc TwinkleTwinkleLittleStar) \n$(wc DangerouslyYours)
                \n$(wc ScaryStory) \n$(wc LabOne.sh)"
        echo -e $memory
        echo "Would you like to make a text file for this information? (y or n)"
        read newFile
        while [[ $newFile != y && $newFile != n ]]; do
            echo "Please enter y or n!"
            read newFile
        done
        if [ $newFile = y ]; then
            echo -e $memory > WordCount.txt
        fi
    fi
    echo " "
done

echo "See you soon $name!"