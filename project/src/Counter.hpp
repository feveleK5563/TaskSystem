#pragma once
#include <limits>

// 何でも計測くん
template<class T> class Counter
{
#undef max
#undef min
private:
    T now_;     // 現在の値
    T add_;     // 加算する値
    T min_;     // 最小値
    T max_;     // 最大値

public:
    // コンストラクタ(現在の値は0、加算量は1)
    Counter():
        now_(0),
        add_(1),
        min_(std::numeric_limits<T>::min()),
        max_(std::numeric_limits<T>::max()) {}
    // コンストラクタ(加算量を設定)
    Counter(T add):
        now_(0),
        add_(add),
        min_(std::numeric_limits<T>::min()),
        max_(std::numeric_limits<T>::max()) {}
    // コンストラクタ(最小値と最大値を設定)
    Counter(T min, T max):
        now_(0),
        add_(1),
        min_(min),
        max_(max) {}
    // コンストラクタ(加算量と最小値と最大値を設定)
    Counter(T add, T min, T max):
        now_(0),
        add_(add),
        min_(min),
        max_(max) {}

    // 各数値を設定する
    void SetCounter(T setNow, T setAdd, T setMin, T setMax)
    {
        now_ = setNow;
        add_ = setAdd;
        min_ = setMin;
        max_ = setMax;
    }

    // 現在の値を0にする
    void Reset()
    {
        now_ = 0;
    }

    // 現在の値を設定する
    void SetNowCnt(T setNow)
    {
        now_ = setNow;
    }

    // 現在の値を最小値にする
    void SetNowMin()
    {
        now_ = min_;
    }

    // 現在の値を最大値にする
    void SetNowMax()
    {
        now_ = max_;
    }

    // 数値を加算する
    // 最大値以上、最小値以下になったら加算を停止する
    void Run()
    {
        now_ += add_;
        if (now_ <= min_) now_ = min_;
        if (now_ >= max_) now_ = max_;
    }

    // 数値を加算する
    // 最大値を超過したら最小値に、最小値未満になったら最大値に直す
    void RunLoop()
    {
        now_ += add_;
        if (now_ < min_) now_ = max_;
        if (now_ > max_) now_ = min_;
    }

    // 現在の値を返す
    const T& GetNow() const
    {
        return now_;
    }

    // (最大値-現在の値)を返す
    T GetNowToMax() const
    {
        return max_ - now_;
    }

    // 最大値を返す
    const T& GetMax() const
    {
        return max_;
    }

    // 最小値を返す
    const T& GetMin() const
    {
        return min_;
    }

    // 現在の値が最大値まで到達していたらtrueを返す
    bool IsMax() const
    {
        return now_ >= max_;
    }

    // 現在の値が最小値まで到達していたらtrueを返す
    bool IsMin() const
    {
        return now_ <= min_;
    }
};