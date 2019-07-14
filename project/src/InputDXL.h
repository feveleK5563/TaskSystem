#pragma once
#include <vector>
#include "DxLib.h"
#include "Math.h"

enum InputState
{
    ON,     //押されている
    OFF,    //押されていない
    DOWN,   //押した瞬間
    UP,     //離した瞬間
};

enum struct MOUSE_INPUT
{
    LEFT    = 0,    //左クリック
    RIGHT   = 1,    //右クリック
    MIDDLE  = 2,    //ホイールボタン
};

enum struct KEY_INPUT
{
    BACK        = 0x0E,     //BackSpaceキー
    TAB         = 0x0F,     //Tabキー
    RETURN      = 0x1C,     //Enterキー

    LSHIFT      = 0x2A,     //左Shiftキー
    RSHIFT      = 0x36,     //右Shiftキー
    LCONTROL    = 0x1D,     //左Ctrlキー
    RCONTROL    = 0x9D,     //右Ctrlキー
    ESCAPE      = 0x01,     //Escキー
    SPACE       = 0x39,     //スペースキー
    PGUP        = 0xC9,     //PageUpキー
    PGDN        = 0xD1,     //PageDownキー
    END         = 0xCF,     //Endキー
    HOME        = 0xC7,     //Homeキー
    LEFT        = 0xCB,     //左キー
    UP          = 0xC8,     //上キー
    RIGHT       = 0xCD,     //右キー
    DOWN        = 0xD0,     //下キー	
    INSERT      = 0xD2,     //Insertキー
    DEL         = 0xD3,     //Deleteキー

    MINUS       = 0x0C,     //－キー
    YEN         = 0x7D,     //￥キー
    PREVTRACK   = 0x90,     //＾キー
    PERIOD      = 0x34,     //．キー
    SLASH       = 0x35,     //／キー
    LALT        = 0x38,     //左Altキー
    RALT        = 0xB8,     //右Altキー
    SCROLL      = 0x46,     //ScrollLockキー
    SEMICOLON   = 0x27,     //；キー
    COLON       = 0x92,     //：キー
    LBRACKET    = 0x1A,     //［キー
    RBRACKET    = 0x1B,     //］キー
    AT          = 0x91,     //＠キー
    BACKSLASH   = 0x2B,     //＼キー
    COMMA       = 0x33,     //，キー
    KANJI       = 0x94,     //漢字キー
    CONVERT     = 0x79,     //変換キー
    NOCONVERT   = 0x7B,     //無変換キー
    KANA        = 0x70,     //カナキー
    APPS        = 0xDD,     //アプリケーションメニューキー
    CAPSLOCK    = 0x3A,     //CaspLockキー
    SYSRQ       = 0xB7,     //PrintScreenキー
    PAUSE       = 0xC5,     //PauseBreakキー
    LWIN        = 0xDB,     //左Winキー
    RWIN        = 0xDC,     //右Winキー

    NUMLOCK     = 0x45,     //テンキーNumLockキー
    NUMPAD0     = 0x52,     //テンキー0
    NUMPAD1     = 0x4F,     //テンキー1
    NUMPAD2     = 0x50,     //テンキー2
    NUMPAD3     = 0x51,     //テンキー3
    NUMPAD4     = 0x4B,     //テンキー4
    NUMPAD5     = 0x4C,     //テンキー5
    NUMPAD6     = 0x4D,     //テンキー6
    NUMPAD7     = 0x47,     //テンキー7
    NUMPAD8     = 0x48,     //テンキー8
    NUMPAD9     = 0x49,     //テンキー9
    MULTIPLY    = 0x37,     //テンキー＊キー
    ADD         = 0x4E,     //テンキー＋キー
    SUBTRACT    = 0x4A,     //テンキー－キー
    DECIMAL     = 0x53,     //テンキー．キー
    DIVIDE      = 0xB5,     //テンキー／キー
    NUMPADENTER = 0x9C,     //テンキーのエンターキー

    F1          = 0x3B,     //F1キー
    F2          = 0x3C,     //F2キー
    F3          = 0x3D,     //F3キー
    F4          = 0x3E,     //F4キー
    F5          = 0x3F,     //F5キー
    F6          = 0x40,     //F6キー
    F7          = 0x41,     //F7キー
    F8          = 0x42,     //F8キー
    F9          = 0x43,     //F9キー
    F10         = 0x44,     //F10キー
    F11         = 0x57,     //F11キー
    F12         = 0x58,     //F12キー

    A           = 0x1E,     //Aキー
    B           = 0x30,     //Bキー
    C           = 0x2E,     //Cキー
    D           = 0x20,     //Dキー
    E           = 0x12,     //Eキー
    F           = 0x21,     //Fキー
    G           = 0x22,     //Gキー
    H           = 0x23,     //Hキー
    I           = 0x17,     //Iキー
    J           = 0x24,     //Jキー
    K           = 0x25,     //Kキー
    L           = 0x26,     //Lキー
    M           = 0x32,     //Mキー
    N           = 0x31,     //Nキー
    O           = 0x18,     //Oキー
    P           = 0x19,     //Pキー
    Q           = 0x10,     //Qキー
    R           = 0x13,     //Rキー
    S           = 0x1F,     //Sキー
    T           = 0x14,     //Tキー
    U           = 0x16,     //Uキー
    V           = 0x2F,     //Vキー
    W           = 0x11,     //Wキー
    X           = 0x2D,     //Xキー
    Y           = 0x15,     //Yキー
    Z           = 0x2C,     //Zキー

