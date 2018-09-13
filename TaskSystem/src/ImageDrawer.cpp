#include "ImageDrawer.h"
#include "DxLib.h"

Color::Color(): r(255), g(255), b(255), alpha(255){}

Color::Color(int r, int g, int b, int alpha): r(r), g(g), b(b), alpha(alpha){}

Color::Color(const Color& color): r(color.r), g(color.g), b(color.b), alpha(color.alpha){}


//-----------------------------------------------------------------------------
//�R���X�g���N�^
ImageDrawer::ImageDrawer():
	nowAnimPattern(0),
	nowAnimImage(0){}


//������(�`�悵�����摜�f�[�^���w��A������true�ŕ`���ʒu�����S)
void ImageDrawer::Initialize(const ImageData& setImageData, bool isCriterrionPosCenter)
{
	imageData = setImageData;
	criterionPos = isCriterrionPosCenter ? MATH::Vec2(imageData.rect.w / 2.f, imageData.rect.h / 2.f) : MATH::Vec2(0, 0);
}
//������(�`�悵�����摜�f�[�^�ƕ`���ʒu���w��)
void ImageDrawer::Initialize(const ImageData& setImageData, const MATH::Vec2& setCriterionPos)
{
	imageData = setImageData;
	criterionPos = setCriterionPos;
}

//�A�j���[�V����������
bool ImageDrawer::AnimUpdate()
{
	nowAnimImage += 1.0f / imageData.anim[nowAnimPattern]->waitTime;

	if (int(nowAnimImage) > abs(imageData.anim[nowAnimPattern]->relativeSheet))
	{
		if (imageData.anim[nowAnimPattern]->isLoop)
		{
			nowAnimImage = 0;
		}
		else
		{
			nowAnimImage = fabsf((float)imageData.anim[nowAnimPattern]->relativeSheet);
		}
		return true;
	}

	return false;
}

//�A�j���[�V�����p�^�[���ԍ��̕ύX
void ImageDrawer::ChangeAnimPattern(int pattern, bool isResetTime)
{
	nowAnimPattern = pattern;

	if (isResetTime == true)
	{
		nowAnimImage = 0;
	}
}

//�`�悷��
void ImageDrawer::Draw(const MATH::Vec2& pos, float scale, float angle, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	int nai = (int)nowAnimImage;
	if (imageData.anim[nowAnimPattern]->relativeSheet < 0)
	{
		nai *= -1;
	}

	DrawRotaGraph2F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�`�悷��(�g�嗦�c����)
void ImageDrawer::Draw(const MATH::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	int nai = (int)nowAnimImage;
	if (imageData.anim[nowAnimPattern]->relativeSheet < 0)
	{
		nai *= -1;
	}

	DrawRotaGraph3F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scaleX, (double)scaleY,
		(double)angle,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�w��ԍ��̉摜��`�悷��(�A�j���[�V�������Ȃ�)
void ImageDrawer::DrawOne(const MATH::Vec2& pos, float scale, float angle, bool isTurn, int imageSheet, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawRotaGraph2F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageSheet],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�w��ԍ��̉摜��`�悷��(�g�嗦�c����)
void ImageDrawer::DrawOne(const MATH::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurn, int imageSheet, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawRotaGraph3F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scaleX, (double)scaleY,
		(double)angle,
		imageData.handle[imageSheet],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�摜�f�[�^���擾
const ImageData& ImageDrawer::GetImageData() const
{
	return imageData;
}