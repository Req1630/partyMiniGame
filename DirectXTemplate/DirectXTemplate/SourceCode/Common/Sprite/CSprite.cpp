#include "CSprite.h"
#include <crtdbg.h>
#include <algorithm>

// �V�F�[�_�t�@�C����(�f�B���N�g�����܂�).
const char SHADER_NAME[] = "Data\\Shader\\Sprite.hlsl";


//�ݽ�׸�.
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

//�޽�׸�.
CSprite::~CSprite()
{
	Release();
}

//������.
HRESULT CSprite::Init( ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	const char* fileName, const SPRITE_STATE& pSs )
{
	m_SState = pSs;
	m_vPos = m_SState.vPos;
	if( FAILED( InitPram( pDevice11, pContext11 )) ){
		return E_FAIL;
	}
	//����ލ쐬.
	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	//����غ�ݍ쐬.
	if( FAILED( InitModel() ) ){
		return E_FAIL;
	}
	// �e�N�X�`���쐬.
	if( FAILED( CreateTexture( fileName, &m_pTexture ))){
		return E_FAIL;
	}

	return S_OK;
}

//���.
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
//	HLSĻ�ق�ǂݍ��ݼ���ނ��쐬����.
//	HLSL: High Level Shading Language �̗�.
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

	//HLSL�����ްï������ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			nullptr,		//ϸے�`�̔z��ւ��߲��(���g�p).
			nullptr,		//�ݸٰ��̧�ق���������̪���ւ��߲��(���g�p).
			"VS_MainUI",	//����޴��ذ�߲�Ċ֐��̖��O.
			"vs_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,				//�̪�ĺ��߲��׸�(���g�p).
			nullptr,		//�گ�� ����� ����̪���ւ��߲��(���g�p).
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,		//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
			nullptr ) ) )		//�߂�l�ւ��߲��(���g�p).
	{
		_ASSERT_EXPR( false, L"hlsl�ǂݍ��ݎ��s" );
		return E_FAIL;
	}
	
	//��L�ō쐬��������ނ���u�ްï������ށv���쐬.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShaderUI ) ) )	//(out)�ްï�������.
	{
		_ASSERT_EXPR( false, L"�ްï������ލ쐬���s" );
		return E_FAIL;
	}
	//HLSL�����ްï������ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			nullptr,		//ϸے�`�̔z��ւ��߲��(���g�p).
			nullptr,		//�ݸٰ��̧�ق���������̪���ւ��߲��(���g�p).
			"VS_Main",	//����޴��ذ�߲�Ċ֐��̖��O.
			"vs_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,				//�̪�ĺ��߲��׸�(���g�p).
			nullptr,		//�گ�� ����� ����̪���ւ��߲��(���g�p).
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,		//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
			nullptr ) ) )		//�߂�l�ւ��߲��(���g�p).
	{
		_ASSERT_EXPR( false, L"hlsl�ǂݍ��ݎ��s" );
		return E_FAIL;
	}

	//��L�ō쐬��������ނ���u�ްï������ށv���쐬.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader ) ) )	//(out)�ްï�������.
	{
		_ASSERT_EXPR( false, L"�ްï������ލ쐬���s" );
		return E_FAIL;
	}
	InitVertexLayout( pCompiledShader );
	SAFE_RELEASE( pErrors );
	SAFE_RELEASE( pCompiledShader );

	//HLSL�����߸�ټ���ނ�����ނ��쐬.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�����̧�ٖ�(HLSĻ��).
			nullptr,		//ϸے�`�̔z��ւ��߲��(���g�p).
			nullptr,		//�ݸٰ��̧�ق���������̪���ւ��߲��(���g�p).
			"PS_Main",		//����޴��ذ�߲�Ċ֐��̖��O.
			"ps_5_0",		//����ނ����ق��w�肷�镶����(���̧��).
			uCompileFlag,	//����޺��߲��׸�.
			0,				//�̪�ĺ��߲��׸�(���g�p).
			nullptr,		//�گ�� ����� ����̪���ւ��߲��(���g�p).
			&pCompiledShader,//����ނ��i�[������؂ւ��߲��.
			&pErrors,		//�װ�ƌx���ꗗ���i�[������؂ւ��߲��.
			nullptr ) ) )		//�߂�l�ւ��߲��(���g�p).
	{
		_ASSERT_EXPR( false, L"hlsl�ǂݍ��ݎ��s" );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//��L�ō쐬��������ނ���u�߸�ټ���ށv���쐬.
	if( FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader ) ) )	//(out)�߸�ټ����.
	{
		_ASSERT_EXPR( false, L"�߸�ټ���ލ쐬���s" );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );

	InitConstantBuffer( &m_pConstantBuffer, sizeof(SHADER_CONSTANT_BUFFER) );


	return S_OK;
}

