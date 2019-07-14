#include "TaskDefData.h"
#include "Character.h"
#include "Task_Map.h"
#include "Task_Camera.h"
#include "ImageLoader.h"

Character::Character():
    velocity_(0.f),
    is_vel_constant_(false),
    grav_cnt_(Physic::gravity),
    is_gravity_(false),
    box_cp_(Math::BoxCP::TOP_LEFT) {}

//-----------------------------------------------------------------------------
//めり込み等の補正を行わない移動処理
void Character::NomalMove(const Math::Vec2& direction)
{
    Math::Vec2 vec(GetVec(direction));

    if (vec == Math::Vec2(0.f, 0.f))
    {
        //移動しないなら何もしない
        return;
    }

    pos_ += vec;
}

//-----------------------------------------------------------------------------
//めり込まない移動処理
void Character::NoSinkMove(const Math::Vec2& direction)
{
    Math::Vec2 vec(GetVec(direction));

    if (vec == Math::Vec2(0.f, 0.f))
    {
        //移動しないなら何もしない
        return;
    }

    //めり込まない移動処理
    auto map = TaskSystem::GetTaskOne<Map::Task>(Map::def_task);
    for (int xy = 0; xy < 2; ++xy)
    {
        Math::Vec2 add;
        while (vec(xy) != 0.f)
        {
            if (vec(xy) > 1.f) { add(xy) = 1.f; vec(xy) -= 1.f; }
            else if (vec(xy) < -1.f) { add(xy) = -1.f; vec(xy) += 1.f; }
            else { add(xy) = vec(xy); vec(xy) = 0.f; }

            if (map->GetHitBlockTrait(land_rect_.GetOffset(pos_ + add, box_cp_))
                != Map::BlockTrait::Non)
            {
                break;
            }
            pos_(xy) += add(xy);
        }
    }

    if (map->IsHitFoot(land_rect_.GetOffset(pos_, box_cp_)))
    {
        grav_cnt_.Reset();
    }
}

//-----------------------------------------------------------------------------
//めり込みなし + 自動避け機能付き移動処理
void Character::AutoRevitionMove(const Math::Vec2& direction)
{
    if (direction == Math::Vec2(0.f, 0.f))
    {
        //移動しないならめり込みなし移動だけ行う
        NoSinkMove(direction);
        return;
    }

    Math::Vec2 cder(direction);

    auto map = TaskSystem::GetTaskOne<Map::Task>(Map::def_task);
    //矩形周辺の接触位置を取得し、その位置によって移動方向を変換する
    switch (map->GetHitRectGirth(land_rect_.GetOffset(pos_, box_cp_), Map::BlockTrait::Nomal))
    {
    case Map::RectGirth::U_LEFT:    //上の左
        if (-0.2f < cder.x && cder.x < 0.2f)
            cder.x = 1.f;   //右方向へ変換
        break;

    case Map::RectGirth::U_RIGHT:   //上の右
        if (-0.2f < cder.x && cder.x < 0.2f)
            cder.x = -1.f;  //左方向へ変換
        break;

    case Map::RectGirth::L_UP:      //左右の上
    case Map::RectGirth::R_UP:
        if (-0.2f < cder.y && cder.y < 0.2f)
            cder.y = 1.f;   //下方向へ変換
        break;

    case Map::RectGirth::L_DOWN:    //左右の下
    case Map::RectGirth::R_DOWN:
        if (-0.2f < cder.y && cder.y < 0.2f)
            cder.y = -1.f;  //上方向へ変換
        break;
    }

    NoSinkMove(cder);
}

//-----------------------------------------------------------------------------
//描画基準位置を設定
void Character::SetBoxCP(Math::BoxCP cp)
{
    box_cp_ = cp;
}

//-----------------------------------------------------------------------------
//座標を設定
void Character::SetPos(const Math::Vec2& pos)
{
    pos_ = pos;
}

//-----------------------------------------------------------------------------
//矩形を設定
void Character::SetLandRect(const Math::Box2D& land_rect)
{
    land_rect_ = land_rect;
}

//-----------------------------------------------------------------------------
//移動速度を設定
void Character::SetVelocity(float velocity)
{
    velocity_ = velocity;
}

//-----------------------------------------------------------------------------
//移動速度成分を円周範囲に補正するフラグを設定
void Character::SetIsVelConstant(bool is_vel_constant)
{
    is_vel_constant_ = is_vel_constant;
}

//-----------------------------------------------------------------------------
//重力有効フラグの設定
void Character::SetIsGravity(bool is_gravity)
{
    is_gravity_ = is_gravity;
    if (!is_gravity_)
    {
        grav_cnt_.Reset();
    }
}


//-----------------------------------------------------------------------------
//座標を取得
const Math::Vec2& Character::GetPos() const
{
    return pos_;
}
//-----------------------------------------------------------------------------
//地形判定用矩形の中心座標を取得
Math::Vec2 Character::GetCenterPos() const
{
    Math::Vec2 ul = land_rect_.GetOffset(pos_, box_cp_).GetPos();
    ul.x += land_rect_.w / 2.f;
    ul.y += land_rect_.h / 2.f;
    return ul;
}
//-----------------------------------------------------------------------------
//カメラ準拠の座標を取得
Math::Vec2 Character::GetPosForCam(bool isCenter) const
{
    auto cam = TaskSystem::GetTaskOne<Camera::Task>(Camera::def_task);
    if (isCenter)
    {
        return cam->GetScreenPos(GetCenterPos());
    }
    return cam->GetScreenPos(pos_);
}

//-----------------------------------------------------------------------------
//地形判定用矩形を取得
Math::Box2D Character::GetLandRect() const
{
    return land_rect_.GetOffset(pos_, box_cp_);
}

//-----------------------------------------------------------------------------
//移動速度を取得
const float& Character::GetVelocity() const
{
    return velocity_;
}

//-----------------------------------------------------------------------------
//重力有効フラグを取得
bool Character::IsGravity() const
{
    return is_gravity_;
}

//-----------------------------------------------------------------------------
//地面と接触しているか取得
bool Character::IsGround() const
{
    auto map = TaskSystem::GetTaskOne<Map::Task>(Map::def_task);
    return map->IsHitFoot(land_rect_.GetOffset(pos_, box_cp_));
}

//-----------------------------------------------------------------------------
//矩形を描画
void Character::DrawRect(bool isFill, int color, bool forCam) const
{
    if (forCam)
    {
        land_rect_.GetOffset(GetPosForCam(), box_cp_).DrawRect(isFill, color);
    }
    else
    {
        land_rect_.GetOffset(pos_, box_cp_).DrawRect(isFill, color);
    }
}

//-----------------------------------------------------------------------------
//加算する移動量を取得(重力計算も行う)
Math::Vec2 Character::GetVec(const Math::Vec2& direction)
{
    Math::Vec2 vec(direction);

    if (direction != Math::Vec2(0, 0) && is_vel_constant_)
    {
        vec.Normalize();
    }
    vec *= velocity_;

    if (is_gravity_)
    {
        vec += GetAddGravityVec();
    }

    return vec;
}

//-----------------------------------------------------------------------------
//加算する重力量を取得
Math::Vec2 Character::GetAddGravityVec()
{
    grav_cnt_.Run();
    return Math::Vec2(0.f, grav_cnt_.GetNow());
}
