#pragma once
#include <memory>
#include <string>
#include "DxLib.h"
#include "Math.h"
#include "ImageDrawer.h"

//----------------------------------------------
//シェーダーに送る情報
struct MLineInfo
{
    FLOAT2  window_size;    //画面サイズ
    FLOAT2  start_pos;      //始端座標
    FLOAT2  end_pos;        //終端座標
    float   thick;          //線の太さ
    float   r;
    float   g;
    float   b;
    float   a;
};

//----------------------------------------------
//シェーダー使うのでその管理
class MResource
{
private:
    static std::weak_ptr<MResource> instance_;

public:
    std::string shader_name;
    std::string buffer_name;

    MResource();    //コンストラクタ
    ~MResource();   //デストラクタ
    static std::shared_ptr<MResource> Create(); //リソースの生成
};

//----------------------------------------------
//インや敵上で描画される線を管理するクラス
class MLine
{
public:
    enum struct MHit
    {
        Parfect,    //優(一致)
        Excess,     //良(過多)
        Short,      //可(部分一致)
        Miss,       //不可(失敗)
    };

private:
    const int MAX_POINT_NUM_ = 4;
    const int MAX_LINE_NUM_  = 6;

    std::shared_ptr<MResource> mres_;
    float dist_;        //線の長さ
    int thick_;         //太さ
    int line_flag_;     //線の発生フラグ

public:
    MLine(float dist, int thick);

    //線をランダムに生成する
    void CreateRandomLine(int line_num);
    //線を追加する
    bool AddLine(int point_a, int point_b);
    bool AddLine(int line_id);
    //線を取得する
    int GetMLine();
    //線をリセットする
    void ResetLine();
    //他の線と判定を行う
    MHit CheckHitLine(int line);

    //線を描画する
    void Draw(const Math::Vec2& pos, const Color& color);
};