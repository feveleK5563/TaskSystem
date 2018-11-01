#pragma once
#include "Counter.hpp"
typedef float(*Ease)(float, float);

class Easing
{
private:
	Counter<float>	time;
	float			volume;

public:
	//コンストラクタ
	Easing();

	//イージングの実行
	//引数：イージング動作の関数ポインタ(Ease_…), 継続時間(float)
	void Run(Ease em, float durationTime);

	//値を取得
	//引数：始点(float), 終点(float)
	float GetVolume(float startPoint, float endPoint);

	//イージングが終了したらtrueが返る
	bool IsEaseEnd();

	//イージングをリセットする
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
