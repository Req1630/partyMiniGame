#include "SphereCollision.h"
#include "SphereModel.h"

#ifdef _DEBUG
bool CSphereCollision::m_IsRender = false;
#endif	// #ifdef _DEBUG.

CSphereCollision::CSphereCollision()
	: m_Radius			( 0.0f )
	, m_AdjRadius		( 0.0f )
#ifdef _DEBUG
	, m_pDebugSphere	( std::make_unique<CSphereModel>() )
#endif	// #ifdef _DEBUG.
{
}

CSphereCollision::~CSphereCollision()
{
}

//----------------------------------------.
// ���f���̔��a�̍쐬.
//----------------------------------------.
HRESULT CSphereCollision::InitModelRadius( LPD3DXMESH pMesh )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr; // ���_�o�b�t�@.
	void* pVertices = nullptr;	// ���_.
	D3DXVECTOR3 vCenter;		// ���S.

	// ���_�o�b�t�@���擾.
	if( FAILED( pMesh->GetVertexBuffer( &pVB ) ) ){
		ERROR_MESSAGE("���b�V�����_�o�b�t�@�̎擾���s");
		return E_FAIL;
	}
	// ���b�V���̒��_�o�b�t�@�����b�N����.
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		SAFE_RELEASE( pVB );
		ERROR_MESSAGE("���b�V�����_�o�b�t�@�̃��b�N���s");
		return E_FAIL;
	}
	// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>( pVertices ),
		pMesh->GetNumVertices(),				// ���_�̐�.
		D3DXGetFVFVertexSize( pMesh->GetFVF() ),// ���_�̏��.
		&vCenter,								// (out)���S���W.
		&m_Radius );							// (out)���a.

	m_Radius = (m_Radius * (*m_pScale)) + m_AdjRadius;

	// �A�����b�N.
	pVB->Unlock();
	SAFE_RELEASE( pVB );

#ifdef _DEBUG
	if( FAILED( m_pDebugSphere->Init( m_Radius ))){
		ERROR_MESSAGE("���f���쐬���s");
		return E_FAIL;
	}
#endif	// #ifdef _DEBUG.

	return S_OK;
}

//----------------------------------------.
// �����蔻��̕\��.
//----------------------------------------.
void CSphereCollision::DebugRender( std::shared_ptr<CCamera> camera )
{
#ifdef _DEBUG
	if( ( GetAsyncKeyState('D') & 0x8000 ) &&
		( GetAsyncKeyState('E') & 0x8000 )){
		if( GetAsyncKeyState('S') & 0x0001 ) m_IsRender = !m_IsRender;
	}
	if( m_IsRender == false ) return;
	m_pDebugSphere->SetPosition( GetPosition() );
	m_pDebugSphere->Render( camera );
#endif	// #ifdef _DEBUG.
}

//----------------------------------------.
// �F��ς��邩�ǂ���.
//----------------------------------------.
void CSphereCollision::SetChangeColor( const bool& changed )
{
#ifdef _DEBUG
	m_pDebugSphere->ChangeColor( changed );
#endif	// #ifdef _DEBUG.
}