#include "CSprite.h"
#include <crtdbg.h>
#include <algorithm>

// シェーダファイル名(ディレクトリも含む).
const char SHADER_NAME[] = "Data\\Shader\\Sprite.hlsl";


//ｺﾝｽﾄﾗｸﾀ.
CSprite::CSprite()
	: m_pVertexShader	( nullptr )
	, m_pVertexLayout	( nullptr )
	, m_pPixelShader	( nullptr )
	, m_pConstantBuffer	( nullptr )
	, m_pVertexBuffer	( nullptr )
	, m_pVertexBufferUI	( nullptr )
	, m_pSampleLinear	( nullptr )
	, m_pTexture		( nullptr )
	, m_AnimCount		( 0 )
	, m_SState			()
	, m_PatternNo		()
{
}

CSprite::CSprite( ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	const char* fileName, const SPRITE_STATE& pSs )
	: CSprite()
{
	Init(  pDevice11, pContext11, fileName,  pSs );
}

//ﾃﾞｽﾄﾗｸﾀ.
CSprite::~CSprite()
{
	Release();
}

//初期化.
HRESULT CSprite::Init( ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	const char* fileName, const SPRITE_STATE& pSs )
{
	m_SState = pSs;
	m_vPos = m_SState.vPos;
	if( FAILED( InitPram( pDevice11, pContext11 )) ){
		return E_FAIL;
	}
	//ｼｪｰﾀﾞ作成.
	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	//板ﾎﾟﾘｺﾞﾝ作成.
	if( FAILED( InitModel() ) ){
		return E_FAIL;
	}
	// テクスチャ作成.
	if( FAILED( CreateTexture( fileName, &m_pTexture ))){
		return E_FAIL;
	}

	return S_OK;
}

//解放.
void CSprite::Release()
{
	SAFE_RELEASE( m_pSampleLinear );
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pVertexBufferUI );
	SAFE_RELEASE( m_pVertexBuffer );
	SAFE_RELEASE( m_pConstantBuffer );
	SAFE_RELEASE( m_pPixelShader );
	SAFE_RELEASE( m_pVertexLayout );
	SAFE_RELEASE( m_pVertexShader );
}

