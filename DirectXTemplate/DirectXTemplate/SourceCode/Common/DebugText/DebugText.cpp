#include "DebugText.h"
#include "..\Shader\DebugTextShader\DebugTextShader.h"

CDebugText::CDebugText()
	: m_pVertexBuffer	()
	, m_pSampleLinear	( nullptr )
	, m_pAsciiTexture	( nullptr )
	, m_pShader			( std::make_unique<CDebugTextShader>() )
	, m_fKerning		()
	, m_vColor			( 0.0f, 0.0f, 0.0f, 0.0f )
{
}

CDebugText::~CDebugText()
{
}

//----------------------------.
// �C���X�^���X�̎擾.
//----------------------------.
CDebugText* CDebugText::GetInstance()
{
	static std::unique_ptr<CDebugText> pInstance =
		std::make_unique<CDebugText>();	// �C���X�^���X�̍쐬.
	return pInstance.get();
}

//----------------------------.
// �������֐�.
//----------------------------.
HRESULT CDebugText::Init(
	ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11,
	float Scale, 
	D3DXVECTOR4 vColor )
{
	GetInstance()->InitPram( pDevice11, pContext11 );

	if( FAILED( GetInstance()->m_pShader->Init( pDevice11, pContext11 ))){
		return E_FAIL;
	}
	if( FAILED( GetInstance()->InitModel())) return E_FAIL;
	if( FAILED( GetInstance()->InitSampleLinear())) return E_FAIL;
	if( FAILED( GetInstance()->InitTexture())) return E_FAIL;

	GetInstance()->m_fAlpha = vColor.w;
	GetInstance()->m_vColor = vColor;
	GetInstance()->m_fScale = Scale / 25.0f;

	return S_OK;
}

//----------------------------.
// �`��֐�.
//----------------------------.
void CDebugText::Render( const std::string& stext )
{
	// �����������[�v.
	for( int i = 0; i < static_cast<int>(stext.length()); i++ ){
		char font = stext[i];
		int index = font - 32;	// �t�H���g�C���f�b�N�X�쐬.

		// �t�H���g�����_�����O.
		GetInstance()->RenderFont( index, GetInstance()->m_vPos.x, GetInstance()->m_vPos.y );
		GetInstance()->m_vPos.x += GetInstance()->m_fKerning[index] * GetInstance()->m_fScale;
	}
}

