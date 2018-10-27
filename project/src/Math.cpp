#include "Math.h"
#include "DxLib.h"

namespace MATH
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
		x(0.f), y(0.f) {}

	Vec2::Vec2(const Vec2& setVec):
		x(setVec.x), y(setVec.y){}

	Vec2::Vec2(int setX, int setY):
		x((float)setX), y((float)setY){}

	Vec2::Vec2(float setX, float setY):
		x(setX), y(setY){}

	Vec2& Vec2::operator =(const Vec2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}
	Vec2 Vec2::operator +(int val) const
	{
		return Vec2(x + val, y + val);
	}
	Vec2 Vec2::operator +(const Vec2& vec) const
	{
		return Vec2(x + vec.x, y + vec.y);
	}
	Vec2 Vec2::operator -(int val) const
	{
		return Vec2(x - val, y - val);
	}
	Vec2 Vec2::operator -(const Vec2& vec) const
	{
		return Vec2(x - vec.x, y - vec.y);
	}
	Vec2 Vec2::operator *(float mul) const
	{
		return Vec2(x * mul, y * mul);
	}
	Vec2 Vec2::operator *(const Vec2& vec) const
	{
		return Vec2(x * vec.x, y * vec.y);
	}
	Vec2 Vec2::operator /(float div) const
	{
		return Vec2(x * div, y * div);
	}
	Vec2 Vec2::operator /(const Vec2& vec) const
	{
		return Vec2(x / vec.x, y / vec.y);
	}
	Vec2& Vec2::operator +=(float val)
	{
		x += val;
		y += val;
		return *this;
	}
	Vec2& Vec2::operator +=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	Vec2& Vec2::operator -=(float val)
	{
		x -= val;
		y -= val;
		return *this;
	}
	Vec2& Vec2::operator -=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	Vec2& Vec2::operator *=(float mul)
	{
		x *= mul;
		y *= mul;
		return *this;
	}
	Vec2& Vec2::operator *=(const Vec2& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}
	Vec2& Vec2::operator /=(float div)
	{
		x /= div;
		y /= div;
		return *this;
	}
	Vec2& Vec2::operator /=(const Vec2& vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	}
	Vec2& Vec2::operator ++()
	{
		++x; ++y;
		return *this;
	}
	Vec2 Vec2::operator ++(int)
	{
		Vec2 tmp = *this;
		++*this;
		return tmp;
	} 
	Vec2& Vec2::operator --()
	{
		--x; --y;
		return *this;
	}
	Vec2 Vec2::operator --(int)
	{
		Vec2 tmp = *this;
		--*this;
		return tmp;
	}
	Vec2 Vec2::operator -() const
	{
		Vec2 tmp = *this;
		tmp.x *= -1.f;
		tmp.y *= -1.f;
		return tmp;
	}


	//--------------------------------------------------------
	//当たり判定と描画機能つき矩形クラス
	Box2D::Box2D():
		x(0), y(0), w(0), h(0){}

	Box2D::Box2D(const Box2D& setBox):
		x(setBox.x), y(setBox.y), w(setBox.w), h(setBox.h){}

	Box2D::Box2D(int setX, int setY, int setW, int setH):
		x(setX), y(setY), w(setW), h(setH){}

	Box2D::Box2D(int setW, int setH):
		x(0), y(0), w(setW), h(setH){}

	bool Box2D::IsHit(const Box2D& box) const
	{
		return	x <= box.x + box.w && box.x < x + w &&
				y <= box.y + box.h && box.y < y + h;
	}
	bool Box2D::IsHit(const Vec2& pos) const
	{
		return	x <= pos.x && pos.x < x + w &&
				y <= pos.y && pos.y < y + h;
	}
	bool Box2D::IsIn(const Box2D& box) const
	{
		return	x <= box.x && box.x + box.w < x + w &&
				y <= box.y && box.y + box.h < y + h;
	}
	void Box2D::DrawRect(bool isFill, int color) const
	{
		DrawBox(x, y, x + w, y + h, color, isFill);
	}

	void Box2D::Offset(int setX, int setY)
	{
		x = setX;
		y = setY;
	}
	void Box2D::Offset(const Vec2& vec)
	{
		x = (int)vec.x;
		y = (int)vec.y;
	}
	Box2D Box2D::OffsetCpy(int setX, int setY) const
	{
		Box2D cpy(setX, setY, w, h);
		return cpy;
	}
	Box2D Box2D::OffsetCpy(const Vec2& vec) const
	{
		Box2D cpy((int)vec.x, (int)vec.y, w, h);
		return cpy;
	}

	Box2D& Box2D::operator =(const Box2D& box)
	{
		x = box.x;
		y = box.y;
		w = box.w;
		h = box.h;
		return *this;
	}
	Box2D Box2D::operator +(const Box2D& box) const
	{
		return Box2D(x + box.x, y + box.y, w + box.w, h + box.h);
	}
	Box2D Box2D::operator -(const Box2D& box) const
	{
		return Box2D(x - box.x, y - box.y, w - box.w, h - box.h);
	}
	Box2D Box2D::operator *(int mul) const
	{
		return Box2D(x, y, w * mul, h * mul);
	}
	Box2D Box2D::operator /(int div) const
	{
		return Box2D(x, y, w / div, h / div);
	}
	Box2D& Box2D::operator +=(const Box2D& box)
	{
		x += box.x;
		y += box.y;
		w += box.w;
		h += box.h;
		return *this;
	}
	Box2D& Box2D::operator -=(const Box2D& box)
	{
		x -= box.x;
		y -= box.y;
		w -= box.w;
		h -= box.h;
		return *this;
	}
	Box2D& Box2D::operator *=(int mul)
	{
		w *= mul;
		h *= mul;
		return *this;
	}
	Box2D& Box2D::operator /=(int div)
	{
		w /= div;
		h /= div;
		return *this;
	}
}