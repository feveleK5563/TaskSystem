#include <assert.h>
#include "ImageLoader.h"
#include "DxLib.h"
#include "UtilityFunctions.h"

AnimData::AnimData():
	startSheet(0),
	relativeSheet(0),
	waitTime(0),
	isLoop(false) {}

AnimData::AnimData(int startSheet, int relativeSheet, float waitTime, bool isLoop) :
	startSheet(startSheet),
	relativeSheet(relativeSheet),
	waitTime(waitTime),
	isLoop(isLoop) {}

//-----------------------------------------------------------------------------

//デストラクタ
ImageLoader::~ImageLoader()
{
	AllDeleteImageData();
}

//画像読み込み
bool ImageLoader::LoadOneImage(const std::string& imageName, const std::string& filePath)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return false;
	}

	//読み込んだ画像のデータを格納
	imageData[imageName].handle = new int[1]{ LoadGraph(filePath.c_str()) };
	imageData[imageName].sheetNum = 1;
	int xSize, ySize;
	GetGraphSize(*(imageData[imageName].handle), &xSize, &ySize);
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	return true;
}

//画像分割読み込み
bool ImageLoader::LoadDivImage(const std::string& imageName, const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return false;
	}

	//読み込んだ画像のデータを格納
	imageData[imageName].handle = new int[allNum] {};
	if (LoadDivGraph(filePath.c_str(), allNum, xNum, yNum, xSize, ySize, imageData[imageName].handle) == -1)
	{
		return false;
	}
	imageData[imageName].sheetNum = allNum;
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	return true;
}

//分割読み込み済みのデータにアニメーションデータを追加
void ImageLoader::AddAnimationData(const std::string& imageName, int startSheet, int endSheet, float waitTime, bool isLoop)
{
	imageData[imageName].anim.emplace_back(
		new AnimData(startSheet, endSheet - startSheet, max(waitTime, 1.f), isLoop)
	);
}

//画像データの取得
const ImageData& ImageLoader::GetImageData(const std::string& imageName)
{
	//アニメーション設定が行われていなかった場合は、便宜的にアニメーションを設定しておく
	if (imageData[imageName].anim.empty())
	{
		AddAnimationData(imageName, 0, 0, 1, false);
	}

	return imageData[imageName];
}

//画像データの解放
std::list<std::pair<const std::string, ImageData>, std::allocator<std::pair<const std::string, ImageData>>>::iterator ImageLoader::DeleteImageData(const std::string& imageName)
{
	if (!imageData.count(imageName))
		return imageData.end();

	for (int i = 0; i < imageData[imageName].sheetNum; ++i)
	{
		DeleteGraph(imageData[imageName].handle[i]);
	}

	if (imageData[imageName].sheetNum == 1)
	{
		UTIL::SafeDelete(imageData[imageName].handle);
	}
	else
	{
		UTIL::SafeDeleteArr(imageData[imageName].handle);
	}

	for (auto animit : imageData[imageName].anim)
	{
		UTIL::SafeDelete(animit);
	}

	return imageData.erase(imageData.lower_bound(imageName));
}

//全ての画像データの解放
void ImageLoader::AllDeleteImageData()
{
	for (	auto it = imageData.begin();
			it != imageData.end();)
	{
		it = DeleteImageData(it->first);
	}
	imageData.clear();
}

ImageLoader* ImageLoader::loader = nullptr;
//インスタンスを得る
ImageLoader& ImageLoader::GetInstance()
{
	assert(loader != nullptr && "ImageLoader hasn't been created!");
	return *loader;
}
//インスタンスを生成する
void ImageLoader::CreateInstance()
{
	if (loader == nullptr)
	{
		loader = new ImageLoader();
	}
}
//インスタンスを解放する
void ImageLoader::DeleteInstance()
{
	UTIL::SafeDelete(loader);
}