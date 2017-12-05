#include <fstream>
#include <unordered_map>
#include "RequirementsLL.h"

using namespace std;
//using namespace __gnu_cxx;

int main(int argc, char ** argv){
	string line;
	int credLimit;
	unordered_map<string, int> credTags;
	vector<RequirementsLL> reqGraph;
	ifstream reqFile(argv[1]);
	if(reqFile.is_open()){
		while(getline(reqFile,line)){
			cout <<"start" << line << "end"<< endl;
			if(line.substr(0,5) == "TOTAL"){
				credLimit = stoi(line.substr(6,3));
				cout << "credlimit: " << credLimit << endl;
			}else if(line.substr(0,6) == "CREDIT"){
				cout << "credTags[" << line.substr(7,1) << "] = " << line.substr(9,3) << endl;
				credTags[line.substr(7,1)] = stoi(line.substr(9,3));
			}else if(line.substr(0,6) == "COURSE"){
				cout << line.substr(7,5) << " added to graph." << endl;
				int classIdx = 15;
				if(line.substr(13,1) == "R"){
					while(classIdx < line.length()){
						cout << line.substr(classIdx,5) << " is a prereq" << endl;
						classIdx += 6;
					}
				}else if(line.substr(13,1) == "O"){
					while(classIdx < line.length()){
						cout << line.substr(classIdx,5) << " is a prereq" << endl;
						classIdx += 6;
					}
				}else if(line.substr(13,1) == "M"){
					cout << line.substr(7,5) << "is mandatory!" << endl;
				}
			}
		}
		reqFile.close();
	}else cout << "Unable to open " << argv[1] << endl;
}
