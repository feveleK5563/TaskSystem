#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "DxLib.h"
#include "ImageDrawer.h"

//シェーダー管理君(とりあえずピクセルシェーダーにだけ対応してるつもり)
class ShaderManager
{
public:
    //インスタンスを生成する
    static void Create();
    //インスタンスを解放する
    static void Delete();

    //指定クラスサイズの定数バッファを作成
    template <typename T>
    static bool CreateConstantBuffer(const std::string& buffer_name)
    {
        return CreateConstantBufferSetSize(buffer_name, sizeof(T));
    }
    //定数バッファを取得
    template <typename T>
    static T& GetConstantBuffer(const std::string& buffer_name)
    {
        return *(T*)GetConstantBufferPointer(buffer_name);
    }

    //シェーダーを読み込む(第四引数がtrueで頂点データが画面サイズぴったりに設定される)
    static bool LoadShader(const std::string& shader_name, const std::string& file_path,
                           int shader_type = DX_SHADERTYPE_PIXEL, bool is_vertex_set_window_size = true);
    //頂点データと描画方法を設定
    static void SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type);
    //画像(テクスチャ)をハンドルで指定してセット(レジスタはデフォルトで0)
    static void SetShaderImage(int image_handle, int slot = 0);
    //画像(テクスチャ)をDrawerで指定してセット(レジスタはデフォルトで0)
    static void SetShaderImage(const ImageDrawer& image_drawer, int slot = 0);
    //定数バッファを更新とシェーダーのセット(レジスタはデフォルトで0)
    static void UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //シェーダーを使って描画
    static void DrawShader(const std::string& shader_name);
    //定数バッファを一つだけシェーダーにセットして描画(レジスタはデフォルトで0)
    static void DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //定数バッファを解放する
    static bool DeleteConstantBuffer(const std::string& buffer_name);
    //作成した定数バッファを全て解放する
    static bool AllDeleteConstantBuffer();
    //シェーダーを解放する
    static bool DeleteShaderData(const std::string& shader_name);
    //読み込んだシェーダーを全て解放する
    static bool AllDeleteShader();

private:
    static bool CreateConstantBufferSetSize(const std::string& buffer_name, int size);
    static void* GetConstantBufferPointer(const std::string& buffer_name);

private:
    class Impl;
    static Impl* impl_;
    static Impl* GetImpl();
};