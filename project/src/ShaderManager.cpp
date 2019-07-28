#include "ShaderManager.h"
#include "Utility.h"
#include "SystemDefine.h"

class ShaderManager::Impl
{
private:
    std::unordered_map<std::string, int> buffer_handle_;	//定数バッファハンドル

    //シェーダーの情報
    struct ShaderData
    {
        int handle = 0;                             //シェーダーハンドル
        int type = 0;                               //タイプ(ピクセルとか頂点とか)
        std::unique_ptr<VERTEX2DSHADER[]> vertex;   //頂点データ
        int vertex_num = 0;                         //頂点データの要素数
        int primitive_type = 0;                     //描画方法
        ShaderData() = default;
    };
    std::unordered_map<std::string, ShaderData> shader_data_;

public:
    Impl() = default;
    ~Impl()
    {
        AllDeleteConstantBuffer();
        AllDeleteShader();
    }

    //指定クラスサイズの定数バッファを作成
    bool CreateConstantBuffer(const std::string& buffer_name, int size)
    {
        int buf_size = 1;
        for (; buf_size < size; buf_size *= 2);	//クラスサイズ以上の2の累乗分だけメモリを確保
        buffer_handle_[buffer_name] = CreateShaderConstantBuffer(buf_size);

        if (buffer_handle_[buffer_name] == -1)
            return false;

        return true;
    }
    //定数バッファを取得
    void* GetConstantBuffer(const std::string& buffer_name)
    {
        return GetBufferShaderConstantBuffer(buffer_handle_[buffer_name]);
    }

    //シェーダーを読み込む(第三引数がtrueで頂点データが画面サイズぴったりに設定される)
    bool LoadShader(const std::string& shader_name, const std::string& file_path,
                    int shader_type, bool is_vertex_set_window_size)
    {
        if (shader_data_.find(shader_name) != shader_data_.end())
        {
            return false;
        }

        shader_data_[shader_name].handle = LoadPixelShader(file_path.c_str());
        if (shader_data_[shader_name].handle == -1) { return false; }

        shader_data_[shader_name].type = shader_type;

        if (!is_vertex_set_window_size) { return true; }

        //頂点データを画面サイズぴったりに設定する
        float x = (float)SysDef::SizeX, y = (float)SysDef::SizeY;
        shader_data_[shader_name].vertex_num = 4;
        shader_data_[shader_name].vertex = std::make_unique<VERTEX2DSHADER[]>(4);
        shader_data_[shader_name].vertex[0].pos = VGet(-1.f, -1.f, 0.f);
        shader_data_[shader_name].vertex[1].pos = VGet(x, -1.f, 0.f);
        shader_data_[shader_name].vertex[2].pos = VGet(-1.f, y, 0.f);
        shader_data_[shader_name].vertex[3].pos = VGet(x, y, 0.f);
        for (int i = 0; i < 4; ++i)
        {
            shader_data_[shader_name].vertex[i].rhw = 1.f;
            shader_data_[shader_name].vertex[i].dif = GetColorU8(255, 255, 255, 255);
            shader_data_[shader_name].vertex[i].spc = GetColorU8(0, 0, 0, 0);
            shader_data_[shader_name].vertex[i].u = float(i % 2);
            shader_data_[shader_name].vertex[i].su = float(i % 2);
            shader_data_[shader_name].vertex[i].v = float(i / 2);
            shader_data_[shader_name].vertex[i].sv = float(i / 2);
        }
        shader_data_[shader_name].primitive_type = DX_PRIMTYPE_TRIANGLESTRIP;

        return true;
    }

