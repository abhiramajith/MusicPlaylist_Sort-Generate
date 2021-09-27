#include "library.h"

//INSTRUCTIONS
/*If inputting your own file you can save it at the same level as main.c and enter the file name as a
 * project argument in 'Edit Configurations' (assignment|Debug), also ensure you have working directory as "$ProjectFileDir$".
 * Alternatively if you wish to run the code in the terminal you must put your text file in cmake-build-debug
 * and go into that directory and run the command in the following format: "assignment.exe example.txt */


//Declaring global variables so they are recognised in other source files

char fileInput[RSIZ][LSIZ] = {'\0'}; //Holds contents of file or user input of artists and songs
char songArr[RSIZ][LSIZ] = {'\0'};  //Holds each song by a respective artist with their name beside it
char cpysongArr[RSIZ][LSIZ] = {'\0'}; //Is a copy of songArr so it can be tokenised without songArr being altered
char randPlaylist[RSIZ][LSIZ] = {'\0'}; //Holds the random playlist of songs
char songName[SONG_SIZE], songDuration[DURATION_SIZE], artist[ARTIST_SIZE], tempArtist[ARTIST_SIZE]; //Holds tokens
int totalDuration = 0; //Holds total duration of random playlist
const char delim[] = "***";
char *token;
int x = 0; //Iterator for an array


int main(int argc, char* argv[])
{

    //Calls to each function with the appropriate arrays
    readResults(fileInput, argc, argv); //passing in argc and argv into read function so it can be dealt with there
    extractResults(fileInput);
    sortResults(songArr);
    printResults(songArr);
    shuffleSongs(songArr);
    randomisedPlaylist(songArr);
    printPlaylist(randPlaylist);

    printf("\nThank you for using this program.\n");

}


