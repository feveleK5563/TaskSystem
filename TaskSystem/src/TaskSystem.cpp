#include "TaskSystem.h"
#include <algorithm>

void TaskSystem::Update()
{
	AllUpdate();	//�S�ẴI�u�W�F�N�g��Update���Ă�
	AddObject();	//�ǉ��\��̃I�u�W�F�N�g��ǉ�����
	KillObject();	//��Ԃ�Kill�̃I�u�W�F�N�g���폜����

	SortObject();	//priority����ɏ����Ƀ\�[�g����
}

void TaskSystem::Draw()
{
	for (auto& it : task)
	{
		it->Draw();
	}
}

void TaskSystem::RegistrationObject(std::shared_ptr<TaskAbstract> createObj)
{
	if (createObj != nullptr)
	{
		addTask.emplace_back(createObj);
		taskData[addTask.back()->groupName].emplace_back(createObj);
	}
}

TaskSystem& TaskSystem::GetInstance()
{
	static TaskSystem ts;
	return ts;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//�S�ẴI�u�W�F�N�g��Update���Ă�
void TaskSystem::AllUpdate()
{
	for (auto& it : task)
	{
		it->Update();
	}
}

//�ǉ��\��̃I�u�W�F�N�g��ǉ�����
void TaskSystem::AddObject()
{
	if (addTask.empty())
		return;

	task.insert(task.end(), addTask.begin(), addTask.end());
	addTask.clear();
	addTask.shrink_to_fit();
}

//��Ԃ�Kill�̃I�u�W�F�N�g���폜����
void TaskSystem::KillObject()
{
	{//�I�u�W�F�N�g�̍폜
		const auto& removeIt = std::remove_if(task.begin(), task.end(),
			[](std::shared_ptr<TaskAbstract>& obj)
		{
			return (obj->state == ObjectState::Kill);
		}
		);
		task.erase(removeIt, task.end());
		task.shrink_to_fit();
	}

	//�f�[�^�̍폜
	for (auto it = taskData.begin();
		 it != taskData.end();
		 ++it)
	{
		const auto& removeIt = std::remove_if(it->second.begin(), it->second.end(),
			[](std::shared_ptr<TaskAbstract>& data)
		{
			return (data->state == ObjectState::Kill);
		}
		);
		it->second.erase(removeIt, it->second.end());
		it->second.shrink_to_fit();

		if ((int)it->second.size() == 0)
		{
			taskData.erase(it);
		}
	}
}

//priority����ɏ����Ƀ\�[�g����
void TaskSystem::SortObject()
{
	std::sort(task.begin(), task.end(), 
		[](std::shared_ptr<TaskAbstract>& left, std::shared_ptr<TaskAbstract>& right)
		{
			return (left->priority < right->priority);
		}
	);
}