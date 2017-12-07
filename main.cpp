#include <fstream>
#include <unordered_map>
#include "RequirementsLL.h"

using namespace std;

unordered_map<string, string> create_offerings_map(string offerings);

int main(int argc, char ** argv){
	string line;
	int credLimit;
	unordered_map<string, int> credTags;
	vector<RequirementsLL> reqGraph;
	ifstream reqFile(argv[1]);
	if(reqFile.is_open()){
		while(getline(reqFile,line)){
			if(line.substr(0,5) == "TOTAL"){
				credLimit = stoi(line.substr(6,3));
				cout << "credlimit: " << credLimit << endl;
			}else if(line.substr(0,6) == "CREDIT"){
				cout << "credTags[" << line.substr(7,1) << "] = " << line.substr(9,3) << endl;
				credTags[line.substr(7,1)] = stoi(line.substr(9,3));
			}else if(line.substr(0,6) == "COURSE"){
				RequirementsLL reqLL;
				reqLL.set_first_requirement(line.substr(7,5),line.substr(13,1));
				cout << line.substr(7,5) << " added to graph." << endl;
				int classIdx = 15;
				if(line.substr(13,1) == "R"){
					while(classIdx < line.length()){
						reqLL.insert_requirement(line.substr(classIdx,5),line.substr(13,1));
						cout << line.substr(classIdx,5) << " is a prereq" << endl;
						classIdx += 6;
					}
				}else if(line.substr(13,1) == "O"){
					while(classIdx < line.length()){
						reqLL.insert_requirement(line.substr(classIdx,5),line.substr(13,1));
						cout << line.substr(classIdx,5) << " is an optional prereq" << endl;
						classIdx += 6;
					}
				}else if(line.substr(13,1) == "M"){
					cout << line.substr(7,5) << " is mandatory!" << endl;
				}
				reqGraph.push_back(reqLL);
			}else if(line.substr(0,6) == "CHOOSE"){
			//This still needs to be done
			}
		}
		reqFile.close();
	}else cout << "Unable to open " << argv[1] << endl;

	unordered_map<string, string> offerings_graph;

	ifstream offerings_file(argv[2]);
	line = "";
	
	if (offerings_file.is_open()) {
		while (getline(offerings_file, line)) {
			string course_name = line.substr(0, 5);
			string credits = line.substr(6);

			cout << "offerings_graph[" << course_name << "] = " << credits << endl;
			offerings_graph[course_name] = credits;
		}

		offerings_file.close();
	} else {
		cout << "Could not open " << argv[2] << endl;
	}
	/*
	cout << endl;
	unordered_map<string, string>::iterator it;
	for (it = offerings_graph.begin() ; it != offerings_graph.end() ; it++) {
		cout << it->first << endl;
	}
	*/
}
