#include "ShaderManager.h"
#include "Utility.h"
#include "SystemDefine.h"

ShaderManager::~ShaderManager()
{
    AllDeleteConstantBuffer();
    AllDeleteShader();
}


//�V�F�[�_�[��ǂݍ���(��O������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
bool ShaderManager::LoadShader(const std::string& shader_name, const std::string& file_path, int shader_type, bool is_vertex_set_window_size)
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
    shader_data_[shader_name].vertexNum = 4;
    shader_data_[shader_name].vertex = std::make_unique<VERTEX2DSHADER[]>(4);
    shader_data_[shader_name].vertex[0].pos = VGet(-1.f, -1.f, 0.f);
    shader_data_[shader_name].vertex[1].pos = VGet(   x, -1.f, 0.f);
    shader_data_[shader_name].vertex[2].pos = VGet(-1.f,    y, 0.f);
    shader_data_[shader_name].vertex[3].pos = VGet(   x,    y, 0.f);
    for (int i = 0; i < 4; ++i)
    {
        shader_data_[shader_name].vertex[i].rhw = 1.f;
        shader_data_[shader_name].vertex[i].dif = GetColorU8(255, 255, 255, 255);
        shader_data_[shader_name].vertex[i].spc = GetColorU8(0, 0, 0, 0);
        shader_data_[shader_name].vertex[i].u =  float(i % 2);
        shader_data_[shader_name].vertex[i].su = float(i % 2);
        shader_data_[shader_name].vertex[i].v =  float(i / 2);
        shader_data_[shader_name].vertex[i].sv = float(i / 2);
    }
    shader_data_[shader_name].primitiveType = DX_PRIMTYPE_TRIANGLESTRIP;

    return true;
}

//���_�f�[�^�ƕ`����@��ݒ�
void ShaderManager::SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type)
{
    shader_data_[shader_name].vertexNum = vertex_num;
    shader_data_[shader_name].vertex = std::make_unique<VERTEX2DSHADER[]>(vertex_num);
    for (int i = 0; i < vertex_num; ++i)
    {
        shader_data_[shader_name].vertex[i] = vertex[i];
    }
    shader_data_[shader_name].primitiveType = primitive_type;
}

//�摜(�e�N�X�`��)���n���h���Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::SetShaderImage(int image_handle, int slot)
{
    SetUseTextureToShader(slot, image_handle);
}
//�摜(�e�N�X�`��)��Drawer�Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::SetShaderImage(const ImageDrawer& imgDrawer, int slot)
{
    SetUseTextureToShader(slot, imgDrawer.GetNowImageHandle());
}

//�萔�o�b�t�@���X�V(���W�X�^�̓f�t�H���g��0)
void ShaderManager::UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot)
{
    //�V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
    UpdateShaderConstantBuffer(buffer_handle_[buffer_name]);
    //�V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
    SetShaderConstantBuffer(buffer_handle_[buffer_name], shader_data_[shader_name].type, slot);
}


//�V�F�[�_�[���g���ĕ`��
void ShaderManager::DrawShader(const std::string& shader_name)
{
    //�V�F�[�_�̃Z�b�g
    SetUsePixelShader(shader_data_[shader_name].handle);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    //�`��
    DrawPrimitive2DToShader(
        shader_data_[shader_name].vertex.get(),
        shader_data_[shader_name].vertexNum,
        shader_data_[shader_name].primitiveType);
}

//�萔�o�b�t�@��������V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
void ShaderManager::DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot)
{
    UpdateAndSetCB(shader_name, buffer_name, slot);
    DrawShader(shader_name);
}


//�萔�o�b�t�@���������
bool ShaderManager::DeleteConstantBuffer(const std::string& buffer_name)
{
    if (buffer_handle_.count(buffer_name)) { return false; }

    DeleteShaderConstantBuffer(buffer_handle_[buffer_name]);
    buffer_handle_.erase(buffer_handle_.lower_bound(buffer_name));
    return true;
}
//�쐬�����萔�o�b�t�@��S�ĉ������
bool ShaderManager::AllDeleteConstantBuffer()
{
    for (auto& it : buffer_handle_)
    {
        DeleteShaderConstantBuffer(it.second);
    }
    buffer_handle_.clear();
    return true;
}
//�V�F�[�_�[���������
bool ShaderManager::DeleteShaderData(const std::string& shader_name)
{
    if (shader_data_.count(shader_name)) { return false; }

    DeleteShader(shader_data_[shader_name].handle);
    shader_data_.erase(shader_data_.lower_bound(shader_name));
    return true;
}
//�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
bool ShaderManager::AllDeleteShader()
{
    for (auto& it : shader_data_)
    {
        DeleteShader(it.second.handle);
    }
    shader_data_.clear();
    return true;
}


ShaderManager* ShaderManager::shader_manager_ = nullptr;
//�C���X�^���X�𓾂�
ShaderManager& ShaderManager::GetInstance()
{
    assert(shader_manager_ != nullptr && "ShaderManager hasn't been created!");
    return *shader_manager_;
}

//�C���X�^���X�𐶐�����
void ShaderManager::CreateInstance()
{
    if (shader_manager_ == nullptr)
    {
        shader_manager_ = new ShaderManager();
    }
}

//�C���X�^���X���������
void ShaderManager::DeleteInstance()
{
    Util::SafeDelete(shader_manager_);
}