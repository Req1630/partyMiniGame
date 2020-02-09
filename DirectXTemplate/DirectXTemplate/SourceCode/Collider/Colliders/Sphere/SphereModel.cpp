#include "SphereModel.h"
#include "..\..\..\Camera\Camera.h"
#include "..\..\..\Common\Shader\SimpleShader\SimpleShader.h"
#include "..\..\..\Common\D3DX\D3DX.h"

CSphereModel::CSphereModel()
	: m_pSimpleShader	( std::make_unique<CSimpleShader>() )
	, m_pVertexBuffer	( nullptr )
	, m_pIndexBuffer	( nullptr )
{
}

CSphereModel::~CSphereModel()
{
	SAFE_RELEASE( m_pIndexBuffer );
	SAFE_RELEASE( m_pVertexBuffer );

	m_pSimpleShader->Release();
}

//---------------------.
// ������.
//---------------------.
HRESULT CSphereModel::Init( const float& radius )
{
	InitPram( CD3DX::GetDevice11(), CD3DX::GetContext11() );

	// �V�F�[�_�[�̍쐬.
	if( FAILED( m_pSimpleShader->Init( m_pDevice11, m_pContext11 ))) return E_FAIL;
	// ���f���̍쐬.
	if( FAILED( InitModel( radius ))) return E_FAIL;

	return S_OK;
}

//---------------------.
// �`��.
//---------------------.
void CSphereModel::Render( std::shared_ptr<CCamera> camera )
{
	D3DXMATRIX mWVP;
	// WVP Matrix�̍쐬.
	CreateWVPMatrix( camera, mWVP );

	// ���݂̐F��ݒ�.
	D3DXVECTOR4 color = m_IsColorChanged == false ? MODEL_COLOR : MODEL_CHANGE_COLOR;

	// �R���X�^���g�o�b�t�@�Ƀf�[�^��n��.
	m_pSimpleShader->SetConstantBufferData( mWVP, color );

	// �e��V�F�[�_�̐ݒ�.
	m_pSimpleShader->ShaderSet( m_pVertexBuffer, m_pIndexBuffer );

	// �v���~�e�B�u�g�|���W�[���Z�b�g.
	m_pContext11->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	SetRasterizerState( enRS_STATE::Wire );
	m_pContext11->DrawIndexed( 930, 0, 0 );
	SetRasterizerState( enRS_STATE::None );
}

//---------------------.
// WVP Matrix�̍쐬.
//---------------------.
D3DXMATRIX CSphereModel::CreateWVPMatrix( std::shared_ptr<CCamera> camera, D3DXMATRIX& mWVP )
{
	// ���[���h�s��.
	D3DXMATRIX mWorld;
	D3DXMATRIX mRot, mTran, mScale;

	// ��].
	D3DXMatrixRotationYawPitchRoll( &mRot, 0.0f, 0.0f, 0.0f );
	// ���s�ړ�.
	D3DXMatrixTranslation( &mTran, m_vPos.x, m_vPos.y, m_vPos.z );
	// �g��k���s��쐬.
	D3DXMatrixScaling( &mScale, m_fScale, m_fScale, m_fScale );
	// ���[���h�s��
	mWorld = mScale * mRot * mTran;
	mWVP = mWorld * camera->GetViewMatrix() * camera->GetProjMatrix();

	return mWVP;
}

//---------------------.
// ���f���̍쐬.
//---------------------.
HRESULT CSphereModel::InitModel( const float& fRadius )
{
	const int U_MAX = 30;
	const int V_MAX = 15;

	// ���_�쐬.
	CSimpleShader::VERTEX vertices[480];
	WORD vertex_num = U_MAX * ( V_MAX + 1 );
	for( int v = 0; v <= V_MAX; v++ ){
		for( int u = 0; u < U_MAX; u++ ){
			float theta	= static_cast<float>(D3DXToRadian( 180.0 * v / V_MAX ));
			float phi	= static_cast<float>(D3DXToRadian( 360.0f * u / U_MAX ));
			float x = sin( theta ) * cos( phi ) * fRadius;
			float y = cos( theta ) * fRadius;
			float z = sin( theta ) * sin( phi ) * fRadius;
			vertices[U_MAX * v + u].Pos = D3DXVECTOR3( x, y, z );
		}
	}

	// �C���f�b�N�X�쐬.
	WORD indexList[930];
	WORD index_num = 2 * V_MAX * ( U_MAX + 1 );
	int i = 0;
	for( int v = 0; v < V_MAX; v++ ){
		for( int u = 0; u <= U_MAX; u++ ){
			if( u == U_MAX ){
				indexList[i++] = v * U_MAX;
				indexList[i++] = ( v + 1 ) * U_MAX;
			} else{
				indexList[i++] = ( v * U_MAX ) + u;
				indexList[i++] = indexList[i - 1] + U_MAX;
			}
		}
	}

	// �ő�v�f�����Z�o����.
	UINT uVerMax = sizeof( vertices ) / sizeof( vertices[0] );

	// �o�b�t�@�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage				= D3D11_USAGE_DEFAULT;		// �g�p���@(�f�t�H���g).
	bd.ByteWidth			= sizeof(CSimpleShader::VERTEX)*vertex_num;// ���_�̃T�C�Y.
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;	// ���_�o�b�t�@�Ƃ��Ĉ���.
	bd.CPUAccessFlags		= 0;						// CPU����̓A�N�Z�X���Ȃ�.
	bd.MiscFlags			= 0;						// ���̑��̃t���O(���g�p).
	bd.StructureByteStride	= 0;						// �\���̂̃T�C�Y(���g�p).

	//���ؿ���ް��\����.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;	//����؂̒��_���.

	//���_�ޯ̧�̍쐬.
	if( FAILED( m_pDevice11->CreateBuffer(
		&bd, &InitData, &m_pVertexBuffer ) ) ){
		_ASSERT_EXPR( false, L"���_�ޯ̧�쐬���s" );
		return E_FAIL;
	}

	D3D11_BUFFER_DESC id;
	id.Usage				= D3D11_USAGE_DEFAULT;	   // �g�p���@(�f�t�H���g).
	id.ByteWidth			= sizeof(WORD)*index_num;  // ���_�̃T�C�Y.
	id.BindFlags			= D3D11_BIND_INDEX_BUFFER; // ���_�o�b�t�@�Ƃ��Ĉ���.
	id.CPUAccessFlags		= 0;					   // CPU����̓A�N�Z�X���Ȃ�.
	id.MiscFlags			= 0;					   // ���̑��̃t���O(���g�p).
	id.StructureByteStride	= 0;					   // �\���̂̃T�C�Y(���g�p).

	D3D11_SUBRESOURCE_DATA IndexData;
	IndexData.pSysMem			= indexList;
	IndexData.SysMemPitch		= 0;
	IndexData.SysMemSlicePitch	= 0;

	if( FAILED( m_pDevice11->CreateBuffer(
		&id, &IndexData, &m_pIndexBuffer ))){
		_ASSERT_EXPR( false, L"�C���f�b�N�X�ޯ̧�쐬���s" );
		return E_FAIL;
	}

	return S_OK;
}