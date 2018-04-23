/*
 Submitted By:
 Riya Joshi
 rxj152630@utdallas.edu
 CS 3377
 Homework6 : GIT Repository and Binary File I/O 
*/
#include<stdlib.h>
#include<stdio.h>
#include<sstream>
#include<string.h>
#include <iostream>
#include "cdk.h"
#include "header.h"
#include <fstream>
//5 rows 3 cols matrix
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
  ifstream fin;
  fin.open("cs3377.bin",ios::in|ios::binary);//open binary file
  if(!fin.is_open())
  {
  	cout<<"ERROR : Cannot open binary file"<<endl;
	return -1;
  }

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  
  //5x3 matrix 5 rows 3 cols
  const char *rowTitles[] = {"R0","a","b","c","d","e"};
  const char *columnTitles[] = {"C0","a","b","c","d","e"}; 
  int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //set matrix cells and then display the matrix

  //Start reading binary file
  //first line of binary file holds a BinaryFileHeader, so read that outside the loop
  BinaryFileHeader *header = new BinaryFileHeader();
  fin.read((char*)header,sizeof(BinaryFileHeader));//reading Binary File Header into header
  char buffer[65];
  int row = 1;
  int col = 1;
  char result[65];
  sprintf(buffer,"%X",header->magicNumber);//hexa decimal FEEDFACE(header->magicNumber)  now converted to "FEEDFACE" and held in buffer
  strcpy(result,"Magic: 0x");
  strcat(result,buffer);//result now holds "Magic: 0xFEEDFACE"
  setCDKMatrixCell(myMatrix,row,col,result);//set matrix cell (1,1) as "Magic: 0xFEEDFACE"
  col++;//2
  //32 bit so %d
  sprintf(buffer,"%d",header->versionNumber);//16 stored as "16" in buffer
  strcpy(result,"Version: ");
  strcat(result,buffer);//result now holds "Version: 16"
  setCDKMatrixCell(myMatrix,row,col,result);//set matrix cell (1,2) as result
  col++;//3
  //64 bit so %lu
  sprintf(buffer,"%lu",header->numRecords);//4 stored as "4"
  strcpy(result,"NumRecords: ");
  strcat(result,buffer);//result holds "NumRecords: 4"
  setCDKMatrixCell(myMatrix,row,col,result);//set matrix cell (1,3) as result

  //The next lines of Binary File are full of BinaryFileRecords
  //NumRecords is the number of Binary File Records to be read
  BinaryFileRecord *record = new BinaryFileRecord();
  while(fin.read((char*)record,sizeof(BinaryFileRecord)))//keep reading the file as long as there is Binary File Record to be read inside the file
  {
  	//after reading the Binary File record set the matrix cells
  	row ++;//2,3,4,5
	col =1;
	//8 bit so %d
  	sprintf(buffer,"%d",record->strLength);//convert length to " " format
	strcpy(result,"strlen: ");
	strcat(result,buffer);
  	setCDKMatrixCell(myMatrix,row,col,result);//set (2,1),(3,1),(4,1),(5,1) with "strlen: record->strLength"
	col++;//2
	setCDKMatrixCell(myMatrix,row,col,record->stringBuffer);//set (2,2),(3,2),(4,2),(5,2) with "record->stringBuffer"

 }
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
