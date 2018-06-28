#include "ImageLoader.h"
#include "DxLib.h"

//�f�X�g���N�^
ImageLoader::~ImageLoader()
{
	AllDeleteImageData();
}

//�摜�ǂݍ���
void ImageLoader::LoadOneImage(const std::string& imageName, const std::string& filePath)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return;
	}

	//string�^��filePath��char*�ɕϊ�
	char* path = new char[filePath.size() + 1];
	std::char_traits<char>::copy(path, filePath.c_str(), filePath.size() + 1);

	//�ǂݍ��񂾉摜�̃f�[�^���i�[
	imageData[imageName].handle = new int[1]{LoadGraph(path)};
	imageData[imageName].sheetNum = 1;
	int xSize, ySize;
	GetGraphSize(*(imageData[imageName].handle), &xSize, &ySize);
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	delete[] path;
}

//�摜�����ǂݍ���
void ImageLoader::LoadDivImage(const std::string& imageName, const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize)
{
	if (imageData.find(imageName) != imageData.end())
	{
		return;
	}

	//string�^��filePath��char*�ɕϊ�
	char* path = new char[filePath.size() + 1];
	std::char_traits<char>::copy(path, filePath.c_str(), filePath.size() + 1);

	imageData[imageName].handle = new int[allNum] {};
	LoadDivGraph(path, allNum, xNum, yNum, xSize, ySize, imageData[imageName].handle);
	imageData[imageName].sheetNum = allNum;
	imageData[imageName].rect = { 0, 0, xSize, ySize };

	delete[] path;
}

//�����ǂݍ��ݍς݂̃f�[�^�ɃA�j���[�V�����f�[�^��ǉ�
void ImageLoader::AddAnimationData(const std::string& imageName, int startPos, int endPos, float waitTime, bool isLoop)
{
	imageData[imageName].anim.emplace_back(
		new AnimData(startPos, endPos - startPos, waitTime, isLoop)
	);
}

//�摜�f�[�^�̎擾
const ImageData& ImageLoader::GetImageData(const std::string& imageName)
{
	return imageData[imageName];
}

//�摜�f�[�^�̉��
auto ImageLoader::DeleteImageData(const std::string& imageName)
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

//�S�Ẳ摜�f�[�^�̉��
void ImageLoader::AllDeleteImageData()
{
	for (	auto it = imageData.begin();
			it != imageData.end();)
	{
		it = DeleteImageData(it->first);
	}
}

//�C���X�^���X�𓾂�
ImageLoader& ImageLoader::GetInstance()
{
	static ImageLoader imageLoader;
	return imageLoader;
}