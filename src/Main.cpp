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

#include<iostream>


#include"EventDL3Handler.h"


using std::cout;
using std::endl;
using std::string;


const char* startString = {
"################################################################\n"
"###                   - Task dl3-Simulator -                 ###"
};

const char* endString = {
"### Task dl3-Simulator exiting ............................... ###\n"
"################################################################"
};



int main(int argc, char *argv[])
{

	cout << startString << endl;

	if(argc != 11) {	// METTER IN INPUT NOME DATABASE E NOME TABELLA
		cout << "Insert 10 input parameters:\n"
		"1 - fitsFileNamePath: Input fits file path.\n"
		"2 - idObs: Insert observation id.\n"
		"3 - idRepo: Insert Repository id.\n"
		"4 - insertMode: '0' to execute Batch insert mode,\n		'1' to execute Transaction Batch insert mode,\n		'2' to execute Streaming insert mode.\n"	//		'3' to execute Streaming by String insert mode.\n		'4' to execute Transaction Batch by string insert mode\n
		"5 - rate: How events per second insert in DB.\n"
		"6 - host: Insert host name.\n"
		"7 - userId: Input database user id.\n"
		"8 - userPwd: Input database user password\n"
		"9 - dbName: Insert database name.\n"
		"10 - tbName: Insert table name.\n"
		 << endl;

		cout << endString << endl;
		return 0;
	}

  const char * fitsFileName = argv[1];
  int idObs = atoi(argv[2]);
  int idRepo = atoi(argv[3]);
	int insertMode = atoi(argv[4]);
	double rate = atof(argv[5]);
	const char * host = argv[6];
	const char * userId = argv[7];
	const char * userPwd = argv[8];
	const char * dbName = argv[9];
	const char * tbName = argv[10];

	// PRINT INPUT PARAMETERS
	cout << "\n	=====" << endl;
	cout << "fitsFileNamePath: " << fitsFileName << endl;
	cout << "idObs: " << idObs << endl;
	cout << "idRepo: " << idRepo << endl;
	cout << "insertMode: " << insertMode << endl;
	cout << "rate: " << rate << endl;
	cout << "host: " << host << endl;
	cout << "userId: " << userId << endl;
	cout << "dbName: " << dbName << endl;
	cout << "tbName: " << tbName << endl;
	cout << "\n	=====" << endl;

	EventDL3Handler evtDL3Handler(fitsFileName, idObs, idRepo, rate, host, userId, userPwd, dbName, tbName);
	if ( insertMode == 0 ) {

		evtDL3Handler.BatchEventManager();

	} else if (insertMode == 1) {

		evtDL3Handler.TransactionBatchEventManager();


	} else if (insertMode == 2) {

		evtDL3Handler.StreamingEventManager();

	} else if ( insertMode != 0 || insertMode != 1 || insertMode != 2 ) {	//|| insertMode != 3

		cout << "ERROR: INSERT MODE PARAMETER! " << endl;

	}



	return 0;
}
