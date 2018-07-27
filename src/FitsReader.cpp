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

#include"FitsReader.h"

FitsReader::FitsReader(const char * _fitsFileName){
  fitsFileName = _fitsFileName;

}

int FitsReader::OpenFitsFile() {

  lastcol = 0;

  if (!fits_open_file(&fptr, fitsFileName, READONLY, &status))
  {
    if ( fits_get_hdu_num(fptr, &hdunum) == 1 )
        /* This is the primary array;  try to move to the */
        /* first extension and see if it is a table */
        fits_movabs_hdu(fptr, 2, &hdutype, &status);  // CI SI MUOVE NEI DIFFERENTI HDU
     else
        fits_get_hdu_type(fptr, &hdutype, &status); /* Get the HDU type */

    if (hdutype == IMAGE_HDU)
        printf("Error: this program only displays tables, not images\n");
    else
    {
      fits_get_num_rows(fptr, &nrows, &status);
      fits_get_num_cols(fptr, &ncols, &status);

      /* find the number of columns that will fit within 80 characters */
      //printf("\nNumero colonne: %d", ncols);
      //printf("\nNumero righe: %d", nrows);
      while(lastcol < ncols) {
        linewidth = 0;
        firstcol = lastcol+1;
        for (lastcol = firstcol; lastcol <= ncols; lastcol++) {
           fits_get_col_display_width(fptr, lastcol, &dispwidth[lastcol], &status);   // Return the display width of a column. This is the length of the string that will be returned by the fits_read_col routine when reading the column as a formatted string. The display width is determined by the TDISPn keyword, if present, otherwise by the data type of the column.
           linewidth += dispwidth[lastcol] + 1;
           //printf("\nLast col: %d", lastcol);
           //if (linewidth > 80)break;
        }
        if (lastcol > firstcol)lastcol--;  /* the last col didn't fit */  // MI PERMETTE DI STAMPARE L'ULTIMA COLONNA SE RESTA COMMENTATO

      }

    }

  }

  if (status) fits_report_error(stderr, status); /* print any error message */
  return(status);

}

long FitsReader::getNrows(){
  //cout << "nrowsFR: " << nrows << endl;
  return nrows;
}

int FitsReader::getNcols(){
  //cout << "nclosFR: " << ncols << endl;
  return ncols;
}

vector<string> FitsReader::getHDU(){

  for (ii = firstcol; ii <= lastcol; ii++) {
      fits_make_keyn("TTYPE", ii, keyword, &status);
      //fits_read_key(fptr, TSTRING, keyword, colname, NULL, &status);
      fits_read_keyword(fptr,keyword, colname, NULL,&status); // ADDED BY ME RETURN COLNAME AS CHAR* DATA TYPE
      colname[dispwidth[ii]] = '\0';  /* truncate long names */
      hdu.push_back(colname);
      //colNameArray[ii] = colname;
      //printf("%*s ",dispwidth[ii], colname);
  }

  return hdu;
}

//vector<double> FitsReader::getTable(){
double ** FitsReader::getTable(){


  //cout << "ncols: " << ncols << endl;
  double value[ncols];

  double** table = new double*[nrows];



  for (jj = 1; jj <= nrows && !status; jj++) {

    table[jj-1] = new double[ncols];

      for (ii = 1; ii <= ncols; ii++)
      {
          /* read value as double*/
          if (fits_read_col_dbl(fptr,ii,jj, 1,1, 0, &value[ii-1], &anynul,&status) ) {
            break;
          }
          //cout << jj << " " << ii << endl;
          table[jj-1][ii-1] = value[ii-1];

          //cout << "value " << ii << " "<< jj<<": " << table[jj][ii] << endl;
          //table.push_back(value[ii]);
          //cout << "Pushato " << ii <<"-esimo elemento" << endl;
      }

      //getchar();
  }

    //fits_close_file(fptr, &status);

  return table;
}