//----------------------------.
// �t�H���g�����_�����O�֐�.
//----------------------------.
void CDebugText::RenderFont( int FontIndex, float x, float y )
{
	D3DXMATRIX mWorld, mView, mProj;
	D3DXMATRIX mScale, mTran;
	D3DXMatrixIdentity( &mWorld );
	D3DXMatrixIdentity( &mProj );

	// �r���[�g�����X�t�H�[��.
	D3DXVECTOR3 vEye( 0.0f, 0.0f, -1.0f );
	D3DXVECTOR3 vLook( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUp( 0.0f, 1.0f, 0.0f );
	D3DXMatrixLookAtLH( &mView, &vEye, &vLook, &vUp );

	mProj._11 =  2.0f / static_cast<float>(WND_W);
	mProj._22 = -2.0f / static_cast<float>(WND_H);
	mProj._41 = -1.0f;
	mProj._42 =  1.0f;

	// ���s�ړ�.
	D3DXMatrixTranslation( &mTran, x,  y, -100.0f );

	// �g��k���s��쐬.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, m_fScale );
	mWorld = mScale * mTran;

	D3DXMATRIX mWVP = mWorld * mView * mProj;

	m_pShader->SetConstantBufferData( mWVP, m_vColor );
	m_pShader->ShaderSet( m_pVertexBuffer[FontIndex], m_pSampleLinear, m_pAsciiTexture );

	// �v���~�e�B�u�g�|���W�[.
	m_pContext11->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	//�`��.
	SetBlend( true );
	SetRasterizerState( enRS_STATE::Back );
	m_pContext11->Draw( 4, 0 );
	SetRasterizerState( enRS_STATE::None );
	SetBlend( false );
}

//----------------------------.
// ���f���̍쐬.
//----------------------------.
HRESULT CDebugText::InitModel()
{
	// 95�������J��Ԃ�.
	for( int i = 0; i < 95; i++ ){
		m_fKerning[i] = 10.0f;
	}

	float left = 0.0f, top = 0.0f, right = 0.0f, bottom = 0.0f;
	int cnt = 0;
	// 2�d���[�v��1�������w�肷��.
	for( int k = 0; k < 10; k++ ){
		for( int i = 0; i < 10; i++ ){
			left	= (k * WDIMENSION);
			top		= (i * DIMENSION);
			right	= (left + m_fKerning[cnt]);
			bottom	= (top + DIMENSION);

			left	/= TEX_DIMENSION;
			top		/= TEX_DIMENSION;
			right	/= TEX_DIMENSION;
			bottom	/= TEX_DIMENSION;

			CDebugTextShader::VERTEX vertices[] =
			{
				D3DXVECTOR3( 0.0f,       DIMENSION, 0.0f ),	D3DXVECTOR2( left,  bottom ),
				D3DXVECTOR3( 0.0f,       0.0f,      0.0f ),	D3DXVECTOR2( left,  top ),
				D3DXVECTOR3( WDIMENSION, DIMENSION, 0.0f ),	D3DXVECTOR2( right, bottom ),
				D3DXVECTOR3( WDIMENSION, 0.0f,      0.0f ),	D3DXVECTOR2( right, top )
			};
			// �ő�v�f�����Z�o����.
			UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

			// �o�b�t�@�\����.
			D3D11_BUFFER_DESC bd;
			bd.Usage				= D3D11_USAGE_DEFAULT;		// �g�p���@.
			bd.ByteWidth			= sizeof(CDebugTextShader::VERTEX)*uVerMax;	//���_�̃T�C�Y.
			bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@�Ƃ��Ĉ���.
			bd.CPUAccessFlags		= 0;		// CPU����̓A�N�Z�X���Ȃ�.
			bd.MiscFlags			= 0;		// ���̑��̃t���O(���g�p).
			bd.StructureByteStride	= 0;		// �\���̂̃T�C�Y(���g�p).

			// �T�u���\�[�X�f�[�^�\����.
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;		// �|���̒��_���Z�b�g.

			// ���_�o�b�t�@�̍쐬.
			if( FAILED( m_pDevice11->CreateBuffer(
				&bd, &InitData, &m_pVertexBuffer[cnt] ) ) ){
				_ASSERT_EXPR( false, L"���_�ޯ̧�쐬���s" );
				return E_FAIL;
			}
			cnt++;
		}
	}
	return S_OK;
}

//----------------------------.
// �T���v���̍쐬.
//----------------------------.
HRESULT CDebugText::InitSampleLinear()
{
	// �e�N�X�`���p�̃T���v���\����.
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory( &samDesc, sizeof( samDesc ) );
	samDesc.Filter		= D3D11_FILTER_MIN_MAG_MIP_POINT;	// POINT:���������e��.
	samDesc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;		// ���b�s���O(WRAP:�J��Ԃ�).
	samDesc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;

	// �T���v���쐬.
	if( FAILED( m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear ))){ // (out)�T���v��.
		_ASSERT_EXPR( false, L"����׍쐬���s" );
		return E_FAIL;
	}
	return S_OK;
}

//----------------------------.
// �e�N�X�`���쐬.
//----------------------------.
HRESULT CDebugText::InitTexture()
{
	// �e�N�X�`���쐬.
	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,					// ���\�[�X���g�p����f�o�C�X�̃|�C���^.
		"Data\\DebugText\\ascii.png",	// �t�@�C����.
		nullptr, 
		nullptr,
		&m_pAsciiTexture,
		nullptr ))){
		_ASSERT_EXPR( false, L"ø����쐬���s" );
		return E_FAIL;
	}
	return S_OK;
}