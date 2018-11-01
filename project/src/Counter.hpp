#pragma once
#include <limits>

//���ł��v������
template<class T> class Counter
{
#undef max
#undef min
private:
	T now;		//���݂̒l
	T add;		//���Z����l
	T min;		//�ŏ��l
	T max;		//�ő�l

public:
	//�R���X�g���N�^(���݂̒l��0�A���Z�ʂ�1)
	Counter():
		now(0),
		add(1),
		min(std::numeric_limits<T>::min()),
		max(std::numeric_limits<T>::max()) {}
	//�R���X�g���N�^(���Z�ʂ�ݒ�)
	Counter(T addVol):
		now(0),
		add(add),
		min(std::numeric_limits<T>::min()),
		max(std::numeric_limits<T>::max()) {}
	//�R���X�g���N�^(�ŏ��l�ƍő�l��ݒ�)
	Counter(T min, T max):
		now(0),
		add(1),
		min(min),
		max(max) {}
	//�R���X�g���N�^(���Z�ʂƍŏ��l�ƍő�l��ݒ�)
	Counter(T add, T min, T max):
		now(0),
		add(add),
		min(min),
		max(max) {}

	//�e���l��ݒ肷��
	void SetCounter(T setNow, T setAdd, T setMin, T setMax)
	{
		now = setNow;
		add = setAdd;
		min = setMin;
		max = setMax;
	}

	//���݂̒l��0�ɂ���
	void Reset()
	{
		now = 0;
	}

	//���݂̒l���ŏ��l�ɂ���
	void SetNowMin()
	{
		now = min;
	}

	//���݂̒l���ő�l�ɂ���
	void SetNowMax()
	{
		now = max;
	}

	//���l�����Z����
	//�ő�l�ȏ�A�ŏ��l�ȉ��ɂȂ�������Z���~����
	void Run()
	{
		now += add;
		if (now <= min) now = min;
		if (now >= max) now = max;
	}

	//���l�����Z����
	//�ő�l�𒴉߂�����ŏ��l�ɁA�ŏ��l�����ɂȂ�����ő�l�ɒ���
	void RunLoop()
	{
		now += add;
		if (now < min) now = max;
		if (now > max) now = min;
	}

	//���݂̒l��Ԃ�
	const T& GetNow() const
	{
		return now;
	}

	//(�ő�l-���݂̒l)��Ԃ�
	T GetNowToMax() const
	{
		return max - now;
	}

	//�ő�l��Ԃ�
	const T& GetMax() const
	{
		return max;
	}

	//�ŏ��l��Ԃ�
	const T& GetMin() const
	{
		return min;
	}

	//���݂̒l���ő�l�܂œ��B���Ă�����true��Ԃ�
	bool IsMax() const
	{
		return now >= max;
	}

	//���݂̒l���ŏ��l�܂œ��B���Ă�����true��Ԃ�
	bool IsMin() const
	{
		return now <= min;
	}
};