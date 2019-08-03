#pragma once
#include <math.h>
#include <cmath>

namespace Math
{
    static const float  PI  = 3.1415926535897932384626433832795028841971f;
    static const double dPI = 3.1415926535897932384626433832795028841971;

    // �x���@ �� �ʓx�@�ϊ�
    float ToRadian(float deg);
    // �ʓx�@ �� �x���@�ϊ�
    float ToDegree(float rad);

    // �͈͓��Ń����_���Ȓl���擾����
    int GetRand(int lower_limit, int upper_limit);

    // �񎟌��x�N�g���N���X
    struct Vec2
    {
        float x, y;

        Vec2();
        Vec2(const Vec2& vec);
        Vec2(int x, int y);
        Vec2(float x, float y);

        float   GetDistance() const;                    // �Εӂ��擾
        float   GetFormedAngle(const Vec2& vec) const;  // �Ȃ��p���擾(���W�A��)
        float   GetDotProduct(const Vec2& vec) const;   // ���ς��擾
        float   GetCrossProduct(const Vec2& vec) const; // �O�ς��擾
        Vec2&   Normalize();                            // �P�ʃx�N�g���ɂ���(���K��)
        Vec2    GetNormalize() const;                   // �P�ʃx�N�g�����擾

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


    // ��`��̊���W�w��p
    enum struct BoxCP
    {
        TOP_LEFT,       // ����
        TOP_MIDDLE,     // ����
        TOP_RIGHT,      // �E��
        MIDDLE_LEFT,    // ����
        CENTER,         // ���S
        MIDDLE_RIGHT,   // �E��
        BOTTOM_LEFT,    // ����
        BOTTOM_MIDDLE,  // ����
        BOTTOM_RIGHT,   // �E��
    };

    // �����蔻��ƕ`��@�\����`�N���X
    struct Box2D
    {
    private:
        

    public:
        float x, y; // ���W
        float w, h; // ��`�T�C�Y

    public:
        Box2D();
        Box2D(const Box2D& box);
        Box2D(const Vec2& pos, const Vec2& rect);
        Box2D(const Vec2& pos, float w, float h);
        Box2D(int x, int y, int w, int h);
        Box2D(float x, float y, float w, float h);

        float GetArea() const;      // �ʐς��擾
        Vec2 GetPos() const;        // ����̍��W���擾

        bool IsHit(const Box2D& box) const; // �w���`�Ƃ̐ڐG����
        bool IsHit(const Vec2& pos) const;  // �w����W�Ƃ̐ڐG����
        bool IsIn(const Box2D& box) const;  // �w���`����`���ɓ����Ă��邩�̔���
        void DrawRect(bool is_fill, int color = 0xffffff) const;    // ��`�̕`��

        void SetPos(const Vec2& pos, BoxCP cp_mode);            // ���W�Ɗ�ʒu��ݒ�
        void Offset(const Vec2& pos, BoxCP cp_mode);            // �w����W���I�t�Z�b�g
        Box2D GetOffset(const Vec2& pos, BoxCP cp_mode) const;  // �I�t�Z�b�g�����l���擾

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
        // ��ʒu����ɍ��W��ϊ�
        Vec2 ChangeCP(const Vec2& pos, BoxCP cp_mode);
    };
}