#include "RequirementsLL.h"

std::string RequirementsLLNode::get_course_name() const {
	return this->course_name;
}

std::string RequirementsLLNode::get_course_status() const {
	return this->course_status;
}

RequirementsLLNode * RequirementsLLNode::get_next_requirement() const {
	return this->next_requirement;
}

void RequirementsLLNode::set_next_requirement(std::string course_name, 
					      std::string course_status) {
	this->next_requirement = new RequirementsLLNode(course_name, 
							course_status);
}

RequirementsLLNode * RequirementsLLNode::operator=(const RequirementsLLNode & rhs) {
	delete this->next_requirement;

	this->course_name = rhs.get_course_name();
	this->course_status = rhs.get_course_status();
	this->next_requirement = rhs.get_next_requirement();

	return this;
}

/* ----------------- LL methods below here ------------------ */

RequirementsLLNode * RequirementsLL::get_first_requirement() const {
	return this->first_requirement;
}

void RequirementsLL::set_first_requirement(std::string course_name, 
					   std::string course_status) {
	this->first_requirement = new RequirementsLLNode(course_name, 
							 course_status);
}

void RequirementsLL::insert_requirement(std::string course_name, 
					std::string course_status) {
	RequirementsLLNode * pointer = this->get_first_requirement();

	if (!pointer) {
		this->set_first_requirement(course_name, course_status);
	} else {
		while (pointer->get_next_requirement()) {
			pointer = pointer->get_next_requirement();
		}

		pointer->set_next_requirement(course_name, course_status);
	}
}


RequirementsLL * RequirementsLL::operator=(const RequirementsLL & rhs) {
	this->~RequirementsLL();

	RequirementsLLNode * pointer = rhs.get_first_requirement();

	while (pointer) {
		this->insert_requirement(pointer->get_course_name(), 
					 pointer->get_course_status());
		pointer = pointer->get_next_requirement();
	}

	return this;
}

RequirementsLL::~RequirementsLL() {
	RequirementsLLNode * pointer = this->get_first_requirement();

	while (pointer) {
		RequirementsLLNode * temp = pointer;
		pointer = pointer->get_next_requirement();
		delete temp;
	}
}
