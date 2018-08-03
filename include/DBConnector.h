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
/* Standard C includes */
#include <string.h>

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <thread>

#include <boost/scoped_ptr.hpp>


#include "mysql_connection.h"
#include "mysql_driver.h"
#include "examples.h"
#include "FileWriter.h"

#include <chrono>
#include <sys/time.h>
#include <sstream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//#define EXAMPLE_HOST "localhost"
//#define EXAMPLE_USER "root"
//#define EXAMPLE_PASS ""
#define ONE_ROW 1
#define QUERY_SIZE 2005000

using namespace std;


class DBConnector{
public:
  DBConnector(int _idObs, int _idRepo, string _host, string _userId, string _userPwd, string _dbName, string _tbName);
  int connect();
  int writeRowInDB(int idObs, int idRepo, double *dataWR);
  int writeTransactionInDB(int idObs, int idRepo, double *dataWR);
  int writeRowInDBByString(int idObs, int idRepo, double *dataWR);
  int writeRowInDBBySprintf(int idObs, int idRepo, double *dataWR);
  int writeTransactionInDBByString(int idObs, int idRepo, double *dataWR);
  vector<string> queryConstructor(string _dbName, int nrows, double **dataWR);
  int writeRowInDBExtQuery(string query);
  int startTransaction();
  int commitTransaction();
  int idObs;
  int idRepo;
  sql::Driver *driver;
  boost::shared_ptr <sql::Connection> con;
  time_t timer;
  string url;
  string userId;
  string userPwd;
  string dbName;
  string tbName;


private:
};
