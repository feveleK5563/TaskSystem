#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

//�A�j���[�V�����f�[�^
struct AnimData
{
	int		startPos;		//�J�n�ʒu
	int		relativePos;	//�I���ʒu�܂ł̑���
	float	waitTime;		//�E�F�C�g
	bool	isLoop;			//���[�v

	AnimData(int startPos, int relativePos, float waitTime, bool isLoop):
		startPos(startPos),
		relativePos(relativePos),
		waitTime(waitTime),
		isLoop(isLoop){}
};

//�摜�f�[�^
struct ImageData
{
	int*					handle;		//�O���t�B�b�N�n���h��
	int						sheetNum;	//�摜����
	std::vector<AnimData*>	anim;		//�A�j���[�V����
	Math::Box2D				rect;		//�摜��`
};

//�摜�ǂݍ��݂���
class ImageLoader
{
private:
	std::unordered_map<std::string, ImageData> imageData;	//�摜�f�[�^

	ImageLoader() = default;

public:
	~ImageLoader();

	//�摜�ǂݍ���
	void LoadOneImage(const std::string& imgName, const std::string& filePath);
	
	//�摜�����ǂݍ���
	void LoadDivImage(const std::string& imgName, const std::string& filePath, int allNum, int xNum, int yNum, int xSize, int ySize);

	//�����ǂݍ��ݍς݂̃f�[�^�ɃA�j���[�V�����f�[�^��ǉ�
	void AddAnimationData(const std::string& imageName, int startPos, int endPos, float waitTime, bool isLoop);

	//�摜�f�[�^�̎擾
	const ImageData& GetImageData(const std::string& imgName);
	
	//�摜�f�[�^�̉��
	auto DeleteImageData(const std::string& imgName);

	//�S�Ẳ摜�f�[�^�̉��
	void AllDeleteImageData();

	//�C���X�^���X�𓾂�
	static ImageLoader& GetInstance();
};

//-----------------------------------------------------------------------------
namespace Image
{
	static ImageLoader& imageLoader = ImageLoader::GetInstance();
}