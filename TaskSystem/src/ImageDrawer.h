#pragma once
#include <vector>
#include "Math.h"
#include "ImageLoader.h"

//�F�w��
struct Color
{
	int r, g, b, alpha;

	Color();
	Color(int r, int g, int b, int alpha);
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

public:
	//�R���X�g���N�^(�`�悵�����摜�f�[�^���w��A������true�ŕ`���ʒu�����S)
	ImageDrawer(const ImageData& imageData, bool isCriterrionPosCenter);
	//�R���X�g���N�^(�`�悵�����摜�f�[�^�ƕ`���ʒu���w��)
	ImageDrawer(const ImageData& imageData, const Math::Vec2& criterionPos);

	bool Run();	//�A�j���[�V����������(�A�j���[�V���������������true���Ԃ�)
	void ChangeAnimPattern(int pattern, bool isResetTime);	//�A�j���[�V�����p�^�[���ԍ��̕ύX

	//�`�悷��
	void Draw(const Math::Vec2& pos, float scale, float angle, bool isTurn, const Color& color);
	//�`�悷��(�g�嗦�c����)
	void Draw(const Math::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurn, const Color& color);
	//�w��ԍ��̉摜��`�悷��
	void DrawOne(const Math::Vec2& pos, float scale, float angle, bool isTurnint, int imageSheet, const Color& color);
	//�w��ԍ��̉摜��`�悷��(�g�嗦�c����)
	void DrawOne(const Math::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurnint, int imageSheet, const Color& color);

	const ImageData& GetImageData() const;	//�摜�f�[�^���擾
};