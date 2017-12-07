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
		RequirementsLLNode(const RequirementsLLNode &other);

		std::string get_course_name() const;
		std::string get_course_status() const;

		RequirementsLLNode * get_next_requirement() const;
		void set_next_requirement(std::string course_name, 
					  std::string course_status);

		RequirementsLLNode * operator=(const RequirementsLLNode & rhs);
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
		RequirementsLL(const RequirementsLL &other);

		RequirementsLLNode * get_first_requirement() const;
		void set_first_requirement(std::string course_name, 
					   std::string course_status);

		void insert_requirement(std::string course_name, 
					std::string course_status);

		RequirementsLL * operator=(const RequirementsLL & rhs);	

		~RequirementsLL();
	private:
		RequirementsLLNode * first_requirement;
};
