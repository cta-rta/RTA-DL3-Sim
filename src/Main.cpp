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

	if(argc != 7) {
		cout << "Insert 6 input parameters:\n"
		"1 - fitsFileNamePath: Input fits file path.\n"
		"2 - idObs: \n"
		"3 - idRepo: \n"
		"4 - rate: How events per second insert in DB.\n"
		"5 - userId: Input database user id.\n"
		"6 - userPwd: Input database user password\n"
		 << endl;

		cout << endString << endl;
		return 0;
	}

  const char * fitsFileName = argv[1];
  int idObs = atoi(argv[2]);
  int idRepo = atoi(argv[3]);
	double rate = atof(argv[4]);
	const char * userId = argv[5];
	const char * userPwd = argv[6];

	// PRINT INPUT PARAMETERS
	cout << "\n	=====" << endl;
	cout << "fitsFileNamePath: " << fitsFileName << endl;
	cout << "idObs: " << idObs << endl;
	cout << "idRepo: " << idRepo << endl;
	cout << "rate: " << rate << endl;
	cout << "userId: " << userId << endl;
	cout << "\n	=====" << endl;

	EventDL3Handler evtDL3Handler(fitsFileName, idObs, idRepo, rate, userId, userPwd);



	return 0;
}
