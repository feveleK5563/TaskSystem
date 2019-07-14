#pragma once
#include <vector>
#include <sstream>
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Map
{
    //ブロックの特性
    enum struct BlockTrait
    {
        Non     = -1,   //何もない
        Nomal   = 0,    //普通の壁、床
    };

    //矩形のヒット位置をお知らせするためのやつ
    enum struct RectGirth
    {
        NON     = 0,        //無効(当たっていないか複数か)
        U_LEFT  = 1 << 0,   //上の左側
        U_RIGHT = 1 << 1,   //上の右側
        D_LEFT  = 1 << 2,   //下の左側
        D_RIGHT = 1 << 3,   //下の右側
        L_UP    = 1 << 4,   //左の上側
        L_DOWN  = 1 << 5,   //左の下側
        R_UP    = 1 << 6,   //左の上側
        R_DOWN  = 1 << 7,   //左の下側
    };
    const int block_size(12);   //ブロックの横・縦幅

    const std::string   def_task  ("マップ"); //タスク名

    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;

    public:
        std::string map_chip_;

        Resource();     //コンストラクタ
        ~Resource();    //デストラクタ
        static std::shared_ptr<Resource> Create();  //リソースの生成
    };

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_; //確保したリソース

        int size_, width_, height_;
        ImageDrawer chip_image_;

        std::vector<std::vector<int>>           map_data_;  //マップデータ
        std::vector<std::vector<Math::Box2D>>   map_rect_;  //マップ矩形

    public:
        //コンストラクタ
        Task();

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create();

        void Initialize() override; //初期化処理
        void Finalize() override;   //終了処理
        void Draw() override;       //描画

        //マップと矩形の当たり判定を行い、接触しているブロックの特性を返す
        BlockTrait GetHitBlockTrait(const Math::Box2D& rect);
        //地面と矩形下部との接触判定を行い、通常ブロックが接触している場合trueを返す
        bool IsHitFoot(const Math::Box2D& rect);
        //矩形の周囲に指定ブロックが接触している場合、その接触位置を返す(複数接触している場合はNon)
        RectGirth GetHitRectGirth(const Math::Box2D& rect, BlockTrait block_trait);

    private:
        //マップデータを読み込む
        void LoadMapData(const std::string& map_data_path);
        //マップデータを削除する
        void DeleteMapData();
        //文字列の「,」を半角スペースに置換し、stringstreamを返す
        std::stringstream ReplaceStrComma(const std::string& str);
    };
}