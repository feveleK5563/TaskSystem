#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Scene
{
	const std::string	defGroupName("あいうえお");	//グループ名
	const float			defPriority(0.f);			//デフォルトの処理優先度

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		ImageData imgData;

		Resource();		//コンストラクタ
		~Resource();	//デストラクタ
		static std::shared_ptr<Resource> Create();	//リソースの生成
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//確保したリソース

		//ImageDrawer imgDrawer;

	public:
		Task();		//コンストラクタ
		~Task();	//デストラクタ
		static const std::shared_ptr<const Task> Create();	//タスクの生成

		void Initialize() override;	//初期化処理
		void Finalize() override;	//終了処理
		void Update() override;		//更新
		void Draw() override;		//描画
	};
}