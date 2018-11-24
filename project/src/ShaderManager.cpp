#include "ShaderManager.h"
#include "Utility.h"
#include "SystemDefine.h"

ShaderManager::~ShaderManager()
{
	AllDeleteConstantBuffer();
	AllDeleteShader();
}


//�V�F�[�_�[��ǂݍ���(��O������true�Œ��_�f�[�^����ʃT�C�Y�҂�����ɐݒ肳���)
bool ShaderManager::LoadShader(const std::string& shaderName, const std::string& filePath, int shaderType, bool isVertexSetWindowSize)
{
	shaderData[shaderName].handle = LoadPixelShader(filePath.c_str());
	if (shaderData[shaderName].handle == -1)
		return false;

	shaderData[shaderName].type = shaderType;

	if (!isVertexSetWindowSize)
		return true;

	//���_�f�[�^����ʃT�C�Y�҂�����ɐݒ肷��
	float x = (float)SysDef::SizeX, y = (float)SysDef::SizeY;
	shaderData[shaderName].vertexNum = 4;
	shaderData[shaderName].vertex = std::make_unique<VERTEX2DSHADER[]>(4);
	shaderData[shaderName].vertex[0].pos = VGet(-1.f, -1.f, 0.f);
	shaderData[shaderName].vertex[1].pos = VGet(   x, -1.f, 0.f);
	shaderData[shaderName].vertex[2].pos = VGet(-1.f,    y, 0.f);
	shaderData[shaderName].vertex[3].pos = VGet(   x,    y, 0.f);
	for (int i = 0; i < 4; ++i)
	{
		shaderData[shaderName].vertex[i].rhw = 1.f;
		shaderData[shaderName].vertex[i].dif = GetColorU8(255, 255, 255, 255);
		shaderData[shaderName].vertex[i].spc = GetColorU8(0, 0, 0, 0);
		shaderData[shaderName].vertex[i].u = float(i % 2);
		shaderData[shaderName].vertex[i].su = float(i % 2);
		shaderData[shaderName].vertex[i].v = float(i / 2);
		shaderData[shaderName].vertex[i].sv = float(i / 2);
	}
	shaderData[shaderName].primitiveType = DX_PRIMTYPE_TRIANGLESTRIP;

	return true;
}

//���_�f�[�^�ƕ`����@��ݒ�
void ShaderManager::SetVertex(std::string shaderName, VERTEX2DSHADER* vertex, int vertexNum, int primitiveType)
{
	shaderData[shaderName].vertexNum = vertexNum;
	shaderData[shaderName].vertex = std::make_unique<VERTEX2DSHADER[]>(vertexNum);
	for (int i = 0; i < vertexNum; ++i)
	{
		shaderData[shaderName].vertex[i] = vertex[i];
	}
	shaderData[shaderName].primitiveType = primitiveType;
}

//�摜(�e�N�X�`��)���n���h���Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::SetShaderImage(int imgHandle, int slot)
{
	SetUseTextureToShader(slot, imgHandle);
}
//�摜(�e�N�X�`��)��Drawer�Ŏw�肵�ăZ�b�g(���W�X�^�̓f�t�H���g��0)
void ShaderManager::SetShaderImage(const ImageDrawer& imgDrawer, int slot)
{
	SetUseTextureToShader(slot, imgDrawer.GetImageHandle());
}

//�萔�o�b�t�@���X�V(���W�X�^�̓f�t�H���g��0)
void ShaderManager::UpdateAndSetCB(const std::string& shaderName, const std::string& bufferName, int slot)
{
	//�V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(bufferHandle[bufferName]);
	//�V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(bufferHandle[bufferName], shaderData[shaderName].type, slot);
}


//�V�F�[�_�[���g���ĕ`��
void ShaderManager::DrawShader(const std::string& shaderName)
{
	//�V�F�[�_�̃Z�b�g
	SetUsePixelShader(shaderData[shaderName].handle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//�`��
	DrawPrimitive2DToShader(
		shaderData[shaderName].vertex.get(),
		shaderData[shaderName].vertexNum,
		shaderData[shaderName].primitiveType);
}

//�萔�o�b�t�@��������V�F�[�_�[�ɃZ�b�g���ĕ`��(���W�X�^�̓f�t�H���g��0)
void ShaderManager::DrawShader(const std::string& shaderName, const std::string& bufferName, int slot)
{
	UpdateAndSetCB(shaderName, bufferName, slot);
	DrawShader(shaderName);
}


//�萔�o�b�t�@���������
bool ShaderManager::DeleteConstantBuffer(const std::string& bufferName)
{
	if (bufferHandle.count(bufferName))
		return false;

	DeleteShaderConstantBuffer(bufferHandle[bufferName]);
	bufferHandle.erase(bufferHandle.lower_bound(bufferName));
	return true;
}
//�쐬�����萔�o�b�t�@��S�ĉ������
bool ShaderManager::AllDeleteConstantBuffer()
{
	for (auto& it : bufferHandle)
	{
		DeleteShaderConstantBuffer(it.second);
	}
	bufferHandle.clear();
	return true;
}
//�V�F�[�_�[���������
bool ShaderManager::DeleteShaderData(const std::string& shaderName)
{
	if (shaderData.count(shaderName))
		return false;

	DeleteShader(shaderData[shaderName].handle);
	shaderData.erase(shaderData.lower_bound(shaderName));
	return true;
}
//�ǂݍ��񂾃V�F�[�_�[��S�ĉ������
bool ShaderManager::AllDeleteShader()
{
	for (auto& it : shaderData)
	{
		DeleteShader(it.second.handle);
	}
	shaderData.clear();
	return true;
}


ShaderManager* ShaderManager::shaderManager = nullptr;
//�C���X�^���X�𓾂�
ShaderManager& ShaderManager::GetInstance()
{
	assert(shaderManager != nullptr && "ShaderManager hasn't been created!");
	return *shaderManager;
}

//�C���X�^���X�𐶐�����
void ShaderManager::CreateInstance()
{
	if (shaderManager == nullptr)
	{
		shaderManager = new ShaderManager();
	}
}

//�C���X�^���X���������
void ShaderManager::DeleteInstance()
{
	Utility::SafeDelete(shaderManager);
}