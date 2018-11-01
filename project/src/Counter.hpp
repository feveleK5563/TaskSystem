#pragma once
#include <limits>

//何でも計測くん
template<class T> class Counter
{
#undef max
#undef min
private:
	T now;		//現在の値
	T add;		//加算する値
	T min;		//最小値
	T max;		//最大値

public:
	//コンストラクタ(現在の値は0、加算量は1)
	Counter():
		now(0),
		add(1),
		min(std::numeric_limits<T>::min()),
		max(std::numeric_limits<T>::max()) {}
	//コンストラクタ(加算量を設定)
	Counter(T addVol):
		now(0),
		add(add),
		min(std::numeric_limits<T>::min()),
		max(std::numeric_limits<T>::max()) {}
	//コンストラクタ(最小値と最大値を設定)
	Counter(T min, T max):
		now(0),
		add(1),
		min(min),
		max(max) {}
	//コンストラクタ(加算量と最小値と最大値を設定)
	Counter(T add, T min, T max):
		now(0),
		add(add),
		min(min),
		max(max) {}

	//各数値を設定する
	void SetCounter(T setNow, T setAdd, T setMin, T setMax)
	{
		now = setNow;
		add = setAdd;
		min = setMin;
		max = setMax;
	}

	//現在の値を0にする
	void Reset()
	{
		now = 0;
	}

	//現在の値を最小値にする
	void SetNowMin()
	{
		now = min;
	}

	//現在の値を最大値にする
	void SetNowMax()
	{
		now = max;
	}

	//数値を加算する
	//最大値以上、最小値以下になったら加算を停止する
	void Run()
	{
		now += add;
		if (now <= min) now = min;
		if (now >= max) now = max;
	}

	//数値を加算する
	//最大値を超過したら最小値に、最小値未満になったら最大値に直す
	void RunLoop()
	{
		now += add;
		if (now < min) now = max;
		if (now > max) now = min;
	}

	//現在の値を返す
	const T& GetNow() const
	{
		return now;
	}

	//(最大値-現在の値)を返す
	T GetNowToMax() const
	{
		return max - now;
	}

	//最大値を返す
	const T& GetMax() const
	{
		return max;
	}

	//最小値を返す
	const T& GetMin() const
	{
		return min;
	}

	//現在の値が最大値まで到達していたらtrueを返す
	bool IsMax() const
	{
		return now >= max;
	}

	//現在の値が最小値まで到達していたらtrueを返す
	bool IsMin() const
	{
		return now <= min;
	}
};