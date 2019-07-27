#pragma once
#include <vector>
#include "Math.h"
#include "ImageLoader.h"

//�F�w��(0 ~ 255)
struct Color
{
    int r, g, b, a;

    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    Color(const Color& color);

    float Fr() const;
    float Fg() const;
    float Fb() const;
    float Fa() const;

    int GetColor();
};

//�摜�f�[�^�̕`��ƃA�j���[�V�����̊Ǘ�
class ImageDrawer
{
private:
    ImageData   image_data_;        //�摜�f�[�^
    Math::Vec2  c_pos_;             //�`��̊�ʒu
    int         now_anim_pattern_;  //���݂̃A�j���[�V�����p�^�[���ԍ�
    float       now_anim_image_;    //���݂̃A�j���[�V�����摜
    bool        is_anim_end_;       //�A�j���[�V�����I���t���O

    float   scale_x_, scale_y_;     //�g�嗦
    bool    is_turn_;               //���]�t���O

public:
    //�R���X�g���N�^
    ImageDrawer();

    //������(�`�悵�����摜�f�[�^���ƕ`���ʒu���Œ�l���Ŏw��)
    void Initialize(const std::string& image_name, Math::BoxCP cp);
    //������(�`�悵�����摜�f�[�^���ƕ`���ʒu�𒼐ڎw��)
    void Initialize(const std::string& image_name, const Math::Vec2& criterion_pos);

    //�A�j���[�V�����̍X�V����
    void AnimUpdate();
    //�A�j���[�V�������I���������ۂ���Ԃ�
    bool IsAnimEnd();
    //�A�j���[�V�����p�^�[���ԍ��̕ύX
    void ChangeAnimPattern(int pattern, bool is_reset_time);

    //�g�嗦��ݒ�
    void SetScale(float scale);
    //�g�嗦��ݒ�(�c����)
    void SetScale(float scale_x, float scale_y);
    //���]���邩�ۂ���ݒ�
    void SetTurnFlag(bool is_turn);
    //���]�t���O�𔽓]
    void ChangeTurnFlag();

    //�ȈՕ`��
    void Draw(const Math::Vec2& pos) const;
    //�`�悷��
    void Draw(const Math::Vec2& pos, float angle, const Color& color = Color()) const;
    //�`��͈͋�`���w�肵�ĕ`�悷��
    void Draw(const Math::Vec2& pos, const Math::Box2D& rect, const Color& color = Color()) const;

    //�w��ԍ��̉摜���ȈՕ`��
    void DrawOne(int image_sheet, const Math::Vec2& pos) const;
    //�w��ԍ��̉摜��`�悷��
    void DrawOne(int image_sheet, const Math::Vec2& pos, float angle, const Color& color = Color()) const;
    //�w��ԍ��̉摜��`��͈͋�`���w�肵�ĕ`�悷��
    void DrawOne(int image_sheet, const Math::Vec2& pos, const Math::Box2D& rect, const Color& color = Color()) const;

    //�V���G�b�g��`��(��񕪕`�悳���)
    void DrawSilhouette(const Math::Vec2& pos, const Color& color = Color()) const;
    //�w��ԍ��̉摜�̃V���G�b�g��`��(��񕪕`�悳���)
    void DrawSilhouetteOne(int image_sheet, const Math::Vec2& pos, const Color& color = Color()) const;

    //���݂̉摜�n���h�����擾
    const int GetNowImageHandle() const;
    //�摜�����]����Ă��邩�ۂ����擾(���]����Ă�����true)
    const bool& GetIsTurn() const;

    //�`��\��̉摜��`���擾
    const Math::Box2D GetDrawImageRect() const;

private:
    //����ȃn���h���̉摜�͖����I
    void CheckHandleError(int image_sheet) const;
};