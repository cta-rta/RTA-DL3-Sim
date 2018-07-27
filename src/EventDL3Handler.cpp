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

#include"EventDL3Handler.h"

EventDL3Handler::EventDL3Handler(const char* _fitsFileName, int _idObs, int _idRepo, double _rate, const char * _userId, const char * _userPwd){


  const char * fitsFileName = _fitsFileName;
  idObs = _idObs;
  idRepo = _idRepo;
  rate = _rate;
  userId = _userId;
  userPwd = _userPwd;

/*
  cout << "EventDL3HandlerConstructor" << endl;
  cout << "FitsFileName: " << fitsFileName << endl;
  cout << "idObs: " << idObs << endl;
  cout << "idREpo: " << idRepo << endl;
  cout << "rate: " << rate << endl;
  cout << "userId: " << userId << endl;
  cout << "userPwd: " << userPwd << endl;
*/

  int nrows = 0;
  int ncols = 0;

  string uId(userId);
  string uPwd(userPwd);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, uId, uPwd);

  //dbConnector.connect();

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }



  double **table = fitsreader.getTable();

  //int tmp = 0;

  for (int jj = 0; jj < rate; jj++) {

    for (int ii = 0; ii < ncols; ii++)
      {

        cout << table[jj][ii] << endl;

      }
      //getchar();
  }

  //tmp = rate;
  dbConnector.writeInDB(idObs, idRepo, rate, table);


}
