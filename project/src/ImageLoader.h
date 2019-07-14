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
    int*                    handle;     //グラフィックハンドル
    int                     sheet_num;  //画像枚数
    std::vector<AnimData*>  anim;       //アニメーション
    Math::Box2D             rect;       //画像矩形
};

//画像読み込みくん
class ImageLoader
{
private:
    std::unordered_map<std::string, ImageData> image_data;  //画像データ

    ImageLoader() = default;
    static ImageLoader* loader;

public:
    ~ImageLoader();

    //画像読み込み
    bool LoadOneImage(const std::string& image_name, const std::string& file_path);

    //画像分割読み込み
    bool LoadDivImage(const std::string& image_name, const std::string& file_path,
                      int all_num, int x_num, int y_num, int x_size, int y_size);

    //分割読み込み済みのデータにアニメーションデータを追加
    void AddAnimationData(const std::string& image_name, int start_sheet, int end_sheet,
                          float wait_time, bool is_loop);

    //画像データの取得
    const ImageData& GetImageData(const std::string& image_name);

    //画像データの解放
    bool DeleteImageData(const std::string& image_name);

    //全ての画像データの解放
    bool AllDeleteImageData();

    //インスタンスを得る
    static ImageLoader& GetInstance();
    //インスタンスを生成する
    static void CreateInstance();
    //インスタンスを解放する
    static void DeleteInstance();

private:
    //安全に画像データを削除する
    bool SafeImageDelete(const std::string& image_name);
};