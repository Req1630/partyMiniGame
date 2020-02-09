#include "ShaderBase.h"

CShaderBase::CShaderBase()
	: m_pDevice11		( nullptr )
	, m_pContext11		( nullptr )
	, m_pVertexShader	( nullptr )
	, m_pPixelShader	( nullptr )
	, m_pVertexLayout	( nullptr )
	, m_pConstantBuffer	( nullptr )
{
}

CShaderBase::~CShaderBase()
{
}

//----------------------------------.
// シェーダー読込関数.
//----------------------------------.
HRESULT CShaderBase::InitShader(
	const char* filePath,
	const char* entryPoint,
	const char* shaderModel,
	UINT compileFlag,
	ID3DBlob** ppCompiledShader,
	ID3DBlob** ppErrors )
{
	return D3DX10CompileFromFile(
		filePath,			// シェーダーファイルパス.
		nullptr,			// マクロ定義のポインター : オプション.
		nullptr,			// インクルードファイルを処理するためのポインタ : オプション.
		entryPoint,			// シェーダーのエントリーポイント関数名.
		shaderModel,		// シェーダーモデルの名前.
		compileFlag,		// シェーダーコンパイルフラグ.
		0,					// エフェクトコンパイルフラグ (0推奨).
		nullptr,			// スレッドポンプインターフェイスへのポインター.
		ppCompiledShader,	// コンパイルされたシェーダーのデータ (out).
		ppErrors,			// コンパイル中のエラー出力 (out).
		nullptr );			// 戻り値のポインタ.
}

//----------------------------------.
// バーテックスシェーダー作成関数.
//----------------------------------.
HRESULT CShaderBase::CreateVertexShader(
	ID3DBlob* pCompiledShader,
	ID3D11VertexShader**	pVertexShader )
{
	return m_pDevice11->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		nullptr,
		pVertexShader );
}

//----------------------------------.
// ピクセルスシェーダー作成関数.
//----------------------------------.
HRESULT CShaderBase::CreatePixelShader(
	ID3DBlob* pCompiledShader,
	ID3D11PixelShader**	pPixelShader )
{
	return m_pDevice11->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		nullptr,
		pPixelShader );
}

//----------------------------------.
// インプットレイアウト作成関数.
//----------------------------------.
HRESULT CShaderBase::CreateInputLayout(
	D3D11_INPUT_ELEMENT_DESC* pLayout,
	UINT numElements,
	ID3DBlob* pCompiledShader, 
	ID3D11InputLayout** m_pVertexLayout )
{
	return m_pDevice11->CreateInputLayout(
		pLayout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		m_pVertexLayout );
}

//----------------------------------.
// コンスタントバッファ作成関数.
//----------------------------------.
HRESULT CShaderBase::CreateConstantBuffer( 
	ID3D11Buffer** pConstantBuffer,
	UINT size )
{
	D3D11_BUFFER_DESC cb;

	cb.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth			= size;
	cb.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags			= 0;
	cb.StructureByteStride	= 0;
	cb.Usage				= D3D11_USAGE_DYNAMIC;

	return m_pDevice11->CreateBuffer( &cb, nullptr, pConstantBuffer );
}

//----------------------------------.
// 頂点インプットレイアウトの取得.
//----------------------------------.
D3D11_INPUT_ELEMENT_DESC CShaderBase::GetPositionInputElement() const
{
	return
	{
		"POSITION",						//位置.
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのﾌｫｰﾏｯﾄ(32bit float型*3).
		0,
		D3D11_APPEND_ALIGNED_ELEMENT,	//ﾃﾞｰﾀの開始位置.
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	};
}