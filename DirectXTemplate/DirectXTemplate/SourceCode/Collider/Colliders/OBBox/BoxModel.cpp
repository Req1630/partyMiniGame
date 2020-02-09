#include "BoxModel.h"
#include "..\..\..\Camera\Camera.h"
#include "..\..\..\Common\Shader\SimpleShader\SimpleShader.h"
#include "..\..\..\Common\D3DX\D3DX.h"

CBoxModel::CBoxModel()
	: m_pSimpleShader	( std::make_unique<CSimpleShader>() )
	, m_pVertexBuffer	( nullptr )
	, m_pIndexBuffer	( nullptr )
{
}

CBoxModel::~CBoxModel()
{
	SAFE_RELEASE( m_pIndexBuffer );
	SAFE_RELEASE( m_pVertexBuffer );

	m_pSimpleShader->Release();
}

//---------------------.
// ������.
//---------------------.
HRESULT CBoxModel::Init( const D3DXVECTOR3& vMaxPoint, const D3DXVECTOR3& vMinPoint )
{
	InitPram( CD3DX::GetDevice11(), CD3DX::GetContext11() );

	// �V�F�[�_�[�̍쐬.
	if( FAILED( m_pSimpleShader->Init( m_pDevice11, m_pContext11 ))) return E_FAIL;
	// ���f���̍쐬.
	if( FAILED( InitModel( vMaxPoint, vMinPoint ))) return E_FAIL;
	 
	return S_OK;
}

//---------------------.
// �`��.
//---------------------.
void CBoxModel::Render( std::shared_ptr<CCamera> camera )
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
	m_pContext11->DrawIndexed( 36, 0, 0 );
	SetRasterizerState( enRS_STATE::None );
}

//---------------------.
// WVP Matrix�̍쐬.
//---------------------.
D3DXMATRIX CBoxModel::CreateWVPMatrix( std::shared_ptr<CCamera> camera, D3DXMATRIX& mWVP )
{
	// ���[���h�s��.
	D3DXMATRIX mWorld;
	D3DXMATRIX mRot, mTran, mScale;

	// ��].
	D3DXMatrixRotationYawPitchRoll( &mRot, m_vRot.y, m_vRot.x, m_vRot.z );
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
HRESULT CBoxModel::InitModel( const D3DXVECTOR3& vMaxPoint, const D3DXVECTOR3& vMinPoint )
{
	//�����(�l�p�`)�̒��_���쐬.
	CSimpleShader::VERTEX vertices[]=
	{
		//���_���W(x,y,z)				 
		D3DXVECTOR3( vMaxPoint.x, vMaxPoint.y,-vMinPoint.z ), //���_�P(���㉜).
		D3DXVECTOR3( vMaxPoint.x,-vMinPoint.y, vMaxPoint.z ), //���_�Q(�E�㉜).
		D3DXVECTOR3( vMaxPoint.x,-vMinPoint.y,-vMinPoint.z ), //���_�R(������).
		D3DXVECTOR3( vMaxPoint.x, vMaxPoint.y, vMaxPoint.z ), //���_�S(�E����).

		D3DXVECTOR3( vMaxPoint.x, vMaxPoint.y, vMaxPoint.z ), //���_�P(�����O).
		D3DXVECTOR3(-vMinPoint.x,-vMinPoint.y, vMaxPoint.z ), //���_�Q(������O).
		D3DXVECTOR3( vMaxPoint.x,-vMinPoint.y, vMaxPoint.z ), //���_�R(�E���O).
		D3DXVECTOR3(-vMinPoint.x, vMaxPoint.y, vMaxPoint.z ), //���_�S(�E����O).

		D3DXVECTOR3(-vMinPoint.x, vMaxPoint.y, vMaxPoint.z ), //���_�P(�����O).
		D3DXVECTOR3(-vMinPoint.x,-vMinPoint.y,-vMinPoint.z ), //���_�Q(���㉜).
		D3DXVECTOR3(-vMinPoint.x,-vMinPoint.y, vMaxPoint.z ), //���_�R(������O).
		D3DXVECTOR3(-vMinPoint.x, vMaxPoint.y,-vMinPoint.z ), //���_�S(������).

		D3DXVECTOR3(-vMinPoint.x, vMaxPoint.y,-vMinPoint.z ), //���_�P(�E���O).
		D3DXVECTOR3( vMaxPoint.x,-vMinPoint.y,-vMinPoint.z ), //���_�Q(�E����O).
		D3DXVECTOR3(-vMinPoint.x,-vMinPoint.y,-vMinPoint.z ), //���_�R(�E�㉜).
		D3DXVECTOR3( vMaxPoint.x, vMaxPoint.y,-vMinPoint.z ), //���_�S(�E����).

		D3DXVECTOR3( vMaxPoint.x,-vMinPoint.y,-vMinPoint.z ), //���_�P(����).
		D3DXVECTOR3(-vMinPoint.x,-vMinPoint.y, vMaxPoint.z ), //���_�Q(����).
		D3DXVECTOR3(-vMinPoint.x,-vMinPoint.y,-vMinPoint.z ), //���_�R(�E��).
		D3DXVECTOR3( vMaxPoint.x,-vMinPoint.y, vMaxPoint.z ), //���_�S(�E��).

		D3DXVECTOR3(-vMinPoint.x, vMaxPoint.y,-vMinPoint.z ), //���_�P(����).
		D3DXVECTOR3( vMaxPoint.x, vMaxPoint.y, vMaxPoint.z ), //���_�Q(����).
		D3DXVECTOR3( vMaxPoint.x, vMaxPoint.y,-vMinPoint.z ), //���_�R(�E��).
		D3DXVECTOR3(-vMinPoint.x, vMaxPoint.y, vMaxPoint.z )  //���_�S(�E��).
	};
	WORD indexList[]{
		0,  1,  2,     1,  0,  3,
		4,  5,  6,     5,  4,  7,
		8,  9,  10,    9,  8,  11,
		12, 13, 14,    13, 12, 15,
		16, 17, 18,    17, 16, 19,
		20, 21, 22,    21, 20, 23,
	};

	// �ő�v�f�����Z�o����.
	UINT uVerMax = sizeof(vertices)/sizeof(vertices[0]);
	UINT uIndexMax = sizeof(indexList)/sizeof(indexList[0]);

	// �o�b�t�@�\����.
	D3D11_BUFFER_DESC bd;
	bd.Usage				= D3D11_USAGE_DEFAULT;		// �g�p���@(�f�t�H���g).
	bd.ByteWidth			= sizeof(CSimpleShader::VERTEX)*uVerMax;// ���_�̃T�C�Y.
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
	id.ByteWidth			= sizeof(WORD)*uIndexMax;  // ���_�̃T�C�Y.
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