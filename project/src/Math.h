#pragma once
#include <math.h>
#include <cmath>

namespace Math
{
    static const float  PI  = 3.1415926535897932384626433832795028841971f;
    static const double dPI = 3.1415926535897932384626433832795028841971;

    // 度数法 → 弧度法変換
    float ToRadian(float deg);
    // 弧度法 → 度数法変換
    float ToDegree(float rad);

    // 範囲内でランダムな値を取得する
    int GetRand(int lower_limit, int upper_limit);

    // 二次元ベクトルクラス
    struct Vec2
    {
        float x, y;

        Vec2();
        Vec2(const Vec2& vec);
        Vec2(int x, int y);
        Vec2(float x, float y);

        float   GetDistance() const;                    // 斜辺を取得
        float   GetFormedAngle(const Vec2& vec) const;  // なす角を取得(ラジアン)
        float   GetDotProduct(const Vec2& vec) const;   // 内積を取得
        float   GetCrossProduct(const Vec2& vec) const; // 外積を取得
        Vec2&   Normalize();                            // 単位ベクトルにする(正規化)
        Vec2    GetNormalize() const;                   // 単位ベクトルを取得

        Vec2&   operator =(const Vec2& vec);
        Vec2    operator +(int val) const;
        Vec2    operator +(float val) const;
        Vec2    operator +(const Vec2& vec) const;
        Vec2    operator -(int val) const;
        Vec2    operator -(float val) const;
        Vec2    operator -(const Vec2& vec) const;
        Vec2    operator *(int mul) const;
        Vec2    operator *(float mul) const;
        Vec2    operator *(const Vec2& vec) const;
        Vec2    operator /(int div) const;
        Vec2    operator /(float div) const;
        Vec2    operator /(const Vec2& vec) const;
        Vec2&   operator +=(int val);
        Vec2&   operator +=(float val);
        Vec2&   operator +=(const Vec2& vec);
        Vec2&   operator -=(int val);
        Vec2&   operator -=(float val);
        Vec2&   operator -=(const Vec2& vec);
        Vec2&   operator *=(int mul);
        Vec2&   operator *=(float mul);
        Vec2&   operator *=(const Vec2& vec);
        Vec2&   operator /=(int div);
        Vec2&   operator /=(float div);
        Vec2&   operator /=(const Vec2& vec);
        Vec2&   operator ++();
        Vec2    operator ++(int);
        Vec2&   operator --();
        Vec2    operator --(int);
        Vec2    operator -() const;
        bool    operator ==(const Vec2& vec) const;
        bool    operator !=(const Vec2& vec) const;
        float&  operator ()(int val);
    };


    // 矩形上の基準座標指定用
    enum struct BoxCP
    {
        TOP_LEFT,       // 左上
        TOP_MIDDLE,     // 中上
        TOP_RIGHT,      // 右上
        MIDDLE_LEFT,    // 左中
        CENTER,         // 中心
        MIDDLE_RIGHT,   // 右中
        BOTTOM_LEFT,    // 左下
        BOTTOM_MIDDLE,  // 中下
        BOTTOM_RIGHT,   // 右下
    };

    // 当たり判定と描画機能つき矩形クラス
    struct Box2D
    {
    private:
        

    public:
        float x, y; // 座標
        float w, h; // 矩形サイズ

    public:
        Box2D();
        Box2D(const Box2D& box);
        Box2D(const Vec2& pos, const Vec2& rect);
        Box2D(const Vec2& pos, float w, float h);
        Box2D(int x, int y, int w, int h);
        Box2D(float x, float y, float w, float h);

        float GetArea() const;      // 面積を取得
        Vec2 GetPos() const;        // 左上の座標を取得

        bool IsHit(const Box2D& box) const; // 指定矩形との接触判定
        bool IsHit(const Vec2& pos) const;  // 指定座標との接触判定
        bool IsIn(const Box2D& box) const;  // 指定矩形が矩形内に入っているかの判定
        void DrawRect(bool is_fill, int color = 0xffffff) const;    // 矩形の描画

        void SetPos(const Vec2& pos, BoxCP cp_mode);            // 座標と基準位置を設定
        void Offset(const Vec2& pos, BoxCP cp_mode);            // 指定座標分オフセット
        Box2D GetOffset(const Vec2& pos, BoxCP cp_mode) const;  // オフセットした値を取得

        Box2D&  operator =(const Box2D& box);
        Box2D   operator +(const Box2D& box) const;
        Box2D   operator -(const Box2D& box) const;
        Box2D   operator *(int mul) const;
        Box2D   operator *(float mul) const;
        Box2D   operator /(int div) const;
        Box2D   operator /(float div) const;
        Box2D&  operator +=(const Box2D& box);
        Box2D&  operator -=(const Box2D& box);
        Box2D&  operator *=(int mul);
        Box2D&  operator *=(float mul);
        Box2D&  operator /=(int div);
        Box2D&  operator /=(float div);
        bool    operator ==(const Box2D& box);
        float&  operator ()(int val);

    private:
        // 基準位置を基に座標を変換
        Vec2 ChangeCP(const Vec2& pos, BoxCP cp_mode);
    };
}