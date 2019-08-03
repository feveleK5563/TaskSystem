#include "Easing.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Math.h"

// コンストラクタ
Easing::Easing() : time_(0.f, 1.f), volume_(0.f) {}

// イージングの実行
// 引数：イージング動作の関数ポインタ(Ease_…), 継続時間(float)
void Easing::Run(Ease em, float duration_time)
{
    time_.SetCounter(0.f, 1.f, duration_time, 0.f);
    time_.Run();
    volume_ = em(time_.GetNow(), duration_time);
}

// 値を取得
// 引数：始点(float), 終点(float)
float Easing::GetVolume(float start_point, float end_point)
{
    return start_point + (volume_ * (start_point - end_point));
}

// イージングが終了したらtrueが返る
bool Easing::IsEaseEnd()
{
    return time_.IsMax();
}

// イージングをリセットする
void Easing::Reset()
{
    time_.Reset();
}

//-----------------------------------------------------------------------------

namespace Ease_Linear
{
    float In(float time, float duration)
    {
        return time / duration;
    }
    float Out(float time, float duration)
    {
        return time / duration;
    }
    float InOut(float time, float duration)
    {
        return time / duration;
    }
}

namespace Ease_Back
{
    float In(float time, float duration)
    {
        float s = 1.70158f;
        float postFix = time /= duration;
        return (postFix)* time* ((s + 1) * time - s);
    }
    float Out(float time, float duration)
    {
        float s = 1.70158f;
        return ((time = time / duration - 1) * time * ((s + 1) * time + s) + 1);
    }
    float InOut(float time, float duration)
    {
        float s = 1.70158f;
        if ((time /= duration / 2) < 1) return 1.f / 2.f * (time * time * (((s *= (1.525f)) + 1) * time - s));
        float postFix = time -= 2;
        return 1.f / 2.f * ((postFix)* time * (((s *= (1.525f)) + 1) * time + s) + 2);
    }
}

namespace Ease_Bounce
{
    float In(float time, float duration)
    {
        return 1.f - Out(duration - time, duration);
    }
    float Out(float time, float duration)
    {
        if ((time /= duration) < (1.f / 2.75f))
        {
            return 7.5625f* time* time;
        }
        else if (time < (2.f / 2.75f))
        {
            float postFix = time -= (1.5f / 2.75f);
            return 7.5625f * (postFix)* time + .75f;
        }
        else if (time < (2.5 / 2.75))
        {
            float postFix = time -= (2.25f / 2.75f);
            return 7.5625f * (postFix)* time + 0.9375f;
        }
        else
        {
            float postFix = time -= (2.625f / 2.75f);
            return 7.5625f * (postFix)* time + 0.984375f;
        }
    }
    float InOut(float time, float duration)
    {
        if (time < duration / 2) return In(time * 2, duration) * 0.5f;
        else return Out(time * 2 - duration, duration) * 0.5f + 0.5f;
    }
}

namespace Ease_Circ
{
    float In(float time, float duration)
    {
        return -1.f * (sqrtf(1 - (time /= duration) * time) - 1);
    }
    float Out(float time, float duration)
    {
        return sqrtf(1 - (time = time / duration - 1) * time);
    }
    float InOut(float time, float duration)
    {
        if ((time /= duration / 2) < 1) return -1.f / 2.f * (sqrtf(1 - time * time) - 1);
        return 1.f / 2.f * (sqrtf(1 - time * (time -= 2)) + 1);
    }
}

namespace Ease_Cubic
{
    float In(float time, float duration)
    {
        return (time /= duration) * time * time;
    }
    float Out(float time, float duration)
    {
        return (time = time / duration - 1) * time * time + 1;
    }
    float InOut(float time, float duration)
    {
        if ((time /= duration / 2) < 1) return 1.f / 2.f * time * time * time;
        return 1.f / 2.f * ((time -= 2) * time * time + 2);
    }
}

namespace Ease_Elastic
{
    float In(float time, float duration)
    {
        if (time == 0) return 0.f;  if ((time /= duration) == 1) return 1.f;
        float p = duration * 0.3f;
        float a = 1.f;
        float s = p / 4;
        float postFix = a * powf(2, 10 * (time -= 1));
        return -postFix * sinf((time * (duration)-s) * (2 * (Math::PI)) / p);
    }
    float Out(float time, float duration)
    {
        if (time == 0) return 0.f;  if ((time /= duration) == 1) return 1.f;
        float p = duration * 0.3f;
        float a = 1.f;
        float s = p / 4;
        return (a * powf(2, -10 * time) * sinf((time * (duration)-s) * (2 * Math::PI) / p) + 1.f);
    }
    float InOut(float time, float duration)
    {
        if (time == 0) return 0.f;  if ((time /= duration / 2) == 2) return 1.f;
        float p = duration * (0.3f * 1.5f);
        float a = 1.f;
        float s = p / 4;

        if (time < 1) {
            float postFix = a * powf(2, 10 * (time -= 1));
            return -0.5f * (postFix * sinf((time * (duration)-s) * (2 * (Math::PI)) / p));
        }
        float postFix = a * powf(2, -10 * (time -= 1));
        return postFix * sinf((time * (duration)-s) * (2 * Math::PI) / p) * 0.5f + 1.f;
    }
}

namespace Ease_Expo
{
    float In(float time, float duration)
    {
        return (time == 0) ? 0.f : powf(2, 10 * (time / duration - 1));
    }
    float Out(float time, float duration)
    {
        return (time == duration) ? 1.f : -powf(2, -10 * time / duration) + 1;
    }
    float InOut(float time, float duration)
    {
        if (time == 0) return 0.f;
        if (time == duration) return 1.f;
        if ((time /= duration / 2) < 1) return 1.f / 2.f * powf(2, 10 * (time - 1));
        return 1.f / 2.f * (-powf(2, -10 * --time) + 2);
    }
}

namespace Ease_Quad
{
    float In(float time, float duration)
    {
        return (time /= duration) * time;
    }
    float Out(float time, float duration)
    {
        return -1.f * (time /= duration) * (time - 2);
    }
    float InOut(float time, float duration)
    {
        if ((time /= duration / 2) < 1) return ((1.f / 2.f) * (time * time));
        return -1.f / 2.f * (((time - 2) * (--time)) - 1);
    }
}

namespace Ease_Quart
{
    float In(float time, float duration)
    {
        return (time /= duration) * time * time * time;
    }
    float Out(float time, float duration)
    {
        return -1.f * ((time = time / duration - 1) * time * time * time - 1);
    }
    float InOut(float time, float duration)
    {
        if ((time /= duration / 2) < 1) return 1.f / 2.f * time * time * time * time;
        return -1.f / 2.f * ((time -= 2) * time * time * time - 2);
    }
}

namespace Ease_Quint
{
    float In(float time, float duration)
    {
        return (time /= duration) * time * time * time * time;
    }
    float Out(float time, float duration)
    {
        return (time = time / duration - 1) * time * time * time * time + 1;
    }
    float InOut(float time, float duration)
    {
        if ((time /= duration / 2) < 1) return 1.f / 2.f * time * time * time * time * time;
        return 1.f / 2.f * ((time -= 2) * time * time * time * time + 2);
    }
}

namespace Ease_Sine
{
    float In(float time, float duration)
    {
        return -1.f * cosf(time / duration * (Math::PI / 2)) + 1.f;
    }
    float Out(float time, float duration)
    {
        return sinf(time / duration * (Math::PI / 2));
    }
    float InOut(float time, float duration)
    {
        return -1.f / 2.f * (cosf(Math::PI * time / duration) - 1);
    }
}