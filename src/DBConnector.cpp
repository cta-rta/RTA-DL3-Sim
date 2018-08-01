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

DBConnector::DBConnector(int _idObs, int _idRepo, string _host, string _userId, string _userPwd, string _dbName, string _tbName){

  url = _host;
  dbName = _dbName;
  tbName = _tbName;
  userId = _userId;
  userPwd = _userPwd;
  idObs = _idObs;
  idRepo = _idRepo;


  cout << "DBConnector constructor" << endl;
  cout << "host: " << url << endl;
  cout << "dbName: " << dbName << endl;
  cout << "tbName: " << tbName << endl;
  cout << "UserId: " << userId << endl;
  cout << "UserPwd: " << userPwd << endl;


}

int DBConnector::connect() {

    try {

      driver = sql::mysql::get_driver_instance();

      /* Using the Driver to create a connection */
  		con.reset(driver->connect (url, userId, userPwd)); // connect to mysql

  		con->setSchema(dbName);


  	} catch (sql::SQLException &e) {
  		/*
  		The MySQL Connector/C++ throws three different exceptions:

  		- sql::MethodNotImplementedException (derived from sql::SQLException)
  		- sql::InvalidArgumentException (derived from sql::SQLException)
  		- sql::SQLException (derived from std::runtime_error)#include <chrono>
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

int DBConnector::startTransaction(){

  /* Creating a "simple" statement - "simple" = not a prepared statement */
	boost::scoped_ptr< sql::Statement > stmt(con->createStatement());

  stmt->execute("START TRANSACTION");

}

int DBConnector::commitTransaction(){

  /* Creating a "simple" statement - "simple" = not a prepared statement */
	boost::scoped_ptr< sql::Statement > stmt(con->createStatement());

  stmt->execute("COMMIT");

}


int DBConnector::writeRowInDBByString(int idObs, int idRepo, double *dataWR){

  stringstream sql;
  string insert;
  stringstream msg;
  int num_rows = 0;
  int status = 0;


  try {


    /* Creating a PreparedStatement */
    boost::scoped_ptr< sql::Statement > stmt(con->createStatement());

    time_t seconds;
    seconds = time(NULL);

    insert = "INSERT INTO "

    + tbName +

    "(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES ("


    + FileWriter::convertToString(dataWR[0]) + " ,"

    + FileWriter::convertToString( idObs ) + " , "

    + FileWriter::convertToString( idRepo ) + " ,"

    + FileWriter::convertToString( dataWR[2] ) + " ,"

    + FileWriter::convertToString( dataWR[3] ) + ", "

    + FileWriter::convertToString( dataWR[4] ) + " , "

    + FileWriter::convertToString( dataWR[5] ) + " ,"

    + FileWriter::convertToString( dataWR[6] ) + " ,"

    + FileWriter::convertToString( dataWR[7] ) + " ,"

    + FileWriter::convertToString( status ) + " , "

    + FileWriter::convertToString( dataWR[1] ) + " ,"

    + FileWriter::convertToString( seconds ) + ")";


    /* executeUpdate() returns the number of affected = inserted rows */
    num_rows += stmt->executeUpdate(insert);


  	if (ONE_ROW != num_rows) {
			msg.str("");
			msg << "Expecting " << ONE_ROW << "rows, reported " << num_rows;
			throw runtime_error(msg.str());
  	}


  } catch (sql::SQLException &e) {
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


/*    NON FUNZIONANTE */
int DBConnector::writeRowInDBByFprintf(int idObs, int idRepo, double *dataWR){

  stringstream sql;
  //fprintf insert;
  stringstream msg;
  int num_rows = 0;
  int status = 0;
  //FileWriter fw;


  try {


    /* Creating a PreparedStatement */
    //boost::scoped_ptr< sql::PreparedStatement >  prep_stmt;
    boost::scoped_ptr< sql::Statement > stmt(con->createStatement());

    FILE * pFile;

    pFile = fopen ("localhost/evt_test/evt/","r+");



    //prep_stmt.reset(con->prepareStatement("INSERT INTO evt(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));

    time_t seconds;
    seconds = time(NULL);


    //fprintf(pFile,"INSERT INTO  %s",tbName,"(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES (%d , %d, %f, %f, %f, %f, %f, %d, %d %f,%d )",dataWR[0], idObs, idRepo, dataWR[2], dataWR[3], dataWR[4], dataWR[5], dataWR[6], dataWR[7], status, dataWR[1], seconds);

    //stmt->execute(insert);
    /* executeUpdate() returns the number of affected = inserted rows */
    //num_rows += stmt->executeUpdate(fprintf(stmt(con->createStatement(),"INSERT INTO  %s",tbName,"(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES (",dataWR[0]," , ",idObs, ", ",idRepo," ,",dataWR[2]," ,",dataWR[3]," ,",dataWR[4],", ",dataWR[5]," , ",dataWR[6]," , ",dataWR[7]," , ",status," , ",dataWR[1]," ,",seconds,")"));
    //num_rows += stmt->executeUpdate();


  	if (ONE_ROW != num_rows) {
			msg.str("");
			msg << "Expecting " << ONE_ROW << "rows, reported " << num_rows;
			throw runtime_error(msg.str());
  	}


  } catch (sql::SQLException &e) {
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

/*  DEPRACATED  */
int DBConnector::writeTransactionInDB(int idObs, int idRepo, double *dataWR){

  stringstream sql;
  stringstream msg;
  int num_rows = 0;
  int status = 0;


  try {


    /* Creating a PreparedStatement */
    boost::scoped_ptr< sql::PreparedStatement >  prep_stmt;

    prep_stmt.reset(con->prepareStatement("INSERT INTO evt(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));

    prep_stmt->setInt(1, (int)dataWR[0]);  // eventidfits

    prep_stmt->setInt(2, idObs);  //observationid

    prep_stmt->setInt(3, idRepo);  //datarepositoryid

    prep_stmt->setDouble(4, dataWR[2]); //ra_deg

    prep_stmt->setDouble(5, dataWR[3]); //dec_deg

    prep_stmt->setDouble(6, dataWR[4]); // energy

    prep_stmt->setDouble(7, dataWR[5]); //detx

    prep_stmt->setDouble(8, dataWR[6]);  //dety

    prep_stmt->setInt(9, (int)dataWR[7]);  //mcid

    prep_stmt->setInt(10, status); //status

    prep_stmt->setDouble(11, dataWR[1] ); //timeraltt

    prep_stmt->setDouble(12, time(&timer)); //timestamp

    num_rows += prep_stmt->executeUpdate();


		if (ONE_ROW != num_rows) {
			msg.str("");
			msg << "Expecting " << ONE_ROW << "rows, reported " << num_rows;
			throw runtime_error(msg.str());
		}


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


int DBConnector::writeTransactionInDBByString(int idObs, int idRepo, double *dataWR){

  stringstream sql;
  string insert;
  stringstream msg;
  int num_rows = 0;
  int status = 0;
  //FileWriter fw;


  try {


    /* Creating a PreparedStatement */
    //boost::scoped_ptr< sql::PreparedStatement >  prep_stmt;
    boost::scoped_ptr< sql::Statement > stmt(con->createStatement());


    //prep_stmt.reset(con->prepareStatement("INSERT INTO evt(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"));

    time_t seconds;
    seconds = time(NULL);

    insert = "INSERT INTO "

    + tbName +

    "(eventidfits, observationid, datarepositoryid, ra_deg, dec_deg, energy, detx, dety, mcid, status, timerealtt, insert_time) VALUES ("


    + FileWriter::convertToString(dataWR[0]) + " ,"

    + FileWriter::convertToString( idObs ) + " , "

    + FileWriter::convertToString( idRepo ) + " ,"

    + FileWriter::convertToString( dataWR[2] ) + " ,"

    + FileWriter::convertToString( dataWR[3] ) + ", "

    + FileWriter::convertToString( dataWR[4] ) + " , "

    + FileWriter::convertToString( dataWR[5] ) + " ,"

    + FileWriter::convertToString( dataWR[6] ) + " ,"

    + FileWriter::convertToString( dataWR[7] ) + " ,"

    + FileWriter::convertToString( status ) + " , "

    + FileWriter::convertToString( dataWR[1] ) + " ,"

    + FileWriter::convertToString( seconds ) + ")";




    //stmt->execute(insert);
    /* executeUpdate() returns the number of affected = inserted rows */
    num_rows += stmt->executeUpdate(insert);


  	if (ONE_ROW != num_rows) {
			msg.str("");
			msg << "Expecting " << ONE_ROW << "rows, reported " << num_rows;
			throw runtime_error(msg.str());
  	}


  } catch (sql::SQLException &e) {
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
