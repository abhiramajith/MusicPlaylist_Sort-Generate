//
// Created by Abhiram on 19/03/2021.
//

#include "library.h"

//Module for sorting, printing and shuffling array of songs

/* This function takes in an array where each line consists of the artist name
 * one of their songs and it's duration each separated by the delimiter "***".
 * The function then sorts this array in alphabetical order using insertion sort.
 * This will sort the artists and their songs alphabetically as once the artists are sorted
 * because the artist name is first on each line when comparing two songs from the same
 * artist the function skips over it as they are identical until it reaches the song names
 * which are different and then sorts them accordingly.*/

void sortResults(char array[][LSIZ])
{

    int j; //Iterator
    int i; //Iterator
    char temp[LSIZ]; //Temporarily holds a given line from the array

    for(i = 1;i < RSIZ;i++){ //For loop iterates through each line in the array starting from index 1 while i < RSIZ

        strcpy(temp,array[i]); //array[i] is copied into temp
        j= i-1; //j is set to the line before i

        while(j >= 0 && strcmp(array[j], temp) > 0){ //loop while j is greater than or equal to 0 and temp is less than array (in terms of ascii)

            strcpy(array[j+1],array[j]); //array[j] is copied into array[j+1] as array[j] is greater than temp
            j--; //j is decremented until it equals 0 to check every line before i
        }
        strcpy(array[j+1],temp); //If temp is greater than array[j] then it is copied into array[j+1]
    }

}

/*This function prints the sorted array of artists and songs
 * in the format specified in the question,
 * it takes in the sorted array as an input*/
void printResults(char array[][LSIZ]){

    printf("\n|Sorted list of artists and songs|\n");

    int i = 0; //Iterator for while loop

    for (int j = 0; j < RSIZ; j++) { //copying contents of sorted array into cpysongArr
        //This is because the array needs to be tokenised which would
        //alter it's contents
        strcpy(cpysongArr[j], array[j]);

    }

    while (i < RSIZ) { //While i is less than the number of rows

        if (cpysongArr[i][0]=='\0') { //If the line is empty i.e the first letter is '/0' move to the next line
            i++;
        }

        else {

            //extract the artist name and store it in tempArtist
            token = strtok(cpysongArr[i], delim);
            strcpy(tempArtist, token);

            /* As each song by an artist starts with the artist's name
             * and the format specifies that the artist is printed once followed
             * by each song the artist name needed to be filtered out after their first
             * song. This was done by storing the current and previous artist's
             * in different variables tempArtist and artist respectively and comparing them.
             */

            if (strcmp(tempArtist, artist) != 0) { //If tempArtist is not the same as artist, will be the first song from any particular artist

                //store current artist in artist
                strcpy(artist, token);

                //Extract and store songName
                token = strtok(NULL, delim);
                strcpy(songName, token);

                //Extract and store songDuration
                token = strtok(NULL, delim);
                strcpy(songDuration, token);

                //Print artist followed by first song and duration on a new line, %c and 15 are used for the bullet point in the given format (I decided to use the sun symbol)
                printf("\n%s \n  %c %s***%s\n", artist, 15, songName, songDuration);


            }

            else if (strcmp(tempArtist, artist) == 0){ //If tempArtist is the same as artist just print the song and duration


                token = strtok(NULL, delim);
                strcpy(songName, token);


                token = strtok(NULL, delim);
                strcpy(songDuration, token);

                //Only print bullet point songName and duration
                printf("  %c %s***%s\n", 15, songName, songDuration);

            }

            i++;// move to next line
        }

    }

    printf("______________________________________________\n");
}


/* This function shuffles the array songArr of artists beside each of
 * their songs using the Fisher-Yates Durstenfeld Knuth Shuffle algorithm
 * so it can be used to select a random playlist.
 * The function takes in an array as an argument.*/

void shuffleSongs(char array [RSIZ][LSIZ]){

    srand(time(NULL));  //Creates random seed for random number generator based on current time

    int i = 1, j; //iterators
                  // i starts at 1 as its used to generate a random number later on so cant be 0

    while (i < RSIZ){ //while i is less than number of rows

        if (array[i][0] == '\0') { //if the line is blank move on
            i++;
        }

        else {// The array is shuffled by swapping array[i] with a random index from 0 to i

            //j is assigned a random number from 0 to the index i
            j = rand() % i;
            // i and j are then swapped using the swapArrElems function
            swapArrElems(array, i, j);

        }
    }

}

/* This function takes in an array and two iterators i and j which
 * hold indexes of artists and their songs.
 * The function then swaps these indexes according to the
 * shuffleSongs function*/

void swapArrElems(char array[][LSIZ], int i, int j) {

    //Swapping array[i] and [j]
    char temp[LSIZ]; //Temporary string to hold array[i] so it is not overwritten
    strcpy(temp, array[i]); //array[i] is copied to temp
    strcpy(array[i], array[j]); //array[j] is copied to array[i]
    strcpy(array[j], temp); //temp is copied to array[j]

}