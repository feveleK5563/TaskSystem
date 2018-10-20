#pragma once
#include <vector>
#include "Math.h"
#include "ImageLoader.h"

//色指定
struct Color
{
	int r, g, b, alpha;

	Color();
	Color(int r, int g, int b, int alpha);
	Color(const Color& color);
};

//画像データの描画とアニメーションの管理
class ImageDrawer
{
private:
	ImageData	imageData;		//画像データ
	MATH::Vec2	criterionPos;	//描画の基準位置
	int			nowAnimPattern;	//現在のアニメーションパターン番号
	float		nowAnimImage;	//現在のアニメーション画像

public:
	//コンストラクタ
	ImageDrawer();

	//初期化(描画したい画像データを指定、第二引数trueで描画基準位置が中心)
	void Initialize(const ImageData& setImageData, bool isCriterrionPosCenter);
	//初期化(描画したい画像データと描画基準位置を指定)
	void Initialize(const ImageData& setImageData, const MATH::Vec2& setCriterionPos);

	//アニメーションの更新処理(アニメーションが一周したらtrueが返る)
	bool AnimUpdate();
	//アニメーションパターン番号の変更
	void ChangeAnimPattern(int pattern, bool isResetTime);

	//描画する
	void Draw(const MATH::Vec2& pos, float scale, float angle, bool isTurn, const Color& color);
	//描画する(拡大率縦横別)
	void Draw(const MATH::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurn, const Color& color);
	//指定番号の画像を描画する
	void DrawOne(const MATH::Vec2& pos, float scale, float angle, bool isTurnint, int imageSheet, const Color& color);
	//指定番号の画像を描画する(拡大率縦横別)
	void DrawOne(const MATH::Vec2& pos, float scaleX, float scaleY, float angle, bool isTurnint, int imageSheet, const Color& color);

	const ImageData& GetImageData() const;	//画像データを取得
};