#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>

enum struct TaskState
{
	Ready,		//����
	Active,		//�ʏ�
	Stop,		//��~
	Kill,		//���ŗv��
	Delete,		//����
}; 

class TaskAbstract
{
public:
	const std::string	groupName;	//�O���[�v��
	float				priority;	//�`��D��x
	TaskState			state;		//���

	//�R���X�g���N�^
	TaskAbstract(	const std::string& groupName,
					float priority,
					TaskState state = TaskState::Active);

	//�f�X�g���N�^
	virtual ~TaskAbstract() {};
	
	virtual void Initialize() = 0;	//����������
	virtual void Finalize() = 0;	//�I������
	virtual void Update() = 0;		//�X�V
	virtual void Draw() = 0;		//�`��

protected:
	void KillMe();	//�������E��
};