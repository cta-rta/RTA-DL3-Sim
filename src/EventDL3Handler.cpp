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

EventDL3Handler::EventDL3Handler(const char* _fitsFileName, int _idObs, int _idRepo, double _rate, const char * _host, const char * _userId, const char * _userPwd,   const char * _dbName, const char * _tbName){


  fitsFileName = _fitsFileName;
  idObs = _idObs;
  idRepo = _idRepo;
  rate = _rate;
  host = _host;
  userId = _userId;
  userPwd = _userPwd;
  dbName = _dbName;
  tbName = _tbName;

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

int EventDL3Handler::BatchEventManager() {

  cout << "BatchEventManager" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/


  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBByString(idObs, idRepo, table[j+i]);

    }

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    sleep(1);

    }

    return 0;
}


int EventDL3Handler::BatchEventManagerExtQuery() {

  cout << "BatchEventManagerExtQuery" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/


  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  vector <string> query = dbConnector.queryConstructor(tbN, nrows, table);

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    for( int j=0 ; j < rate; j ++) {

        dbConnector.writeRowInDBExtQuery(query[j+i]);
    }

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    sleep(1);

    }

    return 0;
}

int EventDL3Handler::BatchEventManagerBySprintf() {

  cout << "BatchEventManagerBySprintf" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/


  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBBySprintf(idObs, idRepo, table[j+i]);

    }

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    sleep(1);

    }

    return 0;
}



int EventDL3Handler::TransactionBatchEventManager() {

  cout << "TransactionBatchEventManager" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();

  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/

  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    dbConnector.startTransaction();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeTransactionInDBByString(idObs, idRepo, table[j+i]);

    }

    dbConnector.commitTransaction();

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    sleep(1);


    }

    return 0;

}


int EventDL3Handler::TransactionBatchEventManagerExtQuery() {

  cout << "TransactionBatchEventManagerExtQueryr" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();

  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/

  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  vector <string> query = dbConnector.queryConstructor(tbN, nrows, table);

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    dbConnector.startTransaction();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBExtQuery(query[j+i]);

    }

    dbConnector.commitTransaction();

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    sleep(1);


    }

    return 0;

}

int EventDL3Handler::TransactionBatchEventManagerBySprintf() {

  cout << "TransactionBatchEventManagerBySprintf" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();

  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/

  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    dbConnector.startTransaction();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBBySprintf(idObs, idRepo, table[j+i]);

    }

    dbConnector.commitTransaction();

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    sleep(1);


    }

    return 0;

}

int EventDL3Handler::StreamingEventManager() {

  cout << "StreamingEventManager" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/

  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBByString(idObs, idRepo, table[j+i]);

      sleep(1/rate);

    }

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    }

    return 0;

}

int EventDL3Handler::StreamingEventManagerExtQuery() {

  cout << "StreamingEventManagerExtQuery" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/

  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  vector <string> query = dbConnector.queryConstructor(tbN, nrows, table);

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBExtQuery(query[j+i]);

      sleep(1/rate);

    }

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    }

    return 0;

}

int EventDL3Handler::StreamingEventManagerBySprintf() {

  cout << "StreamingEventManagerBySprintf" << endl;

  int nrows = 0;
  int ncols = 0;

  string hst(host);
  string uId(userId);
  string uPwd(userPwd);
  string dbN(dbName);
  string tbN(tbName);

  FitsReader fitsreader(fitsFileName);
  DBConnector dbConnector(idObs, idRepo, hst, uId, uPwd, dbN, tbN);

  fitsreader.OpenFitsFile();

  nrows = fitsreader.getNrows();
  ncols = fitsreader.getNcols();

  hdu = fitsreader.getHDU();

  /*    PRINT HDU VALUES  */
  /*for(std::vector<string>::iterator it = hdu.begin(); it != hdu.end(); ++it) {

    cout << *it << endl;
  }*/

  /* fitsReader.getTable restituisce un array 2D double con un time per ogni evento espresso in terrestrial time */
  double **table = fitsreader.getTable();

  dbConnector.connect();

  for(int i = 0 ; i < nrows; i += rate) {

    auto start = std::chrono::system_clock::now();

    for( int j=0 ; j < rate; j ++) {

      dbConnector.writeRowInDBBySprintf(idObs, idRepo, table[j+i]);

      sleep(1/rate);

    }

    auto stop = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = stop-start;

    cout << "Tempo impiegato per inserire " << rate << " eventi = " << diff.count() << " ms" << endl;

    }

    return 0;

}
