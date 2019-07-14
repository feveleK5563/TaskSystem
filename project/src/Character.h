#pragma once
#include "Math.h"
#include "Counter.hpp"
#include "ImageDrawer.h"

//キャラクター(動く者)の動作と描画管理クラス
//接触しているブロックに応じて得られる効果等をここで管理する
class Character
{
private:
    Math::Vec2 pos_;            //座標
    Math::Box2D land_rect_;     //地形判定用矩形
    float velocity_;            //移動速度
    bool is_vel_constant_;      //移動速度を一定にするフラグ
    Counter<float> grav_cnt_;   //重力加算
    bool is_gravity_;           //重力有効フラグ
    Math::BoxCP box_cp_;        //描画基準位置

public:
    Character();

    void NomalMove(const Math::Vec2& direction);            //めり込み等の補正を行わない移動処理
    void NoSinkMove(const Math::Vec2& direction);           //めり込まない移動処理
    void AutoRevitionMove(const Math::Vec2& direction);     //めり込みなし + 自動避け機能付き移動処理

    void SetBoxCP(Math::BoxCP cp);                  //描画基準位置を設定
    void SetPos(const Math::Vec2& pos);             //座標を設定
    void SetLandRect(const Math::Box2D& land_rect); //矩形を設定
    void SetVelocity(const float velocity);         //移動速度を設定
    void SetIsVelConstant(bool is_vel_constant);    //移動速度を一定にするフラグの設定
    void SetIsGravity(bool is_gravity);             //重力有効フラグの設定

    const Math::Vec2& GetPos() const;                       //座標を取得
    Math::Vec2 GetCenterPos() const;                        //地形判定用矩形の中心座標を取得
    Math::Vec2 GetPosForCam(bool isCenter = false) const;   //カメラ準拠の座標を取得
    Math::Box2D GetLandRect() const;        //地形判定用矩形を取得
    const float& GetVelocity() const;       //移動速度を取得
    bool IsGravity() const;                 //重力有効フラグを取得
    bool IsGround() const;                  //地面と接触しているか取得

    //矩形を描画
    void DrawRect(bool is_fill, int color = 0xffffff, bool for_cam = false) const;

private:
    Math::Vec2 GetVec(const Math::Vec2& direction); //加算する移動量を取得(重力計算も行う)
    Math::Vec2 GetAddGravityVec();                  //加算する重力量を取得
};