//===========================================================
//	HLSLﾌｧｲﾙを読み込みｼｪｰﾀﾞを作成する.
//	HLSL: High Level Shading Language の略.
//===========================================================
HRESULT CSprite::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif//#ifdef _DEBUG

	//HLSLからﾊﾞｰﾃｯｸｽｼｪｰﾀﾞのﾌﾞﾛﾌﾞを作成.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//ｼｪｰﾀﾞﾌｧｲﾙ名(HLSLﾌｧｲﾙ).
			nullptr,		//ﾏｸﾛ定義の配列へのﾎﾟｲﾝﾀ(未使用).
			nullptr,		//ｲﾝｸﾙｰﾄﾞﾌｧｲﾙを扱うｲﾝﾀｰﾌｪｲｽへのﾎﾟｲﾝﾀ(未使用).
			"VS_MainUI",	//ｼｪｰﾀﾞｴﾝﾄﾘｰﾎﾟｲﾝﾄ関数の名前.
			"vs_5_0",		//ｼｪｰﾀﾞのﾓﾃﾞﾙを指定する文字列(ﾌﾟﾛﾌｧｲﾙ).
			uCompileFlag,	//ｼｪｰﾀﾞｺﾝﾊﾟｲﾙﾌﾗｸﾞ.
			0,				//ｴﾌｪｸﾄｺﾝﾊﾟｲﾙﾌﾗｸﾞ(未使用).
			nullptr,		//ｽﾚｯﾄﾞ ﾎﾟﾝﾌﾟ ｲﾝﾀｰﾌｪｲｽへのﾎﾟｲﾝﾀ(未使用).
			&pCompiledShader,//ﾌﾞﾛﾌﾞを格納するﾒﾓﾘへのﾎﾟｲﾝﾀ.
			&pErrors,		//ｴﾗｰと警告一覧を格納するﾒﾓﾘへのﾎﾟｲﾝﾀ.
			nullptr ) ) )		//戻り値へのﾎﾟｲﾝﾀ(未使用).
	{
		_ASSERT_EXPR( false, L"hlsl読み込み失敗" );
		return E_FAIL;
	}
	
	//上記で作成したﾌﾞﾛﾌﾞから「ﾊﾞｰﾃｯｸｽｼｪｰﾀﾞ」を作成.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShaderUI ) ) )	//(out)ﾊﾞｰﾃｯｸｽｼｪｰﾀﾞ.
	{
		_ASSERT_EXPR( false, L"ﾊﾞｰﾃｯｸｽｼｪｰﾀﾞ作成失敗" );
		return E_FAIL;
	}
	//HLSLからﾊﾞｰﾃｯｸｽｼｪｰﾀﾞのﾌﾞﾛﾌﾞを作成.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//ｼｪｰﾀﾞﾌｧｲﾙ名(HLSLﾌｧｲﾙ).
			nullptr,		//ﾏｸﾛ定義の配列へのﾎﾟｲﾝﾀ(未使用).
			nullptr,		//ｲﾝｸﾙｰﾄﾞﾌｧｲﾙを扱うｲﾝﾀｰﾌｪｲｽへのﾎﾟｲﾝﾀ(未使用).
			"VS_Main",	//ｼｪｰﾀﾞｴﾝﾄﾘｰﾎﾟｲﾝﾄ関数の名前.
			"vs_5_0",		//ｼｪｰﾀﾞのﾓﾃﾞﾙを指定する文字列(ﾌﾟﾛﾌｧｲﾙ).
			uCompileFlag,	//ｼｪｰﾀﾞｺﾝﾊﾟｲﾙﾌﾗｸﾞ.
			0,				//ｴﾌｪｸﾄｺﾝﾊﾟｲﾙﾌﾗｸﾞ(未使用).
			nullptr,		//ｽﾚｯﾄﾞ ﾎﾟﾝﾌﾟ ｲﾝﾀｰﾌｪｲｽへのﾎﾟｲﾝﾀ(未使用).
			&pCompiledShader,//ﾌﾞﾛﾌﾞを格納するﾒﾓﾘへのﾎﾟｲﾝﾀ.
			&pErrors,		//ｴﾗｰと警告一覧を格納するﾒﾓﾘへのﾎﾟｲﾝﾀ.
			nullptr ) ) )		//戻り値へのﾎﾟｲﾝﾀ(未使用).
	{
		_ASSERT_EXPR( false, L"hlsl読み込み失敗" );
		return E_FAIL;
	}

	//上記で作成したﾌﾞﾛﾌﾞから「ﾊﾞｰﾃｯｸｽｼｪｰﾀﾞ」を作成.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader ) ) )	//(out)ﾊﾞｰﾃｯｸｽｼｪｰﾀﾞ.
	{
		_ASSERT_EXPR( false, L"ﾊﾞｰﾃｯｸｽｼｪｰﾀﾞ作成失敗" );
		return E_FAIL;
	}
	InitVertexLayout( pCompiledShader );
	SAFE_RELEASE( pErrors );
	SAFE_RELEASE( pCompiledShader );

	//HLSLからﾋﾟｸｾﾙｼｪｰﾀﾞのﾌﾞﾛﾌﾞを作成.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//ｼｪｰﾀﾞﾌｧｲﾙ名(HLSLﾌｧｲﾙ).
			nullptr,		//ﾏｸﾛ定義の配列へのﾎﾟｲﾝﾀ(未使用).
			nullptr,		//ｲﾝｸﾙｰﾄﾞﾌｧｲﾙを扱うｲﾝﾀｰﾌｪｲｽへのﾎﾟｲﾝﾀ(未使用).
			"PS_Main",		//ｼｪｰﾀﾞｴﾝﾄﾘｰﾎﾟｲﾝﾄ関数の名前.
			"ps_5_0",		//ｼｪｰﾀﾞのﾓﾃﾞﾙを指定する文字列(ﾌﾟﾛﾌｧｲﾙ).
			uCompileFlag,	//ｼｪｰﾀﾞｺﾝﾊﾟｲﾙﾌﾗｸﾞ.
			0,				//ｴﾌｪｸﾄｺﾝﾊﾟｲﾙﾌﾗｸﾞ(未使用).
			nullptr,		//ｽﾚｯﾄﾞ ﾎﾟﾝﾌﾟ ｲﾝﾀｰﾌｪｲｽへのﾎﾟｲﾝﾀ(未使用).
			&pCompiledShader,//ﾌﾞﾛﾌﾞを格納するﾒﾓﾘへのﾎﾟｲﾝﾀ.
			&pErrors,		//ｴﾗｰと警告一覧を格納するﾒﾓﾘへのﾎﾟｲﾝﾀ.
			nullptr ) ) )		//戻り値へのﾎﾟｲﾝﾀ(未使用).
	{
		_ASSERT_EXPR( false, L"hlsl読み込み失敗" );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//上記で作成したﾌﾞﾛﾌﾞから「ﾋﾟｸｾﾙｼｪｰﾀﾞ」を作成.
	if( FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader ) ) )	//(out)ﾋﾟｸｾﾙｼｪｰﾀﾞ.
	{
		_ASSERT_EXPR( false, L"ﾋﾟｸｾﾙｼｪｰﾀﾞ作成失敗" );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );

	InitConstantBuffer( &m_pConstantBuffer, sizeof(SHADER_CONSTANT_BUFFER) );


	return S_OK;
}

