#pragma once
#include <vector>
#include "Math.h"
#include "ImageLoader.h"

//色指定(0 ~ 255)
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

//画像データの描画とアニメーションの管理
class ImageDrawer
{
private:
    ImageData   image_data_;        //画像データ
    Math::Vec2  c_pos_;             //描画の基準位置
    int         now_anim_pattern_;  //現在のアニメーションパターン番号
    float       now_anim_image_;    //現在のアニメーション画像
    bool        is_anim_end_;       //アニメーション終了フラグ

    float   scale_x_, scale_y_;     //拡大率
    bool    is_turn_;               //反転フラグ

public:
    //コンストラクタ
    ImageDrawer();

    //初期化(描画したい画像データ名と描画基準位置を固定値名で指定)
    void Initialize(const std::string& image_name, Math::BoxCP cp);
    //初期化(描画したい画像データ名と描画基準位置を直接指定)
    void Initialize(const std::string& image_name, const Math::Vec2& criterion_pos);

    //アニメーションの更新処理
    void AnimUpdate();
    //アニメーションが終了したか否かを返す
    bool IsAnimEnd();
    //アニメーションパターン番号の変更
    void ChangeAnimPattern(int pattern, bool is_reset_time);

    //拡大率を設定
    void SetScale(float scale);
    //拡大率を設定(縦横別)
    void SetScale(float scale_x, float scale_y);
    //反転するか否かを設定
    void SetTurnFlag(bool is_turn);
    //反転フラグを反転
    void ChangeTurnFlag();

    //簡易描画
    void Draw(const Math::Vec2& pos) const;
    //描画する
    void Draw(const Math::Vec2& pos, float angle, const Color& color = Color()) const;
    //描画範囲矩形を指定して描画する
    void Draw(const Math::Vec2& pos, const Math::Box2D& rect, const Color& color = Color()) const;

    //指定番号の画像を簡易描画
    void DrawOne(int image_sheet, const Math::Vec2& pos) const;
    //指定番号の画像を描画する
    void DrawOne(int image_sheet, const Math::Vec2& pos, float angle, const Color& color = Color()) const;
    //指定番号の画像を描画範囲矩形を指定して描画する
    void DrawOne(int image_sheet, const Math::Vec2& pos, const Math::Box2D& rect, const Color& color = Color()) const;

    //シルエットを描画(二回分描画される)
    void DrawSilhouette(const Math::Vec2& pos, const Color& color = Color()) const;
    //指定番号の画像のシルエットを描画(二回分描画される)
    void DrawSilhouetteOne(int image_sheet, const Math::Vec2& pos, const Color& color = Color()) const;

    //現在の画像ハンドルを取得
    const int GetNowImageHandle() const;
    //画像が反転されているか否かを取得(反転されていたらtrue)
    const bool& GetIsTurn() const;

    //描画予定の画像矩形を取得
    const Math::Box2D GetDrawImageRect() const;

private:
    //そんなハンドルの画像は無い！
    void CheckHandleError(int image_sheet) const;
};