#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class RequirementsLLNode {
	public:
		RequirementsLLNode(std::string course_name, std::string course_status) {
			this->course_name = course_name;
			this->course_status = course_status;
			this->next_requirement = nullptr;
		}

		std::string get_course_name();
		std::string get_course_status();

		RequirementsLLNode * get_next_requirement();
		void set_next_requirement(std::string course_name, 
					  std::string course_status);
	private:
		std::string course_name;
		std::string course_status;

		RequirementsLLNode * next_requirement;
};

class RequirementsLL {
	public:
		RequirementsLL() {
			first_requirement = nullptr;
		}

		RequirementsLLNode * get_first_requirement();
		void set_first_requirement(std::string course_name, 
					   std::string course_status);

		void insert_requirement(std::string course_name, 
					std::string course_status);

		~RequirementsLL();
	private:
		RequirementsLLNode * first_requirement;
};
