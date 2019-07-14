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
//コンストラクタ
ImageDrawer::ImageDrawer():
    now_anim_pattern_(0),
    now_anim_image_(0),
    is_anim_end_(false),
    scale_x_(1.f),
    scale_y_(1.f),
    is_turn_(false){}


//初期化(描画したい画像データを指定、第二引数trueで描画基準位置が中心)
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
//初期化(描画したい画像データと描画基準位置を指定)
void ImageDrawer::Initialize(const std::string& image_name, const Math::Vec2& criterion_pos)
{
    image_data_ = ImageLoader::GetInstance().GetImageData(image_name);
    c_pos_ = criterion_pos;
}

//アニメーションさせる
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

//アニメーションが終了したか否かを返す
bool ImageDrawer::IsAnimEnd()
{
    return is_anim_end_;
}

//アニメーションパターン番号の変更
void ImageDrawer::ChangeAnimPattern(int pattern, bool reset_time)
{
    now_anim_pattern_ = pattern;
    is_anim_end_ = false;

    if (reset_time == true)
    {
        now_anim_image_ = 0;
    }
}

//拡大率を設定
void ImageDrawer::SetScale(float scale)
{
    scale_x_ = scale;
    scale_y_ = scale;
}
//拡大率を設定(縦横別)
void ImageDrawer::SetScale(float scale_x, float scale_y)
{
    scale_x_ = scale_x;
    scale_y_ = scale_y;
}
//反転するか否かを設定
void ImageDrawer::SetTurnFlag(bool is_turn)
{
    is_turn_ = is_turn;
    is_anim_end_ = false;
}
//反転フラグを反転
void ImageDrawer::ChangeTurnFlag()
{
    is_turn_ = !is_turn_;
    is_anim_end_ = false;
}

//簡易描画
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

//描画する
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

//描画範囲矩形を指定して描画する(描画の基準位置は無視する)
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


//指定番号の画像を簡易描画(アニメーションしない)
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

//指定番号の画像を描画する(アニメーションしない)
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

//指定番号の画像を描画範囲矩形を指定して描画する
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

//シルエットを描画させる
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

//シルエットを描画させる
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

//現在の画像ハンドルを取得
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

//画像が反転されているか否かを取得(反転されていたらtrue)
const bool& ImageDrawer::GetIsTurn() const
{
    return is_turn_;
}

//描画予定の画像矩形を取得
const Math::Box2D ImageDrawer::GetDrawImageRect() const
{
    Math::Box2D rect(image_data_.rect);
    rect.x -= c_pos_.x;
    rect.y -= c_pos_.y;
    rect.w *= scale_x_;
    rect.h *= scale_y_;
    return rect;
}

//そんなハンドルの画像は無い！
void ImageDrawer::CheckHandleError(int image_sheet) const
{
    if (image_sheet < 0 || image_data_.sheet_num <= image_sheet)
    {
        assert(false && "There is no image assigned to that handle!");
    }
}