#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef vector< vector<double> > vecvec;

ifstream iFile;
ofstream oFile;

bool readState(string fileName, vecvec &HList, vecvec &VList, vecvec &particleStates);
bool writeState(string fileName, vecvec HList, vecvec VList, vecvec particleStates);

int main() {
	vecvec HList;
	vecvec VList;
	vecvec particleStates;

	for(int i=0; i<5; i++) {
		vector<double> temp1;
		vector<double> temp2;
		vector<double> temp3;

		for(int j=0; j<3; j++) {
			temp1.push_back(i+j);
			temp2.push_back(i+j+10);

		}
		HList.push_back(temp1);
		VList.push_back(temp2);

		temp3.push_back(i+20);
		temp3.push_back(i+20+1);

		particleStates.push_back(temp3);


	}

	writeState("test.txt", HList, VList, particleStates);
	readState("test.txt", HList, VList, particleStates);

	cout << "HList: " << endl;
	for(vector<double> barrier : HList) {
		for(double coord : barrier) {
			cout << coord << ",";
		}
		cout << endl;
	}
	cout << endl;

	cout << "VList: " << endl;	
	for(vector<double> barrier : VList) {
		for(double coord : barrier) {
			cout << coord << ",";
		}
		cout << endl;
	}
	cout << endl;

	cout << "particleStates: " << endl;
	for(vector<double> particle : particleStates) {
		for(double coord : particle) {
			cout << coord << ",";
		}
		cout << endl;
	}
	cout << endl;


}

bool readState(string fileName, vecvec &HList, vecvec &VList, vecvec &particleStates) {
	iFile.open(fileName);

	//Read in CSV as a vector of vectors of strings
	vector < vector<string> > data;
	while (iFile) {
	    string s;
	    if (!getline( iFile, s )) break;

	    istringstream ss( s );
	    vector <string> record;

	    while (ss) {
	      string s;
	      if (!getline( ss, s, ',' )) break;
	      record.push_back( s );
	    }

	    data.push_back( record );
	}
	if (!iFile.eof()) {
	    cerr << "Fooey!\n";
	    return false;
	}
	iFile.close();

	//Clear any exisitng items in the lists
	HList.clear();
	VList.clear();
	particleStates.clear();

	//Read in each vector
    for(int i=0; i < data[0].size(); i+=3) {
    	vector<double> temp;
    	temp.push_back(stod(data[0][i]));
    	temp.push_back(stod(data[0][i+1]));
    	temp.push_back(stod(data[0][i+2]));

    	HList.push_back(temp);
    }

    for(int i=0; i < data[1].size(); i+=3) {
    	vector<double> temp;
		temp.push_back(stod(data[1][i]));
    	temp.push_back(stod(data[1][i+1]));
    	temp.push_back(stod(data[1][i+2]));    	
    	VList.push_back(temp);
    }

    for(int i=0; i < data[2].size(); i+=2) {
    	vector<double> temp;
		temp.push_back(stod(data[2][i]));
    	temp.push_back(stod(data[2][i+1]));
    	particleStates.push_back(temp);
    }

    return true;


}


bool writeState(string fileName, vecvec HList, vecvec VList, vecvec particleStates) {
	oFile.open(fileName);
	string out;
	out = "";
	for(vector<double> barrier : HList) {
		for(double coord : barrier) {
			out += to_string(coord) + ",";
		}
	}
	out.pop_back();
	oFile << out << endl;

	out = "";
	for(vector<double> barrier : VList) {
		for(double coord : barrier) {
			out += to_string(coord) + ",";
		}
	}
	out.pop_back();
	oFile << out << endl;

	out = "";
	for(vector<double> particle : particleStates) {
		for(double coord : particle) {
			out += to_string(coord) + ",";
		}
	}
	out.pop_back();
	oFile << out << endl;

	oFile.close();

	return true;





}
