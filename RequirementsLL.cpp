#include "RequirementsLL.h"

std::string RequirementsLLNode::get_course_name() {
	return this->course_name;
}

std::string RequirementsLLNode::get_course_status() {
	return this->course_status;
}

RequirementsLLNode * RequirementsLLNode::get_next_requirement() {
	return this->next_requirement;
}

void RequirementsLLNode::set_next_requirement(std::string course_name, 
					      std::string course_status) {
	this->next_requirement = new RequirementsLLNode(course_name, course_status);
}

/* ----------------- LL methods below here ------------------ */

RequirementsLLNode * RequirementsLL::get_first_requirement() {
	return this->first_requirement;
}

void RequirementsLL::set_first_requirement(std::string course_name, 
					   std::string course_status) {
	this->first_requirement = new RequirementsLLNode(course_name, course_status);
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

RequirementsLL::~RequirementsLL() {
	RequirementsLLNode * pointer = this->get_first_requirement();

	while (pointer) {
		RequirementsLLNode * temp = pointer;
		pointer = pointer->get_next_requirement();
		delete temp;
	}
}
