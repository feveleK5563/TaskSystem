#pragma once
#include <string>

enum struct ObjectState
{
	Active,		//’Êí
	Stop,		//’â~
	Kill,		//Á–Å
};

struct DataAbstract
{
	const std::string	groupName;	//ƒOƒ‹[ƒv–¼
	float				priority;	//•`‰æ—Dæ“x
	ObjectState			state;		//ó‘Ô

	DataAbstract(const std::string& groupName, float priority) :
		groupName(groupName),
		priority(priority),
		state(ObjectState::Active) {};

	virtual ~DataAbstract() {};
};