#include "ImageLoader.h"
#include "DxLib.h"
#include "Utility.h"

AnimData::AnimData():
    start_sheet(0),
    relative_sheet(0),
    wait_time(0),
    is_loop(false) {}

AnimData::AnimData(int start_sheet, int relative_sheet, float wait_time, bool is_loop) :
    start_sheet(start_sheet),
    relative_sheet(relative_sheet),
    wait_time(wait_time),
    is_loop(is_loop) {}

//-----------------------------------------------------------------------------

//デストラクタ
ImageLoader::~ImageLoader()
{
    AllDeleteImageData();
}

//画像読み込み
bool ImageLoader::LoadOneImage(const std::string& image_name, const std::string& file_path)
{
    if (image_data.find(image_name) != image_data.end())
    {
        //すでに読み込まれていたら何もしない
        return false;
    }

    //読み込んだ画像のデータを格納
    image_data[image_name].handle = new int[1]{ LoadGraph(file_path.c_str()) };
    image_data[image_name].sheet_num = 1;
    int xSize, ySize;
    GetGraphSize(*(image_data[image_name].handle), &xSize, &ySize);
    image_data[image_name].rect = Math::Box2D(0, 0, xSize, ySize);

    return true;
}

//画像分割読み込み
bool ImageLoader::LoadDivImage(const std::string& image_name, const std::string& file_path,
                               int all_num, int x_num, int y_num, int x_size, int y_size)
{
    if (image_data.find(image_name) != image_data.end())
    {
        return false;
    }

    //読み込んだ画像のデータを格納
    image_data[image_name].handle = new int[all_num] {};
    if (LoadDivGraph(file_path.c_str(), all_num, x_num, y_num, x_size, y_size, image_data[image_name].handle) == -1)
    {
        //読み込み失敗
        assert(false && "image divload error!!!");
    }
    image_data[image_name].sheet_num = all_num;
    image_data[image_name].rect = Math::Box2D(0, 0, x_size, y_size);

    return true;
}

//分割読み込み済みのデータにアニメーションデータを追加
void ImageLoader::AddAnimationData(const std::string& image_name, int start_sheet, int end_sheet,
                                   float wait_time, bool is_loop)
{
    image_data[image_name].anim.emplace_back(
        new AnimData(start_sheet, end_sheet - start_sheet, max(wait_time, 1.f), is_loop)
    );
}

//画像データの取得
const ImageData& ImageLoader::GetImageData(const std::string& image_name)
{
    //アニメーション設定が行われていなかった場合は、便宜的にアニメーションを設定しておく
    if (image_data[image_name].anim.empty())
    {
        AddAnimationData(image_name, 0, 0, 1, false);
    }

    return image_data[image_name];
}

//画像データの解放
bool ImageLoader::DeleteImageData(const std::string& image_name)
{
    if (!SafeImageDelete(image_name)) { return false; }

    image_data.erase(image_data.lower_bound(image_name));
    return true;
}

//全ての画像データの解放
bool ImageLoader::AllDeleteImageData()
{
    for (auto it = image_data.begin();
         it != image_data.end();)
    {
        SafeImageDelete(it->first);
        it = image_data.erase(image_data.lower_bound(it->first));
    }
    image_data.clear();
    return true;
}

ImageLoader* ImageLoader::loader = nullptr;
//インスタンスを得る
ImageLoader& ImageLoader::GetInstance()
{
    assert(loader != nullptr && "ImageLoader hasn't been created!");
    return *loader;
}
//インスタンスを生成する
void ImageLoader::CreateInstance()
{
    if (loader == nullptr)
    {
        loader = new ImageLoader();
    }
}
//インスタンスを解放する
void ImageLoader::DeleteInstance()
{
    Util::SafeDelete(loader);
}

//安全に画像データを削除する
bool ImageLoader::SafeImageDelete(const std::string& image_name)
{
    if (!image_data.count(image_name)) { return false; }

    for (int i = 0; i < image_data[image_name].sheet_num; ++i)
    {
        DeleteGraph(image_data[image_name].handle[i]);
    }

    if (image_data[image_name].sheet_num == 1)
    {
        Util::SafeDelete(image_data[image_name].handle);
    }
    else
    {
        Util::SafeDeleteArr(image_data[image_name].handle);
    }

    for (auto animit : image_data[image_name].anim)
    {
        Util::SafeDelete(animit);
    }

    return true;
}