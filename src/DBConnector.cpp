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
  		con.reset(driver->connect (url, userId, userPwd)); // connect to mysql

  		con->setSchema(database);

  		boost::scoped_ptr< sql::Statement > stmt(con->createStatement());


  	} catch (sql::SQLException &e) {
  		/*
  		The MySQL Connector/C++ throws three different exceptions:

  		- sql::MethodNotImplementedException (derived from sql::SQLException)
  		- sql::InvalidArgumentException (derived from sql::SQLException)
  		- sql::SQLException (derived from std::runtime_error)#include <chrono>
  		*/#include <chrono>
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

int DBConnector::writeRowInDB(int _idObs, int _idRepo, double _mjdferi, double _mjdferf, double *dataWR){


  int idObs = _idObs;
  int idRepo = _idRepo;
  double mjdferi = _mjdferi;
  double mjdferf = _mjdferf;
  stringstream sql;
  stringstream msg;
  int num_rows;
  int status = 0;


  try {


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


    //rate
    //cout << "i: " << i << endl;
    //cout << dataWR[i][0] << endl;
    prep_stmt->setInt(1, (int)dataWR[0]);  // eventidfits
    //cout << "idObs: "<< idObs << endl;
    prep_stmt->setInt(2, idObs);  //observationid
    //cout<< "idRepo: "<< idRepo << endl;
    prep_stmt->setInt(3, idRepo);  //datarepositoryid
    //cout << dataWR[i][2] << endl;
    prep_stmt->setDouble(4, 0);  //time dataWR[i][1]
    //cout << dataWR[i][3] << endl;
    prep_stmt->setDouble(5, dataWR[2]); //ra_deg
    //cout << dataWR[i][4] << endl;
    prep_stmt->setDouble(6, dataWR[3]); //dec_deg
    //cout << dataWR[i][5] << endl;
    prep_stmt->setDouble(7, dataWR[4]); // energy
    //cout << dataWR[i][6] << endl;
    prep_stmt->setDouble(8, dataWR[5]); //detx
    //cout << dataWR[i][7] << endl;
    prep_stmt->setDouble(9, dataWR[6]);  //dety
    //cout << dataWR[i][8] << endl;
    prep_stmt->setInt(10, (int)dataWR[7]);  //mcid
    prep_stmt->setInt(11, status); //status
    prep_stmt->setDouble(12, dataWR[1] ); //timeraltt
    prep_stmt->setDouble(13, time(&timer));



    /* executeUpdate() returns the number of affected = inserted rows */
    num_rows += prep_stmt->executeUpdate();
    //cout << "Num rows added: "<< num_rows << endl;



  		if (ONE_ROW != num_rows) {
  			msg.str("");
  			msg << "Expecting " << ONE_ROW << "rows, reported " << num_rows;
  			throw runtime_error(msg.str());
  		}
  		//cout << "#\t Test table populated" << endl;

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
