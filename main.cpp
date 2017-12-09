#include <fstream>
#include <unordered_map>
#include "RequirementsLL.h"

using namespace std;

int main(int argc, char ** argv){
	string line;
	int credLimit;
	unordered_map<string, int> credTags;
	vector<RequirementsLL> reqGraph;
	ifstream reqFile(argv[1]);
	int count = 1;
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
				string classes = line.substr(7);
				char number = classes[0];
				classes = classes.substr(2);

				vector<string> options;

				while (classes.length() >= 5) {
					if (classes.length() != 5) {
						options.push_back(classes.substr(0, 5));
						classes = classes.substr(6);
					} else {
						options.push_back(classes);
						classes = "";
					}
				}

				int index;
				// O(n) update time
				for (index = 0 ; index < reqGraph.size() ; index++) {
					int i;
					for (i = 0 ; i < options.size() ; i++) {
						if (reqGraph[index].get_first_requirement()->get_course_name() ==
						   options[i]) {
							reqGraph[index].get_first_requirement()->choose[0] = count;
							reqGraph[index].get_first_requirement()->choose[1] = number - '0';
							options.erase(options.begin()+i);
						}
					}
				}

				for (index = 0 ; index < reqGraph.size() ; index++) {
					cout << reqGraph[index].get_first_requirement()->get_course_name()
						<< " " << reqGraph[index].get_first_requirement()->choose[0]
						<< ", " << reqGraph[index].get_first_requirement()->choose[1] << endl;
				}

				count++;
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

	ifstream schedule_file(argv[3]);
	line = "";
}
