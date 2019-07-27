#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

//アニメーションデータ
struct AnimData
{
    int     start_sheet;        //開始位置
    int     relative_sheet;     //終了位置までの相対
    float   wait_time;          //ウェイト
    bool    is_loop;            //ループ

    AnimData();
    AnimData(int start_sheet, int relative_sheet, float wait_time, bool is_loop);
};

//画像データ
struct ImageData
{
    int*                    handle = nullptr;   //グラフィックハンドル
    int                     sheet_num = 0;      //画像枚数
    std::vector<AnimData*>  anim;               //アニメーション
    Math::Box2D             rect;               //画像矩形
};

//画像読み込みくん
class ImageLoader
{
public:
    //インスタンスを生成する
    static void Create();
    //インスタンスを解放する
    static void Delete();

    //画像読み込み
    static bool LoadOneImage(const std::string& image_name, const std::string& file_path);

    //画像分割読み込み
    static bool LoadDivImage(const std::string& image_name, const std::string& file_path,
                             int all_num, int x_num, int y_num, int x_size, int y_size);

    //分割読み込み済みのデータにアニメーションデータを追加
    static void AddAnimationData(const std::string& image_name, int start_sheet, int end_sheet,
                                 float wait_time, bool is_loop);

    //画像データの取得
    static const ImageData& GetImageData(const std::string& image_name);

    //画像データの解放
    static bool DeleteImageData(const std::string& image_name);

    //全ての画像データの解放
    static bool AllDeleteImageData();

private:
    class Impl;
    static Impl* impl_;
    static Impl* GetImpl();
};