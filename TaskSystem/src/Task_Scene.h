#pragma once
#include "TaskSystem.h"

namespace Scene
{
	const std::string gn("あいうえお");	//グループ名

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		int hogehoge;

	public:
		Task();

		void Update() override;
		void Draw() override;

		static const std::shared_ptr<const Task> Create();
	};
}