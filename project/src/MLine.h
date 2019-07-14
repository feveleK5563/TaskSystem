#pragma once
#include <memory>
#include <string>
#include "DxLib.h"
#include "Math.h"
#include "ImageDrawer.h"

//----------------------------------------------
//�V�F�[�_�[�ɑ�����
struct MLineInfo
{
    FLOAT2  window_size;    //��ʃT�C�Y
    FLOAT2  start_pos;      //�n�[���W
    FLOAT2  end_pos;        //�I�[���W
    float   thick;          //���̑���
    float   r;
    float   g;
    float   b;
    float   a;
};

//----------------------------------------------
//�V�F�[�_�[�g���̂ł��̊Ǘ�
class MResource
{
private:
    static std::weak_ptr<MResource> instance_;

public:
    std::string shader_name;
    std::string buffer_name;

    MResource();    //�R���X�g���N�^
    ~MResource();   //�f�X�g���N�^
    static std::shared_ptr<MResource> Create(); //���\�[�X�̐���
};

//----------------------------------------------
//�C����G��ŕ`�悳�������Ǘ�����N���X
class MLine
{
public:
    enum struct MHit
    {
        Parfect,    //�D(��v)
        Excess,     //��(�ߑ�)
        Short,      //��(������v)
        Miss,       //�s��(���s)
    };

private:
    const int MAX_POINT_NUM_ = 4;
    const int MAX_LINE_NUM_  = 6;

    std::shared_ptr<MResource> mres_;
    float dist_;        //���̒���
    int thick_;         //����
    int line_flag_;     //���̔����t���O

public:
    MLine(float dist, int thick);

    //���������_���ɐ�������
    void CreateRandomLine(int line_num);
    //����ǉ�����
    bool AddLine(int point_a, int point_b);
    bool AddLine(int line_id);
    //�����擾����
    int GetMLine();
    //�������Z�b�g����
    void ResetLine();
    //���̐��Ɣ�����s��
    MHit CheckHitLine(int line);

    //����`�悷��
    void Draw(const Math::Vec2& pos, const Color& color);
};