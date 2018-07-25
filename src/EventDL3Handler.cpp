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

EventDL3Handler::EventDL3Handler(const char* _fitsFileName,int _idObs,int _idRepo,double _tmin,double _tmax,double _rate,const char * _userId,const char * _userPwd){

  cout << "EventDL3HandlerConstructor" << endl;

  const char * fitsFileName = _fitsFileName;
  cout << "FitsFileName: " << fitsFileName << endl;
  idObs = _idObs;
  cout << "idObs: " << idObs << endl;
  idRepo = _idRepo;
  cout << "idREpo: " << idRepo << endl;
  tmin = _tmin;
  cout << "tmin: " << tmin << endl;
  tmax = _tmax;
  cout << "tmax: " << tmax << endl;
  rate = _rate;
  cout << "rate: " << rate << endl;
  userId = _userId;
  cout << "userId: " << userId << endl;
  userPwd = _userPwd;

  cout << "userPwd: " << userPwd << endl;

  int nrows = 0;
  int ncols = 0;

  FitsReader fitsreader(fitsFileName);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }


  table = fitsreader.getTable();

  for(std::vector<double>::iterator it = table.begin(); it != table.end(); ++it) {

    cout << *it << endl;
  }
  getchar();


}
