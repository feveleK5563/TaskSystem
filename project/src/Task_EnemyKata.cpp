#include "Task_EnemyKata.h"
#include "TaskDefData.h"
#include "Task_Mudra.h"
#include "Utility.h"

namespace EnemyKata
{
    //----------------------------------------------
    //�^�X�N�̃R���X�g���N�^
    Task::Task(float dist, int thick, int max_line, int min_line):
        TaskAbstract(def_task),
        mline_(dist, thick)
    {
        SetPriority(Priority::MLINE);
        mline_.CreateRandomLine(Util::GetRand(max_line, min_line));
    }
    //----------------------------------------------
    //�^�X�N�̃f�X�g���N�^
    Task::~Task()
    {
    }
    //----------------------------------------------
    //�^�X�N�̐���
    std::shared_ptr<Task> Task::Create(float dist, int thick, int max_line, int min_line)
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>(dist, thick, max_line, min_line);
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
        auto mudra = TaskSystem::GetTaskOne<Mudra::Task>(Mudra::def_task);
        if (mudra && mudra->IsActive())
        {
            mline_.Draw(pos_, Color(255, 0, 0));
        }
    }

    //----------------------------------------------
    void Task::SetDrawPos(const Math::Vec2& pos)
    {
        pos_ = pos;
    }

    //----------------------------------------------
    //Mudra�Ƃ̔��茋�ʂ��擾����
    MLine::MHit Task::GetHitState()
    {
        auto mudra = TaskSystem::GetTaskOne<Mudra::Task>(Mudra::def_task);
        if (mudra)
        {
            return mline_.CheckHitLine(mudra->GetMLine());
        }
        return MLine::MHit::Miss;
    }
}