#include <fstream>
//#include <hash_map>
#include "RequirementsLL.h"

using namespace std;
//using namespace __gnu_cxx;

int main(int argc, char ** argv){
	string line;
	int credLimit;
	//hash_map<const string, int, hash<const char*>, eqstr> credTags;
	ifstream reqFile(argv[1]);
	if(reqFile.is_open()){
		while(getline(reqFile,line,' ')){
			cout << line << endl;
			if(line == "TOTAL"){
				getline(reqFile,line,' ');
				credLimit = stoi(line);
			}
			if(line == "CREDIT"){
				//string credLetter;
				//getline(reqFile,credLetter,' ');
				//getline(reqFile,line,' ');
				//cout << "credTags[" << credLetter << "] = " << line << endl;
				//credTags[credLetter] = stoi(line)
			}
		}
		reqFile.close();
	}else cout << "Unable to open " << argv[1] << endl;
	//hash_map<const string, int, hash<const char*>, eqstr> classes;
}
