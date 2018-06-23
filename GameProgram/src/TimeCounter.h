#pragma once

//���Ԍv������
//
class TimeCounter
{
private:
	int cntTime;	//�o�ߎ���
	int endTime;	//�I������
	bool isTimeEnd;	//�I�����Ԉȏ�v�����Ă��邩�ۂ�

public:
	//�R���X�g���N�^
	TimeCounter();
	//�I�����Ԃ�ݒ肷��R���X�g���N�^
	TimeCounter(int endTime);

	//�o�ߎ��Ԃ�0�ɂ���
	void ResetCntTime();

	//�I�����Ԃ�ݒ肷��
	void SetEndTime(int setEndTime);

	//���Ԃ𑪂�
	//�I�����Ԃ�ݒ肵�Ă���ꍇ�A���̎��Ԉȏ�ɂȂ������~����
	void Run();

	//���݂̌o�ߎ��Ԃ�Ԃ�
	int GetNowCntTime() const;

	//�o�ߎ��Ԃ��I�����Ԃ܂œ��B���Ă�����true��Ԃ�
	bool IsTimeEnd() const;
};