#define NOMINMAX
#include <algorithm>
#include "ImageLoader.h"
#include "DxLib.h"

AnimData::AnimData():
	startPos(0),
	relativePos(0),
	waitTime(0),
	isLoop(false) {}

AnimData::AnimData(int startPos, int relativePos, float waitTime, bool isLoop) :
	startPos(startPos),
	relativePos(relativePos),
	waitTime(waitTime),
	isLoop(isLoop) {}

//-----------------------------------------------------------------------------

//デストラクタ
ImageLoader::~ImageLoader()
{
	AllDeleteImageData();
}

//画像読み込み
void ImageLoader::LoadOneImage(const std::string& imageName, const std::string& filePath)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return;
	}

	//string型のfilePathをchar*に変換
	char* path = new char[filePath.size() + 1];
	std::char_traits<char>::copy(path, filePath.c_str(), filePath.size() + 1);

	//読み込んだ画像のデータを格納
	imageData[imageName].handle = new int[1]{LoadGraph(path)};
	imageData[imageName].sheetNum = 1;
	int xSize, ySize;
	GetGraphSize(*(imageData[imageName].handle), &xSize, &ySize);
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	delete[] path;
}

//画像分割読み込み
void ImageLoader::LoadDivImage(const std::string& imageName, const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return;
	}

	//string型のfilePathをchar*に変換
	char* path = new char[filePath.size() + 1];
	std::char_traits<char>::copy(path, filePath.c_str(), filePath.size() + 1);

	imageData[imageName].handle = new int[allNum] {};
	LoadDivGraph(path, allNum, xNum, yNum, xSize, ySize, imageData[imageName].handle);
	imageData[imageName].sheetNum = allNum;
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	delete[] path;
}

//分割読み込み済みのデータにアニメーションデータを追加
void ImageLoader::AddAnimationData(const std::string& imageName, int startPos, int endPos, float waitTime, bool isLoop)
{
	imageData[imageName].anim.emplace_back(
		new AnimData(startPos, endPos - startPos, std::max(waitTime, 1.f), isLoop)
	);
}

//画像データの取得
const ImageData& ImageLoader::GetImageData(const std::string& imageName)
{
	//アニメーション設定が行われていなかった場合
	//便宜的にアニメーションを設定しておく
	if (imageData[imageName].anim.empty())
	{
		AddAnimationData(imageName, 0, 0, 1, false);
	}

	return imageData[imageName];
}

//画像データの解放
std::list<std::pair<const std::string, ImageData>, std::allocator<std::pair<const std::string, ImageData>>>::iterator ImageLoader::DeleteImageData(const std::string& imageName)
{
	for (int i = 0; i < imageData[imageName].sheetNum; ++i)
	{
		DeleteGraph(imageData[imageName].handle[i]);
	}

	if (imageData[imageName].sheetNum == 1)
	{
		delete imageData[imageName].handle;
	}
	else
	{
		delete[] imageData[imageName].handle;
	}

	for (auto animit : imageData[imageName].anim)
	{
		delete animit;
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
}

//インスタンスを得る
ImageLoader& ImageLoader::GetInstance()
{
	static ImageLoader imageLoader;
	return imageLoader;
}