#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "TaskAbstract.h"

class TaskSystem
{
private:
	std::vector<std::shared_ptr<TaskAbstract>> task;
	std::vector<std::shared_ptr<TaskAbstract>> addTask;
	std::unordered_map<std::string, std::vector<std::shared_ptr<TaskAbstract>>> taskData;

public:
	TaskSystem();
	~TaskSystem();

	void Update();													//�X�V
	void Draw();													//�`��
	void RegistrationTask(std::shared_ptr<TaskAbstract> createObj);	//�^�X�N��ǉ�����

	void KillTask(const std::string& groupName);	//�w�肵���O���[�v���̃^�X�N�̏�Ԃ�Kill�ɂ���
	void AllKillTask();								//�o�^����Ă���^�X�N�̏�Ԃ�S��Kill�ɂ���
	void AllDeleteTask();							//�o�^����Ă���^�X�N��S�ċ����폜����(�f�X�g���N�^�ŌĂ΂��)
	
	//�w�肵���O���[�v���̓��A�擪�݂̂�n��
	template<class T>
	std::shared_ptr<const T> GetTaskOne(const std::string& groupName)
	{
		if (taskData.find(groupName) != taskData.end())
		{
			return std::static_pointer_cast<const T>(taskData[groupName].front());
		}

		return nullptr;
	}

	//�w�肵���O���[�v���̃^�X�N���܂Ƃ߂ēn��
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<const T>>> GetTaskGroup(const std::string& groupName)
	{
		if (taskData.find(groupName) != taskData.end())
		{
			std::shared_ptr<std::vector<std::shared_ptr<const T>>> gd =
				std::make_shared<std::vector<std::shared_ptr<const T>>>();

			gd->reserve(taskData[groupName].size() * sizeof(gd));

			for (auto it : taskData[groupName])
			{
				gd->emplace_back(std::static_pointer_cast<const T>(it));
			}

			return gd;
		}

		return nullptr;
	}

	//�C���X�^���X�𓾂�
	static TaskSystem& GetInstance();

private:
	void AllUpdate();		//�S�Ẵ^�X�N��Update���Ă�
	void AddTask();			//�ǉ��\��̃^�X�N��ǉ�����
	void StateDeleteTask();	//��Ԃ�Delete�̃^�X�N���폜����
	void SortTask();		//priority����ɏ����Ƀ\�[�g����
};

namespace TS
{
	static TaskSystem& taskSystem = TaskSystem::GetInstance();
}