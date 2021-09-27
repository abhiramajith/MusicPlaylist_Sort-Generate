//
// Created by Abhiram on 19/03/2021.
//

#ifndef ASSIGNMENT_LIBRARY_H
#define ASSIGNMENT_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define LSIZ 128 //Number of columns in a 2D array
#define RSIZ 100 //Number of rows in a 2D array
#define DEFAULT_FILE "artistes+songs.txt"
#define SONG_SIZE 100 //Max character size for songs
#define DURATION_SIZE 6 //Max character size for duration
#define ARTIST_SIZE 100 //Max character size for artist
#define HOUR_IN_SECONDS 3600 //1 hour in seconds
#define HOUR_IN_MINUTES 60   //1 hour in minutes
#define DELIM_SIZE 3 //number of characters delim uses "***"



//Global variables initialised here so they can be used in other source files
char fileInput[RSIZ][LSIZ];
char songArr[RSIZ][LSIZ];
char cpysongArr[RSIZ][LSIZ];
char randPlaylist[RSIZ][LSIZ];
char songName[SONG_SIZE], songDuration[DURATION_SIZE], artist[ARTIST_SIZE], tempArtist[ARTIST_SIZE];
int totalDuration;
const char delim[4];
char *token;
int x;

//Function prototypes
void readResults(char array[][LSIZ], int argc, char* argv[]);
void extractResults(char array[][LSIZ]);
void sortResults(char array[RSIZ][LSIZ]);
void storeResults( char array[RSIZ][LSIZ], char tempArtist[ARTIST_SIZE], char songName[SONG_SIZE], char songDuration[DURATION_SIZE]);
void printResults(char array[][LSIZ]);
void shuffleSongs(char array[][LSIZ]);
void swapArrElems(char array[][LSIZ], int i, int j);
void randomisedPlaylist(char array[RSIZ][LSIZ]);
int songCheck(char tempArtist[ARTIST_SIZE], char array[][LSIZ], int j);
void printPlaylist(char array[][LSIZ]);



#endif //ASSIGNMENT_LIBRARY_H
