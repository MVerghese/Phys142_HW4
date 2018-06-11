#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef vector< vector<double> > vecvec;

ifstream iFile;
ofstream oFile;

bool readState(string fileName, vecvec &HList, vecvec &VList, vecvec &boundingBoxes, vecvec &particleStates, vecvec &particleMomentums);
bool writeState(string fileName, vecvec HList, vecvec VList, vecvec boundingBoxes, vecvec particleStates, vecvec particleMomentums);

int main() {
	vecvec HList;
	vecvec VList;
	vecvec boundingBoxes;
	vecvec particleStates;
	vecvec particleMomentums;

	for(int i=0; i<5; i++) {
		vector<double> temp1;
		vector<double> temp2;
		vector<double> temp3;
		vector<double> temp4;
		vector<double> temp5;




		for(int j=0; j<3; j++) {
			temp1.push_back(i+j);
			temp2.push_back(i+j+10);

		}

		for(int k=0; k<4; k++) {
			temp3.push_back(i+k+20);
		}

		HList.push_back(temp1);
		VList.push_back(temp2);
		boundingBoxes.push_back(temp3);


		temp4.push_back(i+30);
		temp4.push_back(i+30+1);

		temp5.push_back(i+40);
		temp5.push_back(i+40+1);

		particleStates.push_back(temp4);
		particleMomentums.push_back(temp5);


	}

	//writeState("test.txt", HList, VList, boundingBoxes, particleStates, particleMomentums);
	readState("test.txt", HList, VList, boundingBoxes, particleStates, particleMomentums);

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

bool readState(string fileName, vecvec &HList, vecvec &VList, vecvec &boundingBoxes, vecvec &particleStates, vecvec &particleMomentums) {
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
	boundingBoxes.clear();
	particleStates.clear();
	particleMomentums.clear();

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

	for(int i=0; i < data[2].size(); i+=5) {
    	vector<double> temp;
		temp.push_back(stod(data[2][i]));
    	temp.push_back(stod(data[2][i+1]));
    	temp.push_back(stod(data[2][i+2]));
    	temp.push_back(stod(data[2][i+3]));
    	temp.push_back(stod(data[2][i+4]));    	
    	boundingBoxes.push_back(temp);
    }

    for(int i=0; i < data[3].size(); i+=2) {
    	vector<double> temp;
		temp.push_back(stod(data[3][i]));
    	temp.push_back(stod(data[3][i+1]));
    	particleStates.push_back(temp);
    }

	for(int i=0; i < data[4].size(); i+=2) {
    	vector<double> temp;
		temp.push_back(stod(data[4][i]));
    	temp.push_back(stod(data[4][i+1]));
    	particleMomentums.push_back(temp);
    }
    return true;


}


bool writeState(string fileName, vecvec HList, vecvec VList, vecvec boundingBoxes, vecvec particleStates, vecvec particleMomentums) {
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
	for(vector<double> box : boundingBoxes) {
		for(double coord : box) {
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

	out = "";
	for(vector<double> particle : particleMomentums) {
		for(double coord : particle) {
			out += to_string(coord) + ",";
		}
	}
	out.pop_back();
	oFile << out << endl;


	oFile.close();

	return true;





}
