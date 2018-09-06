#pragma once

namespace UTIL
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

	//�͈͓��Ń����_���Ȓl���w������擾����
	int GetRand(int lowerLimit, int upperLimit);
}