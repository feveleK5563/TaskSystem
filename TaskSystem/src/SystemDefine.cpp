#include "SystemDefine.h"

const int SystemDefine::windowSizeX = 1280;	//�E�B���h�E�T�C�YX
const int SystemDefine::windowSizeY = 720;	//�E�B���h�E�T�C�YY

//��ʊO����(�����ɉ摜�T�C�Y���w��A��ʊO�ɏo�Ă�����true)
bool SystemDefine::WindowOutBox(const Math::Box2D& hitBase)
{
	Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
	return !windowBox.Hit(hitBase);
}

//��ʓ�����(�����ɉ摜�T�C�Y���w��A��ʓ��ɂ�����true)
bool SystemDefine::WindowInBox(const Math::Box2D& hitBase)
{
	Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
	return windowBox.In(hitBase);
}

//���S��delete����
template<class T>void SystemDefine::SafeDelete(T& t)
{
	if (t != nullptr)
	{
		delete t;
		t = nullptr;
	}
}

//���S��delete����(�z���)
template<class T>void SystemDefine::SafeDeleteArr(T& t)
{
	if (t != nullptr)
	{
		delete[] t;
		t = nullptr;
	}
}