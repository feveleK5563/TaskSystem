#include <iostream>
#include <math.h>
#include "DxLib.h"
#include "InputDXL.h"
#include "Utility.h"

//-----------------------------------------------------------------------------
//コンストラクタ
InputDXL::ButtonInfo::ButtonInfo() :
    duration_time_(0),
    state_(OFF) {}

//-----------------------------------------------------------------------------
//状態の設定と状態持続時間の計測
void InputDXL::ButtonInfo::SetState(const InputState setState)
{
    if (state_ == setState)
    {
        ++duration_time_;
    }
    else
    {
        duration_time_ = 0;
    }
    state_ = setState;
}

//-----------------------------------------------------------------------------
//入力状況から状態を設定
void InputDXL::ButtonInfo::AutoSetState(const bool isButtonOn)
{
    if (isButtonOn)
    {
        if (state_ == DOWN || state_ == ON)
        {
            SetState(ON);
        }
        else
        {
            SetState(DOWN);
        }
    }
    else
    {
        if (state_ == UP || state_ == OFF)
        {
            SetState(OFF);
        }
        else
        {
            SetState(UP);
        }
    }
}

//-----------------------------------------------------------------------------
//状態の取得
const InputState& InputDXL::ButtonInfo::GetInputState() const
{
    return state_;
}

//-----------------------------------------------------------------------------
//状態持続時間を取得
int InputDXL::ButtonInfo::GetDurationTime(const InputState instate) const
{
    if (state_ == instate)
    {
        return duration_time_;
    }
    return -1;
}

//-----------------------------------------------------------------------------
//状態の比較(一致)
bool InputDXL::ButtonInfo::operator ==(const InputState instate) const
{
    return state_ == instate;
}

//-----------------------------------------------------------------------------
//状態の比較(不一致)
bool InputDXL::ButtonInfo::operator!=(const InputState instate) const
{
    return state_ != instate;
}


//-----------------------------------------------------------------------------
//コンストラクタ
InputDXL::MouseInput::MouseInput():
    pos_(0.f, 0.f),
    is_input_(false){}

//-----------------------------------------------------------------------------
//マウス入力情報を受け取る
bool InputDXL::MouseInput::GetInputState()
{
    int state = GetMouseInput();
    for (int i = 0; i < ButtonNum::mouse; ++i)
    {
        mouse_info_[i].AutoSetState(state & (1 << i));
    }
    is_input_ = state > 0;

    int x, y;
    GetMousePoint(&x, &y);
    pos_.x = (float)x;
    pos_.y = (float)y;

    return true;
}
//-----------------------------------------------------------------------------
//マウスの座標を取得する
const Math::Vec2& InputDXL::MouseInput::GetPos() const
{
    return pos_;
}
//-----------------------------------------------------------------------------
//何らかの入力があったか否か
bool InputDXL::MouseInput::IsInput() const
{
    return is_input_;
}
//-----------------------------------------------------------------------------
//指定ボタンの持つ入力情報を取得する
const InputDXL::ButtonInfo& InputDXL::MouseInput::operator [](const MOUSE_INPUT mouseInput) const
{
    return mouse_info_[(int)mouseInput];
}


//-----------------------------------------------------------------------------
//キー入力情報を受け取る
bool InputDXL::KeyInput::GetInputState()
{
    char getHitKeyStateAll_Key[ButtonNum::key];
    GetHitKeyStateAll(getHitKeyStateAll_Key);
    for (int i = 0; i < ButtonNum::key; ++i)
    {
        key_info_[i].AutoSetState(getHitKeyStateAll_Key[i]);
    }
    return true;
}
//-----------------------------------------------------------------------------
//何らかの入力があったか否か
bool InputDXL::KeyInput::IsInput() const
{
    return CheckHitKeyAll() == 0;
}
//-----------------------------------------------------------------------------
//指定キーの持つ入力情報を取得する
const InputDXL::ButtonInfo& InputDXL::KeyInput::operator [](const KEY_INPUT keyInput) const
{
    return key_info_[(int)keyInput];
}


//-----------------------------------------------------------------------------
//コンストラクタ(ジョイパッドの番号を設定する)
InputDXL::PadInput::PadInput(unsigned int id):
    input_id_(id),
    analog_LX_(0.f), analog_LY_(0.f),
    analog_RX_(0.f), analog_RY_(0.f),
    is_input_(false){}

//-----------------------------------------------------------------------------
//ジョイパッドの入力情報を受け取る
bool InputDXL::PadInput::GetInputState()
{
    int state = GetJoypadInputState(input_id_);
    for (int i = 0; i < ButtonNum::pad; ++i)
    {
        pad_info_[i].AutoSetState(state & (1 << i));
    }
    is_input_ = state > 0;

    int lx, ly, rx, ry;
    GetJoypadAnalogInput(&lx, &ly, input_id_);
    GetJoypadAnalogInputRight(&rx, &ry, input_id_);
    analog_LX_ = float(lx) / 1000.f;
    analog_LY_ = float(ly) / 1000.f;
    analog_RX_ = float(rx) / 1000.f;
    analog_RY_ = float(ry) / 1000.f;

    return true;
}
//-----------------------------------------------------------------------------
//左スティックの角度を取得する
float InputDXL::PadInput::GetAngleStickL() const
{
    return atan2f(analog_LY_, analog_LX_);
}
//-----------------------------------------------------------------------------
//右スティックの角度を取得する
float InputDXL::PadInput::GetAngleStickR() const
{
    return atan2f(analog_RY_, analog_RX_);
}
//-----------------------------------------------------------------------------
//左スティックの傾き量を取得する(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickL() const
{
    return min(std::sqrtf(analog_LX_ * analog_LX_ + analog_LY_ * analog_LY_), 1.f);
}
//-----------------------------------------------------------------------------
//右スティックの傾き量を取得する(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickR() const
{
    return min(std::sqrtf(analog_RX_ * analog_RX_ + analog_RY_ * analog_RY_), 1.f);
}
//-----------------------------------------------------------------------------
//左スティックの傾きと角度をベクトルで取得
Math::Vec2 InputDXL::PadInput::GetVecStickL() const
{
    Math::Vec2 vec;
    vec.x = cos(GetAngleStickL());
    vec.y = sin(GetAngleStickL());
    vec *= GetVolumeStickL();
    return vec;
}
//-----------------------------------------------------------------------------
//右スティックの傾きと角度をベクトルで取得
Math::Vec2 InputDXL::PadInput::GetVecStickR() const
{
    Math::Vec2 vec;
    vec.x = cos(GetAngleStickR());
    vec.y = sin(GetAngleStickR());
    vec *= GetVolumeStickR();
    return vec;
}
//-----------------------------------------------------------------------------
//何らかの入力があったか否か
bool InputDXL::PadInput::IsInput() const
{
    return is_input_;
}
//-----------------------------------------------------------------------------
//指定ボタンの入力情報を取得する
const InputDXL::ButtonInfo& InputDXL::PadInput::operator [](const PAD_INPUT padInput) const
{
    return pad_info_[(int)padInput];
}



