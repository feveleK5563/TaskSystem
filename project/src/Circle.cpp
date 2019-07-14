#include "Circle.h"
#include "ShaderManager.h"
#include "SystemDefine.h"

std::weak_ptr<CResource> CResource::instance_;
//----------------------------------------------
//リソースのコンストラクタ
CResource::CResource()
{
    shader_name = "circleShader";
    auto& shader = ShaderManager::GetInstance();
    shader.LoadShader(shader_name, "data/shader/circle.pso");
    buffer_name = "circleBuffer";
    shader.CreateConstantBuffer<CircleInfo>(buffer_name);
}
//----------------------------------------------
//リソースのデストラクタ
CResource::~CResource()
{
    auto& shader = ShaderManager::GetInstance();
    shader.DeleteShaderData(shader_name);
    shader.DeleteConstantBuffer(buffer_name);
}
//----------------------------------------------
//リソースの生成
std::shared_ptr<CResource> CResource::Create()
{
    auto sp = instance_.lock();
    if (!sp)
    {
        sp = std::make_shared<CResource>();
        instance_ = sp;
    }
    return sp;
}


//----------------------------------------------
Circle::Circle(float spread_speed):
    cres_(CResource::Create()),
    counter_(spread_speed, 0.f, spread_speed * 60.f)
{
    window_size_.u = SysDef::SizeX;
    window_size_.v = SysDef::SizeY;
    radius_ = 0.f;
    color_flag_ = false;

    counter_.SetNowMax();
}

//----------------------------------------------
//更新
void Circle::Update()
{
    counter_.Run();
}

//----------------------------------------------
//描画
void Circle::Draw(const Math::Vec2& pos, const Color& color)
{
    //ピクセルシェーダー用の定数バッファのアドレスを取得
    auto& shaderManager = ShaderManager::GetInstance();
    auto& cb = shaderManager.GetConstantBuffer<CircleInfo>(cres_->buffer_name);

    //各値を書き込み
    cb.window_size = window_size_;
    cb.center_pos.u = pos.x;
    cb.center_pos.v = pos.y;
    cb.radius = counter_.GetNow();
    cb.color_flag = color_flag_;
    cb.r = color.Fr();
    cb.g = color.Fg();
    cb.b = color.Fb();
    cb.a = color.Fa();

    shaderManager.DrawShader(cres_->shader_name, cres_->buffer_name);
}

//----------------------------------------------
//着色フラグ
void Circle::SetColorFlag(bool color_flag)
{
    color_flag_ = color_flag;
    counter_.Reset();
}