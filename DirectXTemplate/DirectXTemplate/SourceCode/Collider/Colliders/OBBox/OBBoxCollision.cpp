#include "OBBoxCollision.h"
#include "BoxModel.h"

#ifdef _DEBUG
bool COBBoxCollision::m_IsRender = false;
#endif	// #ifdef _DEBUG.

COBBoxCollision::COBBoxCollision()
	: m_vLength			{ 0.0f, 0.0f, 0.0f }
	, m_vDirection		()
	, m_vAdjLength		{ 0.0f, 0.0f, 0.0f }
#ifdef _DEBUG
	, m_pDebugBox		( std::make_unique<CBoxModel>() )
#endif	// #ifdef _DEBUG.
{
}

COBBoxCollision::~COBBoxCollision()
{
}

//----------------------------------------.
// ���f���̃{�b�N�X�̍쐬.
//----------------------------------------.
HRESULT COBBoxCollision::InitModelBox( LPD3DXMESH pMesh )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	VOID* pVertices = nullptr;
	D3DXVECTOR3	Max, Min;

	if( FAILED( pMesh->GetVertexBuffer( &pVB ) ) ){
		_ASSERT_EXPR( false, L"���_�o�b�t�@�擾���s" );
		return E_FAIL;
	}
	// ���b�V���̒��_�o�b�t�@�����b�N����.
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		_ASSERT_EXPR( false, L"���_�o�b�t�@�̃��b�N���s" );
		SAFE_RELEASE( pVB );
		return E_FAIL;
	}
	// ���b�V�����̒��_�ʒu�̍ő�ƍŏ�����������.
	D3DXComputeBoundingBox(
		static_cast<D3DXVECTOR3*>( pVertices ),
		pMesh->GetNumVertices(),
		D3DXGetFVFVertexSize(
			pMesh->GetFVF() ),
		&Min, &Max );	// (out)�ŏ�,�ő咸�_.

	pVB->Unlock();		// �A�����b�N.
	SAFE_RELEASE( pVB );	// �g�p�ςݒ��_�o�b�t�@�̉��.

	m_vLength.x = ((fabsf( Max.x - Min.x ) * (*m_pScale)) / 2.0f) + m_vAdjLength.x;
	m_vLength.y = ((fabsf( Max.y - Min.y ) * (*m_pScale)) / 2.0f) + m_vAdjLength.y;
	m_vLength.z = ((fabsf( Max.z - Min.z ) * (*m_pScale)) / 2.0f) + m_vAdjLength.z;
#ifdef _DEBUG
	m_pDebugBox->Init( m_vLength, m_vLength );
#endif	// #ifdef _DEBUG.
	return S_OK;
}

//----------------------------------------.
// �����蔻��̕\��.
//----------------------------------------.
void COBBoxCollision::DebugRender( std::shared_ptr<CCamera> camera )
{
#ifdef _DEBUG
	if( ( GetAsyncKeyState('D') & 0x8000 ) &&
		( GetAsyncKeyState('E') & 0x8000 )){
		if( GetAsyncKeyState('B') & 0x0001 ) m_IsRender = !m_IsRender;
	}
	if( m_IsRender == false ) return;
	m_pDebugBox->SetRotation( GetRotation() );
	m_pDebugBox->SetPosition( GetPosition() );
	m_pDebugBox->Render( camera );
#endif	// #ifdef _DEBUG.
}

//----------------------------------------.
// �F��ς��邩�ǂ���.
//----------------------------------------.
void COBBoxCollision::SetChangeColor( const bool& changed )
{
#ifdef _DEBUG
	m_pDebugBox->ChangeColor( changed );
#endif	// #ifdef _DEBUG.
}

//----------------------------------------.
// �����x�N�g���擾�֐�.
//----------------------------------------.
D3DXVECTOR3 COBBoxCollision::GetDirection( const int& index )
{
	D3DXMATRIX mRot;
	D3DXVECTOR3 vRot = *m_pvRotation;
	D3DXMatrixRotationYawPitchRoll( &mRot, vRot.y, vRot.x, vRot.z );

	m_vDirection[0] = D3DXVECTOR3( mRot._11, mRot._12, mRot._13 );
	m_vDirection[1] = D3DXVECTOR3( mRot._21, mRot._22, mRot._23 );
	m_vDirection[2] = D3DXVECTOR3( mRot._31, mRot._32, mRot._33 );

	return m_vDirection[index];
}