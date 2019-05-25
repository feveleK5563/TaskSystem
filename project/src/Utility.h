#pragma once
#include <cstdio>
#include <iostream>

//�ȉ��̃}�N���̍쐬�҂�tonarinohito�Ȃ̂Ŗ�肪��������tonarinohito�̂���
#ifdef _DEBUG
//�f�o�b�O���ɃR���\�[����\������
#define ShowConsole() Utility::Console c
//�f�o�b�O���ɃR���\�[����ʂ֏o��
#define DOUT std::cout
//�t�@�C�����ƍs�����R���\�[����ʂ֏o��
#define FILE_AND_LINE std::cout << __FILE__ << ":" << __LINE__ << std::endl

#else
//�f�o�b�O�p�̂��ꂱ��𖳎�����
#define NDEBUG	//assert����
#define ShowConsole() __noop
#define DOUT false && std::cout
#define FILE_AND_LINE false

#endif
#include <assert.h>


namespace Utility
{
	//���|�C���^�����S��delete����
	template<class T>void SafeDelete(T& t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	//���|�C���^�����S��delete����(�z���)
	template<class T>void SafeDeleteArr(T& t)
	{
		if (t != nullptr)
		{
			delete[] t;
			t = nullptr;
		}
	}

	//�͈͓��Ń����_���Ȓl���擾����
	int GetRand(int lowerLimit, int upperLimit);

	//�R���\�[����ʂ��o���Acout,cin��������
	class Console final
	{
	private:
		std::FILE* in;
		std::FILE* out;

	public:
		Console();
		~Console();
	};
}