    //頂点データと描画方法を設定
    void SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type)
    {
        shader_data_[shader_name].vertex_num = vertex_num;
        shader_data_[shader_name].vertex = std::make_unique<VERTEX2DSHADER[]>(vertex_num);
        for (int i = 0; i < vertex_num; ++i)
        {
            shader_data_[shader_name].vertex[i] = vertex[i];
        }
        shader_data_[shader_name].primitive_type = primitive_type;
    }

    //画像(テクスチャ)をハンドルで指定してセット(レジスタはデフォルトで0)
    void SetShaderImage(int image_handle, int slot)
    {
        SetUseTextureToShader(slot, image_handle);
    }
    //画像(テクスチャ)をDrawerで指定してセット(レジスタはデフォルトで0)
    void SetShaderImage(const ImageDrawer& imgDrawer, int slot)
    {
        SetUseTextureToShader(slot, imgDrawer.GetNowImageHandle());
    }

    //定数バッファを更新(レジスタはデフォルトで0)
    void UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot)
    {
        //シェーダー用の定数バッファを更新して書き込んだ内容を反映する
        UpdateShaderConstantBuffer(buffer_handle_[buffer_name]);
        //シェーダー用の定数バッファを定数バッファレジスタにセット
        SetShaderConstantBuffer(buffer_handle_[buffer_name], shader_data_[shader_name].type, slot);
    }


    //シェーダーを使って描画
    void DrawShader(const std::string& shader_name)
    {
        //シェーダのセット
        SetUsePixelShader(shader_data_[shader_name].handle);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        //描画
        DrawPrimitive2DToShader(
            shader_data_[shader_name].vertex.get(),
            shader_data_[shader_name].vertex_num,
            shader_data_[shader_name].primitive_type);
    }

    //定数バッファを一つだけシェーダーにセットして描画(レジスタはデフォルトで0)
    void DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot)
    {
        UpdateAndSetCB(shader_name, buffer_name, slot);
        DrawShader(shader_name);
    }


    //定数バッファを解放する
    bool DeleteConstantBuffer(const std::string& buffer_name)
    {
        if (buffer_handle_.count(buffer_name)) { return false; }

        DeleteShaderConstantBuffer(buffer_handle_[buffer_name]);
        buffer_handle_.erase(buffer_handle_.lower_bound(buffer_name));
        return true;
    }
    //作成した定数バッファを全て解放する
    bool AllDeleteConstantBuffer()
    {
        for (auto& it : buffer_handle_)
        {
            DeleteShaderConstantBuffer(it.second);
        }
        buffer_handle_.clear();
        return true;
    }
    //シェーダーを解放する
    bool DeleteShaderData(const std::string& shader_name)
    {
        if (shader_data_.count(shader_name)) { return false; }

        DeleteShader(shader_data_[shader_name].handle);
        shader_data_.erase(shader_data_.lower_bound(shader_name));
        return true;
    }
    //読み込んだシェーダーを全て解放する
    bool AllDeleteShader()
    {
        for (auto& it : shader_data_)
        {
            DeleteShader(it.second.handle);
        }
        shader_data_.clear();
        return true;
    }
};

//-----------------------------------------------------------------------------
ShaderManager::Impl* ShaderManager::impl_ = nullptr;
ShaderManager::Impl* ShaderManager::GetImpl()
{
    assert(impl_ && "ShaderManager hasn't been created!!");
    return impl_;
}
//-----------------------------------------------------------------------------

// インスタンスを生成する
void ShaderManager::Create()
{
    if (!impl_)
    {
        impl_ = new Impl();
    }
}

// インスタンスを解放する
void ShaderManager::Delete()
{
    Util::SafeDelete(impl_);
}

//シェーダーを読み込む(第四引数がtrueで頂点データが画面サイズぴったりに設定される)
bool ShaderManager::LoadShader(const std::string& shader_name, const std::string& file_path,
                               int shader_type, bool is_vertex_set_window_size)
{
    return GetImpl()->LoadShader(shader_name, file_path, shader_type, is_vertex_set_window_size);
}

//頂点データと描画方法を設定
void ShaderManager::SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type)
{
    GetImpl()->SetVertex(shader_name, vertex, vertex_num, primitive_type);
}

//画像(テクスチャ)をハンドルで指定してセット(レジスタはデフォルトで0)
void ShaderManager::SetShaderImage(int image_handle, int slot)
{
    GetImpl()->SetShaderImage(image_handle, slot);
}

//画像(テクスチャ)をDrawerで指定してセット(レジスタはデフォルトで0)
void ShaderManager::SetShaderImage(const ImageDrawer& image_drawer, int slot)
{
    GetImpl()->SetShaderImage(image_drawer, slot);
}

//定数バッファを更新とシェーダーのセット(レジスタはデフォルトで0)
void ShaderManager::UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot)
{
    GetImpl()->UpdateAndSetCB(shader_name, buffer_name, slot);
}

//シェーダーを使って描画
void ShaderManager::DrawShader(const std::string& shader_name)
{
    GetImpl()->DrawShader(shader_name);
}

//定数バッファを一つだけシェーダーにセットして描画(レジスタはデフォルトで0)
void ShaderManager::DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot)
{
    GetImpl()->DrawShader(shader_name, buffer_name, slot);
}

//定数バッファを解放する
bool ShaderManager::DeleteConstantBuffer(const std::string& buffer_name)
{
    return GetImpl()->DeleteConstantBuffer(buffer_name);
}

//作成した定数バッファを全て解放する
bool ShaderManager::AllDeleteConstantBuffer()
{
    return GetImpl()->AllDeleteConstantBuffer();
}

//シェーダーを解放する
bool ShaderManager::DeleteShaderData(const std::string& shader_name)
{
    return GetImpl()->DeleteShaderData(shader_name);
}

//読み込んだシェーダーを全て解放する
bool ShaderManager::AllDeleteShader()
{
    return GetImpl()->AllDeleteShader();
}

bool ShaderManager::CreateConstantBufferSetSize(const std::string& buffer_name, int size)
{
    return GetImpl()->CreateConstantBuffer(buffer_name, size);
}

void* ShaderManager::GetConstantBufferPointer(const std::string& buffer_name)
{
    return GetImpl()->GetConstantBuffer(buffer_name);
}