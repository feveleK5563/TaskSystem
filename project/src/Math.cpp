#include "Math.h"
#include "DxLib.h"
#include "Utility.h"

namespace Math
{
    //弧度法変換
    float ToRadian(float deg)
    {
        return deg * PI / 180.0f;
    }

    //度数法変換
    float ToDegree(float rad)
    {
        return 180.0f * rad / PI;
    }

    //--------------------------------------------------------
    //二次元ベクトルクラス
    Vec2::Vec2():
        x(0.f), y(0.f) {}

    Vec2::Vec2(const Vec2& vec):
        x(vec.x), y(vec.y){}

    Vec2::Vec2(int x, int y):
        x((float)x), y((float)y){}

    Vec2::Vec2(float x, float y):
        x(x), y(y){}

    float Vec2::GetDistance() const
    {
        return std::hypotf(x, y);
    }
    float Vec2::GetFormedAngle(const Vec2& vec) const
    {
        return std::acosf(this->GetDotProduct(vec) / (this->GetDistance() * vec.GetDistance()));
    }
    float Vec2::GetDotProduct(const Vec2& vec) const
    {
        return (x * vec.x) + (y * vec.y);
    }
    float Vec2::GetCrossProduct(const Vec2& vec) const
    {
        return (x * vec.x) - (y * vec.y);
    }
    Vec2& Vec2::Normalize()
    {
        float dist = GetDistance();
        assert(dist != 0 && "divition by zero!");
        *this /= dist;
        return *this;
    }
    Vec2 Vec2::GetNormalize() const
    {
        Vec2 tmp(*this);
        return tmp.Normalize();
    }
    
