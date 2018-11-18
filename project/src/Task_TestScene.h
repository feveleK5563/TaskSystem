#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

namespace TestScene
{
	const std::string	defGroupName	("テスト用シーン");	//グループ名
	const std::string	defTaskName		("テスト用タスク");	//タスク名
	const float			defPriority(0.f);	//デフォルトの処理優先度

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		std::string imageName;

		Resource();		//コンストラクタ
		~Resource();	//デストラクタ
		static std::shared_ptr<Resource> Create();	//リソースの生成
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//確保したリソース
		ImageDrawer imgDrawer;

		int pshandle;				//ピクセルシェーダーのハンドル
		int pscbhandle;				//ピクセルシェーダー用の定数バッファハンドル
		VERTEX2DSHADER vertex[4];	//頂点データ

		Counter<float> timer;	//時間計測
		MATH::Vec2 mousePos;	//マウスの座標
		bool onClick;			//クリックしたか否か

		//シェーダーに送る値
		struct constantBuffer
		{
			FLOAT2 windowSize;
			FLOAT2 mousePos;
			float radius;
			bool onClick;
		};

	public:
		//コンストラクタ
		Task();
		
		//デストラクタ
		~Task();
		
		//タスクの生成
		static std::shared_ptr<Task> Create();

		void Initialize() override;	//初期化処理
		void Finalize() override;	//終了処理
		void Update() override;		//更新
		void Draw() override;		//描画
	};
}