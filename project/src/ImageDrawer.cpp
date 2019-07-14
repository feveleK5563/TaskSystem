#include "ImageDrawer.h"
#include "DxLib.h"
#include "Utility.h"
#include "ImageLoader.h"

Color::Color():
    r(255), g(255), b(255), a(255){}

Color::Color (int r, int g, int b):
    r(r), g(g), b(b), a(255){}

Color::Color (int r, int g, int b, int a):
    r(r), g(g), b(b), a(a){}

Color::Color (float r, float g, float b):
    r(int(r * 255.f)), g(int(g * 255.f)), b(int(b * 255.f)), a(255){}

Color::Color (float r, float g, float b, float a):
    r(int(r * 255.f)), g(int(g * 255.f)), b(int(b * 255.f)), a(int(a * 255.f)){}

Color::Color(const Color& color): r(color.r), g(color.g), b(color.b), a(color.a){}

float Color::Fr() const { return float(r) / 255.f; }
float Color::Fg() const { return float(g) / 255.f; }
float Color::Fb() const { return float(b) / 255.f; }
float Color::Fa() const { return float(a) / 255.f; }

int Color::GetColor() { return r * g * b; }

//-----------------------------------------------------------------------------
//�R���X�g���N�^
ImageDrawer::ImageDrawer():
    now_anim_pattern_(0),
    now_anim_image_(0),
    is_anim_end_(false),
    scale_x_(1.f),
    scale_y_(1.f),
    is_turn_(false){}


//������(�`�悵�����摜�f�[�^���w��A������true�ŕ`���ʒu�����S)
void ImageDrawer::Initialize(const std::string& image_name, Math::BoxCP cp)
{
    image_data_ = ImageLoader::GetInstance().GetImageData(image_name);
    switch (cp)
    {
    case Math::BoxCP::TOP_LEFT:
        c_pos_ = Math::Vec2(0.f, 0.f);
        break;
    case Math::BoxCP::TOP_MIDDLE:
        c_pos_ = Math::Vec2(image_data_.rect.w / 2.f, 0.f);
        break;
    case Math::BoxCP::TOP_RIGHT:
        c_pos_ = Math::Vec2(image_data_.rect.w, 0.f);
        break;
    case Math::BoxCP::MIDDLE_LEFT:
        c_pos_ = Math::Vec2(0.f, image_data_.rect.h / 2.f);
        break;
    case Math::BoxCP::CENTER:
        c_pos_ = Math::Vec2(image_data_.rect.w / 2.f, image_data_.rect.h / 2.f);
        break;
    case Math::BoxCP::MIDDLE_RIGHT:
        c_pos_ = Math::Vec2(image_data_.rect.w, image_data_.rect.h / 2.f);
        break;
    case Math::BoxCP::BOTTOM_LEFT:
        c_pos_ = Math::Vec2(0.f, image_data_.rect.h);
        break;
    case Math::BoxCP::BOTTOM_MIDDLE:
        c_pos_ = Math::Vec2(image_data_.rect.w / 2.f, image_data_.rect.h);
        break;
    case Math::BoxCP::BOTTOM_RIGHT:
        c_pos_ = Math::Vec2(image_data_.rect.w, image_data_.rect.h);
        break;
    }
}
//������(�`�悵�����摜�f�[�^�ƕ`���ʒu���w��)
void ImageDrawer::Initialize(const std::string& image_name, const Math::Vec2& criterion_pos)
{
    image_data_ = ImageLoader::GetInstance().GetImageData(image_name);
    c_pos_ = criterion_pos;
}

//�A�j���[�V����������
void ImageDrawer::AnimUpdate()
{
    now_anim_image_ += 1.0f / image_data_.anim[now_anim_pattern_]->wait_time;

    if (int(now_anim_image_) > abs(image_data_.anim[now_anim_pattern_]->relative_sheet))
    {
        if (image_data_.anim[now_anim_pattern_]->is_loop)
        {
            now_anim_image_ = 0;
        }
        else
        {
            now_anim_image_ = fabsf((float)image_data_.anim[now_anim_pattern_]->relative_sheet);
            is_anim_end_ = true;
        }
        return;
    }
    is_anim_end_ = false;
}

//�A�j���[�V�������I���������ۂ���Ԃ�
bool ImageDrawer::IsAnimEnd()
{
    return is_anim_end_;
}

//�A�j���[�V�����p�^�[���ԍ��̕ύX
void ImageDrawer::ChangeAnimPattern(int pattern, bool reset_time)
{
    now_anim_pattern_ = pattern;
    is_anim_end_ = false;

    if (reset_time == true)
    {
        now_anim_image_ = 0;
    }
}

//�g�嗦��ݒ�
void ImageDrawer::SetScale(float scale)
{
    scale_x_ = scale;
    scale_y_ = scale;
}
//�g�嗦��ݒ�(�c����)
void ImageDrawer::SetScale(float scale_x, float scale_y)
{
    scale_x_ = scale_x;
    scale_y_ = scale_y;
}
//���]���邩�ۂ���ݒ�
void ImageDrawer::SetTurnFlag(bool is_turn)
{
    is_turn_ = is_turn;
    is_anim_end_ = false;
}
//���]�t���O�𔽓]
void ImageDrawer::ChangeTurnFlag()
{
    is_turn_ = !is_turn_;
    is_anim_end_ = false;
}

