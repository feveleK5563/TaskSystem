#pragma once

class GameSystem
{
public:
	GameSystem();

	void Initialize();	//����������

private:
	bool IsFullScreenMode();	//�t���X�N���[�����[�h�ɂ��邩�ۂ������b�Z�[�W�{�b�N�X�Ŗ₤
	bool Run();					//���[�v���񂷍ۂ̔��菈��

public:
	void MainLoop();	//���C�����[�v
	void Finalize();	//�I������
};