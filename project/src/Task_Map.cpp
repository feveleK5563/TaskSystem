#include <algorithm>
#include <fstream>
#include "Task_Map.h"
#include "TaskDefData.h"
#include "ImageLoader.h"
#include "Utility.h"
#include "Task_Camera.h"

namespace Map
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //リソースのコンストラクタ
    Resource::Resource()
    {
        map_chip_ = "mapChip";

        auto& imgl = ImageLoader::GetInstance();
        imgl.LoadDivImage(map_chip_, "data/image/mapChip.png", 1, 1, 1, block_size, block_size);
    }
    //----------------------------------------------
    //リソースのデストラクタ
    Resource::~Resource()
    {
        auto& imgl = ImageLoader::GetInstance();
        imgl.DeleteImageData(map_chip_);
    }
    //----------------------------------------------
    //リソースの生成
    std::shared_ptr<Resource> Resource::Create()
    {
        auto sp = instance_.lock();
        if (!sp)
        {
            sp = std::make_shared<Resource>();
            instance_ = sp;
        }
        return sp;
    }

    //☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
    //★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

    //----------------------------------------------
    //タスクのコンストラクタ
    Task::Task():
        TaskAbstract(def_task),
        res_(Resource::Create()),
        size_(0),
        width_(0),
        height_(0)
    {
        SetPriority(Priority::MAP);
    }
    //----------------------------------------------
    //タスクのデストラクタ
    Task::~Task()
    {

    }
    //----------------------------------------------
    //タスクの生成
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task = 
            std::make_shared<Task>();
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
    //◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

    //----------------------------------------------
    //初期化処理
    //----------------------------------------------
    void Task::Initialize()
    {
        chip_image_.Initialize(res_->map_chip_, Math::BoxCP::TOP_LEFT);
        chip_image_.SetScale(Ratio::layer_main);
        size_ = int((float)block_size * Ratio::layer_main);

        LoadMapData("data/map/test.csv");
    }

    //----------------------------------------------
    //終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
        DeleteMapData();
    }

    //----------------------------------------------
    //描画
    //----------------------------------------------
    void Task::Draw()
    {
        auto cam = TaskSystem::GetTaskOne<Camera::Task>(Camera::def_task);
        for (int y = 0; y < height_; ++y)
        {
            for (int x = 0; x < width_; ++x)
            {
                if (map_data_[y][x] <= -1) continue;

                chip_image_.DrawOne(map_data_[y][x], cam->GetScreenPos(map_rect_[y][x].GetPos()));
            }
        }
    }


    //----------------------------------------------
    //マップと矩形の当たり判定を行い、接触しているブロック番号を返す
    BlockTrait Task::GetHitBlockTrait(const Math::Box2D& rect)
    {
        int sx = int(rect.x / size_);
        int sy = int(rect.y / size_);
        int ex = int((rect.x + rect.w) / size_);
        int ey = int((rect.y + rect.h) / size_);

        //画面外チェック
        if (sx < 0 || sy < 0 ||
            ex >= width_ || ey >= height_)
        {
            assert(false && "Player is out of map!");
        }

        for (int y = sy; y <= ey; ++y)
        {
            for (int x = sx; x <= ex; ++x)
            {
                if (BlockTrait(map_data_[y][x]) != BlockTrait::Non &&
                    rect.IsHit(map_rect_[y][x]))
                {
                    return BlockTrait(map_data_[y][x]);
                }
            }
        }
        return BlockTrait::Non;
    }

    //----------------------------------------------
    //地面と矩形下部との接触判定を行い、通常ブロックが接触している場合trueを返す
    bool Task::IsHitFoot(const Math::Box2D& rect)
    {
        Math::Box2D down(1.f, rect.h + 1.f, rect.w - 1.f, 1.f); //矩形下部
        if (GetHitBlockTrait(down.GetOffset(rect.GetPos(), Math::BoxCP::TOP_LEFT))
            == BlockTrait::Nomal)
        {
            return true;
        }
        return false;
    }

    //----------------------------------------------
    //矩形の周囲に指定ブロックが接触している場合、その接触位置を返す(複数接触している場合はNon)
    RectGirth Task::GetHitRectGirth(const Math::Box2D& rect, BlockTrait block_trait)
    {
        Math::Box2D girthRect[2] = 
        {
            Math::Box2D(0.f, 0.f, (rect.w / 2.f), 1.f),	//上下
            Math::Box2D(0.f, 0.f, 1.f, (rect.h / 2.f)),	//左右
        };
        Math::Vec2 pos(rect.GetPos());
        Math::Vec2 offsetPos[8] =
        {
            Math::Vec2(0.f, -1.f) + pos,                        //上の左
            Math::Vec2((rect.w / 2.f), -1.f) + pos,             //上の右
            Math::Vec2(0.f, (rect.h + 1.f)) + pos,              //下の左
            Math::Vec2((rect.w / 2.f), (rect.h + 1.f)) + pos,   //下の右

            Math::Vec2(-1.f, 0.f) + pos,                        //左の上
            Math::Vec2(-1.f, (rect.h / 2.f)) + pos,             //左の下
            Math::Vec2((rect.w + 1.f), 0.f) + pos,              //右の上
            Math::Vec2((rect.w + 1.f), (rect.h / 2.f)) + pos,   //右の下
        };

        //接触している部分にフラグを立てる
        int hit_girth = 0;
        for (int i = 0; i < 8; ++i)
        {
            //通常壁との接触だった場合は記録
            if (GetHitBlockTrait(girthRect[i / 4].GetOffset(offsetPos[i], Math::BoxCP::TOP_LEFT))
                == block_trait)
            {
                hit_girth += (1 << i);
            }
        }

        //立っているフラグが一つだけの場合はその位置を返す
        if (hit_girth != 0 && !(hit_girth & (hit_girth - 1)))
        {
            return RectGirth(hit_girth);
        }
        return RectGirth::NON;
    }

    //----------------------------------------------
    //マップデータを読み込む
    void Task::LoadMapData(const std::string& map_data_path)
    {
        DeleteMapData();

        std::string tmpstr;
        std::ifstream fin(map_data_path);
        assert(fin && "MapDataFile was not found!");

        std::getline(fin, tmpstr);
        ReplaceStrComma(tmpstr) >> width_ >> height_;

        map_rect_.resize(height_, std::vector<Math::Box2D>(width_));
        map_data_.resize(height_, std::vector<int>(width_));

        for (int y = 0; y < height_; ++y)
        {
            std::getline(fin, tmpstr);
            std::stringstream tmpss = ReplaceStrComma(tmpstr);
            for (int x = 0; x < width_; ++x)
            {
                map_rect_[y][x] = Math::Box2D(
                    x * size_,
                    y * size_,
                    size_,
                    size_);

                tmpss >> map_data_[y][x];
            }
        }
    }

    //----------------------------------------------
    //マップデータを削除する
    void Task::DeleteMapData()
    {
        for (auto& it : map_data_)
        {
            it.clear();
            it.shrink_to_fit();
        }
        map_data_.clear();
        map_data_.shrink_to_fit();

        for (auto& it : map_rect_)
        {
            it.clear();
            it.shrink_to_fit();
        }
        map_rect_.clear();
        map_rect_.shrink_to_fit();
    }

    //----------------------------------------------
    //文字列の「,」を半角スペースに置換し、stringstreamを返す
    std::stringstream Task::ReplaceStrComma(const std::string& str)
    {
        std::stringstream ss;
        std::string tmp_str = str;
        std::replace(tmp_str.begin(), tmp_str.end(), ',', ' ');
        ss << tmp_str;
    
        return ss;
    }
}