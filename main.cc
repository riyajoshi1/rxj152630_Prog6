/*
 Submitted By:
 Riya Joshi
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
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

int main()
{
  ifstream fin;
  fin.open("cs3377.bin",ios::in|ios::binary);
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

  //example : 3X4 matrix
  //const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  //const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  //5x3 matrix 5 rows 3 cols
  const char *rowTitles[] = {"R0","a","b","c","d","e"};
  const char *columnTitles[] = {"C0","a","b","c","d","e"}; 
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

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

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  BinaryFileHeader *header = new BinaryFileHeader();
  fin.read((char*)header,sizeof(BinaryFileHeader));
  char buffer[65];
  int row = 1;
  int col = 1;
  char result[65];
  sprintf(buffer,"%X",header->magicNumber);//hexa decimal FEEDFACE now converted to "FEEDFACE"
  strcpy(result,"Magic: 0x");
  strcat(result,buffer);
  setCDKMatrixCell(myMatrix,row,col,result);//1,1
  col++;
  sprintf(buffer,"%d",header->versionNumber);//decimal 16 stored as "16"
  strcpy(result,"Version: ");
  strcat(result,buffer);
  setCDKMatrixCell(myMatrix,row,col,result);//1,2
  col++;
  sprintf(buffer,"%lu",header->numRecords);//decimal 4 stored as "4"
  strcpy(result,"NumRecords: ");
  strcat(result,buffer);
  setCDKMatrixCell(myMatrix,row,col,result);//1,3

  BinaryFileRecord *record = new BinaryFileRecord();
  while(fin.read((char*)record,sizeof(BinaryFileRecord)))
  {
  	row ++;//2,3,4,5
	col =1;
  	sprintf(buffer,"%d",record->strLength);
	strcpy(result,"strlen: ");
	strcat(result,buffer);
  	setCDKMatrixCell(myMatrix,row,col,result);//(2,1),(3,1),(4,1),(5,1)
	col++;//2
	setCDKMatrixCell(myMatrix,row,col,record->stringBuffer);//(2,2),(3,2),(4,2),(5,2)

 }
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
