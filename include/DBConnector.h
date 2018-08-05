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




#include "FileWriter.h"

#include <chrono>
#include <sys/time.h>
#include <sstream>



#define ONE_ROW 1
#define QUERY_SIZE 2005000

using namespace std;


class DBConnector{
  public:

    DBConnector(string _host, string _userId, string _userPwd, string _dbName);

    virtual int connect() = 0;
    virtual int startTransaction() = 0;
    virtual int commitTransaction() = 0;






  private:
    string url;
    string userId;
    string userPwd;
    string dbName;



 };
