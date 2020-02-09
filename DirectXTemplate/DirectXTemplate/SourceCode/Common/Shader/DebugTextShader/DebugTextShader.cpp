#include "DebugTextShader.h"

CDebugTextShader::CDebugTextShader()
{
}

CDebugTextShader::~CDebugTextShader()
{
}

//--------------------------------------.
// ������.
//--------------------------------------.
HRESULT CDebugTextShader::Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	if( FAILED( InitShader())) return E_FAIL;

	return S_OK;
}

//--------------------------------------.
// ���.
//--------------------------------------.
HRESULT CDebugTextShader::Release()
{
	SAFE_RELEASE( m_pVertexShader );
	SAFE_RELEASE( m_pPixelShader );
	SAFE_RELEASE( m_pVertexLayout );
	SAFE_RELEASE( m_pConstantBuffer );

	m_pDevice11 = nullptr;
	m_pContext11 = nullptr;

	return S_OK;
}

//--------------------------------------.
// �R���X�^���g�o�b�t�@�Ƀf�[�^��n��.
//--------------------------------------.
void CDebugTextShader::SetConstantBufferData( const D3DXMATRIX& mWVP, const D3DXVECTOR4& color )
{
	// �V�F�[�_�[�̃R���X�^���g�o�b�t�@�Ɋe��f�[�^��n��.
	D3D11_MAPPED_SUBRESOURCE pData;
	C_BUFFER cb;	// �R���X�^���g�o�b�t�@.

	if( SUCCEEDED(
		m_pContext11->Map( m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) ){

		cb.mWVP = mWVP;
		cb.vColor = color;
		cb.fAlpha.x = color.w;

		D3DXMatrixTranspose( &cb.mWVP, &cb.mWVP );

		memcpy_s( pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb) );

		m_pContext11->Unmap( m_pConstantBuffer, 0 );
	}
}

//--------------------------------------.
// �e��V�F�[�_�̐ݒ�.
//--------------------------------------.
void CDebugTextShader::ShaderSet( ID3D11Buffer* pVertexBuffer, ID3D11SamplerState* pSampleLinear, ID3D11ShaderResourceView* pAsciiTexture )
{
	// �g�p����V�F�[�_�̃Z�b�g.
	m_pContext11->VSSetShader( m_pVertexShader, nullptr, 0 );	// ���_�V�F�[�_.
	m_pContext11->PSSetShader( m_pPixelShader, nullptr, 0 );	// �s�N�Z���V�F�[�_.

	// ���̃R���X�^���g�o�b�t�@���ǂ̃V�F�[�_�Ŏg�p���邩�H.
	m_pContext11->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );	// ���_�V�F�[�_.
	m_pContext11->PSSetConstantBuffers( 0, 1, &m_pConstantBuffer );	// �s�N�Z���V�F�[�_�[.

	// ���_�o�b�t�@���Z�b�g.
	UINT stride = sizeof(VERTEX); // �f�[�^�̊Ԋu.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers( 0, 1, &pVertexBuffer, &stride, &offset );
	m_pContext11->PSSetSamplers( 0, 1, &pSampleLinear );
	m_pContext11->PSSetShaderResources( 0, 1, &pAsciiTexture );

	// ���_�C���v�b�g���C�A�E�g���Z�b�g.
	m_pContext11->IASetInputLayout( m_pVertexLayout );
}

//--------------------------------------.
// �V�F�[�_�[�쐬.
//--------------------------------------.
HRESULT CDebugTextShader::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	// #ifdef _DEBUG

	// HLSL����o�[�e�b�N�X�V�F�[�_�[�̃u���u���쐬.
	if( FAILED( CShaderBase::InitShader(
			SHADER_NAME,
			"VS_Main",
			"vs_5_0",
			uCompileFlag,
			&pCompiledShader,
			&pErrors ))){
		_ASSERT_EXPR( false, L"hlsl�ǂݍ��ݎ��s" );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//�@��L�ō쐬�����u���u����o�[�e�b�N�X�V�F�[�_�[���쐬.
	if( FAILED(
		CShaderBase::CreateVertexShader( pCompiledShader, &m_pVertexShader ))){
		_ASSERT_EXPR( false, L"�ްï������ލ쐬���s" );
		return E_FAIL;
	}

	//���_���߯�ڲ��Ă��`.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		CShaderBase::GetPositionInputElement(),
		{
			"TEXCOORD",						//ø����ʒu.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGI��̫�ϯ�(32bit float�^*2).
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,	//�ް��̊J�n�ʒu.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};
	// ���_�C���v�b�g���C�A�E�g�̔z��v�f�����Z�o.
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	// ���_�C���v�b�g���C�A�E�g���쐬.
	if( FAILED(
		CShaderBase::CreateInputLayout( 
			layout,
			numElements,
			pCompiledShader,
			&m_pVertexLayout ))){
		_ASSERT_EXPR( false, L"���_���߯�ڲ��č쐬���s" );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );

	// HLSL����s�N�Z���V�F�[�_�[�̃u���u���쐬.
	if( FAILED(
		CShaderBase::InitShader(
			SHADER_NAME,
			"PS_Main",
			"ps_5_0",
			uCompileFlag,
			&pCompiledShader,
			&pErrors ))){
		_ASSERT_EXPR( false, L"hlsl�ǂݍ��ݎ��s" );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	// ��L�ō쐬�����u���u����s�N�Z���V�F�[�_�[���쐬.
	if( FAILED(
		CShaderBase::CreatePixelShader( pCompiledShader, &m_pPixelShader ))){
		_ASSERT_EXPR( false, L"�߸�ټ���ލ쐬���s" );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );

	// �R���X�^���g(�萔)�o�b�t�@�쐬.
	if( FAILED( CShaderBase::CreateConstantBuffer( &m_pConstantBuffer, sizeof(C_BUFFER) ))){
		_ASSERT_EXPR( false, L"�ݽ����ޯ̧�쐬���s" );
		return E_FAIL;
	}

	return S_OK;
}