/*
Gabe Davidson
2338642
gadavidson@chapman.edu
FileProcessor.h -> Assignment 5

Header class for FileProcessor
...

References:
- None
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

class FileProcessor{
  private:
    string outfile;
    string infile;
    ofstream writer;
    ifstream reader;
  public:
    FileProcessor();
    FileProcessor(char modi, string inout);
    FileProcessor(string in, string out);
    ~FileProcessor();

    string readFileLine();
    void writeFileLine(string line);
    void openReader(string in);
    void openWriter(string out);
    void closeReader();
    void closeWriter();
    bool endOfReadFile();

};

#endif
