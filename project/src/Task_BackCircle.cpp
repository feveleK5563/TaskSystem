#include "Task_BackCircle.h"
#include "ShaderManager.h"
#include "SystemDefine.h"
#include "TaskDefData.h"

namespace BackCircle
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        shader_name = "circleShader";
        ShaderManager::LoadShader(shader_name, "data/shader/circle.pso");
        buffer_name = "circleBuffer";
        ShaderManager::CreateConstantBuffer<CircleInfo>(buffer_name);
    }
    //----------------------------------------------
    //���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        ShaderManager::DeleteShaderData(shader_name);
        ShaderManager::DeleteConstantBuffer(buffer_name);
    }
    //----------------------------------------------
    //���\�[�X�̐���
    std::shared_ptr<Resource> Resource::Create()
    {
        auto sp = instance_.lock();
        if (!sp)
        {
            sp = std::make_shared<Resource>();
            instance_ = sp;
        }
        return sp;
    }

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //�^�X�N�̃R���X�g���N�^
    Task::Task(const Color& color):
        TaskAbstract(def_task),
        res_(Resource::Create()),
        counter_(SPREAD_SPEED_, 0.f, SPREAD_SPEED_ * 60.f)
    {
        info_.window_size.u = SysDef::SizeX;
        info_.window_size.v = SysDef::SizeY;
        info_.r = color.Fr();
        info_.g = color.Fg();
        info_.b = color.Fb();
        info_.a = color.Fa();

        counter_.SetNowMax();

        SetPriority(Priority::CIRCLE);
    }
    //----------------------------------------------
    //�^�X�N�̃f�X�g���N�^
    Task::~Task()
    {
    }
    //----------------------------------------------
    //�^�X�N�̐���
    std::shared_ptr<Task> Task::Create(const Color& color)
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>(color);
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //����������
    //----------------------------------------------
    void Task::Initialize()
    {
    }

    //----------------------------------------------
    //�I������
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    //�X�V
    //----------------------------------------------
    void Task::Update()
    {
        counter_.Run();
        info_.radius = counter_.GetNow();
    }

    //----------------------------------------------
    //�`��
    //----------------------------------------------
    void Task::Draw()
    {
        //�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
        auto& cb = ShaderManager::GetConstantBuffer<CircleInfo>(res_->buffer_name);

        //�e�l����������
        cb.window_size = info_.window_size;
        cb.center_pos = info_.center_pos;
        cb.radius = info_.radius;
        cb.color_flag = info_.color_flag;
        cb.r = info_.r;
        cb.g = info_.g;
        cb.b = info_.b;
        cb.a = info_.a;

        ShaderManager::DrawShader(res_->shader_name, res_->buffer_name);
    }

    //----------------------------------------------
    //���F�t���O�ݒ�
    void Task::SetColorFlag(bool color_flag)
    {
        info_.color_flag = color_flag;
        counter_.Reset();
        info_.radius = 0.f;
    }

    //----------------------------------------------
    //���W�ݒ�
    void Task::SetPos(const Math::Vec2& pos)
    {
        info_.center_pos.u = pos.x;
        info_.center_pos.v = pos.y;
    }
}