InputDXL::MouseInput* InputDXL::mouse_ = nullptr;
//-----------------------------------------------------------------------------
//マウスのインスタンスを取得
const InputDXL::MouseInput& InputDXL::GetMouse()
{
    assert(IsCreatedMouseInstance() && "MouseInput hasn't been created!");
    return *mouse_;
}
//-----------------------------------------------------------------------------
//マウスのインスタンスを生成
void InputDXL::CreateMouseInstance()
{
    if (!IsCreatedMouseInstance())
    {
        mouse_ = new MouseInput();
    }
}
//-----------------------------------------------------------------------------
//マウスのインスタンスを解放する
void InputDXL::DeleteMouseInstance()
{
    Util::SafeDelete(mouse_);
}
//-----------------------------------------------------------------------------
//マウスのインスタンスが生成されているか否かを取得
bool InputDXL::IsCreatedMouseInstance()
{
    if (mouse_ != nullptr) { return true; }
    return false;
}
//-----------------------------------------------------------------------------
//マウスの入力情報を取得する
bool InputDXL::GetMouseInputState()
{
    if (!IsCreatedMouseInstance()) { return true; }
    return mouse_->GetInputState();
}

InputDXL::KeyInput* InputDXL::key_ = nullptr;
//-----------------------------------------------------------------------------
//キーボードのインスタンスを取得
const InputDXL::KeyInput& InputDXL::GetKey()
{
    assert(IsCreatedKeyInstance() && "KeyInput hasn't been created!");
    return *key_;
}
//-----------------------------------------------------------------------------
//キーボードのインスタンスを生成
void InputDXL::CreateKeyInstance()
{
    if (!IsCreatedKeyInstance())
    {
        key_ = new KeyInput();
    }
}
//-----------------------------------------------------------------------------
//キーボードのインスタンスを解放する
void InputDXL::DeleteKeyInstance()
{
    Util::SafeDelete(key_);
}
//-----------------------------------------------------------------------------
//キーボードのインスタンスが生成されているか否かを取得
bool InputDXL::IsCreatedKeyInstance()
{
    if (key_ != nullptr) { return true; }
    return false;
}
//-----------------------------------------------------------------------------
//キーボードの入力情報を取得する
bool InputDXL::GetKeyInputState()
{
    if (!IsCreatedKeyInstance()) { return true; }
    return key_->GetInputState();
}

std::vector<InputDXL::PadInput*> InputDXL::pad_;
//-----------------------------------------------------------------------------
//ジョイパッドのインスタンスを取得
const InputDXL::PadInput& InputDXL::GetPad(unsigned int id)
{
    assert(IsCreatedPadInstance(id) && "PadInput hasn't been created!");
    return *pad_[id];
}
//-----------------------------------------------------------------------------
//ジョイパッドのインスタンスを生成
void InputDXL::CreatePadInstance(unsigned int padNum)
{
    //いったんリセットしてから再生成する
    DeletePadInstance();
    pad_.resize(padNum);
    for (unsigned int i = 0; i < padNum; ++i)
    {
        pad_[i] = new PadInput(i + 1);
    }
}
//-----------------------------------------------------------------------------
//ジョイパッドのインスタンスを解放する
void InputDXL::DeletePadInstance()
{
    if (pad_.size() <= 0) { return; }

    for (auto& it : pad_)
    {
        Util::SafeDelete(it);
    }
    pad_.clear();
    pad_.shrink_to_fit();
}
//-----------------------------------------------------------------------------
//指定番号のジョイパッドのインスタンスが生成されているか否かを取得
bool InputDXL::IsCreatedPadInstance(unsigned int id)
{
    if (id >= pad_.size()) { return false; }
    return true;
}
//-----------------------------------------------------------------------------
//ジョイパッドの入力情報を全て取得する
bool InputDXL::GetPadAllInputState()
{
    bool isCompleteInput = true;
    for (auto& it : pad_)
    {
        isCompleteInput = isCompleteInput && it->GetInputState();
    }
    return isCompleteInput;
}

//-----------------------------------------------------------------------------
//入力情報を取得
bool InputDXL::GetAllInputState()
{
    return GetMouseInputState() &&
           GetKeyInputState() &&
           GetPadAllInputState();
}

//-----------------------------------------------------------------------------
//生成した全てのインスタンスを解放
void InputDXL::DeleteAllInstance()
{
    DeleteMouseInstance();
    DeleteKeyInstance();
    DeletePadInstance();
}