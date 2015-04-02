#include "includes/fileIO.h"
#include <string>

bool fileIO::openFile(string fileName){
	if(fileName == "")
		return false;

	pFile = fopen(fileName.c_str(),"r+");

	return pFile != NULL;	
}

bool fileIO::openFileW(string fileName){
        if(fileName == "")
                return false;

        pFile = fopen(fileName.c_str(),"w");

        return pFile != NULL;
}


void fileIO::closeFile(){
	fclose(pFile);
}

string fileIO::readPos(int pos,int size){
	char buffer[size];
	fseek(pFile,pos,SEEK_SET);
	if(fgets(buffer,size,pFile) != NULL){

		return string(buffer);
	}else{
		throw;		
	}
	
}

string fileIO::readLine(){
	char* buffer = (char*)malloc(10000*sizeof(char));
	if(fgets (buffer, 10000, pFile) == NULL){
		return string("NULL");
	}
	string line(buffer);
	if (!line.empty() && line[line.length()-1] == '\n') {
		line.erase(line.length()-1);
	}
	return line;
}

void  fileIO::writeAtPos(int pos, string value){
	if(pFile != NULL){
		fseek(pFile,pos,SEEK_SET);
		fputs(value.c_str(),pFile);
		fflush(pFile);
	}
	
}
