#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class RequirementsLLNode {
	public:
		RequirementsLLNode() {
			next_requirement = nullptr;
		}

		std::string get_course_name();
		RequirementsLLNode * get_next_requirement();

	private:
		std::string course_name;
		RequirementsLLNode * next_requirement;
};

class RequirementsLL {
	public:
		RequirementsLL() {
			first_requirement = nullptr;
		}

		RequirementsLLNode * get_first_requirement();

		~RequirementsLL();
	private:
		RequirementsLLNode * first_requirement;
};
