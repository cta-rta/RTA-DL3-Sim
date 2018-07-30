/*
 ==========================================================================
 RTA-DL3-Sim C++ https://github.com/cta-rta/RTA-DL3-Sim
 Copyright (C) 2018 Giancarlo Zollino
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ==========================================================================
*/

#include<iostream>
#include<vector>

#include "fitsio.h"

using std::cout;
using std::endl;
using std::string;
//using std::vector;
using namespace std;

class FitsReader {
public:

  FitsReader(const char * _fitsFileName);
  int OpenFitsFile();
  long getNrows();
  int getNcols();
  double getMJDREFI();
  double getMJDREFF();
  std::vector <string> getHDU();
  //std::vector <double>  getTable();
  double ** getTable();

  const char * fitsFileName;
  fitsfile *fptr;      /* FITS file pointer, defined in fitsio.h */

  char keyword[FLEN_KEYWORD], colname[FLEN_VALUE];
  int status = 0;   /*  CFITSIO status value MUST be initialized to zero!  */
  int hdunum;
  int hdutype;
  int ncols = 0;
  int ii;
  int anynul;
  int dispwidth[1000];
  int firstcol, lastcol = 0, linewidth;
  long jj;
  long nrows =0;
  std::vector<string> hdu;
  //std::vector<double> table;
  double ** table;
  static string colNameArray[8];
};
