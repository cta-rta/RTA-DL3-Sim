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

//#include "CtaEvtReader.h"
//#include "FileWriter.h"
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

	if(argc != 9) {
		cout << "Insert 9 input parameters:\n"
		"1 - fitsFileNamePath: Input fits file path.\n"
		"2 - idObs: \n"
		"3 - idRepo: \n"
		"4 - tmin: \n"
		"5 - tmax: \n"
		"6 - rate: \n"
		"7 - userId: \n"
		"8 - userPwd: \n"
		 << endl;

		cout << endString << endl;
		return 0;
	}

  const char * fitsFileName = argv[1];
  int idObs = atoi(argv[2]);
  int idRepo = atoi(argv[3]);
	double tmin = atof(argv[4]);
	double tmax = atof(argv[5]);
	double rate = atof(argv[6]);
	const char * userId = argv[7];
	const char * userPwd = argv[8];

	// PRINT INPUT PARAMETERS
	cout << "\n" << endl;
	cout << "fitsFileNamePath: " << fitsFileName << endl;
	cout << "idObs: " << idObs << endl;
	cout << "idRepo: " << idRepo << endl;
	cout << "tmin: " << tmin << endl;
	cout << "tmax: " << tmax << endl;
	cout << "rate: " << rate << endl;
	cout << "userId: " << userId << endl;
	cout << "userPwd: " << userPwd << endl;

	EventDL3Handler evtDL3Handler(fitsFileName,idObs,idRepo,tmin,tmax,rate,userId,userPwd);



	return 0;
}