    Vec2& Vec2::operator =(const Vec2& vec)
    {
        x = vec.x;
        y = vec.y;
        return *this;
    }
    Vec2 Vec2::operator +(int val) const
    {
        return Vec2(x + (float)val, y + (float)val);
    }
    Vec2 Vec2::operator +(float val) const
    {
        return Vec2(x + val, y + val);
    }
    Vec2 Vec2::operator +(const Vec2& vec) const
    {
        return Vec2(x + vec.x, y + vec.y);
    }
    Vec2 Vec2::operator -(int val) const
    {
        return Vec2(x - (float)val, y - (float)val);
    }
    Vec2 Vec2::operator -(float val) const
    {
        return Vec2(x - val, y - val);
    }
    Vec2 Vec2::operator -(const Vec2& vec) const
    {
        return Vec2(x - vec.x, y - vec.y);
    }
    Vec2 Vec2::operator *(int mul) const
    {
        return Vec2(x * (float)mul, y * (float)mul);
    }
    Vec2 Vec2::operator *(float mul) const
    {
        return Vec2(x * mul, y * mul);
    }
    Vec2 Vec2::operator *(const Vec2& vec) const
    {
        return Vec2(x * vec.x, y * vec.y);
    }
    Vec2 Vec2::operator /(int div) const
    {
        return Vec2(x / (float)div, y / (float)div);
    }
    Vec2 Vec2::operator /(float div) const
    {
        return Vec2(x / div, y / div);
    }
    Vec2 Vec2::operator /(const Vec2& vec) const
    {
        return Vec2(x / vec.x, y / vec.y);
    }
    Vec2& Vec2::operator +=(int val)
    {
        x += (float)val;
        y += (float)val;
        return *this;
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
    Vec2& Vec2::operator -=(int val)
    {
        x -= (float)val;
        y -= (float)val;
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
    Vec2& Vec2::operator *=(int mul)
    {
        x *= (float)mul;
        y *= (float)mul;
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
    Vec2& Vec2::operator /=(int div)
    {
        x /= (float)div;
        y /= (float)div;
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
    bool Vec2::operator ==(const Vec2& vec) const
    {
        return (x == vec.x) && (y == vec.y);
    }
    bool Vec2::operator !=(const Vec2& vec) const
    {
        return (x != vec.x) || (y != vec.y);
    }
    float& Vec2::operator()(int val)
    {
        switch (val % 2)
        {
        case 0: return x;
        case 1: return y;
        }
        assert(false && "out of range");
        return x;
    }


    //--------------------------------------------------------
    //当たり判定と描画機能つき矩形クラス
    Box2D::Box2D():
        x(0.f), y(0.f), w(0.f), h(0.f){}

    Box2D::Box2D(const Box2D& box):
        x(box.x), y(box.y), w(box.w), h(box.h){}

    Box2D::Box2D(const Vec2& pos, const Vec2& rect):
        x(pos.x), y(pos.y), w(rect.x), h(rect.y){}

    Box2D::Box2D(const Vec2& pos, float w, float h):
        x(pos.x), y(pos.y), w(w), h(h){}

    Box2D::Box2D(int x, int y, int w, int h) :
        x((float)x), y((float)y), w((float)w), h((float)h){}

    Box2D::Box2D(float x, float y, float w, float h):
        x(x), y(y), w(w), h(h){}

    float Box2D::GetArea() const
    {
        return w * y;
    }
    Vec2 Box2D::GetPos() const
    {
        return Vec2(x, y);
    }

    bool Box2D::IsHit(const Box2D& box) const
    {
        return x < box.x + box.w && box.x < x + w &&
               y < box.y + box.h && box.y < y + h;
    }
    bool Box2D::IsHit(const Vec2& pos) const
    {
        return x < pos.x && pos.x < x + w &&
               y < pos.y && pos.y < y + h;
    }
    bool Box2D::IsIn(const Box2D& box) const
    {
        return x < box.x && box.x + box.w < x + w &&
               y < box.y && box.y + box.h < y + h;
    }
    void Box2D::DrawRect(bool isFill, int color) const
    {
        DrawBoxAA(x, y, x + w, y + h, color, isFill);
    }

    void Box2D::SetPos(const Vec2& pos, BoxCP cp_mode)
    {
        Vec2 cp(ChangeCP(pos, cp_mode));
        x = cp.x;
        y = cp.y;
    }
    void Box2D::Offset(const Vec2& pos, BoxCP cp_mode)
    {
        Vec2 cp(ChangeCP(pos, cp_mode));
        x += cp.x;
        y += cp.y;
    }
    Box2D Box2D::GetOffset(const Vec2& pos, BoxCP cp_mode) const
    {
        Box2D cpy(*this);
        cpy.Offset(pos, cp_mode);
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
        return Box2D(x, y, w * (float)mul, h * (float)mul);
    }
    Box2D Box2D::operator *(float mul) const
    {
        return Box2D(x, y, w * mul, h * mul);
    }
    Box2D Box2D::operator /(int div) const
    {
        return Box2D(x, y, w / (float)div, h / (float)div);
    }
    Box2D Box2D::operator /(float div) const
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
    Box2D& Box2D::operator *=(float mul)
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
    Box2D& Box2D::operator /=(float div)
    {
        w /= div;
        h /= div;
        return *this;
    }
    bool Box2D::operator ==(const Box2D& box)
    {
        return (x == box.x) && (y == box.y) &&
               (w == box.w) && (h == box.h);
    }
    float& Box2D::operator ()(int val)
    {
        switch (val % 4)
        {
        case 0: return x;
        case 1: return y;
        case 2: return w;
        case 3: return h;
        }
        assert(false && "out of range");
        return x;
    }

    Vec2 Box2D::ChangeCP(const Vec2& pos, BoxCP cp_mode)
    {
        Vec2 cp;
        switch (cp_mode)
        {
        case Math::BoxCP::TOP_LEFT:
            cp.x = pos.x;
            cp.y = pos.y;
            break;
        case Math::BoxCP::TOP_MIDDLE:
            cp.x = pos.x - (w / 2.f);
            cp.y = pos.y;
            break;
        case Math::BoxCP::TOP_RIGHT:
            cp.x = pos.x - w;
            cp.y = pos.y;
            break;
        case Math::BoxCP::MIDDLE_LEFT:
            cp.x = pos.x;
            cp.y = pos.y - (h / 2.f);
            break;
        case Math::BoxCP::CENTER:
            cp.x = pos.x - (w / 2.f);
            cp.y = pos.y - (h / 2.f);
            break;
        case Math::BoxCP::MIDDLE_RIGHT:
            cp.x = pos.x - w;
            cp.y = pos.y - (h / 2.f);
            break;
        case Math::BoxCP::BOTTOM_LEFT:
            cp.x = pos.x;
            cp.y = pos.y - h;
            break;
        case Math::BoxCP::BOTTOM_MIDDLE:
            cp.x = pos.x - (w / 2.f);
            cp.y = pos.y - h;
            break;
        case Math::BoxCP::BOTTOM_RIGHT:
            cp.x = pos.x - w;
            cp.y = pos.y - h;
            break;
        }
        return cp;
    }
}