#include "ShaderManager.h"
#include "Utility.h"
#include "SystemDefine.h"

class ShaderManager::Impl
{
private:
    std::unordered_map<std::string, int> buffer_handle_;	//�萔�o�b�t�@�n���h��

    //�V�F�[�_�[�̏��
    struct ShaderData
    {
        int handle = 0;                             //�V�F�[�_�[�n���h��
        int type = 0;                               //�^�C�v(�s�N�Z���Ƃ����_�Ƃ�)
        std::unique_ptr<VERTEX2DSHADER[]> vertex;   //���_�f�[�^
        int vertex_num = 0;                         //���_�f�[�^�̗v�f��
        int primitive_type = 0;                     //�`����@
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

    //�w��N���X�T�C�Y�̒萔�o�b�t�@���쐬
    bool CreateConstantBuffer(const std::string& buffer_name, int size)
    {
        int buf_size = 1;
        for (; buf_size < size; buf_size *= 2);	//�N���X�T�C�Y�ȏ��2�̗ݏ敪�������������m��
        buffer_handle_[buffer_name] = CreateShaderConstantBuffer(buf_size);

        if (buffer_handle_[buffer_name] == -1)
            return false;

        return true;
    }
    //�萔�o�b�t�@���擾
    void* GetConstantBuffer(const std::string& buffer_name)
    {
        return GetBufferShaderConstantBuffer(buffer_handle_[buffer_name]);
    }

    //�V�F�[�_�[��ǂݍ���(��O������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
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

        //���_�f�[�^����ʃT�C�Y�҂�����ɐݒ肷��
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

    //���_�f�[�^�ƕ`����@��ݒ�
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

    //�摜(�e�N�X�`��)���n���h���Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
    void SetShaderImage(int image_handle, int slot)
    {
        SetUseTextureToShader(slot, image_handle);
    }
    //�摜(�e�N�X�`��)��Drawer�Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
    void SetShaderImage(const ImageDrawer& imgDrawer, int slot)
    {
        SetUseTextureToShader(slot, imgDrawer.GetNowImageHandle());
    }

    //�萔�o�b�t�@���X�V(���W�X�^�̓f�t�H���g��0)
    void UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot)
    {
        //�V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
        UpdateShaderConstantBuffer(buffer_handle_[buffer_name]);
        //�V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
        SetShaderConstantBuffer(buffer_handle_[buffer_name], shader_data_[shader_name].type, slot);
    }


    //�V�F�[�_�[���g���ĕ`��
    void DrawShader(const std::string& shader_name)
    {
        //�V�F�[�_�̃Z�b�g
        SetUsePixelShader(shader_data_[shader_name].handle);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        //�`��
        DrawPrimitive2DToShader(
            shader_data_[shader_name].vertex.get(),
            shader_data_[shader_name].vertex_num,
            shader_data_[shader_name].primitive_type);
    }

    //�萔�o�b�t�@��������V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
    void DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot)
    {
        UpdateAndSetCB(shader_name, buffer_name, slot);
        DrawShader(shader_name);
    }


    //�萔�o�b�t�@���������
    bool DeleteConstantBuffer(const std::string& buffer_name)
    {
        if (buffer_handle_.count(buffer_name)) { return false; }

        DeleteShaderConstantBuffer(buffer_handle_[buffer_name]);
        buffer_handle_.erase(buffer_handle_.lower_bound(buffer_name));
        return true;
    }
    //�쐬�����萔�o�b�t�@��S�ĉ������
    bool AllDeleteConstantBuffer()
    {
        for (auto& it : buffer_handle_)
        {
            DeleteShaderConstantBuffer(it.second);
        }
        buffer_handle_.clear();
        return true;
    }
    //�V�F�[�_�[���������
    bool DeleteShaderData(const std::string& shader_name)
    {
        if (shader_data_.count(shader_name)) { return false; }

        DeleteShader(shader_data_[shader_name].handle);
        shader_data_.erase(shader_data_.lower_bound(shader_name));
        return true;
    }
    //�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
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

// �C���X�^���X�𐶐�����
void ShaderManager::Create()
{
    if (!impl_)
    {
        impl_ = new Impl();
    }
}

// �C���X�^���X���������
void ShaderManager::Delete()
{
    Util::SafeDelete(impl_);
}

//�V�F�[�_�[��ǂݍ���(��l������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
bool ShaderManager::LoadShader(const std::string& shader_name, const std::string& file_path,
                               int shader_type, bool is_vertex_set_window_size)
{
    return GetImpl()->LoadShader(shader_name, file_path, shader_type, is_vertex_set_window_size);
}

//���_�f�[�^�ƕ`����@��ݒ�
void ShaderManager::SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type)
{
    GetImpl()->SetVertex(shader_name, vertex, vertex_num, primitive_type);
}

//�摜(�e�N�X�`��)���n���h���Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::SetShaderImage(int image_handle, int slot)
{
    GetImpl()->SetShaderImage(image_handle, slot);
}

//�摜(�e�N�X�`��)��Drawer�Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::SetShaderImage(const ImageDrawer& image_drawer, int slot)
{
    GetImpl()->SetShaderImage(image_drawer, slot);
}

//�萔�o�b�t�@���X�V�ƃV�F�[�_�[�̃Z�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot)
{
    GetImpl()->UpdateAndSetCB(shader_name, buffer_name, slot);
}

//�V�F�[�_�[���g���ĕ`��
void ShaderManager::DrawShader(const std::string& shader_name)
{
    GetImpl()->DrawShader(shader_name);
}

//�萔�o�b�t�@��������V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
void ShaderManager::DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot)
{
    GetImpl()->DrawShader(shader_name, buffer_name, slot);
}

//�萔�o�b�t�@���������
bool ShaderManager::DeleteConstantBuffer(const std::string& buffer_name)
{
    return GetImpl()->DeleteConstantBuffer(buffer_name);
}

//�쐬�����萔�o�b�t�@��S�ĉ������
bool ShaderManager::AllDeleteConstantBuffer()
{
    return GetImpl()->AllDeleteConstantBuffer();
}

//�V�F�[�_�[���������
bool ShaderManager::DeleteShaderData(const std::string& shader_name)
{
    return GetImpl()->DeleteShaderData(shader_name);
}

//�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
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