#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "DxLib.h"
#include "ImageDrawer.h"

//シェーダー管理君(とりあえずピクセルシェーダーにだけ対応してるつもり)
class ShaderManager
{
private:
	std::unordered_map<std::string, int> bufferHandle;	//定数バッファハンドル

	//シェーダーの情報
	struct ShaderData
	{
		int handle;									//シェーダーハンドル
		int type;									//タイプ(ピクセルとか頂点とか)
		std::unique_ptr<VERTEX2DSHADER[]> vertex;	//頂点データ
		int vertexNum;								//頂点データの要素数
		int primitiveType;							//描画方法
	};
	std::unordered_map<std::string, ShaderData> shaderData;

	ShaderManager() = default;
	static ShaderManager* shaderManager;

public:
	~ShaderManager();

	//指定クラスサイズの定数バッファを作成(バッファIDが返る)
	template <typename T>
	bool CreateConstantBuffer(std::string bufferName)
	{
		int num = 1, size = sizeof(T);
		for (; num < size; num *= 2);	//クラスサイズ以上の2の累乗分だけメモリを確保
		bufferHandle[bufferName] = CreateShaderConstantBuffer(num);

		if (bufferHandle[bufferName] == -1)
			return false;

		return true;
	}
	//定数バッファを取得
	template <typename T>
	T& GetConstantBuffer(std::string bufferName)
	{
		T* tmp = (T*)GetBufferShaderConstantBuffer(bufferHandle[bufferName]);
		return *tmp;
	}


	//シェーダーを読み込む(第四引数がtrueで頂点データが画面サイズぴったりに設定される)
	bool LoadShader(std::string shaderName, std::string filePath,
					int shaderType = DX_SHADERTYPE_PIXEL, bool isVertexSetWindowSize = true);
	//頂点データと描画方法を設定
	void SetVertex(std::string shaderName, VERTEX2DSHADER* vertex, int vertexNum, int primitiveType);
	//画像(テクスチャ)をセット(レジスタはデフォルトで0)
	void SetShaderImage(const ImageDrawer& imgDrawer, int slot = 0);
	//定数バッファをシェーダーにセットして描画(レジスタはデフォルトで0)
	void DrawShader(std::string shaderName, std::string bufferName, int slot = 0);

	//定数バッファを解放する
	bool DeleteConstantBuffer(std::string bufferName);
	//作成した定数バッファを全て解放する
	bool AllDeleteConstantBuffer();
	//シェーダーを解放する
	bool DeleteShaderData(std::string shaderName);
	//読み込んだシェーダーを全て解放する
	bool AllDeleteShader();


	//インスタンスを得る
	static ShaderManager& GetInstance();
	//インスタンスを生成する
	static void CreateInstance();
	//インスタンスを解放する
	static void DeleteInstance();
};