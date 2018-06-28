#include "ImageDrawer.h"
#include "DxLib.h"

Color::Color(): r(255), g(255), b(255){}

Color::Color(int r, int g, int b): r(r), g(g), b(b){}

Color::Color(const Color& color): r(color.r), g(color.g), b(color.b){}

//-----------------------------------------------------------------------------

//�R���X�g���N�^(�`�悵�����摜�f�[�^�ƃ��[�v���邩�ۂ����w��)
ImageDrawer::ImageDrawer(const ImageData& imageData, const Math::Vec2& criterionPos):
	imageData(imageData),
	criterionPos(criterionPos),
	nowAnimPattern(0),
	nowAnimImage(0),
	color() {}

//�R���X�g���N�^(�`�悵�����摜�f�[�^�ƃ��[�v���邩�ۂ����w��)
ImageDrawer::ImageDrawer(const ImageData& imageData, const Math::Vec2& criterionPos, const Color& color):
	imageData(imageData),
	criterionPos(criterionPos),
	nowAnimPattern(0),
	nowAnimImage(0),
	color(color) {}

//�A�j���[�V����������
bool ImageDrawer::Run()
{
	if (nowAnimImage > imageData.anim[nowAnimPattern]->relativePos)
	{
		if (imageData.anim[nowAnimPattern]->isLoop)
		{
			nowAnimImage = 0;
		}
		else
		{
			nowAnimImage = (float)imageData.anim[nowAnimPattern]->relativePos;
		}
		return true;
	}

	if (imageData.anim[nowAnimPattern]->relativePos >= 0)
		nowAnimImage += 1.0f / imageData.anim[nowAnimPattern]->waitTime;
	else
		nowAnimImage -= 1.0f / imageData.anim[nowAnimPattern]->waitTime;

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
void ImageDrawer::Draw(const Math::Vec2& pos, float scale, float angle, bool isTurn)
{
	SetDrawBright(color.r, color.g, color.b);

	DrawRotaGraph2F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageData.anim[nowAnimPattern]->startPos + (int)nowAnimImage],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
}

//�w��ԍ��̉摜��`�悷��(�A�j���[�V�������Ȃ�)
void ImageDrawer::DrawOne(const Math::Vec2& pos, float scale, float angle, bool isTurn, int imageSheet)
{
	SetDrawBright(color.r, color.g, color.b);

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
}

//�摜�f�[�^���擾
const ImageData& ImageDrawer::GetImageData() const
{
	return imageData;
}