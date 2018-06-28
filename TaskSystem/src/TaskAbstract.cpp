#include "TaskAbstract.h"

TaskAbstract::TaskAbstract(	const std::string& groupName,
							float priority,
							ObjectState state):
	groupName(groupName),
	priority(priority),
	state(state) {}