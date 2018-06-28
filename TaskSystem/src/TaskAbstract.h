#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>

enum struct ObjectState
{
	Active,		//’Êí
	Stop,		//’â~
	Kill,		//Á–Å
}; 

class TaskAbstract
{
public:
	const std::string	groupName;	//ƒOƒ‹[ƒv–¼
	float				priority;	//•`‰æ—Dæ“x
	ObjectState			state;		//ó‘Ô

	TaskAbstract(	const std::string& groupName,
					float priority,
					ObjectState state = ObjectState::Active);

	virtual ~TaskAbstract() {};
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
};