HRESULT CSprite::InitVertexLayout( ID3DBlob* pCompiledShader )
{
	//���_���߯�ڲ��Ă��`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//�ʒu.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI��̫�ϯ�(32bit float�^*3).
			0,
			0,								//�ް��̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",						//ø����ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGI��̫�ϯ�(32bit float�^*2).
			0,
			12,								//�ް��̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	//���_���߯�ڲ��Ă̔z��v�f�����Z�o.
	UINT numElements = sizeof( layout ) / sizeof( layout[0] );

	//���_���߯�ڲ��Ă��쐬.
	if( FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout ) ) )	//(out)���_���߯�ڲ���.
	{
		_ASSERT_EXPR( false, L"���_���߯�ڲ��č쐬���s" );
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSprite::InitConstantBuffer( ID3D11Buffer** ppConstantBuffer, UINT size )
{
	//�ݽ���(�萔)�ޯ̧�쐬.
	//����ނɓ���̐��l�𑗂��ޯ̧.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;		//�ݽ����ޯ̧���w��.
	cb.ByteWidth			= size;								//�ݽ����ޯ̧�̻���.
	cb.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;			//�������݂ű���.
	cb.MiscFlags			= 0;								//���̑����׸�(���g�p).
	cb.StructureByteStride	= 0;								//�\���̻̂���(���g�p).
	cb.Usage				= D3D11_USAGE_DYNAMIC;				//�g�p���@:���ڏ�������.

	//�ݽ����ޯ̧�̍쐬.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			ppConstantBuffer ) ) ){
		_ASSERT_EXPR( false, L"�ݽ����ޯ̧�쐬���s" );
		return E_FAIL;
	}

	return S_OK;
}

