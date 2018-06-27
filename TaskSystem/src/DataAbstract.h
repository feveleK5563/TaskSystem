#pragma once
#include <string>

enum struct ObjectState
{
	Active,		//�ʏ�
	Stop,		//��~
	Kill,		//����
};

struct DataAbstract
{
	const std::string	groupName;	//�O���[�v��
	float				priority;	//�`��D��x
	ObjectState			state;		//���

	DataAbstract(const std::string& groupName, float priority) :
		groupName(groupName),
		priority(priority),
		state(ObjectState::Active) {};

	virtual ~DataAbstract() {};
};