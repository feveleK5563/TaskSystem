#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

//アニメーションデータ
struct AnimData
{
	int		startSheet;		//開始位置
	int		relativeSheet;	//終了位置までの相対
	float	waitTime;		//ウェイト
	bool	isLoop;			//ループ

	AnimData();
	AnimData(int startSheet, int relativeSheet, float waitTime, bool isLoop);
};

//画像データ
struct ImageData
{
	int*					handle;		//グラフィックハンドル
	int						sheetNum;	//画像枚数
	std::vector<AnimData*>	anim;		//アニメーション
	MATH::Box2D				rect;		//画像矩形
};

//画像読み込みくん
class ImageLoader
{
private:
	std::unordered_map<std::string, ImageData> imageData;	//画像データ

	ImageLoader() = default;
	static ImageLoader* loader;

public:
	~ImageLoader();

	//画像読み込み
	bool LoadOneImage(const std::string& imgName, const std::string& filePath);
	
	//画像分割読み込み
	bool LoadDivImage(const std::string& imgName, const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize);

	//分割読み込み済みのデータにアニメーションデータを追加
	void AddAnimationData(const std::string& imageName, int startSheet, int endSheet, float waitTime, bool isLoop);

	//画像データの取得
	const ImageData& GetImageData(const std::string& imgName);
	
	//画像データの解放
	std::list<std::pair<const std::string, ImageData>, std::allocator<std::pair<const std::string, ImageData>>>::iterator DeleteImageData(const std::string& imgName);

	//全ての画像データの解放
	void AllDeleteImageData();

	//インスタンスを得る
	static ImageLoader& GetInstance();
	//インスタンスを生成する
	static void CreateInstance();
	//インスタンスを解放する
	static void DeleteInstance();
};