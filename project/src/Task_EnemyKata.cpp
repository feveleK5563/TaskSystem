#include "Task_EnemyKata.h"
#include "TaskDefData.h"
#include "Task_Mudra.h"
#include "Utility.h"

namespace EnemyKata
{
    //----------------------------------------------
    //タスクのコンストラクタ
    Task::Task(float dist, int thick, int max_line, int min_line):
        TaskAbstract(def_task),
        mline_(dist, thick)
    {
        SetPriority(Priority::MLINE);
        mline_.CreateRandomLine(Util::GetRand(max_line, min_line));
    }
    //----------------------------------------------
    //タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    //タスクの生成
    std::shared_ptr<Task> Task::Create(float dist, int thick, int max_line, int min_line)
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>(dist, thick, max_line, min_line);
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
    }

    //----------------------------------------------
    //終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    //描画
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
    //Mudraとの判定結果を取得する
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