//�ȈՕ`��
void ImageDrawer::Draw(const Math::Vec2& pos) const
{
    int handle = GetNowImageHandle();

    DrawRotaGraph3F(
        pos.x, pos.y,
        c_pos_.x, c_pos_.y,
        (double)scale_x_, (double)scale_y_,
        0.0,
        handle,
        true,
        is_turn_,
        false);
}

//�`�悷��
void ImageDrawer::Draw(const Math::Vec2& pos, float angle, const Color& color) const
{
    SetDrawBright(color.r, color.g, color.b);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);

    int handle = GetNowImageHandle();

    DrawRotaGraph3F(
        pos.x, pos.y,
        c_pos_.x, c_pos_.y,
        (double)scale_x_, (double)scale_y_,
        (double)angle,
        handle,
        true,
        is_turn_,
        false);

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�`��͈͋�`���w�肵�ĕ`�悷��(�`��̊�ʒu�͖�������)
void ImageDrawer::Draw(const Math::Vec2& pos, const Math::Box2D& rect, const Color& color) const
{
    SetDrawBright(color.r, color.g, color.b);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);

    int handle = GetNowImageHandle();

    Math::Vec2 tmppos = -pos;

    DrawRectGraphF(
        pos.x - c_pos_.x, pos.y - c_pos_.y,
        (int)rect.x, (int)rect.y,
        (int)rect.w, (int)rect.h,
        handle,
        true,
        is_turn_,
        false);

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//�w��ԍ��̉摜���ȈՕ`��(�A�j���[�V�������Ȃ�)
void ImageDrawer::DrawOne(int image_sheet, const Math::Vec2& pos) const
{
    CheckHandleError(image_sheet);

    DrawRotaGraph3F(
        pos.x, pos.y,
        c_pos_.x, c_pos_.y,
        (double)scale_x_, (double)scale_y_,
        0.0,
        image_data_.handle[image_sheet],
        true,
        is_turn_,
        false);
}

//�w��ԍ��̉摜��`�悷��(�A�j���[�V�������Ȃ�)
void ImageDrawer::DrawOne(int image_sheet, const Math::Vec2& pos, float angle, const Color& color) const
{
    CheckHandleError(image_sheet);

    SetDrawBright(color.r, color.g, color.b);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);

    DrawRotaGraph3F(
        pos.x, pos.y,
        c_pos_.x, c_pos_.y,
        (double)scale_x_, (double)scale_y_,
        (double)angle,
        image_data_.handle[image_sheet],
        true,
        is_turn_,
        false);

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�w��ԍ��̉摜��`��͈͋�`���w�肵�ĕ`�悷��
void ImageDrawer::DrawOne(int image_sheet, const Math::Vec2& pos, const Math::Box2D& rect, const Color& color) const
{
    CheckHandleError(image_sheet);

    SetDrawBright(color.r, color.g, color.b);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);

    DrawRectGraphF(
        pos.x - c_pos_.x, pos.y - c_pos_.y,
        (int)rect.x, (int)rect.y,
        (int)rect.w, (int)rect.h,
        image_data_.handle[image_sheet],
        true,
        is_turn_,
        false);

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�V���G�b�g��`�悳����
void ImageDrawer::DrawSilhouette(const Math::Vec2& pos, const Color& color) const
{
    SetDrawBright(color.r, color.g, color.b);
    SetDrawBlendMode(DX_BLENDMODE_INVSRC, color.a);
    Draw(pos);

    SetDrawBlendMode(DX_BLENDMODE_ADD, color.a);
    Draw(pos);

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�V���G�b�g��`�悳����
void ImageDrawer::DrawSilhouetteOne(int image_sheet, const Math::Vec2& pos, const Color& color) const
{
    SetDrawBright(color.r, color.g, color.b);
    SetDrawBlendMode(DX_BLENDMODE_INVSRC, color.a);
    DrawOne(image_sheet, pos);

    SetDrawBlendMode(DX_BLENDMODE_ADD, color.a);
    DrawOne(image_sheet, pos);

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//���݂̉摜�n���h�����擾
const int ImageDrawer::GetNowImageHandle() const
{
    int nai = (int)now_anim_image_;
    if (image_data_.anim[now_anim_pattern_]->relative_sheet < 0)
    {
        nai *= -1;
    }

    int imageSheet = image_data_.anim[now_anim_pattern_]->start_sheet + nai;
    CheckHandleError(imageSheet);

    return image_data_.handle[imageSheet];
}

//�摜�����]����Ă��邩�ۂ����擾(���]����Ă�����true)
const bool& ImageDrawer::GetIsTurn() const
{
    return is_turn_;
}

//�`��\��̉摜��`���擾
const Math::Box2D ImageDrawer::GetDrawImageRect() const
{
    Math::Box2D rect(image_data_.rect);
    rect.x -= c_pos_.x;
    rect.y -= c_pos_.y;
    rect.w *= scale_x_;
    rect.h *= scale_y_;
    return rect;
}

//����ȃn���h���̉摜�͖����I
void ImageDrawer::CheckHandleError(int image_sheet) const
{
    if (image_sheet < 0 || image_data_.sheet_num <= image_sheet)
    {
        assert(false && "There is no image assigned to that handle!");
    }
}