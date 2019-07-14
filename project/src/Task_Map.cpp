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
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        map_chip_ = "mapChip";

        auto& imgl = ImageLoader::GetInstance();
        imgl.LoadDivImage(map_chip_, "data/image/mapChip.png", 1, 1, 1, block_size, block_size);
    }
    //----------------------------------------------
    //���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        auto& imgl = ImageLoader::GetInstance();
        imgl.DeleteImageData(map_chip_);
    }
    //----------------------------------------------
    //���\�[�X�̐���
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

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //�^�X�N�̃R���X�g���N�^
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
    //�^�X�N�̃f�X�g���N�^
    Task::~Task()
    {

    }
    //----------------------------------------------
    //�^�X�N�̐���
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task = 
            std::make_shared<Task>();
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //����������
    //----------------------------------------------
    void Task::Initialize()
    {
        chip_image_.Initialize(res_->map_chip_, Math::BoxCP::TOP_LEFT);
        chip_image_.SetScale(Ratio::layer_main);
        size_ = int((float)block_size * Ratio::layer_main);

        LoadMapData("data/map/test.csv");
    }

    //----------------------------------------------
    //�I������
    //----------------------------------------------
    void Task::Finalize()
    {
        DeleteMapData();
    }

    //----------------------------------------------
    //�`��
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
    //�}�b�v�Ƌ�`�̓����蔻����s���A�ڐG���Ă���u���b�N�ԍ���Ԃ�
    BlockTrait Task::GetHitBlockTrait(const Math::Box2D& rect)
    {
        int sx = int(rect.x / size_);
        int sy = int(rect.y / size_);
        int ex = int((rect.x + rect.w) / size_);
        int ey = int((rect.y + rect.h) / size_);

        //��ʊO�`�F�b�N
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
    //�n�ʂƋ�`�����Ƃ̐ڐG������s���A�ʏ�u���b�N���ڐG���Ă���ꍇtrue��Ԃ�
    bool Task::IsHitFoot(const Math::Box2D& rect)
    {
        Math::Box2D down(1.f, rect.h + 1.f, rect.w - 1.f, 1.f); //��`����
        if (GetHitBlockTrait(down.GetOffset(rect.GetPos(), Math::BoxCP::TOP_LEFT))
            == BlockTrait::Nomal)
        {
            return true;
        }
        return false;
    }

    //----------------------------------------------
    //��`�̎��͂Ɏw��u���b�N���ڐG���Ă���ꍇ�A���̐ڐG�ʒu��Ԃ�(�����ڐG���Ă���ꍇ��Non)
    RectGirth Task::GetHitRectGirth(const Math::Box2D& rect, BlockTrait block_trait)
    {
        Math::Box2D girthRect[2] = 
        {
            Math::Box2D(0.f, 0.f, (rect.w / 2.f), 1.f),	//�㉺
            Math::Box2D(0.f, 0.f, 1.f, (rect.h / 2.f)),	//���E
        };
        Math::Vec2 pos(rect.GetPos());
        Math::Vec2 offsetPos[8] =
        {
            Math::Vec2(0.f, -1.f) + pos,                        //��̍�
            Math::Vec2((rect.w / 2.f), -1.f) + pos,             //��̉E
            Math::Vec2(0.f, (rect.h + 1.f)) + pos,              //���̍�
            Math::Vec2((rect.w / 2.f), (rect.h + 1.f)) + pos,   //���̉E

            Math::Vec2(-1.f, 0.f) + pos,                        //���̏�
            Math::Vec2(-1.f, (rect.h / 2.f)) + pos,             //���̉�
            Math::Vec2((rect.w + 1.f), 0.f) + pos,              //�E�̏�
            Math::Vec2((rect.w + 1.f), (rect.h / 2.f)) + pos,   //�E�̉�
        };

        //�ڐG���Ă��镔���Ƀt���O�𗧂Ă�
        int hit_girth = 0;
        for (int i = 0; i < 8; ++i)
        {
            //�ʏ�ǂƂ̐ڐG�������ꍇ�͋L�^
            if (GetHitBlockTrait(girthRect[i / 4].GetOffset(offsetPos[i], Math::BoxCP::TOP_LEFT))
                == block_trait)
            {
                hit_girth += (1 << i);
            }
        }

        //�����Ă���t���O��������̏ꍇ�͂��̈ʒu��Ԃ�
        if (hit_girth != 0 && !(hit_girth & (hit_girth - 1)))
        {
            return RectGirth(hit_girth);
        }
        return RectGirth::NON;
    }

    //----------------------------------------------
    //�}�b�v�f�[�^��ǂݍ���
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
    //�}�b�v�f�[�^���폜����
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
    //������́u,�v�𔼊p�X�y�[�X�ɒu�����Astringstream��Ԃ�
    std::stringstream Task::ReplaceStrComma(const std::string& str)
    {
        std::stringstream ss;
        std::string tmp_str = str;
        std::replace(tmp_str.begin(), tmp_str.end(), ',', ' ');
        ss << tmp_str;
    
        return ss;
    }
}