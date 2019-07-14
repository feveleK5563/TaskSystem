#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "TaskAbstract.h"

class TaskSystem
{
public:
    //インスタンスを生成する
    static void Create();
    //インスタンスを解放する
    static void Delete();

    static void Update();                                           // 更新
    static void Draw();                                             // 描画
    static void AddTask(std::shared_ptr<TaskAbstract> create_task); // タスクを追加する

    // 指定したタスクが存在しているか調べる
    static bool IsHaveTask(const std::string& task_name);
    // 指定したタスクの状態を変更する
    static void SetStateTask(const std::string& task_name, TaskState task_state);
    // 指定したタスクを削除する
    static void KillTask(const std::string& task_name);

    // 登録されているタスクの状態を全て変更する
    static void AllSetStateTask(TaskState task_state);
    // 登録されているタスクを全て強制削除する(デストラクタで呼ばれる)
    static void AllDeleteTask();

    // 全タスク数を取得する
    static int GetAllTaskNum();

    // 指定したタスクの内、先頭のみを渡す
    template<class T>
    static std::shared_ptr<T> GetTaskOne(const std::string& task_name)
    {
        if (impl_)
        {
            return impl_->GetTaskOne(task_name);
        }
        return std::shared_ptr<T>();
    }
    //指定したタスクをまとめて渡す
    template<class T>
    static std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskAll(const std::string& task_name)
    {
        if (impl_)
        {
            impl_->GetTaskAll(task_name);
        }
        return std::shared_ptr<std::vector<std::shared_ptr<T>>>();
    }

private:
    class Impl;
    static std::unique_ptr<Impl> impl_;
};