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
        if (IsHaveTask(task_name))
        {
            std::shared_ptr<TaskAbstract> task_data = GetTaskAbstractOne(task_name);
            return std::static_pointer_cast<T>(task_data);
        }
        return std::shared_ptr<T>();
    }
    // 指定したタスクをまとめて渡す
    template<class T>
    static std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskAll(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            const std::vector<std::shared_ptr<TaskAbstract>>* task_data = GetTaskAbstractAll(task_name);
            if (!task_data)
            {
                return std::shared_ptr<std::vector<std::shared_ptr<T>>>();
            }

            std::shared_ptr<std::vector<std::shared_ptr<T>>> gt =
                    std::make_shared<std::vector<std::shared_ptr<T>>>();

            gt->reserve(task_data->size());

            for (auto it : *task_data)
            {
                gt->emplace_back(std::static_pointer_cast<T>(it));
            }
            return gt;
        }
        return std::shared_ptr<std::vector<std::shared_ptr<T>>>();
    }

private:
    static std::shared_ptr<TaskAbstract> GetTaskAbstractOne(const std::string& task_name);
    static const std::vector<std::shared_ptr<TaskAbstract>>* GetTaskAbstractAll(const std::string& task_name);

private:
    class Impl;
    static Impl* impl_;
};