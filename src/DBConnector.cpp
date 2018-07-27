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

#include"DBConnector.h"

DBConnector::DBConnector(int _idObs,int _idRepo, string _userId,string _userPwd){

  url = "localhost";
  userId = _userId;
  userPwd = _userPwd;
  idObs = _idObs;
  idRepo = _idRepo;

/*
  cout << "DBConnector constructor" << endl;
  cout << "UserId: " << userId << endl;
  cout << "UserPwd: " << userPwd << endl;
*/

}

int DBConnector::connect() {

    try {

      driver = sql::mysql::get_driver_instance();

      /* Using the Driver to create a connection */
  		boost::scoped_ptr< sql::Connection > con(driver->connect(url, userId, userPwd));
  		con->setSchema(database);

  		boost::scoped_ptr< sql::Statement > stmt(con->createStatement());
  		boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT 'Welcome to Connector/C++' AS _message"));
  		cout << "\t... running 'SELECT 'Welcome to Connector/C++' AS _message'" << endl;
  		while (res->next()) {
  			cout << "\t... MySQL replies: " << res->getString("_message") << endl;
  			cout << "\t... say it again, MySQL" << endl;
  			cout << "\t....MySQL replies: " << res->getString(1) << endl;
  		}

  	} catch (sql::SQLException &e) {
  		/*
  		The MySQL Connector/C++ throws three different exceptions:

  		- sql::MethodNotImplementedException (derived from sql::SQLException)
  		- sql::InvalidArgumentException (derived from sql::SQLException)
  		- sql::SQLException (derived from std::runtime_error)
  		*/
  		cout << "# ERR: SQLException in " << __FILE__;
  		cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
  		/* Use what() (derived from std::runtime_error) to fetch the error message */
  		cout << "# ERR: " << e.what();
  		cout << " (MySQL error code: " << e.getErrorCode();
  		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

  		return EXIT_FAILURE;
  	} catch (std::runtime_error &e) {

  		cout << "# ERR: runtime_error in " << __FILE__;
  		cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
  		cout << "# ERR: " << e.what() << endl;
  		cout << "not ok 1 - examples/connect.php" << endl;

  		return EXIT_FAILURE;
  	}


  	cout << endl;

  	cout << endl;
  	return EXIT_SUCCESS;
  }

int DBConnector::writeInDB(int _idObs, int _idRepo, int _rate, double **dataWR){


  int idObs = _idObs;
  int idRepo = _idRepo;
  int rate = _rate;
  stringstream sql;
  stringstream msg;
  int num_rows;
  int status = 0;


  /*cout << "\n\nINSIDE WRITEINDB\n"  << endl;
  for (int i=0; i <rate; i++) {
    for(int j=0; j <8; j++) {
        cout << "(i="<<i<<" j="<<j<<") "<<dataWR[i][j] << endl;
    }
    cout << endl;
  }*/

  try {

    /* Using the Driver to create a connection */
    driver = sql::mysql::get_driver_instance();
		boost::scoped_ptr< sql::Connection > con(driver->connect(url, userId, userPwd));

    /* Creating a "simple" statement - "simple" = not a prepared statement */
		boost::scoped_ptr< sql::Statement > stmt(con->createStatement());

		/* ##### */
		stmt->execute("USE " + database);

    /*
    The first useful example - prepare() once, execute() n + 1 times
    NOTE: The MySQL Server does not support named parameters. You have to use
    the placeholder syntax shown below. There is no emulation which would you
    allow to use named parameter like ':param1'. Use '?'. Parameters are 1-based.
    */
    //boost::scoped_ptr< sql::PreparedStatement > prep_stmt(con->prepareStatement("SELECT * FROM evt"));
    std::auto_ptr< sql::PreparedStatement >  prep_stmt;
    //prep_stmt->execute();

    num_rows = 0;
    prep_stmt.reset(con->prepareStatement("INSERT INTO evt(eventidfits, observationid, datarepositoryid, time, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));

    //cout << "\n\nINSIDE WRITEINDB -> Preparing statement\n"  << endl;


    for (int i = 0; i < rate; i++) {
      //cout << "i: " << i << endl;
      //cout << dataWR[i][0] << endl;
      prep_stmt->setInt(1, (int)dataWR[i][0]);  // eventidfits
      //cout << "idObs: "<< idObs << endl;
      prep_stmt->setInt(2, idObs);  //observationid
      //cout<< "idRepo: "<< idRepo << endl;
      prep_stmt->setInt(3, idRepo);  //datarepositoryid
      //cout << dataWR[i][2] << endl;
      prep_stmt->setDouble(4, dataWR[i][1]);  //time
      //cout << dataWR[i][3] << endl;
      prep_stmt->setDouble(5, dataWR[i][2]); //ra_deg
      //cout << dataWR[i][4] << endl;
      prep_stmt->setDouble(6, dataWR[i][3]); //dec_deg
      //cout << dataWR[i][5] << endl;
      prep_stmt->setDouble(7, dataWR[i][4]); // energy
      //cout << dataWR[i][6] << endl;
      prep_stmt->setDouble(8, dataWR[i][5]); //detx
      //cout << dataWR[i][7] << endl;
      prep_stmt->setDouble(9, dataWR[i][6]);  //dety
      //cout << dataWR[i][8] << endl;
      prep_stmt->setInt(10, (int)dataWR[i][7]);  //mcid
      prep_stmt->setInt(11, status); //status
      prep_stmt->setDouble(12, 12); //timeraltt
      prep_stmt->setInt(13, 13);  //insert_time

      /* executeUpdate() returns the number of affected = inserted rows */
      num_rows += prep_stmt->executeUpdate();
    }

  		if (EXAMPLE_NUM_TEST_ROWS != num_rows) {
  			msg.str("");
  			msg << "Expecting " << EXAMPLE_NUM_TEST_ROWS << "rows, reported " << num_rows;
  			throw runtime_error(msg.str());
  		}
  		cout << "#\t Test table populated" << endl;

  }  catch (sql::SQLException &e) {
		/*
		The MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
		cout << endl;
		cout << "# ERR: DbcException in " << __FILE__;
		cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
		/* Use what(), getErrorCode() and getSQLState() */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "# ERR: Your server seems not to support PS at all because its MYSQL <4.1" << endl;
		}
		cout << "not ok 1 - RTA-DL3-Sim/DBConnector.cpp" << endl;

		return EXIT_FAILURE;
	} catch (std::runtime_error &e) {

		cout << endl;
		cout << "# ERR: runtime_error in " << __FILE__;
		cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what() << endl;
		cout << "not ok 1 - RTA-DL3-Sim/DBConnector.cpp" << endl;

		return EXIT_FAILURE;
	}
}
