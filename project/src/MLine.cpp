#include "MLine.h"
#include "SystemDefine.h"
#include "ShaderManager.h"
#include "Utility.h"

std::weak_ptr<MResource> MResource::instance_;
//----------------------------------------------
//リソースのコンストラクタ
MResource::MResource()
{
    shader_name = "lineShader";
    auto& shader = ShaderManager::GetInstance();
    shader.LoadShader(shader_name, "data/shader/mline.pso");
    buffer_name = "lineBuffer";
    shader.CreateConstantBuffer<MLineInfo>(buffer_name);
}
//----------------------------------------------
//リソースのデストラクタ
MResource::~MResource()
{
    auto& shader = ShaderManager::GetInstance();
    shader.DeleteShaderData(shader_name);
    shader.DeleteConstantBuffer(buffer_name);
}
//----------------------------------------------
//リソースの生成
std::shared_ptr<MResource> MResource::Create()
{
    auto sp = instance_.lock();
    if (!sp)
    {
        sp = std::make_shared<MResource>();
        instance_ = sp;
    }
    return sp;
}


//----------------------------------------------
MLine::MLine(float dist, int thick):
    mres_(MResource::Create()),
    dist_(dist),
    thick_(thick),
    line_flag_(0)
{
    thick_ = int(dist_ * 3.f) * thick_;
}

//-----------------------------------------------
//線をランダムに生成する
void MLine::CreateRandomLine(int line_num)
{
    if (line_num <= 0 || MAX_LINE_NUM_ < line_num)
    {
        return;
    }
    ResetLine();

    //ランダムに線を引く
    int line = Util::GetRand(0, MAX_LINE_NUM_ - 1);
    AddLine(line);

    //前に引いた線から再び線を引く
    int* rrr = new int[MAX_LINE_NUM_];
    for (int i = 1; i < line_num; ++i)
    {
        //ランダムに線を並べる
        rrr[0] = Util::GetRand(0, MAX_LINE_NUM_ - 1);
        for (int j = 1; j < MAX_LINE_NUM_; ++j)
        {
            rrr[j] = (rrr[j - 1] + 1) % MAX_LINE_NUM_;
        }

        //ピックアップした線の内、前の線とつながっている線を使用する
        for (int j = 0; j < MAX_LINE_NUM_; ++j)
        {
            if ((rrr[j] != ((MAX_LINE_NUM_ - 1) - line)) &&	//接続不能な線でない
                AddLine(rrr[j]))	//まだその線を引いていない
            {
                line = rrr[j];
                break;
            }
        }
    }
    Util::SafeDeleteArr(rrr);
}

//-----------------------------------------------
//線を追加する
bool MLine::AddLine(int point_a, int point_b)
{
    if (point_a < 0 || MAX_POINT_NUM_ <= point_a ||
        point_b < 0 || MAX_POINT_NUM_ <= point_b)
    {
        return false;
    }

    int line = 0;
    if (point_a == 0 || point_b == 0) { line = point_a + point_b - 1; }
    else { line = point_a + point_b; }

    if (AddLine(line))
    {
        return true;
    }
    return false;
}
bool MLine::AddLine(int line_id)
{
    if (line_id < 0 || MAX_LINE_NUM_ <= line_id)
    {
        return false;
    }

    int line = 1 << line_id;
    if ((line_flag_ & line) == 0)
    {
        line_flag_ += line;
        return true;
    }
    return false;
}

//-----------------------------------------------
//線を取得する
int MLine::GetMLine()
{
    return line_flag_;
}

//-----------------------------------------------
//線をリセットする
void MLine::ResetLine()
{
    line_flag_ = 0;
}

//-----------------------------------------------
//他の線と判定を行う
MLine::MHit MLine::CheckHitLine(int line)
{
    if (line_flag_ == line)
    {
        return MHit::Parfect;
    }

    if (line_flag_ & line)
    {
        if ((line_flag_ & line) == line_flag_)
        {
            return MHit::Excess;
        }
        return MHit::Short;
    }

    return MHit::Miss;
}

//-----------------------------------------------
//線を描画する
void MLine::Draw(const Math::Vec2& pos, const Color& color)
{
    auto& shader = ShaderManager::GetInstance();
    auto& cb = shader.GetConstantBuffer<MLineInfo>(mres_->buffer_name);
    cb.window_size.u = SysDef::SizeX;
    cb.window_size.v = SysDef::SizeY;
    cb.r = color.Fr();
    cb.g = color.Fg();
    cb.b = color.Fb();
    cb.a = color.Fa();
    float tmp = float(Util::GetRand(5, 10)) * 0.1f * thick_;

    for (int i = 0; i < MAX_LINE_NUM_; ++i)
    {
        if ((line_flag_ & (1 << i)) == 0) { continue; }
        cb.start_pos.u = pos.x;
        cb.start_pos.v = pos.y;
        cb.end_pos.u = pos.x;
        cb.end_pos.v = pos.y;
        cb.thick = tmp;

        switch (i)
        {
        case 0: cb.start_pos.v -= dist_; cb.end_pos.u -= dist_; break;	//0-1
        case 1: cb.start_pos.v -= dist_; cb.end_pos.u += dist_; break;	//0-2
        case 2: cb.start_pos.v -= dist_; cb.end_pos.v += dist_; break;	//0-3
        case 3: cb.start_pos.u -= dist_; cb.end_pos.u += dist_; break;	//1-2
        case 4: cb.start_pos.v += dist_; cb.end_pos.u -= dist_; break;	//1-3
        case 5: cb.start_pos.v += dist_; cb.end_pos.u += dist_; break;	//2-3
        }
        shader.DrawShader(mres_->shader_name, mres_->buffer_name);
    }
}