HRESULT CSprite::InitVertexLayout( ID3DBlob* pCompiledShader )
{
	//頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄを定義.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//位置.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのﾌｫｰﾏｯﾄ(32bit float型*3).
			0,
			0,								//ﾃﾞｰﾀの開始位置.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",						//ﾃｸｽﾁｬ位置.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGIのﾌｫｰﾏｯﾄ(32bit float型*2).
			0,
			12,								//ﾃﾞｰﾀの開始位置.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	//頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄの配列要素数を算出.
	UINT numElements = sizeof( layout ) / sizeof( layout[0] );

	//頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄを作成.
	if( FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout ) ) )	//(out)頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄ.
	{
		_ASSERT_EXPR( false, L"頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄ作成失敗" );
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSprite::InitConstantBuffer( ID3D11Buffer** ppConstantBuffer, UINT size )
{
	//ｺﾝｽﾀﾝﾄ(定数)ﾊﾞｯﾌｧ作成.
	//ｼｪｰﾀﾞに特定の数値を送るﾊﾞｯﾌｧ.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;		//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧを指定.
	cb.ByteWidth			= size;								//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧのｻｲｽﾞ.
	cb.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;			//書き込みでｱｸｾｽ.
	cb.MiscFlags			= 0;								//その他のﾌﾗｸﾞ(未使用).
	cb.StructureByteStride	= 0;								//構造体のｻｲｽﾞ(未使用).
	cb.Usage				= D3D11_USAGE_DYNAMIC;				//使用方法:直接書き込み.

	//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧの作成.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			ppConstantBuffer ) ) ){
		_ASSERT_EXPR( false, L"ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧ作成失敗" );
		return E_FAIL;
	}

	return S_OK;
}

//ﾓﾃﾞﾙ作成.
HRESULT CSprite::InitModel()
{
	float w = m_SState.Disp.w;	// 表示スプライト幅,
	float h = m_SState.Disp.h;	// 表示スプライト高さ,
	float u = m_SState.Stride.w / m_SState.Base.w;	// 1コマ当たりの幅,
	float v = m_SState.Stride.h / m_SState.Base.h;	// 1コマ当たりの高さ.
	
	//-------------------------------.
	// UI用.
	//-------------------------------.
	//板ﾎﾟﾘ(四角形)の頂点を作成.
	VERTEX verticesUI[] =
	{
		// ポリゴンの中心を頂点とする.
		//頂点座標(x,y,z)				 UV座標(u,v)
		D3DXVECTOR3( -w / 2,  h / 2, 0.0f ), D3DXVECTOR2( 0.0f,    v ),	//頂点１(左下).
		D3DXVECTOR3( -w / 2, -h / 2, 0.0f ), D3DXVECTOR2( 0.0f, 0.0f ),	//頂点２(左上).
		D3DXVECTOR3(  w / 2,  h / 2, 0.0f ), D3DXVECTOR2(    u,    v ),	//頂点３(右下).
		D3DXVECTOR3(  w / 2, -h / 2, 0.0f ), D3DXVECTOR2(    u, 0.0f )	//頂点４(右上).
	};
	InitVertex( &m_pVertexBufferUI, verticesUI );

	//-------------------------------.
	// 3D用.
	//-------------------------------.
	int as = myGcd( (int)m_SState.Disp.w, (int)m_SState.Disp.h );
	w = m_SState.Disp.w / as;
	h = m_SState.Disp.h / as;
	//板ﾎﾟﾘ(四角形)の頂点を作成.
	VERTEX vertices[] =
	{
		// ポリゴンの中心を頂点とする.
		//頂点座標(x,y,z)				 UV座標(u,v)
		D3DXVECTOR3( -w / 2, -h / 2, 0.0f ), D3DXVECTOR2( 0.0f,    v ),	//頂点１(左下).
		D3DXVECTOR3( -w / 2,  h / 2, 0.0f ), D3DXVECTOR2( 0.0f, 0.0f ),	//頂点２(左上).
		D3DXVECTOR3(  w / 2, -h / 2, 0.0f ), D3DXVECTOR2(    u,    v ),	//頂点３(右下).
		D3DXVECTOR3(  w / 2,  h / 2, 0.0f ), D3DXVECTOR2(    u, 0.0f )	//頂点４(右上).
	};
	InitVertex( &m_pVertexBuffer, vertices );
	
	InitSample();

	return S_OK;
}

