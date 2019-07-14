#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "TaskAbstract.h"

class TaskSystem
{
private:
    std::vector<std::shared_ptr<TaskAbstract>> task_;
    std::vector<std::shared_ptr<TaskAbstract>> add_task_;
    std::unordered_map<std::string,
            std::vector<std::shared_ptr<TaskAbstract>>> task_data_;

    bool sort_flag_;

    TaskSystem();
    static TaskSystem* ts_;

public:
    ~TaskSystem();

    void Update();                                           // 更新
    void Draw();                                             // 描画
    void AddTask(std::shared_ptr<TaskAbstract> create_task); // タスクを追加する

    // 指定したタスクが存在しているか調べる
    bool IsHaveTask(const std::string& task_name);
    // 指定したタスクの状態を変更する
    void SetStateTask(const std::string& task_name, TaskState task_state);
    // 指定したタスクを削除する
    void KillTask(const std::string& task_name);

    // 登録されているタスクの状態を全て変更する
    void AllSetStateTask(TaskState task_state);
    // 登録されているタスクを全て強制削除する(デストラクタで呼ばれる)
    void AllDeleteTask();

    // 全タスク数を取得する
    int GetAllTaskNum();

    // 指定したタスクの内、先頭のみを渡す
    template<class T>
    std::shared_ptr<T> GetTaskOne(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            return std::static_pointer_cast<T>(task_data_[task_name].front());
        }
        return std::shared_ptr<T>();
    }
    //指定したタスクをまとめて渡す
    template<class T>
    std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskAll(const std::string& task_name)
    {
        std::shared_ptr<std::vector<std::shared_ptr<T>>> gt;

        if (IsHaveTask(task_name))
        {
            gt = std::make_shared<std::vector<std::shared_ptr<T>>>();

            gt->reserve(task_data_[task_name].size());

            for (auto it : task_data_[task_name])
            {
                gt->emplace_back(std::static_pointer_cast<T>(it));
            }
        }
        return gt;
    }

    //インスタンスを得る
    static TaskSystem& Get();
    //インスタンスを生成する
    static void Create();
    //インスタンスを解放する
    static void Delete();

private:
    void AllUpdate();       //全てのタスクのUpdateを呼ぶ
    void AddTask();         //追加予定のタスクを追加する
    void StateDeleteTask(); //状態がDeleteのタスクを削除する
    void SortTask();        //priorityを基に昇順にソートする
};