//
// Created by Abhiram on 19/03/2021.
//
#include "library.h"

//Module for generating random playlist

/* This function creates a randomised playlist using an array of
 * shuffled songs */
void randomisedPlaylist(char array[RSIZ][LSIZ]){

    //The array of shuffled songs is copied into cpysongArr so it is not altered during tokenisation
    for (int i = 0; i < RSIZ; i++) {
        strcpy(cpysongArr[i], array[i]);
    }

    int i = 0; //row iterator
    int j = 0; //iterator for randPlaylist
    int minutes ,seconds;  //holds minutes and seconds in each song

    while (totalDuration <  HOUR_IN_SECONDS && i < RSIZ) { //loops while totalDuration is less than 3600 seconds (1 hour) and i is less than no. of rows

        nextSong:
        if (cpysongArr[i][0] == '\0') { //if the line is blank move on
            i++;
        }

        else {

            //Extracting and storing tokens in respective variables
            token = strtok(cpysongArr[i], delim);
            strcpy(tempArtist, token);

            token = strtok(NULL, delim);
            strcpy(songName, token);

            token = strtok(NULL, delim);
            strcpy(songDuration, token);

            /*tempArtist, randPlaylist and j are sent to the function songCheck
             *this function ensures that there isn't more than 2 songs in a row from the
             *same artist and that an artist doesn't appear more than thrice in a playlist*/

            if (songCheck(tempArtist, randPlaylist, j) == 1){ //if songcheck returns one that means the previous 2 songs are
                                                              //from the same artists as the one in tempArtist at the moment

                i++; //i is incremented to move to a different artist than the two previous

                goto nextSong; /*This goto statement is for jumping to where a label
                                *is placed (line 22) in the program as the iterator has
                                * been incremented so the next song can be tokenised.*/

            }

            if (songCheck(tempArtist, randPlaylist, j) == 2){ //A return code of 2 indicates that the current artist in tempArtist is
                                                              //already present 3 times in the playlist therefore another song should be chosen
                i++;
                goto nextSong;

            }

            else { //If the current artist and song is clear to go into the random playlist

                //sscanf is used to read formmatted input from a string which in this case is the songDuration
                //it allows the minutes and seconds of the duration to be stored as integers
                sscanf(songDuration, "%d:%d", &minutes, &seconds);

                strcpy(randPlaylist[j], array[i]); //Copies the current song in array[i] into randPlaylist[j]

                totalDuration += ((minutes * HOUR_IN_MINUTES) + seconds); //the duration of the song is converted to seconds and added to totalDuration

                i++; //i is incremented moving to the next location in the array of shuffled songs

                j++; //j is incremented moving to the next location in the random playlist

            }
        }
    }
}

/* This function takes in the current artist in tempArtist,
 * an array (randPlaylist) and the iterator of the array j
 * as arguments. The function ensures that there isn't more than
 * 2 songs from the same artist in a row and that an artist doesn't
 * feature more than 3 times in the random playlist as per the given
 * instructions. j is passed in as it indicates how many entries are already
 * in the playlist.*/
int songCheck(char tempArtist[ARTIST_SIZE], char array[][LSIZ], int j) {

    //Creating two copy arrays to hold the contents of randPlaylist so
    //it can be tokenised without alteration
    char copyArray[RSIZ][LSIZ] = {'\0'};
    char copyArray2[RSIZ][LSIZ] = {'\0'};

    //Copying contents of array into copyArrays
    for (int i = 0; i < j; i++) {
        strcpy(copyArray[i], array[i]);
        strcpy(copyArray2[i], array[i]);
    }

    char artist1[ARTIST_SIZE], artist2[ARTIST_SIZE]; //These variables will hold the names of the previous 2 artists in the playlist
    int artistCount = 0; //Counter for number of times an artist is in the playlist

    if (j > 1) { //if there is more than 2 entries in randPlaylist (j is greater than 1)

        //As j is incremented at once a song is added to get the previous 2 songs
        // j-1 and j-2 must be used

        token = strtok(copyArray[j-1], delim);  //Gets last artist
        strcpy(artist1, token);

        token = strtok(copyArray[j-2], delim); //Gets 2nd last artist
        strcpy(artist2, token);

        /* If the artist in tempArtist is the same as artist1 and artist2 then adding
         * tempArtist will cause 3 songs from the same artist in a row therefore it returns 1
         * which indicates to the randomPlaylist function to use a different song*/
        if ( (strcmp(artist1, tempArtist) == 0) && (strcmp(artist2, tempArtist) == 0) ){
            return 1;
        }

        //This for loop is used to check through copyArray2 to count how many occurrences
        //of the artist in tempArtist are in the playlist
        for (int i = 0; i < j; i++){

            if (copyArray2[i][0] == '\0') { //If line is empty move on
                i++;
            }

            else{

                //Getting the artist at line copyArray[i] and copying it to artist1
                token = strtok(copyArray2[i], delim);
                strcpy(artist1, token);

                //If artist1 is the same as tempArtist increment artistCount
                if (strcmp(tempArtist, artist1) == 0){
                    artistCount += 1;

                }

            }

        }

        /* If artist count is 3 then the function returns 2
         * which indicates that there are already 3 songs in the playlist
         * from the artist in tempArtist so the randomPlaylist function
         * will move to the next song*/
        if (artistCount == 3){
            return 2;
        }

    }

    return 0; //return 0 if the current song is okay to be used
}

/* This function prints the randomised playlist to the format specified
 * it takes in an array as an argument (randPlaylist)*/

void printPlaylist(char array[][LSIZ]) {

    printf("\n|Randomised Playlist|\n");


    for (int i = 0; i < RSIZ; i++) {

        if (array[i][0] == '\0') { //If there is a blank line stop printing
            break;
        }

        //Extracting and storing tokens in respective variables
        token = strtok(array[i], delim);
        strcpy(artist, token);

        token = strtok(NULL, delim);
        strcpy(songName, token);

        token = strtok(NULL, delim);
        strcpy(songDuration, token);

        printf("%s: '%s' (%s)\n", artist, songName, songDuration); //Printing each song in the given format


    }

    int minutes = totalDuration / HOUR_IN_MINUTES; //Getting total minutes of the playlist by integer dividing the totalDuration by 60
    int seconds = totalDuration % HOUR_IN_MINUTES; //Getting total seconds by getting the modulo of the totalDuration and 60

    printf("\nTotal Duration: %d:%02d\n", minutes, seconds); //Printing the Total Duration of the playlist
    //%02d ensure that if the number of seconds is between
    // 0 and 9 it will be displayed with a 0 before it

}
