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
	std::unordered_map<std::string, int> bufferHandle;	//�萔�o�b�t�@�n���h��

	//�V�F�[�_�[�̏��
	struct ShaderData
	{
		int handle;									//�V�F�[�_�[�n���h��
		int type;									//�^�C�v(�s�N�Z���Ƃ����_�Ƃ�)
		std::unique_ptr<VERTEX2DSHADER[]> vertex;	//���_�f�[�^
		int vertexNum;								//���_�f�[�^�̗v�f��
		int primitiveType;							//�`����@
	};
	std::unordered_map<std::string, ShaderData> shaderData;

	ShaderManager() = default;
	static ShaderManager* shaderManager;

public:
	~ShaderManager();

	//�w��N���X�T�C�Y�̒萔�o�b�t�@���쐬(�o�b�t�@ID���Ԃ�)
	template <typename T>
	bool CreateConstantBuffer(std::string bufferName)
	{
		int num = 1, size = sizeof(T);
		for (; num < size; num *= 2);	//�N���X�T�C�Y�ȏ��2�̗ݏ敪�������������m��
		bufferHandle[bufferName] = CreateShaderConstantBuffer(num);

		if (bufferHandle[bufferName] == -1)
			return false;

		return true;
	}
	//�萔�o�b�t�@���擾
	template <typename T>
	T& GetConstantBuffer(std::string bufferName)
	{
		T* tmp = (T*)GetBufferShaderConstantBuffer(bufferHandle[bufferName]);
		return *tmp;
	}


	//�V�F�[�_�[��ǂݍ���(��l������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
	bool LoadShader(std::string shaderName, std::string filePath,
					int shaderType = DX_SHADERTYPE_PIXEL, bool isVertexSetWindowSize = true);
	//���_�f�[�^�ƕ`����@��ݒ�
	void SetVertex(std::string shaderName, VERTEX2DSHADER* vertex, int vertexNum, int primitiveType);
	//�摜(�e�N�X�`��)���Z�b�g(���W�X�^�̓f�t�H���g��0)
	void SetShaderImage(const ImageDrawer& imgDrawer, int slot = 0);
	//�萔�o�b�t�@���V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
	void DrawShader(std::string shaderName, std::string bufferName, int slot = 0);

	//�萔�o�b�t�@���������
	bool DeleteConstantBuffer(std::string bufferName);
	//�쐬�����萔�o�b�t�@��S�ĉ������
	bool AllDeleteConstantBuffer();
	//�V�F�[�_�[���������
	bool DeleteShaderData(std::string shaderName);
	//�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
	bool AllDeleteShader();


	//�C���X�^���X�𓾂�
	static ShaderManager& GetInstance();
	//�C���X�^���X�𐶐�����
	static void CreateInstance();
	//�C���X�^���X���������
	static void DeleteInstance();
};