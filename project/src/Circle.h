#pragma once
#include <memory>
#include <string>
#include "DxLib.h"
#include "Math.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

//シェーダーに送る情報
struct CircleInfo
{
    FLOAT2 window_size; //画面サイズ
    FLOAT2 center_pos;  //中心座標
    float radius;       //半径
    bool color_flag;    //着色フラグ
    float   r;
    float   g;
    float   b;
    float   a;
};

//----------------------------------------------
//シェーダー使うのでその管理
class CResource
{
private:
    static std::weak_ptr<CResource> instance_;

public:
    std::string shader_name;
    std::string buffer_name;

    CResource();    //コンストラクタ
    ~CResource();   //デストラクタ
    static std::shared_ptr<CResource> Create(); //リソースの生成
};

//----------------------------------------------
//インや敵上で描画される線を管理するクラス
class Circle
{
private:
    FLOAT2 window_size_; //画面サイズ
    float radius_;       //半径
    bool color_flag_;    //着色フラグ

    std::shared_ptr<CResource> cres_;
    Counter<float> counter_;

public:
    Circle(float spread_speed);

    //更新
    void Update();

    //描画
    void Draw(const Math::Vec2& pos, const Color& color);

    //着色フラグ設定
    void SetColorFlag(bool color_flag);
};