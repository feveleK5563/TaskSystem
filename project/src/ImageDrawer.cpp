#include "ImageDrawer.h"
#include "DxLib.h"

Color::Color(): r(255), g(255), b(255), alpha(255){}

Color::Color(int r, int g, int b, int alpha): r(r), g(g), b(b), alpha(alpha){}

Color::Color(const Color& color): r(color.r), g(color.g), b(color.b), alpha(color.alpha){}


//-----------------------------------------------------------------------------
//コンストラクタ
ImageDrawer::ImageDrawer():
	nowAnimPattern(0),
	nowAnimImage(0){}


//初期化(描画したい画像データを指定、第二引数trueで描画基準位置が中心)
void ImageDrawer::Initialize(const ImageData& setImageData, bool isCriterrionPosCenter)
{
	imageData = setImageData;
	cPos = isCriterrionPosCenter ? MATH::Vec2(imageData.rect.w / 2.f, imageData.rect.h / 2.f) : MATH::Vec2(0, 0);
}
//初期化(描画したい画像データと描画基準位置を指定)
void ImageDrawer::Initialize(const ImageData& setImageData, const MATH::Vec2& setCriterionPos)
{
	imageData = setImageData;
	cPos = setCriterionPos;
}

//アニメーションさせる
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

//アニメーションパターン番号の変更
void ImageDrawer::ChangeAnimPattern(int pattern, bool isResetTime)
{
	nowAnimPattern = pattern;


	if (isResetTime == true)
	{
		nowAnimImage = 0;
	}
}

//簡易描画
void ImageDrawer::Draw(const MATH::Vec2& pos, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	int nai = (int)nowAnimImage;
	if (imageData.anim[nowAnimPattern]->relativeSheet < 0)
	{
		nai *= -1;
	}

	DrawGraphF(
		pos.x - cPos.x, pos.y - cPos.y,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//描画する
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
		cPos.x, cPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//描画する(拡大率縦横別)
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
		cPos.x, cPos.y,
		(double)scaleX, (double)scaleY,
		(double)angle,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//描画範囲矩形を指定して描画する(描画の基準位置は無視する)
void ImageDrawer::Draw(const MATH::Vec2& pos, const MATH::Vec2& criterionPos, const MATH::Box2D& rect, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	int nai = (int)nowAnimImage;
	if (imageData.anim[nowAnimPattern]->relativeSheet < 0)
	{
		nai *= -1;
	}

	MATH::Vec2 tmppos = -pos;

	DrawRectGraphF(
		pos.x - criterionPos.x, pos.y - criterionPos.y,
		rect.x, rect.y,
		rect.w, rect.h,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//指定番号の画像を簡易描画
void ImageDrawer::DrawOne(int imageSheet, const MATH::Vec2& pos, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawGraphF(pos.x, pos.y, imageData.handle[imageSheet], true);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//指定番号の画像を描画する(アニメーションしない)
void ImageDrawer::DrawOne(int imageSheet, const MATH::Vec2& pos, float scale, float angle, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawRotaGraph2F(
		pos.x, pos.y,
		cPos.x, cPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageSheet],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//指定番号の画像を描画する(拡大率縦横別)
void ImageDrawer::DrawOne(int imageSheet, const MATH::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawRotaGraph3F(
		pos.x, pos.y,
		cPos.x, cPos.y,
		(double)scaleX, (double)scaleY,
		(double)angle,
		imageData.handle[imageSheet],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ImageDrawer::DrawOne(int imageSheet, const MATH::Vec2& pos, const MATH::Vec2& criterionPos, const MATH::Box2D& rect, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawRectGraphF(
		pos.x - criterionPos.x, pos.y - criterionPos.y,
		rect.x, rect.y,
		rect.w, rect.h,
		imageData.handle[imageSheet],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//画像データを取得
const ImageData& ImageDrawer::GetImageData() const
{
	return imageData;
}