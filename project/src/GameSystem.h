#pragma once

class GameSystem
{
public:
	GameSystem();

	void Initialize();	//����������
	void MainLoop();	//���C�����[�v
	void Finalize();	//�I������

private:
	bool IsFullScreenMode();	//�t���X�N���[�����[�h�ɂ��邩�ۂ������b�Z�[�W�{�b�N�X�Ŗ₤
	bool Run();					//���[�v���񂷍ۂ̔��菈��

	void FirstCreateTask();		//�ŏ��ɍ쐬����^�X�N
};