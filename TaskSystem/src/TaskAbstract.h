#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>

enum struct ObjectState
{
	Active,		//�ʏ�
	Stop,		//��~
	Kill,		//����
}; 

class TaskAbstract
{
public:
	const std::string	groupName;	//�O���[�v��
	float				priority;	//�`��D��x
	ObjectState			state;		//���

	TaskAbstract(	const std::string& groupName,
					float priority,
					ObjectState state = ObjectState::Active);

	virtual ~TaskAbstract() {};
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
};