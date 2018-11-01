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
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::shared_ptr<TaskAbstract>>>> taskData;

	TaskSystem();
	static TaskSystem* ts;

public:
	~TaskSystem();

	bool Update();											//�X�V(�^�X�N�����݂��Ȃ������ꍇfalse��Ԃ�)
	void Draw();											//�`��
	void AddTask(std::shared_ptr<TaskAbstract> createObj);	//�^�X�N��ǉ�����

	bool IsHaveGroup(const std::string& groupName);	//�w�肵���O���[�v�����݂��Ă��邩���ׂ�
	void KillGroup(const std::string& groupName);		//�w�肵���O���[�v���̃^�X�N��S�ĎE��
	void SleepGroup(const std::string& groupName);		//�w�肵���O���[�v���̃^�X�N�̒�~�A�Đ���؂�ւ���

	bool IsHaveTask(const std::string& groupName, const std::string& taskName);	//�w�肵���^�X�N�����݂��Ă��邩���ׂ�
	void KillTask(const std::string& groupName, const std::string& taskName);		//�w�肵���^�X�N��S�ĎE��
	void SleepTask(const std::string& groupName, const std::string& taskName);		//�w�肵���^�X�N�̒�~�A�Đ���؂�ւ���

	void AllKillTask();		//�o�^����Ă���^�X�N��S�ĎE��
	void AllDeleteTask();	//�o�^����Ă���^�X�N��S�ċ����폜����(�f�X�g���N�^�ŌĂ΂��)
	
	//�w�肵���^�X�N�̓��A�擪�݂̂�n��
	template<class T>
	std::shared_ptr<T> GetTaskOne(const std::string& groupName, const std::string& taskName)
	{
		if (IsHaveTask(groupName, taskName))
		{
			return std::static_pointer_cast<T>(taskData[groupName][taskName].front());
		}

		return std::shared_ptr<T>();
	}
	//�w�肵���^�X�N���܂Ƃ߂ēn��
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskGroup(const std::string& groupName, const std::string& taskName)
	{
		std::shared_ptr<std::vector<std::shared_ptr<T>>> gt;

		if (IsHaveTask(groupName, taskName))
		{
			gt = std::make_shared<std::vector<std::shared_ptr<T>>>();

			gt->reserve(taskData[groupName][taskName].size());

			for (auto it : taskData[groupName][taskName])
			{
				gt->emplace_back(std::static_pointer_cast<T>(it));
			}
		}

		return gt;
	}

	//�C���X�^���X�𓾂�
	static TaskSystem& GetInstance();
	//�C���X�^���X�𐶐�����
	static void CreateInstance();
	//�C���X�^���X���������
	static void DeleteInstance();

private:
	bool AllUpdate();		//�S�Ẵ^�X�N��Update���Ă�(�^�X�N�����݂��Ȃ������ꍇfalse��Ԃ�)
	void AddTask();			//�ǉ��\��̃^�X�N��ǉ�����
	void StateDeleteTask();	//��Ԃ�Delete�̃^�X�N���폜����
	void SortTask();		//priority����ɏ����Ƀ\�[�g����
};