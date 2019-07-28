#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "DxLib.h"
#include "ImageDrawer.h"

//�V�F�[�_�[�Ǘ��N(�Ƃ肠�����s�N�Z���V�F�[�_�[�ɂ����Ή����Ă����)
class ShaderManager
{
public:
    //�C���X�^���X�𐶐�����
    static void Create();
    //�C���X�^���X���������
    static void Delete();

    //�w��N���X�T�C�Y�̒萔�o�b�t�@���쐬
    template <typename T>
    static bool CreateConstantBuffer(const std::string& buffer_name)
    {
        return CreateConstantBufferSetSize(buffer_name, sizeof(T));
    }
    //�萔�o�b�t�@���擾
    template <typename T>
    static T& GetConstantBuffer(const std::string& buffer_name)
    {
        return *(T*)GetConstantBufferPointer(buffer_name);
    }

    //�V�F�[�_�[��ǂݍ���(��l������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
    static bool LoadShader(const std::string& shader_name, const std::string& file_path,
                           int shader_type = DX_SHADERTYPE_PIXEL, bool is_vertex_set_window_size = true);
    //���_�f�[�^�ƕ`����@��ݒ�
    static void SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type);
    //�摜(�e�N�X�`��)���n���h���Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
    static void SetShaderImage(int image_handle, int slot = 0);
    //�摜(�e�N�X�`��)��Drawer�Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
    static void SetShaderImage(const ImageDrawer& image_drawer, int slot = 0);
    //�萔�o�b�t�@���X�V�ƃV�F�[�_�[�̃Z�b�g(���W�X�^�̓f�t�H���g��0)
    static void UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //�V�F�[�_�[���g���ĕ`��
    static void DrawShader(const std::string& shader_name);
    //�萔�o�b�t�@��������V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
    static void DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //�萔�o�b�t�@���������
    static bool DeleteConstantBuffer(const std::string& buffer_name);
    //�쐬�����萔�o�b�t�@��S�ĉ������
    static bool AllDeleteConstantBuffer();
    //�V�F�[�_�[���������
    static bool DeleteShaderData(const std::string& shader_name);
    //�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
    static bool AllDeleteShader();

private:
    static bool CreateConstantBufferSetSize(const std::string& buffer_name, int size);
    static void* GetConstantBufferPointer(const std::string& buffer_name);

private:
    class Impl;
    static Impl* impl_;
    static Impl* GetImpl();
};