    NUM0        = 0x0B,     //0キー
    NUM1        = 0x02,     //1キー
    NUM2        = 0x03,     //2キー
    NUM3        = 0x04,     //3キー
    NUM4        = 0x05,     //4キー
    NUM5        = 0x06,     //5キー
    NUM6        = 0x07,     //6キー
    NUM7        = 0x08,     //7キー
    NUM8        = 0x09,     //8キー
    NUM9        = 0x0A,     //9キー
};

enum struct PAD_INPUT
{
    DOWN    = 0,    //十字ボタン下
    LEFT    = 1,    //十字ボタン左
    RIGHT   = 2,    //十字ボタン右
    UP      = 3,    //十字ボタン上
    A       = 4,    //Aボタン
    B       = 5,    //Bボタン
    X       = 6,    //Xボタン
    Y       = 7,    //Yボタン
    L1      = 8,    //L1ボタン
    R1      = 9,    //R1ボタン
    SELECT  = 10,   //SELECTボタン(BACKボタン)
    START   = 11,   //STARTボタン
    L3      = 12,   //L3ボタン(左スティック押し込み)
    R3      = 13,   //R3ボタン(右スティック押し込み)
};

struct ButtonNum
{
    static const int mouse  = 3;
    static const int key    = 256;
    static const int pad    = 28;
};

class InputDXL
{
private:
    //-----------------------------------------------------------------------------
    //入力情報の管理
    class ButtonInfo
    {
    private:
        int duration_time_;
        InputState state_;

    public:
        ButtonInfo();
        void SetState(const InputState state);
        void AutoSetState(const bool is_button_on);

        const InputState& GetInputState() const;
        int GetDurationTime(const InputState instate) const;
        bool operator ==(const InputState instate) const;
        bool operator !=(const InputState instate) const;
    };

    //-----------------------------------------------------------------------------
    //マウスの入力情報を保持する
    class MouseInput
    {
    private:
        ButtonInfo mouse_info_[ButtonNum::mouse];
        Math::Vec2 pos_;
        bool is_input_;

    public:
        MouseInput();

        bool GetInputState();

        const Math::Vec2& GetPos() const;   //マウスポインタの座標を取得
        bool IsInput() const;               //何らかの入力があったか否か

        const ButtonInfo& operator [](const MOUSE_INPUT mouse_input) const;
    };

    //-----------------------------------------------------------------------------
    //キーボードの入力情報を保持する
    class KeyInput
    {
    private:
        ButtonInfo key_info_[ButtonNum::key];

    public:
        KeyInput() = default;

        bool GetInputState();

        bool IsInput() const;	//何らかの入力があったか否か

        const ButtonInfo& operator [](const KEY_INPUT key_input_) const;
    };

    //-----------------------------------------------------------------------------
    //ゲームパッドの入力情報を保持する
    class PadInput
    {
    private:
        unsigned int input_id_;
        ButtonInfo pad_info_[ButtonNum::pad];
        float analog_LX_, analog_LY_,
              analog_RX_, analog_RY_;
        bool is_input_;

    public:
        PadInput(unsigned int id);

        bool GetInputState();

        float GetAngleStickL() const;       //左スティックの角度を取得
        float GetAngleStickR() const;       //右スティックの角度を取得
        float GetVolumeStickL() const;      //左スティックの傾き量の大きさを取得
        float GetVolumeStickR() const;      //右スティックの傾き量の大きさを取得
        Math::Vec2 GetVecStickL() const;    //左スティックの傾きと角度をベクトルで取得
        Math::Vec2 GetVecStickR() const;    //右スティックの傾きと角度をベクトルで取得
        bool IsInput() const;               //何らかの入力があったか否か

        const ButtonInfo& operator [](const PAD_INPUT pad_input) const;
    };

    static MouseInput* mouse_;
    static KeyInput* key_;
    static std::vector<PadInput*> pad_;

public:
    //マウスのインスタンスを取得
    static const MouseInput& GetMouse();
    //マウスのインスタンスを生成
    static void CreateMouseInstance();
    //マウスのインスタンスを解放
    static void DeleteMouseInstance();
    //マウスのインスタンスが生成されているか否かを取得
    static bool IsCreatedMouseInstance();
    //マウスの入力情報を取得
    private: static bool GetMouseInputState();

public:
    //キーボードのインスタンスを取得
    static const KeyInput& GetKey();
    //キーボードのインスタンスを生成
    static void CreateKeyInstance();
    //キーボードのインスタンスを解放
    static void DeleteKeyInstance();
    //キーボードのインスタンスが生成されているか否かを取得
    static bool IsCreatedKeyInstance();
    //キーボードの入力情報を取得
    private: static bool GetKeyInputState();

public:
    //指定番号のジョイパッドのインスタンスを取得
    static const PadInput& GetPad(unsigned int id);
    //指定個数ジョイパッドのインスタンスを生成
    static void CreatePadInstance(unsigned int pad_num);
    //ジョイパッドのインスタンスを解放
    static void DeletePadInstance();
    //指定番号のジョイパッドのインスタンスが生成されているか否かを取得(デフォルトで0番)
    static bool IsCreatedPadInstance(unsigned int id = 0u);
    //ジョイパッドの入力情報を全て取得
    private: static bool GetPadAllInputState();

public:
    //全ての入力情報を取得
    static bool GetAllInputState();

    //生成した全てのインスタンスを解放
    static void DeleteAllInstance();
};