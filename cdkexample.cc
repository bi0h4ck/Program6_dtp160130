/*
 * Usage of CDK Matrix
 * Program6 by Diem Pham - dtp160130
 * CS3366.002
 */

#include <iostream>
#include "cdk.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary file content"

using namespace std;
  class BinaryFileHeader{
    public:
    uint32_t magicNumber;
    uint32_t versionNumber;
    uint64_t numRecords;
};

const int maxRecordStringLength = 25;
class BinaryFileRecord{
  public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main() {

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix
  ostringstream oss;
  ostringstream os;

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();

  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
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
   * Dipslay header
   * 
   */
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  oss << "Magic: "  << "0x" << std::uppercase << setfill('0') << std::setw(8) << std::hex <<  myHeader -> magicNumber; 
  setCDKMatrixCell(myMatrix, 1, 1, strdup(oss.str().c_str()));
  oss.str("");
  
  oss << "Version: " << myHeader -> versionNumber; 
  setCDKMatrixCell(myMatrix, 1, 2, strdup(oss.str().c_str()));
  oss.str("");
  
  oss << "NumRecords: " << myHeader -> numRecords;
  setCDKMatrixCell(myMatrix, 1, 3, strdup(oss.str().c_str()));
  oss.str("");

  binInfile.clear();
  int i = 2;
 while(!binInfile.eof()) { /* Loop through records to print out on the matrix*/
    binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
    os << "strlen: " << strlen(myRecord -> stringBuffer);
    setCDKMatrixCell(myMatrix, i, 1, strdup(os.str().c_str()));
    os.str("");
    
    setCDKMatrixCell(myMatrix, i, 2, myRecord -> stringBuffer);
    
    i = i + 1;
  }

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
