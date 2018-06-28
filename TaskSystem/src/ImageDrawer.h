#pragma once
#include <vector>
#include "Math.h"
#include "ImageLoader.h"

//�F�w��
struct Color
{
	int r, g, b;

	Color();
	Color(int r, int g, int b);
	Color(const Color& color);
};

//�摜�f�[�^�̕`��ƃA�j���[�V�����̊Ǘ�
class ImageDrawer
{
private:
	ImageData	imageData;		//�摜�f�[�^
	Math::Vec2	criterionPos;	//�`��̊�ʒu
	int			nowAnimPattern;	//���݂̃A�j���[�V�����p�^�[���ԍ�
	float		nowAnimImage;	//���݂̃A�j���[�V�����摜
	Color		color;			//RGB(�ԗΐ�)

public:
	//�R���X�g���N�^(�`�悵�����摜�f�[�^���w��)
	ImageDrawer(const ImageData& imageData, const Math::Vec2& criterionPos);
	//�R���X�g���N�^(�`�悵�����摜�f�[�^�ƕ`��P�x���w��)
	ImageDrawer(const ImageData& imageData, const Math::Vec2& criterionPos, const Color& color);

	bool Run();	//�A�j���[�V����������(�A�j���[�V���������������true���Ԃ�)
	void ChangeAnimPattern(int pattern, bool isResetTime);	//�A�j���[�V�����p�^�[���ԍ��̕ύX

	void Draw(const Math::Vec2& pos, float scale, float angle, bool isTurn);	//�`�悷��
	void DrawOne(const Math::Vec2& pos, float scale, float angle, bool isTurnint, int imageSheet);	//�w��ԍ��̉摜��`�悷��

	const ImageData& GetImageData() const;	//�摜�f�[�^���擾
};