//���ٍ쐬.
HRESULT CSprite::InitModel()
{
	float w = m_SState.Disp.w;	// �\���X�v���C�g��,
	float h = m_SState.Disp.h;	// �\���X�v���C�g����,
	float u = m_SState.Stride.w / m_SState.Base.w;	// 1�R�}������̕�,
	float v = m_SState.Stride.h / m_SState.Base.h;	// 1�R�}������̍���.
	
	//-------------------------------.
	// UI�p.
	//-------------------------------.
	//�����(�l�p�`)�̒��_���쐬.
	VERTEX verticesUI[] =
	{
		// �|���S���̒��S�𒸓_�Ƃ���.
		//���_���W(x,y,z)				 UV���W(u,v)
		D3DXVECTOR3( -w / 2,  h / 2, 0.0f ), D3DXVECTOR2( 0.0f,    v ),	//���_�P(����).
		D3DXVECTOR3( -w / 2, -h / 2, 0.0f ), D3DXVECTOR2( 0.0f, 0.0f ),	//���_�Q(����).
		D3DXVECTOR3(  w / 2,  h / 2, 0.0f ), D3DXVECTOR2(    u,    v ),	//���_�R(�E��).
		D3DXVECTOR3(  w / 2, -h / 2, 0.0f ), D3DXVECTOR2(    u, 0.0f )	//���_�S(�E��).
	};
	InitVertex( &m_pVertexBufferUI, verticesUI );

	//-------------------------------.
	// 3D�p.
	//-------------------------------.
	int as = myGcd( (int)m_SState.Disp.w, (int)m_SState.Disp.h );
	w = m_SState.Disp.w / as;
	h = m_SState.Disp.h / as;
	//�����(�l�p�`)�̒��_���쐬.
	VERTEX vertices[] =
	{
		// �|���S���̒��S�𒸓_�Ƃ���.
		//���_���W(x,y,z)				 UV���W(u,v)
		D3DXVECTOR3( -w / 2, -h / 2, 0.0f ), D3DXVECTOR2( 0.0f,    v ),	//���_�P(����).
		D3DXVECTOR3( -w / 2,  h / 2, 0.0f ), D3DXVECTOR2( 0.0f, 0.0f ),	//���_�Q(����).
		D3DXVECTOR3(  w / 2, -h / 2, 0.0f ), D3DXVECTOR2(    u,    v ),	//���_�R(�E��).
		D3DXVECTOR3(  w / 2,  h / 2, 0.0f ), D3DXVECTOR2(    u, 0.0f )	//���_�S(�E��).
	};
	InitVertex( &m_pVertexBuffer, vertices );
	
	InitSample();

	return S_OK;
}

HRESULT CSprite::InitVertex( ID3D11Buffer** ppVertxtBuffer, VERTEX* pVertex )
{
	//�ޯ̧�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage				= D3D11_USAGE_DEFAULT;			// �g�p���@(��̫��).
	bd.ByteWidth			= sizeof(VERTEX) * 4;			// ���_�̻���.
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;		// ���_�ޯ̧�Ƃ��Ĉ���.
	bd.CPUAccessFlags		= 0;							// CPU����ͱ������Ȃ�.
	bd.MiscFlags			= 0;							// ���̑����׸�(���g�p).
	bd.StructureByteStride	= 0;							// �\���̻̂���(���g�p).

	// ���ؿ���ް��\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pVertex;	//����؂̒��_���.

	// ���_�ޯ̧�̍쐬.
	if( FAILED( m_pDevice11->CreateBuffer(
		&bd, &InitData, ppVertxtBuffer ) ) ){
		_ASSERT_EXPR( false, L"���_�ޯ̧�쐬���s" );
		return E_FAIL;
	}

	//���_�ޯ̧���.
	UINT stride = sizeof( VERTEX );	//�ް��Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1,
		ppVertxtBuffer, &stride, &offset );

	return S_OK;
}

HRESULT CSprite::InitSample()
{
	// �e�N�X�`���p�̃T���v���\����.
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory( &samDesc, sizeof( samDesc ) );
	samDesc.Filter		= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;
	// �T���v���쐬.
	if( FAILED( m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear ) ) )
	{
		ERROR_MESSAGE( "�T���v���쐬���s" );
		return E_FAIL;
	}

	return S_OK;
}

// �e�N�X�`���쐬.
HRESULT CSprite::CreateTexture( const char* fileName,
	ID3D11ShaderResourceView** pTexture )
{
	//ø����쐬.
	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,	//ؿ�����g�p�������޲����߲��.
		fileName,		//̧�ٖ�.
		nullptr, nullptr,
		pTexture,		//(out)ø���.
		nullptr ) ) ){
		_ASSERT_EXPR( false, L"ø����쐬���s" );
		return E_FAIL;
	}

	return S_OK;
}

