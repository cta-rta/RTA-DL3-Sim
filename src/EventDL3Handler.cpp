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


  fitsFileName = _fitsFileName;
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

  //EventManager();
}

int EventDL3Handler::EventManager() {

  //cout << "EventManager" << endl;

  int nrows = 0;
  int ncols = 0;

  string uId(userId);
  string uPwd(userPwd);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, uId, uPwd);

  dbConnector.connect();

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  long double mjdferi = fitsreader.getMJDREFI();
  double mjdferf = fitsreader.getMJDREFF();
  //cout << "mjdferi" << mjdferi << endl;
  //cout << "mjdferf" << mjdferf << endl;


  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/



  double **table = fitsreader.getTable();


  for(int i = 0 ; i < nrows; i += rate) {



    auto start = std::chrono::system_clock::now();


    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDB(idObs, idRepo, mjdferi, mjdferf, table[j+i]);

    }


    auto stop = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = stop-start;


    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    }
    //getchar();

    return 0;
}
