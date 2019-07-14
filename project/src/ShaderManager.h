#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "DxLib.h"
#include "ImageDrawer.h"

//�V�F�[�_�[�Ǘ��N(�Ƃ肠�����s�N�Z���V�F�[�_�[�ɂ����Ή����Ă����)
class ShaderManager
{
private:
    std::unordered_map<std::string, int> buffer_handle_;	//�萔�o�b�t�@�n���h��

    //�V�F�[�_�[�̏��
    struct ShaderData
    {
        int handle;                                 //�V�F�[�_�[�n���h��
        int type;                                   //�^�C�v(�s�N�Z���Ƃ����_�Ƃ�)
        std::unique_ptr<VERTEX2DSHADER[]> vertex;   //���_�f�[�^
        int vertexNum;                              //���_�f�[�^�̗v�f��
        int primitiveType;                          //�`����@
        ShaderData() = default;
    };
    std::unordered_map<std::string, ShaderData> shader_data_;

    ShaderManager() = default;
    static ShaderManager* shader_manager_;

public:
    ~ShaderManager();

    //�w��N���X�T�C�Y�̒萔�o�b�t�@���쐬
    template <typename T>
    bool CreateConstantBuffer(const std::string& buffer_name)
    {
        int num = 1, size = sizeof(T);
        for (; num < size; num *= 2);	//�N���X�T�C�Y�ȏ��2�̗ݏ敪�������������m��
        buffer_handle_[buffer_name] = CreateShaderConstantBuffer(num);

        if (buffer_handle_[buffer_name] == -1)
            return false;

        return true;
    }
    //�萔�o�b�t�@���擾
    template <typename T>
    T& GetConstantBuffer(const std::string& buffer_name)
    {
        T* tmp = (T*)GetBufferShaderConstantBuffer(buffer_handle_[buffer_name]);
        return *tmp;
    }


    //�V�F�[�_�[��ǂݍ���(��l������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
    bool LoadShader(const std::string& shader_name, const std::string& file_path,
                    int shader_type = DX_SHADERTYPE_PIXEL, bool is_vertex_set_window_size = true);
    //���_�f�[�^�ƕ`����@��ݒ�
    void SetVertex(std::string shader_name, VERTEX2DSHADER* vertex, int vertex_num, int primitive_type);
    //�摜(�e�N�X�`��)���n���h���Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
    void SetShaderImage(int image_handle, int slot = 0);
    //�摜(�e�N�X�`��)��Drawer�Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
    void SetShaderImage(const ImageDrawer& image_drawer, int slot = 0);
    //�萔�o�b�t�@���X�V�ƃV�F�[�_�[�̃Z�b�g(���W�X�^�̓f�t�H���g��0)
    void UpdateAndSetCB(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //�V�F�[�_�[���g���ĕ`��
    void DrawShader(const std::string& shader_name);
    //�萔�o�b�t�@��������V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
    void DrawShader(const std::string& shader_name, const std::string& buffer_name, int slot = 0);

    //�萔�o�b�t�@���������
    bool DeleteConstantBuffer(const std::string& buffer_name);
    //�쐬�����萔�o�b�t�@��S�ĉ������
    bool AllDeleteConstantBuffer();
    //�V�F�[�_�[���������
    bool DeleteShaderData(const std::string& shader_name);
    //�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
    bool AllDeleteShader();


    //�C���X�^���X�𓾂�
    static ShaderManager& GetInstance();
    //�C���X�^���X�𐶐�����
    static void CreateInstance();
    //�C���X�^���X���������
    static void DeleteInstance();
};