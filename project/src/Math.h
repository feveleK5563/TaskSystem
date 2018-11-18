#pragma once
#include <math.h>
#include <cmath>

namespace MATH
{
	static const float	PI	= 3.1415926535897932384626433832795028841971f;
	static const double	dPI = 3.1415926535897932384626433832795028841971;

	//�x���@ �� �ʓx�@�ϊ�
	float ToRadian(float deg);
	//�ʓx�@ �� �x���@�ϊ�
	float ToDegree(float rad);

	//�񎟌��x�N�g���N���X
	struct Vec2
	{
		float x, y;

		Vec2();
		Vec2(const Vec2& setVec);
		Vec2(int setX, int setY);
		Vec2(float setX, float setY);

		float	Hypotenuse() const;						//�Εӂ��擾
		float	FormedAngle(const Vec2& vec) const;		//�Ȃ��p���擾(���W�A��)
		float	InnerProduct(const Vec2& vec) const;	//���ς��擾
		float	OuterProduct(const Vec2& vec) const;	//�O�ς��擾
		Vec2&	Normalize();							//�P�ʃx�N�g���ɂ���(���K��)
		Vec2	NormalizeCpy() const;					//�P�ʃx�N�g�����擾

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

	//�����蔻��ƕ`��@�\����`�N���X
	struct Box2D
	{
		int x, y, w, h;

		Box2D();
		Box2D(const Box2D& setBox);
		Box2D(int setX, int setY, int setW, int setH);
		Box2D(int setW, int setH);

		int Area() const;		//�ʐς��擾
		Vec2 GetPos() const;	//���W���擾

		bool IsHit(const Box2D& box) const;	//�w���`�Ƃ̐ڐG����
		bool IsHit(const Vec2& pos) const;	//�w����W�Ƃ̐ڐG����
		bool IsIn(const Box2D& box) const;	//�w���`����`���ɓ����Ă��邩�̔���
		void DrawRect(bool isFill, int color = 0xffffff) const;	//��`�̕`��

		Box2D& Set(int setX, int setY);		//�w����W�ɐݒ�
		Box2D& Set(const Vec2& vec);		//�w����W�ɐݒ�
		Box2D SetCpy(int setX, int setY);	//�w����W�ɐݒ肵���l���擾
		Box2D SetCpy(const Vec2& vec);		//�w����W�ɐݒ肵���l���擾

		Box2D& Offset(int setX, int setY);			//�w����W���I�t�Z�b�g
		Box2D& Offset(const Vec2& vec);				//�w����W���I�t�Z�b�g
		Box2D OffsetCpy(int setX, int setY) const;	//�I�t�Z�b�g�����l���擾
		Box2D OffsetCpy(const Vec2& vec) const;		//�I�t�Z�b�g�����l���擾

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