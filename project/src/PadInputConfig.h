#pragma once
#include <vector>
#include <array>
#include "InputDXL.h"

// ゲームパッドコンフィグマン(ゲーム内入力設定と状態の取得)
class PadInputConfig
{
private:
    class PadConfig
    {
    private:
        const unsigned int input_id_;           // 番号
        std::vector<PAD_INPUT> pad_set_;        // ゲームパッドのコンフィグ
        std::vector<KEY_INPUT> key_set_;        // キーボードのコンフィグ
        bool use_pad_;  // パッドを使用するか否か
        bool use_key_;  // キーボードを使用するか否か

    public:
        // コンストラクタ
        PadConfig(unsigned int id, bool use_pad, bool use_key);

        // パッド配置を初期化
        void Initialize();
        // パッド配置を変更
        void SetPadConfig(PAD_INPUT target, PAD_INPUT set);
        // パッドのキー割り当てを変更
        void SetPadConfig(PAD_INPUT target, KEY_INPUT set);
        // 左スティックのキー割り当てを変更
        void SetLStickConfig(KEY_INPUT l, KEY_INPUT r, KEY_INPUT u, KEY_INPUT d);
        // 右スティックのキー割り当てを変更
        void SetRStickConfig(KEY_INPUT l, KEY_INPUT r, KEY_INPUT u, KEY_INPUT d);

        // キーとパッドから得られる入力状態を統合して返す
        InputState GetState(PAD_INPUT target) const;
        // 左スティックのベクトルを取得する
        Math::Vec2 GetVecStickL() const;
        // 右スティックのベクトルを取得する
        Math::Vec2 GetVecStickR() const;
    };
    static std::vector<PadConfig*> config;

    PadInputConfig() = default;

public:
    // ゲームパッドコンフィグマンのインスタンス取得
    static PadConfig& Get(unsigned int id);
    // ゲームパッドコンフィグマンのインスタンス生成
    static void Create(unsigned int pad_num, bool use_pad, bool use_key);
    // ゲームパッドコンフィグマンのインスタンス削除
    static void Delete();
    // 指定番号のゲームパッドコンフィグマンが生成されているか否かを取得
    static bool IsCreated(unsigned int id);
};