//�����ݸޗp.
void CSprite::Render( const D3DXMATRIX& mView, const D3DXMATRIX& mProj )
{
	//�@���[���h�s��, �X�P�[���s��, ��]�s��, ���s�ړ��s��.
	D3DXMATRIX mWorld, mScale, mRot, mTran;

	// �g��k���s��쐬.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, 1.0f );
	// ��]�s����쐬.
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	// ���s�ړ��s��.
	D3DXMatrixTranslation( &mTran, m_vPos.x, m_vPos.y, m_vPos.z );
	// ���[���h�s��쐬.
	mWorld = mScale * mRot * mTran;

	//�g�p���鼪��ނ̓o�^.
	m_pContext11->VSSetShader( m_pVertexShader, nullptr, 0 );
	m_pContext11->PSSetShader( m_pPixelShader, nullptr, 0 );

	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cb;
	//�ޯ̧�����ް��̏��������J�n����map.
	if( SUCCEEDED(
		m_pContext11->Map( m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) ){
		//ܰ��ލs���n��.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose( &m, &m );//�s���]�u����.
		cb.mWVP = m;

		// �r���[�|�[�g�̕�,������n��.
		cb.fViewPortWidth	= static_cast<float>(WND_W);
		cb.fViewPortHeight	= static_cast<float>(WND_H);

		// �A���t�@�l��n��.
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
	//���̺ݽ����ޯ̧���ǂ̼���ނŎg�����H.
	m_pContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

	//���_�ޯ̧���.
	UINT stride = sizeof( VERTEX );//�ް��̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers( 0, 1,
		&m_pVertexBuffer, &stride, &offset );

	//���_���߯�ڲ��Ă��.
	m_pContext11->IASetInputLayout( m_pVertexLayout );
	//����è�ށE���ۼް���.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//ø����𼪰�ނɓn��.
	m_pContext11->PSSetSamplers( 0, 1, &m_pSampleLinear );
	m_pContext11->PSSetShaderResources( 0, 1, &m_pTexture );

	//����è�ނ������ݸ�.
	m_pContext11->Draw( 4, 0 );//�����(���_4��).
}

void CSprite::RenderUI()
{
	//�@���[���h�s��, �X�P�[���s��, ��]�s��, ���s�ړ��s��.
	D3DXMATRIX mWorld, mScale, mRot, mTran;

	// �g��k���s��쐬.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, 1.0f );
	// ��]�s����쐬.
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.x, m_vRot.y, m_vRot.z );
	// ���s�ړ��s��.
	D3DXMatrixTranslation( &mTran, m_vPos.x, m_vPos.y, 0.0f );
	// ���[���h�s��쐬.
	mWorld = mScale * mRot * mTran;

	//�g�p���鼪��ނ̓o�^.
	m_pContext11->VSSetShader( m_pVertexShaderUI, nullptr, 0 );
	m_pContext11->PSSetShader( m_pPixelShader, nullptr, 0 );

	//����ނ̺ݽ����ޯ̧�Ɋe���ް���n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cb;
	//�ޯ̧�����ް��̏��������J�n����map.
	if( SUCCEEDED(
		m_pContext11->Map( m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) ){
		//ܰ��ލs���n��.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose( &m, &m );//�s���]�u����.
		cb.mW = m;

		// �r���[�|�[�g�̕�,������n��.
		cb.fViewPortWidth	= static_cast<float>(WND_W);
		cb.fViewPortHeight	= static_cast<float>(WND_H);

		// �A���t�@�l��n��.
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
	//���̺ݽ����ޯ̧���ǂ̼���ނŎg�����H.
	m_pContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	m_pContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

	//���_�ޯ̧���.
	UINT stride = sizeof( VERTEX );//�ް��̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers( 0, 1,
		&m_pVertexBufferUI, &stride, &offset );

	//���_���߯�ڲ��Ă��.
	m_pContext11->IASetInputLayout( m_pVertexLayout );
	//����è�ށE���ۼް���.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//ø����𼪰�ނɓn��.
	m_pContext11->PSSetSamplers( 0, 1, &m_pSampleLinear );
	m_pContext11->PSSetShaderResources( 0, 1, &m_pTexture );

	//����è�ނ������ݸ�.
	m_pContext11->Draw( 4, 0 );//�����(���_4��).
}