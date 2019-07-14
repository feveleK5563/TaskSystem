#pragma once

//拡大率
namespace Ratio
{
    const float layer_main      (3.f);
};

//描画順
enum Priority
{
    CAMERA = 0, //カメラ

    BACK,       //背景
    CIRCLE,     //円形ブワっと背景
    MAP,        //マップ
    ENEMY,      //敵
    PLAYER,     //プレイヤー
    MUDRA,      //イン
    JOUETSU,    //ジョウエツくん
    MLINE,      //ライン

    ALL_TASK_TYPE_NUM,
};

//その他のデータ
namespace Physic
{
	const float gravity	(0.5f);
}