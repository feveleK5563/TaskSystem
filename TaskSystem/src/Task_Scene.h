#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Scene
{
	const std::string	defGroupName("����������");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		ImageData imgData;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X

		//ImageDrawer imgDrawer;

	public:
		Task();		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static const std::shared_ptr<const Task> Create();	//�^�X�N�̐���

		void Initialize() override;	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}