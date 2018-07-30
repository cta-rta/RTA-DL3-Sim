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

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <thread>

#include <boost/scoped_ptr.hpp>


/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "examples.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//#define EXAMPLE_HOST "localhost"
//#define EXAMPLE_USER "root"
//#define EXAMPLE_PASS ""
#define ONE_ROW 1

using namespace std;

class DBConnector{
public:
  DBConnector(int idObs,int idRepo, string userId, string userPwd);
  int connect();
  int writeRawInDB(int _idObs, int _idRepo, double _mjdferi, double _mjdferf, double *dataWR);
  int idObs;
  int idRepo;
  sql::Driver *driver;
  boost::shared_ptr <sql::Connection> con;
  //boost::shared_ptr< sql::Connection > con;
  string url;
  string userId;
  string userPwd;
  string database="evt_test";

private:
};
