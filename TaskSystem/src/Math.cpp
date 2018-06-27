#include "Math.h"

namespace Math
{
	//弧度法変換
	float ToRadian(float val)
	{
		return val * PI / 180.0f;
	}

	//度数法変換
	float ToDegree(float val)
	{
		return 180.0f * val / PI;
	}

	//--------------------------------------------------------
	//二次元ベクトルクラス
	Vec2::Vec2():
		x(0.0f), y(0.0f) {}

	Vec2::Vec2(const Vec2& setVec):
		x(setVec.x), y(setVec.y){}

	Vec2::Vec2(float setX, float setY):
		x(setX), y(setY){}

	void Vec2::operator =(const Vec2& vec)
	{
		x = vec.x;
		y = vec.y;
	}
	Vec2 Vec2::operator +(const Vec2& vec) const
	{
		Vec2 retVec(x + vec.x, y + vec.y);
		return retVec;
	}
	Vec2 Vec2::operator -(const Vec2& vec) const
	{
		Vec2 retVec(x - vec.x, y - vec.y);
		return retVec;
	}
	void Vec2::operator +=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
	}
	void Vec2::operator -=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	//--------------------------------------------------------
	//矩形クラス
	Box2D::Box2D():
		x(0), y(0), w(0), h(0),
		baseX(0), baseY(0){}

	Box2D::Box2D(const Box2D& setBox):
		x(setBox.x), y(setBox.y), w(setBox.w), h(setBox.h),
		baseX(setBox.x), baseY(setBox.y){}

	Box2D::Box2D(int setX, int setY, int setW, int setH):
		x(setX), y(setY), w(setW), h(setH),
		baseX(setX), baseY(setY) {}

	bool Box2D::Hit(const Box2D& box) const
	{
		return	x <= box.x + box.w && box.x < x + w &&
				y <= box.y + box.h && box.y < y + h;
	}
	
	bool Box2D::In(const Box2D& box) const
	{
		return	x <= box.x && box.x + box.w < x + w &&
				y <= box.y && box.y + box.h < y + h;
	}

	void Box2D::Offset(int setX, int setY)
	{
		x = baseX + setX;
		y = baseY + setY;
	}
	void Box2D::Offset(const Vec2& vec)
	{
		x = baseX + (int)vec.x;
		y = baseY + (int)vec.y;
	}

	Box2D Box2D::OffsetCpy(int setX, int setY) const
	{
		Box2D cpy(baseX + setX, baseY + setY, w, h);
		return cpy;
	}
	Box2D Box2D::OffsetCpy(const Vec2& vec) const
	{
		Box2D cpy(baseX + (int)vec.x, baseY + (int)vec.y, w , h);
		return cpy;
	}

	void Box2D::operator =(const Box2D& box)
	{
		x = box.x;
		y = box.y;
		w = box.w;
		h = box.h;
		baseX = x;
		baseY = y;
	}
	Box2D Box2D::operator +(const Box2D& box) const
	{
		Box2D retBox(x + box.x, y + box.y, w + box.w, h + box.h);
		return retBox;
	}
	Box2D Box2D::operator -(const Box2D& box) const
	{
		Box2D retBox(x - box.x, y - box.y, w - box.w, h - box.h);
		return retBox;
	}
	void Box2D::operator +=(const Box2D& box)
	{
		x += box.x;
		y += box.y;
		w += box.w;
		h += box.h;
		baseX = x;
		baseY = y;
	}
	void Box2D::operator -=(const Box2D& box)
	{
		x -= box.x;
		y -= box.y;
		w -= box.w;
		h -= box.h;
		baseX = x;
		baseY = y;
	}
}