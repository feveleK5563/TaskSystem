#pragma once
#include "Counter.hpp"
typedef float(*Ease)(float, float);

class Easing
{
private:
	Counter<float>	time;
	float			volume;

public:
	//�R���X�g���N�^
	Easing();

	//�C�[�W���O�̎��s
	//�����F�C�[�W���O����̊֐��|�C���^(Ease_�c), �p������(float)
	void Run(Ease em, float durationTime);

	//�l���擾
	//�����F�n�_(float), �I�_(float)
	float GetVolume(float startPoint, float endPoint);

	//�C�[�W���O���I��������true���Ԃ�
	bool IsEaseEnd();

	//�C�[�W���O�����Z�b�g����
	void Reset();
};


//-----------------------------------------------------------------------------


namespace Ease_Linear
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Back
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Bounce
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Circ
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Cubic
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Elastic
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Expo
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Quad
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Quart
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Quint
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}

namespace Ease_Sine
{
	float In(float time, float duration);
	float Out(float time, float duration);
	float InOut(float time, float duration);
}
