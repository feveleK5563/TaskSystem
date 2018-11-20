#include "ShaderManager.h"
#include <assert.h>
#include "UtilityFunctions.h"
#include "SystemDefine.h"

ShaderManager::~ShaderManager()
{
	AllDeleteConstantBuffer();
	AllDeleteShader();
}


//シェーダーを読み込む(第三引数がtrueで頂点データが画面サイズぴったりに設定される)
bool ShaderManager::LoadShader(std::string shaderName, std::string filePath, int shaderType, bool isVertexSetWindowSize)
{
	shaderData[shaderName].handle = LoadPixelShader(filePath.c_str());
	if (shaderData[shaderName].handle == -1)
		return false;

	shaderData[shaderName].type = shaderType;

	if (!isVertexSetWindowSize)
		return true;

	//頂点データを画面サイズぴったりに設定する
	float x = (float)SYSDEF::SizeX, y = (float)SYSDEF::SizeY;
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

//頂点データと描画方法を設定
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

//画像(テクスチャ)をセット(レジスタはデフォルトで0)
void ShaderManager::SetShaderImage(const ImageDrawer& imgDrawer, int slot)
{
	SetUseTextureToShader(slot, imgDrawer.GetImageHandle());
}

//定数バッファをシェーダーにセットして描画(レジスタはデフォルトで0)
void ShaderManager::DrawShader(std::string shaderName, std::string bufferName, int slot)
{
	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(bufferHandle[bufferName]);
	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(bufferHandle[bufferName], shaderData[shaderName].type, slot);
	//ピクセルシェーダのセット
	SetUsePixelShader(shaderData[shaderName].handle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//描画
	DrawPrimitive2DToShader(
		shaderData[shaderName].vertex.get(),
		shaderData[shaderName].vertexNum,
		shaderData[shaderName].primitiveType);
}


//定数バッファを解放する
bool ShaderManager::DeleteConstantBuffer(std::string bufferName)
{
	if (bufferHandle.count(bufferName))
		return false;

	DeleteShaderConstantBuffer(bufferHandle[bufferName]);
	bufferHandle.erase(bufferHandle.lower_bound(bufferName));
	return true;
}
//作成した定数バッファを全て解放する
bool ShaderManager::AllDeleteConstantBuffer()
{
	for (auto& it : bufferHandle)
	{
		DeleteShaderConstantBuffer(it.second);
	}
	bufferHandle.clear();
	return true;
}
//シェーダーを解放する
bool ShaderManager::DeleteShaderData(std::string shaderName)
{
	if (shaderData.count(shaderName))
		return false;

	DeleteShader(shaderData[shaderName].handle);
	shaderData.erase(shaderData.lower_bound(shaderName));
	return true;
}
//読み込んだシェーダーを全て解放する
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
//インスタンスを得る
ShaderManager& ShaderManager::GetInstance()
{
	assert(shaderManager != nullptr && "ShaderManager hasn't been created!");
	return *shaderManager;
}

//インスタンスを生成する
void ShaderManager::CreateInstance()
{
	if (shaderManager == nullptr)
	{
		shaderManager = new ShaderManager();
	}
}

//インスタンスを解放する
void ShaderManager::DeleteInstance()
{
	UTIL::SafeDelete(shaderManager);
}