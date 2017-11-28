#include <"RequirementsLL.h">

std::string RequirementsLLNode::get_course_name() {
	return this->course_name;
}

RequirementsLLNode * RequirementsLLNode::get_next_requirement() {
	return this->next_requirement;
}

RequirementsLLNode * RequirementsLL::get_first_requirement() {
	return this->first_requirement;
}

RequirementsLL::~RequirementsLL() {
	RequirementsLLNode * pointer = this->first_requirement;

	while (pointer) {
		RequirementsLLNode * temp = pointer;
		pointer = pointer->next_requirement;
		delete temp;
	}
}
