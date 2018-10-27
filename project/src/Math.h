#pragma once
#include <math.h>

namespace MATH
{
	static const float	PI	= 3.1415926535897932384626433832795028841971f;
	static const double	dPI = 3.1415926535897932384626433832795028841971;

	//弧度法変換
	float ToRadian(float val);
	//度数法変換
	float ToDegree(float val);

	//二次元ベクトルクラス
	struct Vec2
	{
		float x, y;

		Vec2();
		Vec2(const Vec2& setVec);
		Vec2(int setX, int setY);
		Vec2(float setX, float setY);

		Vec2&	operator =(const Vec2& vec);
		Vec2	operator +(int val) const;
		Vec2	operator +(const Vec2& vec) const;
		Vec2	operator -(int val) const;
		Vec2	operator -(const Vec2& vec) const;
		Vec2	operator *(float mul) const;
		Vec2	operator *(const Vec2& vec) const;
		Vec2	operator /(float div) const;
		Vec2	operator /(const Vec2& vec) const;
		Vec2&	operator +=(float val);
		Vec2&	operator +=(const Vec2& vec);
		Vec2&	operator -=(float val);
		Vec2&	operator -=(const Vec2& vec);
		Vec2&	operator *=(float mul);
		Vec2&	operator *=(const Vec2& vec);
		Vec2&	operator /=(float div);
		Vec2&	operator /=(const Vec2& vec);
		Vec2&	operator ++();
		Vec2	operator ++(int);
		Vec2&	operator --();
		Vec2	operator --(int);
		Vec2	operator -() const;
	};

	//当たり判定と描画機能つき矩形クラス
	struct Box2D
	{
		int x, y, w, h;

		Box2D();
		Box2D(const Box2D& setBox);
		Box2D(int setX, int setY, int setW, int setH);
		Box2D(int setW, int setH);

		bool IsHit(const Box2D& box) const;
		bool IsHit(const Vec2& pos) const;
		bool IsIn(const Box2D& box) const;
		void DrawRect(bool isFill, int color = 0xffffff) const;

		void Offset(int setX, int setY);
		void Offset(const Vec2& vec);
		Box2D OffsetCpy(int setX, int setY) const;
		Box2D OffsetCpy(const Vec2& vec) const;

		Box2D&	operator =(const Box2D& box);
		Box2D	operator +(const Box2D& box) const;
		Box2D	operator -(const Box2D& box) const;
		Box2D	operator *(int mul) const;
		Box2D	operator /(int div) const;
		Box2D&	operator +=(const Box2D& box);
		Box2D&	operator -=(const Box2D& box);
		Box2D&	operator *=(int mul);
		Box2D&	operator /=(int div);
	};
}