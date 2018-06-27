#pragma once
#include <math.h>

namespace Math
{
	static const float PI = 3.14159265358979323846264338327950288419f;

	//弧度法変換
	float ToRadian(float val);
	//度数法変換
	float ToDegree(float val);

	//二次元ベクトルクラス
	class Vec2
	{
	public:
		float x, y;

		Vec2();
		Vec2(const Vec2& setVec);
		Vec2(float setX, float setY);

		void operator =(const Vec2& vec);
		Vec2 operator +(const Vec2& vec) const;
		Vec2 operator -(const Vec2& vec) const;
		void operator +=(const Vec2& vec);
		void operator -=(const Vec2& vec);
	};

	//当たり判定機能つき矩形クラス
	class Box2D
	{
	public:
		int x, y, w, h;
		int baseX, baseY;

		Box2D();
		Box2D(const Box2D& setBox);
		Box2D(int setX, int setY, int setW, int setH);

		bool Hit(const Box2D& box) const;
		bool In(const Box2D& box) const;

		void Offset(int setX, int setY);
		void Offset(const Vec2& vec);

		Box2D OffsetCpy(int setX, int setY) const;
		Box2D OffsetCpy(const Vec2& vec) const;

		void operator =(const Box2D& box);
		Box2D operator +(const Box2D& box) const;
		Box2D operator -(const Box2D& box) const;
		void operator +=(const Box2D& box);
		void operator -=(const Box2D& box);
	};
}