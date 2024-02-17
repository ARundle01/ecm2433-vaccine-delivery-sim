#ifndef __FILEMANIP_HPP
#define __FILEMANIP_HPP
/*--------------------------- Includes --------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <orderingExceptions.hpp>
/*--------------------------- Namespace -------------------------------------*/
using namespace std;
/*--------------------------- Function Prototypes ---------------------------*/
int fileLength(ifstream&);
char * getFileContents(string);
int numberOfLines(char *);
void splitFileContents(string *, char *);
/*---------------------------------------------------------------------------*/
#endif
