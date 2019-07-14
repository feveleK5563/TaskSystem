#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

//�A�j���[�V�����f�[�^
struct AnimData
{
    int     start_sheet;        //�J�n�ʒu
    int     relative_sheet;     //�I���ʒu�܂ł̑���
    float   wait_time;          //�E�F�C�g
    bool    is_loop;            //���[�v

    AnimData();
    AnimData(int start_sheet, int relative_sheet, float wait_time, bool is_loop);
};

//�摜�f�[�^
struct ImageData
{
    int*                    handle;     //�O���t�B�b�N�n���h��
    int                     sheet_num;  //�摜����
    std::vector<AnimData*>  anim;       //�A�j���[�V����
    Math::Box2D             rect;       //�摜��`
};

//�摜�ǂݍ��݂���
class ImageLoader
{
private:
    std::unordered_map<std::string, ImageData> image_data;  //�摜�f�[�^

    ImageLoader() = default;
    static ImageLoader* loader;

public:
    ~ImageLoader();

    //�摜�ǂݍ���
    bool LoadOneImage(const std::string& image_name, const std::string& file_path);

    //�摜�����ǂݍ���
    bool LoadDivImage(const std::string& image_name, const std::string& file_path,
                      int all_num, int x_num, int y_num, int x_size, int y_size);

    //�����ǂݍ��ݍς݂̃f�[�^�ɃA�j���[�V�����f�[�^��ǉ�
    void AddAnimationData(const std::string& image_name, int start_sheet, int end_sheet,
                          float wait_time, bool is_loop);

    //�摜�f�[�^�̎擾
    const ImageData& GetImageData(const std::string& image_name);

    //�摜�f�[�^�̉��
    bool DeleteImageData(const std::string& image_name);

    //�S�Ẳ摜�f�[�^�̉��
    bool AllDeleteImageData();

    //�C���X�^���X�𓾂�
    static ImageLoader& GetInstance();
    //�C���X�^���X�𐶐�����
    static void CreateInstance();
    //�C���X�^���X���������
    static void DeleteInstance();

private:
    //���S�ɉ摜�f�[�^���폜����
    bool SafeImageDelete(const std::string& image_name);
};