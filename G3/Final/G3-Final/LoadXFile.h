#ifndef LOADXFILE_H
#define LOADXFILE_H
//These three functions are used for
//returning the initials, score, and
//date accomplished from the x file to
//the main.cpp file because I forgot
//how to do external calls. 
char* GetInitial(int index);
int GetScore(int index);
char* GetDate(int index);
struct high_score_return
{
	char userInitial[4];
	int highScore;
	char dateAccomplished[11];
};
//high_score_return scoreDataReturn[11] = {NULL};
//This function is for loading the x file
//to the program and getting all the data
//that is in it.
void LoadXFile();
#endif