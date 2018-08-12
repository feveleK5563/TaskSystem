#pragma once
#include <random>
#include <memory>
#include <vector>
#include "Math.h"

namespace SystemDefine
{
	const int windowSizeX(1280);	//�E�B���h�E�T�C�YX
	const int windowSizeY(720);		//�E�B���h�E�T�C�YY

	//��ʊO����(�����ɋ�`���w��A��ʊO�ɏo�Ă�����true)
	bool WindowOutBox(const Math::Box2D& hitBase);
	//��ʓ�����(�����ɋ�`���w��A��ʓ��ɂ�����true)
	bool WindowInBox(const Math::Box2D& hitBase);

	//���|�C���^�����S��delete����
	template<class T> void SafeDelete(T& t);
	//���|�C���^�����S��delete����(�z���)
	template<class T> void SafeDeleteArr(T& t);

	//�͈͓��Ń����_���Ȓl���w������擾����
	int GetRand(int lowerLimit, int upperLimit);
};