//
// Created by Abhiram on 19/03/2021.
//
#include "library.h"

//Module for reading, extracting and storing data from file of songs and artists

/* This function reads the artists and songs from either a file or from user input and
 * stores the contents in the 2D character array the function is called with.
 * The commandline arguments argc and argv are also passed in from main so the user file can be opened using commandline.
 * Files will only open if saved at same level as main.c and if working directory is $ProjectFileDir$*/

void readResults(char array[][LSIZ], int argc, char* argv[]) {

    FILE *fptr; //fptr is a pointer to the text file specified
    int i = 0;


    //If number of arguments is greater than 1 user has inputted filename
    if (argc > 1) {

        //fopen opens the file with "r" for reading the contents. If it can't be opened it will return NULL and resort to opening the default file.
        //argv[1] contains the filename inputted by the user
        if ((fptr = fopen(argv[1], "r")) == NULL) {

            printf("\nFile could not be opened\n");
            printf("'%s' was not found in the directory or cannot be opened.\n", argv[1]);
            printf("If using terminal please enter argument as follows: 'assignment.exe example.txt' and make sure you are in cmake-build-debug and so is your file\n");
            printf("If using Edit Configurations simply enter the file name: 'example.txt' in program arguments and ensure file is at same level as main.c\n");
            printf("Thank you for using this program.\n");
            exit(1);
        }

        else {

            //If user's file was used, stores its contents in array function was called with

            printf("\nUsing user specified file %s\n", argv[1]);
            while (fgets(array[i], LSIZ, fptr)) {

                array[i][strlen(array[i]) - 1] = '\0';
                i++;

            }
        }

    }

    else { //Else user did not input any arguments therefore use default file

        if ((fptr = fopen(DEFAULT_FILE, "r")) == NULL) { //This file is used if the user's file is not found.

            printf("\nFile could not be opened\n");
            printf("'%s' was not found in the directory.\n", DEFAULT_FILE);

        }

        else {

            printf("\nNo file was specified therefore resorting to default file.\n");
            printf("Please refer to README.txt learn to use your own file\n\n");

            //If default was used stores the contents of 'artistes+songs.txt' in the array the function was called with
            while (fgets(array[i], LSIZ, fptr)) {

                array[i][strlen(array[i]) - 1] = '\0'; //Stripping the \n and replacing with \0 in each line
                i++;

            }
        }
    }

    //Closing file
    fclose(fptr);

    if ( fptr == NULL){
        //If user file and default file cannot be opened resorts to user input from keyboard


            //Informing user of format for manually typing songs
            printf("\nRequesting user input for artists and songs\n");
            printf("Please enter the artists, songs and song duration in the following format:\n");
            printf("\nArtiste name\n"
                   "Song title***Song duration(mm:ss)\n"
                   "Song title***Song duration(mm:ss)\n"
                   "...\n"
                   "Song title***Song duration(mm:ss)\n"
                   "<blank line>\n"
                   "Artiste name\n"
                   "Song title***Song duration(mm:ss)\n"
                   "Song title***Song duration(mm:ss)\n");
            printf("Please ensure names of artists and songs start with capitals.\n");
            printf("Enter two blank lines to stop adding entries.\n"); //Stopping condition

            //Storing user input in specified array
            while (fgets(array[i], LSIZ, stdin)) {

                /*If last entry is '/0' and current entry is '/n' stop taking input
                 * This is because if user hits enter twice the first will be converted to '/0'
                 * as the \n is stripped but the second stays as a '\n' */
                if (array[i - 1][0] == '\0' && array[i][0] == '\n') {
                    break;
                }

                array[i][strlen(array[i]) - 1] = '\0'; //Stripping '\n' at end of each inputted line
                i++; //moving to next location in array
            }
        }

}


/* This function takes in the array of results from the file or user input
 * and extracts the artist, their songs and their respective durations
 * and these are stored in a separate array with the artist's name beside each
 * of their songs using the function storeResults*/
void extractResults(char array[][LSIZ])
{

    for (int i = 0;  i < RSIZ;  i++) { //For loop goes through rows of array

        int j = 0; //j iterates through columns of array

        /* As the file of artists of songs is formatted like the below example
                The National
                Fireproof***2:58
         * To extract the artists name you check the current line letter by letter for the
         * null terminator as there is no delimiter present in an artists name,
         * the presence of a delimiter signifies its a song*/

        while (array[i][j] != '\0') { //Checking each line character by character until '\0'

            if (array[i][j] == '*') { //Signifies song line
                break;
            }

            j++; //Moving to next character

        }

        if (array[i][j] == '\0'){ //If a null terminator is found it is an artist

            strcpy(tempArtist, array[i]); //copy artists name into tempArtist

        }

        else if (array[i][j] == '*') { //If '*' delimiter is found its a song of the current artist in tempArtist

            //Extracts first token and stores it in variable songName
            token = strtok(array[i], delim);
            strcpy(songName, token);

            //Extracts second token and stores it in variable songDuration
            token = strtok(NULL, delim);
            strcpy(songDuration, token);

            /*The artist, current song and the songs duration are sent to the
             * storeResults function where they are placed on the same line in the
             * specified array songArr.*/
            storeResults(songArr, tempArtist, songName, songDuration);

        }
    }
}

/* This function takes in an array, an artist, a song and it's duration and
 * the artist's name is placed next to the song and stored in the array.
 * The artists, song and duration are separated using the "***" delimiter.
 * For example the following line in the original array:
    The National
    Fireproof***2:58
 * Will be stored like this in the new array:
    The National***FireProof***2:58
 *This allows for easy sorting and string manipulation later on.*/
void storeResults( char array[RSIZ][LSIZ], char tempArtist[ARTIST_SIZE], char songName[SONG_SIZE], char songDuration[DURATION_SIZE]) {

    /*Getting the length of the artist name and song name
     *This gives the location on the current line after the artist or song to enter
     *the next parameter*/
    int artistSize = strlen(tempArtist);
    int songSize = strlen(songName);

    strcpy(array[x], tempArtist);//Artist name is copied in first
    strcpy(&array[x][artistSize], delim);//Then the delimiter is copied in straight after which is why artistSize is used
    strcpy(&array[x][artistSize+DELIM_SIZE], songName);//Then the songName is added at artistSize + DELIM_SIZE (3) which accounts for the artist name and delimiter
    strcpy(&array[x][artistSize+DELIM_SIZE+songSize], delim);//Another delim is placed after the songname so at location artistSize+3+songSize
    strcpy(&array[x][artistSize+DELIM_SIZE+songSize+DELIM_SIZE],songDuration);//Finally song duration is added at the end at location artistSize+3+songSize+3
    x++; //Iterating x which indicates the line in the current array
    //x is a global variable as this function is repeatedly called therefore x needs to be retained

}


