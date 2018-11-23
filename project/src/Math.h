#pragma once
#include <math.h>
#include <cmath>

namespace Math
{
	static const float	PI	= 3.1415926535897932384626433832795028841971f;
	static const double	dPI = 3.1415926535897932384626433832795028841971;

	//度数法 → 弧度法変換
	float ToRadian(float deg);
	//弧度法 → 度数法変換
	float ToDegree(float rad);

	//二次元ベクトルクラス
	struct Vec2
	{
		float x, y;

		Vec2();
		Vec2(const Vec2& setVec);
		Vec2(int setX, int setY);
		Vec2(float setX, float setY);

		float	GetDistance() const;					//斜辺を取得
		float	GetFormedAngle(const Vec2& vec) const;	//なす角を取得(ラジアン)
		float	GetDotProduct(const Vec2& vec) const;	//内積を取得
		float	GetCrossProduct(const Vec2& vec) const;	//外積を取得
		Vec2&	Normalize();							//単位ベクトルにする(正規化)
		Vec2	GetNormalize() const;					//単位ベクトルを取得

		Vec2&	operator =(const Vec2& vec);
		Vec2	operator +(int val) const;
		Vec2	operator +(float val) const;
		Vec2	operator +(const Vec2& vec) const;
		Vec2	operator -(int val) const;
		Vec2	operator -(float val) const;
		Vec2	operator -(const Vec2& vec) const;
		Vec2	operator *(int mul) const;
		Vec2	operator *(float mul) const;
		Vec2	operator *(const Vec2& vec) const;
		Vec2	operator /(int div) const;
		Vec2	operator /(float div) const;
		Vec2	operator /(const Vec2& vec) const;
		Vec2&	operator +=(int val);
		Vec2&	operator +=(float val);
		Vec2&	operator +=(const Vec2& vec);
		Vec2&	operator -=(int val);
		Vec2&	operator -=(float val);
		Vec2&	operator -=(const Vec2& vec);
		Vec2&	operator *=(int mul);
		Vec2&	operator *=(float mul);
		Vec2&	operator *=(const Vec2& vec);
		Vec2&	operator /=(int div);
		Vec2&	operator /=(float div);
		Vec2&	operator /=(const Vec2& vec);
		Vec2&	operator ++();
		Vec2	operator ++(int);
		Vec2&	operator --();
		Vec2	operator --(int);
		Vec2	operator -() const;
		bool	operator ==(const Vec2& vec) const;
		bool	operator <(const Vec2& vec) const;
		bool	operator >(const Vec2& vec) const;
		bool	operator <=(const Vec2& vec) const;
		bool	operator >=(const Vec2& vec) const;
		float	operator [](int val) const;
	};

	//当たり判定と描画機能つき矩形クラス
	struct Box2D
	{
		int x, y, w, h;

		Box2D();
		Box2D(const Box2D& setBox);
		Box2D(int setX, int setY, int setW, int setH);
		Box2D(int setW, int setH);

		int Area() const;		//面積を取得
		Vec2 GetPos() const;	//座標を取得

		bool IsHit(const Box2D& box) const;	//指定矩形との接触判定
		bool IsHit(const Vec2& pos) const;	//指定座標との接触判定
		bool IsIn(const Box2D& box) const;	//指定矩形が矩形内に入っているかの判定
		void DrawRect(bool isFill, int color = 0xffffff) const;	//矩形の描画

		Box2D& Set(int setX, int setY);		//指定座標に設定
		Box2D& Set(const Vec2& vec);		//指定座標に設定
		Box2D GetSet(int setX, int setY);	//指定座標に設定した値を取得
		Box2D GetSet(const Vec2& vec);		//指定座標に設定した値を取得

		Box2D& Offset(int setX, int setY);			//指定座標分オフセット
		Box2D& Offset(const Vec2& vec);				//指定座標分オフセット
		Box2D GetOffset(int setX, int setY) const;	//オフセットした値を取得
		Box2D GetOffset(const Vec2& vec) const;		//オフセットした値を取得

		Box2D&	operator =(const Box2D& box);
		Box2D	operator +(const Box2D& box) const;
		Box2D	operator -(const Box2D& box) const;
		Box2D	operator *(int mul) const;
		Box2D	operator /(int div) const;
		Box2D&	operator +=(const Box2D& box);
		Box2D&	operator -=(const Box2D& box);
		Box2D&	operator *=(int mul);
		Box2D&	operator /=(int div);
		bool	operator ==(const Box2D& box);
		int		operator [](int val);
	};
}