#include "Toon.h"

CToon::CToon()
	: m_pDevice11		( nullptr )
	, m_pVertexShader	( nullptr )
	, m_pVertexLayout	( nullptr )
	, m_pPixelShader	( nullptr )
	, m_pToonTexture	( nullptr )
{
}

CToon::~CToon()
{
}

HRESULT CToon::InitShader()
{
	

	return S_OK;
}

HRESULT CToon::InitVertexShader()
{
//	ID3DBlob* pCompiledShader = nullptr;
//	ID3DBlob* pErrors = nullptr;
//	UINT uCompileFlag = 0;
//#ifdef _DEBUG
//	uCompileFlag =
//		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
//#endif	// #ifdef _DEBUG
//
//	//-------------------------------------.
//	//	�o�[�e�b�N�X�V�F�[�_�[�̍쐬.
//	//-------------------------------------.
//	// �u���u�̍쐬.
//	if( FAILED( CCommon::InitShader( 
//		SHADER_FIEL_PATH, 
//		SHADER_ENTRY_POINT,
//		SHADER_MODEL,
//		uCompileFlag, 
//		&pCompiledShader,
//		&pErrors )) ){
//
//		ERROR_MESSAGE( "hlsl�Ǎ����s" );
//		return E_FAIL;
//	}
//	// �V�F�[�_�[�̍쐬.
//	if( FAILED( m_pDevice11->CreateVertexShader(
//		pCompiledShader->GetBufferPointer(),
//		pCompiledShader->GetBufferSize(),
//		nullptr,
//		&m_pVertexShader ))){
//
//		ERROR_MESSAGE( "�o�[�e�b�N�X�V�F�[�_�[�쐬���s" );
//		return E_FAIL;
//	}
//	InitVertexLayout( pCompiledShader );
//
	return S_OK;
}

HRESULT CToon::InitVertexLayout( ID3DBlob* pCompiledShader )
{
	// ���_���߯�ڲ��Ă��`.
	D3D11_INPUT_ELEMENT_DESC layout[3];
	// ���_���߯�ڲ��Ă̔z��v�f�����Z�o.
	UINT numElements = 0;
	D3D11_INPUT_ELEMENT_DESC tmp[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0, 0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",  0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,   0,24,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	numElements = sizeof(tmp) / sizeof(tmp[0]);	// �v�f���Z�o.
	memcpy_s( layout, sizeof(layout),
		tmp, sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);


	//���_���߯�ڲ��Ă��쐬.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout)))	//(out)���_���߯�ڲ���.
	{
		_ASSERT_EXPR(false, L"���_���߯�ڲ��č쐬���s");
		return E_FAIL;
	}

	return S_OK;
}