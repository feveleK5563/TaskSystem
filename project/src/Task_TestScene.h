#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

namespace TestScene
{
	const std::string	defGroupName	("�e�X�g�p�V�[��");	//�O���[�v��
	const std::string	defTaskName		("�e�X�g�p�^�X�N");	//�^�X�N��
	const float			defPriority(0.f);	//�f�t�H���g�̏����D��x

	//�V�F�[�_�[�ɑ���\����
	struct constantBuffer
	{
		FLOAT2 windowSize;
		FLOAT2 mousePos;
		float radius;
		bool onClick;
	};

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		std::string imageName;
		std::string sName;
		std::string cbName;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X
		ImageDrawer imgDrawer;

		Counter<float> timer;	//���Ԍv��
		Math::Vec2 mousePos;	//�}�E�X�̍��W
		bool onClick;			//�N���b�N�������ۂ�

	public:
		//�R���X�g���N�^
		Task();
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create();

		void Initialize() override;	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}