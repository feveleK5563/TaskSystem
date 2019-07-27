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
    int*                    handle = nullptr;   //�O���t�B�b�N�n���h��
    int                     sheet_num = 0;      //�摜����
    std::vector<AnimData*>  anim;               //�A�j���[�V����
    Math::Box2D             rect;               //�摜��`
};

//�摜�ǂݍ��݂���
class ImageLoader
{
public:
    //�C���X�^���X�𐶐�����
    static void Create();
    //�C���X�^���X���������
    static void Delete();

    //�摜�ǂݍ���
    static bool LoadOneImage(const std::string& image_name, const std::string& file_path);

    //�摜�����ǂݍ���
    static bool LoadDivImage(const std::string& image_name, const std::string& file_path,
                             int all_num, int x_num, int y_num, int x_size, int y_size);

    //�����ǂݍ��ݍς݂̃f�[�^�ɃA�j���[�V�����f�[�^��ǉ�
    static void AddAnimationData(const std::string& image_name, int start_sheet, int end_sheet,
                                 float wait_time, bool is_loop);

    //�摜�f�[�^�̎擾
    static const ImageData& GetImageData(const std::string& image_name);

    //�摜�f�[�^�̉��
    static bool DeleteImageData(const std::string& image_name);

    //�S�Ẳ摜�f�[�^�̉��
    static bool AllDeleteImageData();

private:
    class Impl;
    static Impl* impl_;
    static Impl* GetImpl();
};