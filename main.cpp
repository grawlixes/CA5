#include <fstream>
#include <algorithm>
#include <unordered_map>
#include "RequirementsLL.h"

using namespace std;

int main(int argc, char ** argv){
	string line;
	string error_message = "";

	int credLimit;
	int count = 1;

	unordered_map<string, int> credTags;

	vector<RequirementsLL> reqGraph;

	// has as many elements as there are "CHOOSE" lines
	vector<int> choose_options;
	vector<string> choose_reqs;

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
				string classes = line.substr(7);
				choose_reqs.push_back(classes);

				char number = classes[0];
				choose_options.push_back(number - '0');
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
							// the index of the choice in the vector
							reqGraph[index].get_first_requirement()->choose[0] = count;
							// how many are needed at that index (value at index)
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
	vector<string> schedule;
	if (schedule_file.is_open()){
		while(getline(schedule_file,line)){
			schedule.push_back(line);
		}
		schedule_file.close();
	}
	//order the semesters
	string temp;
	for(int i = 0; i < schedule.size(); i++){
		for(int j = i+1; j < schedule.size(); j++){
			if(schedule[i].substr(1,4) == schedule[j].substr(1,4)){
				if(schedule[i][0] < schedule[j][0]){
					temp = schedule[i];
					schedule[i] = schedule[j];
					schedule[j] = temp;
				}
			}else{
				if(schedule[i].substr(1,4) > schedule[j].substr(1,4)){
					temp = schedule[i];
					schedule[i] = schedule[j];
					schedule[j] = temp;
				}
			}
		}
	}
	for(int i = 0; i < schedule.size(); i++){
		cout << schedule[i] << endl;
	}
	int credCount;
	bool preMet, mandatory, tagMet;
	preMet = true;
	mandatory = true;
	tagMet = true;
	vector<string> takenClasses;
	for(int i = 0; i < schedule.size(); i++){
		int classIdx = 6;
		vector<string> semesterClasses;
		while(classIdx < schedule[i].length() && preMet){
			int graphIdx = 0;
			while(graphIdx < reqGraph.size() && reqGraph[graphIdx].get_first_requirement()->get_course_name() != schedule[i].substr(classIdx,5)){
				graphIdx++;
			}
			RequirementsLLNode* myPtr = reqGraph[graphIdx].get_first_requirement();
			if(myPtr->get_course_status() == "R"){
				while(myPtr->get_next_requirement()){
					if(find(takenClasses.begin(), takenClasses.end(), myPtr->get_next_requirement()->get_course_name()) == takenClasses.end()) {
						preMet = false;
						error_message = "Prerequisite " + myPtr->get_next_requirement()->get_course_name() + " for " + reqGraph[graphIdx].get_first_requirement()->get_course_name() + " not yet taken";
						break;
					} 
				}				
			}			 

			char semester_taken = schedule[i][0];
			char semester_offered = offerings_graph[reqGraph[graphIdx].get_first_requirement()->get_course_name()][2];

			if (semester_taken != semester_offered and semester_offered != 'E') {
				error_message = "Class " + reqGraph[graphIdx].get_first_requirement()->get_course_name() +
						" is not offered this semseter.";
			}

			if (preMet && reqGraph[graphIdx].get_first_requirement()->choose[1] != 0) {
				choose_options[(reqGraph[graphIdx].get_first_requirement()->choose[0])-1] -= 1;
			}

			//cout << reqGraph[graphIdx].get_first_requirement()->get_course_name() << endl;
			//cout << "graphIdx: " << graphIdx << endl;
			classIdx += 6;
		}
		if(!preMet){
			break;
		}
	}

	if (preMet) {
		int a;
		for (a = 0 ; a < choose_options.size() ; a++) {
			if (choose_options[a] != 0) {
				error_message = "Missing " + to_string(choose_options[a])
						+ " courses from any of the following: " +
						choose_reqs[a];
				break;
			}
		}
	}


	if (error_message != "") {
		cout << "Schedule is flawed." << endl << endl;
		cout << error_message << endl;
	} else {
		cout << "You're good to go!" << endl;
	}
}



// VVV IGNORE THESE THEY ARE TAKEN CARE OF VVV



/* This code goes where the class was accepted.
   It checks to see if the class that was accepted
   fulfills any CHOOSE requirements, and if so,
   it marks down the number of that number which we
   need by one (saved in choose_options). At the end,
   I will check to see that all are marked down to zero. If not,
   I will list the CHOOSE courses and how many are needed.

if (myPtr->choose[1] != 0) {
	choose_options[(myPtr->choose[0])-1] -= 1;
}

--------

   This goes after all the classes are checked. If nothing was caught before,
   it'll check all of the elements in the options vector and make sure they're
   all zero. If even one of them is 1 or more, then we need that many more classes
   from the (index+1)th CHOOSE statement in order to pass this requirement.
   The assignment requires the course name(s) to be listed specifically, but we only
   have to actually name one discrepancy.

int a;
for (a = 0 ; a < choose_options.size() ; a++) {
	if (choose_options[a] != 0) {
		error_message = "Missing " + to_string(choose_options[a])
			        + " courses from any of the following: " +
				choose_reqs[a]";
		break;
	}
}

		   			Will move this code. */
