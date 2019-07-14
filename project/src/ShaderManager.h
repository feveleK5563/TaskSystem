#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "DxLib.h"
#include "ImageDrawer.h"

//シェーダー管理君(とりあえずピクセルシェーダーにだけ対応してるつもり)
class ShaderManager
{
private:
    std::unordered_map<std::string, int> buffer_handle_;	//定数バッファハンドル

    //シェーダーの情報
    struct ShaderData
    {
        int handle;                                 //シェーダーハンドル
        int type;                                   //タイプ(ピクセルとか頂点とか)
        std::unique_ptr<VERTEX2DSHADER[]> vertex;   //頂点データ
        int vertexNum;                              //頂点データの要素数
        int primitiveType;                          //描画方法
        ShaderData() = default;
    };
    std::unordered_map<std::string, ShaderData> shader_data_;

    ShaderManager() = default;
    static ShaderManager* shader_manager_;

public:
    ~ShaderManager();

    //指定クラスサイズの定数バッファを作成
    template <typename T>
    bool CreateConstantBuffer(const std::string& buffer_name)
    {
        int num = 1, size = sizeof(T);
        for (; num < size; num *= 2);	//クラスサイズ以上の2の累乗分だけメモリを確保
        buffer_handle_[buffer_name] = CreateShaderConstantBuffer(num);

        if (buffer_handle_[buffer_name] == -1)
            return false;

        return true;
    }
    //定数バッファを取得
    template <typename T>
    T& GetConstantBuffer(const std::string& buffer_name)
    {
        T* tmp = (T*)GetBufferShaderConstantBuffer(buffer_handle_[buffer_name]);
        return *tmp;
    }


    //シェーダーを読み込む(第四引数がtrueで頂点データが画面サイズぴったりに設定される)
    bool LoadShader(const std::string& shader_name, const std::string& file_path,
                    int shader_type = DX_SHADERTYPE_PIXEL, bool is_vertex_set_window_size = true);
    //頂点データと描画方法を設定
    void SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type);
    //画像(テクスチャ)をハンドルで指定してセット(レジスタはデフォルトで0)
    void SetShaderImage(int image_handle, int slot = 0);
    //画像(テクスチャ)をDrawerで指定してセット(レジスタはデフォルトで0)
    void SetShaderImage(const ImageDrawer& image_drawer, int slot = 0);
    //定数バッファを更新とシェーダーのセット(レジスタはデフォルトで0)
    void UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //シェーダーを使って描画
    void DrawShader(const std::string& shader_name);
    //定数バッファを一つだけシェーダーにセットして描画(レジスタはデフォルトで0)
    void DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //定数バッファを解放する
    bool DeleteConstantBuffer(const std::string& buffer_name);
    //作成した定数バッファを全て解放する
    bool AllDeleteConstantBuffer();
    //シェーダーを解放する
    bool DeleteShaderData(const std::string& shader_name);
    //読み込んだシェーダーを全て解放する
    bool AllDeleteShader();


    //インスタンスを得る
    static ShaderManager& GetInstance();
    //インスタンスを生成する
    static void CreateInstance();
    //インスタンスを解放する
    static void DeleteInstance();
};