HRESULT CSprite::InitVertex( ID3D11Buffer** ppVertxtBuffer, VERTEX* pVertex )
{
	//ﾊﾞｯﾌｧ構造体.
	D3D11_BUFFER_DESC bd;
	bd.Usage				= D3D11_USAGE_DEFAULT;			// 使用方法(ﾃﾞﾌｫﾙﾄ).
	bd.ByteWidth			= sizeof(VERTEX) * 4;			// 頂点のｻｲｽﾞ.
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;		// 頂点ﾊﾞｯﾌｧとして扱う.
	bd.CPUAccessFlags		= 0;							// CPUからはｱｸｾｽしない.
	bd.MiscFlags			= 0;							// その他のﾌﾗｸﾞ(未使用).
	bd.StructureByteStride	= 0;							// 構造体のｻｲｽﾞ(未使用).

	// ｻﾌﾞﾘｿｰｽﾃﾞｰﾀ構造体.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pVertex;	//板ﾎﾟﾘの頂点をｾｯﾄ.

	// 頂点ﾊﾞｯﾌｧの作成.
	if( FAILED( m_pDevice11->CreateBuffer(
		&bd, &InitData, ppVertxtBuffer ) ) ){
		_ASSERT_EXPR( false, L"頂点ﾊﾞｯﾌｧ作成失敗" );
		return E_FAIL;
	}

	//頂点ﾊﾞｯﾌｧをｾｯﾄ.
	UINT stride = sizeof( VERTEX );	//ﾃﾞｰﾀ間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1,
		ppVertxtBuffer, &stride, &offset );

	return S_OK;
}

HRESULT CSprite::InitSample()
{
	// テクスチャ用のサンプラ構造体.
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory( &samDesc, sizeof( samDesc ) );
	samDesc.Filter		= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;
	// サンプラ作成.
	if( FAILED( m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear ) ) )
	{
		ERROR_MESSAGE( "サンプラ作成失敗" );
		return E_FAIL;
	}

	return S_OK;
}

// テクスチャ作成.
HRESULT CSprite::CreateTexture( const char* fileName,
	ID3D11ShaderResourceView** pTexture )
{
	//ﾃｸｽﾁｬ作成.
	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,	//ﾘｿｰｽを使用するﾃﾞﾊﾞｲｽのﾎﾟｲﾝﾀ.
		fileName,		//ﾌｧｲﾙ名.
		nullptr, nullptr,
		pTexture,		//(out)ﾃｸｽﾁｬ.
		nullptr ) ) ){
		_ASSERT_EXPR( false, L"ﾃｸｽﾁｬ作成失敗" );
		return E_FAIL;
	}

	return S_OK;
}

