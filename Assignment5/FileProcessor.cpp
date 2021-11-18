/*
Gabe Davidson
2338642
gadavidson@chapman.edu
FileProcessor.cpp -> Assignment 5

Implementation file for the FileProcessor class.
FileProcessor class holds the model for reading from and writing to files

Sources:
- None
*/

#include "FileProcessor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

// constructor
FileProcessor::FileProcessor(){
  infile = "";
  outfile = "";
}

FileProcessor::FileProcessor(char modi, const string inout){
  if (modi == 'r'){
    infile = inout;
    reader.open(infile);
  }
  else if (modi == 'w'){
    outfile = inout;
    writer.open(outfile);
  }
  else {
    throw std::runtime_error("Not a valid FileProcessor modifier");
  }
}

FileProcessor::FileProcessor(const string in, const string out){
  infile = in;
  outfile = out;
  reader.open(infile);
  writer.open(outfile);
}

// destructor
FileProcessor::~FileProcessor(){
}

string FileProcessor::readFileLine(){
  string line = "";
  getline(reader, line);
  return line;
}

void FileProcessor::writeFileLine(string line){
  try{
    writer << line << '\n';
  }
  catch (...){
    //
  }
}

void FileProcessor::openReader(string in){
  infile = in;
  try{
    reader.open(in);
  }
  catch (...){
    //
  }
}

void FileProcessor::openWriter(string out){
  outfile = out;
  try{
    writer.open(out);
  }
  catch(...){
    //
  }
}

bool FileProcessor::endOfReadFile(){
  return (reader.eof());
}

void FileProcessor::closeReader(){
  try{
    reader.close();
  }
  catch (...) {
    //
  }
}

void FileProcessor::closeWriter(){
  try{
    writer.close();
  }
  catch (...) {
    //
  }
}
