#ifndef _FILEIO_H_  
#define _FILEIO_H_ 

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class fileIO{

private:
        FILE *pFile;
public:
        bool openFile(string);
	bool openFileW(string);
        void closeFile();
	string readPos(int,int);
	string readLine();
	void writeAtPos(int,string);
};

#endif