//ﾚﾝﾀﾞﾘﾝｸﾞ用.
void CSprite::Render( const D3DXMATRIX& mView, const D3DXMATRIX& mProj )
{
	//　ワールド行列, スケール行列, 回転行列, 平行移動行列.
	D3DXMATRIX mWorld, mScale, mRot, mTran;

	// 拡大縮小行列作成.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, 1.0f );
	// 回転行列を作成.
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	// 平行移動行列.
	D3DXMatrixTranslation( &mTran, m_vPos.x, m_vPos.y, m_vPos.z );
	// ワールド行列作成.
	mWorld = mScale * mRot * mTran;

	//使用するｼｪｰﾀﾞの登録.
	m_pContext11->VSSetShader( m_pVertexShader, nullptr, 0 );
	m_pContext11->PSSetShader( m_pPixelShader, nullptr, 0 );

	//ｼｪｰﾀﾞのｺﾝｽﾀﾝﾄﾊﾞｯﾌｧに各種ﾃﾞｰﾀを渡す.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cb;
	//ﾊﾞｯﾌｧ内のﾃﾞｰﾀの書き換え開始時にmap.
	if( SUCCEEDED(
		m_pContext11->Map( m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) ){
		//ﾜｰﾙﾄﾞ行列を渡す.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose( &m, &m );//行列を転置する.
		cb.mWVP = m;

		// ビューポートの幅,高さを渡す.
		cb.fViewPortWidth	= static_cast<float>(WND_W);
		cb.fViewPortHeight	= static_cast<float>(WND_H);

		// アルファ値を渡す.
		cb.fAlpha = m_fAlpha;

		cb.vUV.x = 1.0f;
		cb.vUV.y = 1.0f;
		
		memcpy_s( 
			pData.pData, 
			pData.RowPitch,
			(void*)(&cb),
			sizeof(cb) );

		m_pContext11->Unmap( m_pConstantBuffer, 0 );
	}
	//このｺﾝｽﾀﾝﾄﾊﾞｯﾌｧをどのｼｪｰﾀﾞで使うか？.
	m_pContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

	//頂点ﾊﾞｯﾌｧをｾｯﾄ.
	UINT stride = sizeof( VERTEX );//ﾃﾞｰﾀの間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers( 0, 1,
		&m_pVertexBuffer, &stride, &offset );

	//頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄをｾｯﾄ.
	m_pContext11->IASetInputLayout( m_pVertexLayout );
	//ﾌﾟﾘﾐﾃｨﾌﾞ・ﾄﾎﾟﾛｼﾞｰをｾｯﾄ.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//ﾃｸｽﾁｬをｼｪｰﾀﾞに渡す.
	m_pContext11->PSSetSamplers( 0, 1, &m_pSampleLinear );
	m_pContext11->PSSetShaderResources( 0, 1, &m_pTexture );

	//ﾌﾟﾘﾐﾃｨﾌﾞをﾚﾝﾀﾞﾘﾝｸﾞ.
	m_pContext11->Draw( 4, 0 );//板ﾎﾟﾘ(頂点4つ分).
}

void CSprite::RenderUI()
{
	//　ワールド行列, スケール行列, 回転行列, 平行移動行列.
	D3DXMATRIX mWorld, mScale, mRot, mTran;

	// 拡大縮小行列作成.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, 1.0f );
	// 回転行列を作成.
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	// 平行移動行列.
	D3DXMatrixTranslation( &mTran, m_vPos.x, m_vPos.y, 0.0f );
	// ワールド行列作成.
	mWorld = mScale * mRot * mTran;

	//使用するｼｪｰﾀﾞの登録.
	m_pContext11->VSSetShader( m_pVertexShaderUI, nullptr, 0 );
	m_pContext11->PSSetShader( m_pPixelShader, nullptr, 0 );

	//ｼｪｰﾀﾞのｺﾝｽﾀﾝﾄﾊﾞｯﾌｧに各種ﾃﾞｰﾀを渡す.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cb;
	//ﾊﾞｯﾌｧ内のﾃﾞｰﾀの書き換え開始時にmap.
	if( SUCCEEDED(
		m_pContext11->Map( m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) ){
		//ﾜｰﾙﾄﾞ行列を渡す.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose( &m, &m );//行列を転置する.
		cb.mW = m;

		// ビューポートの幅,高さを渡す.
		cb.fViewPortWidth	= static_cast<float>(WND_W);
		cb.fViewPortHeight	= static_cast<float>(WND_H);

		// アルファ値を渡す.
		cb.fAlpha = m_fAlpha;

		cb.vUV.x = 1.0f;
		cb.vUV.y = 1.0f;

		memcpy_s( 
			pData.pData, 
			pData.RowPitch,
			(void*)(&cb),
			sizeof(cb) );

		m_pContext11->Unmap( m_pConstantBuffer, 0 );
	}
	//このｺﾝｽﾀﾝﾄﾊﾞｯﾌｧをどのｼｪｰﾀﾞで使うか？.
	m_pContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

	//頂点ﾊﾞｯﾌｧをｾｯﾄ.
	UINT stride = sizeof( VERTEX );//ﾃﾞｰﾀの間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers( 0, 1,
		&m_pVertexBufferUI, &stride, &offset );

	//頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄをｾｯﾄ.
	m_pContext11->IASetInputLayout( m_pVertexLayout );
	//ﾌﾟﾘﾐﾃｨﾌﾞ・ﾄﾎﾟﾛｼﾞｰをｾｯﾄ.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//ﾃｸｽﾁｬをｼｪｰﾀﾞに渡す.
	m_pContext11->PSSetSamplers( 0, 1, &m_pSampleLinear );
	m_pContext11->PSSetShaderResources( 0, 1, &m_pTexture );

	//ﾌﾟﾘﾐﾃｨﾌﾞをﾚﾝﾀﾞﾘﾝｸﾞ.
	m_pContext11->Draw( 4, 0 );//板ﾎﾟﾘ(頂点4つ分).
}