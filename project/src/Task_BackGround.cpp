#include "Task_BackGround.h"
#include "ImageLoader.h"
#include "TaskDefData.h"

namespace BackGround
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        back_image_ = "back";
        ImageLoader::LoadOneImage(back_image_, "data/image/back.png");
    }
    //----------------------------------------------
    //���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData(back_image_);
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
        res_(Resource::Create())
    {
        SetPriority(Priority::BACK);
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
        back_.Initialize(res_->back_image_, Math::BoxCP::TOP_LEFT);
        back_.SetScale(Ratio::layer_main);
    }

    //----------------------------------------------
    //�I������
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    //�`��
    //----------------------------------------------
    void Task::Draw()
    {
        back_.Draw(Math::Vec2(0, 0));
    }
}