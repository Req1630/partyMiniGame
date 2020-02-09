#include "CollsionManager.h"
#include "..\Colliders\Sphere\SphereCollision.h"
#include "..\Colliders\OBBox\OBBoxCollision.h"
#include "..\..\Global.h"

CCollsionManager::CCollsionManager()
	: m_pSphere	( std::make_shared<CSphereCollision>() )
	, m_pOBBox	( std::make_shared<COBBoxCollision>() )
{
}

CCollsionManager::~CCollsionManager()
{
}

//----------------------------------.
// ������.
//----------------------------------.
HRESULT CCollsionManager::Init( LPD3DXMESH pMesh, D3DXVECTOR3* pPos, D3DXVECTOR3* pRot, float* pScale )
{
	m_pSphere->SetPosition( pPos );
	m_pSphere->SetRotation( pRot );
	m_pSphere->SetScale( pScale );
	if( FAILED( m_pSphere->InitModelRadius( pMesh ))) return E_FAIL;
	m_pOBBox->SetPosition( pPos );
	m_pOBBox->SetRotation( pRot );
	m_pOBBox->SetScale( pScale );
	if( FAILED( m_pOBBox->InitModelBox( pMesh ))) return E_FAIL;

	return S_OK;
}

//-------------------------.
// �f�o�b�O�p�`��.
//-------------------------.
void CCollsionManager::DebugRender( std::shared_ptr<CCamera> camera )
{
	m_pSphere->DebugRender( camera );
	m_pOBBox->DebugRender( camera );
}

//----------------------------------.
// �X�t�B�A���m�̓����蔻��.
//----------------------------------.
bool CCollsionManager::IsShereToShere( pSphereCollision pSphere )
{
	// 2�_��(���S�_)�̋��������߂�.
	const D3DXVECTOR3 vLength = pSphere->GetPosition() - m_pSphere->GetPosition();
	// �����ɕϊ�����.
	const float length = D3DXVec3Length( &vLength );
	// 2�̔��a�̍��v.
	float twoRadiusTotal = m_pSphere->GetRadius() + pSphere->GetRadius();
	
	// 2�_�Ԃ̋�����2�̔��a�̍��v���傫���̂�.
	// �Փ˂��Ă��Ȃ�.
	if( length >= twoRadiusTotal ){
		m_pSphere->SetChangeColor( false );
		return false;
	}

	m_pSphere->SetChangeColor( true );

	// �Փ˂��Ă���.
	return true;
}

//----------------------------------.
// OBB���m�̓����蔻��.
//----------------------------------.
bool CCollsionManager::IsOBBToOBB( pOBBoxCollision pOBBox )
{
	auto LenSegOnSeparateAxis = []( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 )
	{
		// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z.
		// ������Sep�͕W��������Ă��邱��.
		FLOAT r1 = fabs(D3DXVec3Dot( Sep, e1 ));
		FLOAT r2 = fabs(D3DXVec3Dot( Sep, e2 ));
		FLOAT r3 = e3 ? (fabs(D3DXVec3Dot( Sep, e3 ))) : 0;
		return r1 + r2 + r3;
	};
	// �e�����x�N�g���̊m��.
	// �iN***:�W���������x�N�g���j.
	D3DXVECTOR3 NAe1 = m_pOBBox->GetDirection(0), Ae1 = NAe1 * m_pOBBox->GetLength().x;
	D3DXVECTOR3 NAe2 = m_pOBBox->GetDirection(1), Ae2 = NAe2 * m_pOBBox->GetLength().y;
	D3DXVECTOR3 NAe3 = m_pOBBox->GetDirection(2), Ae3 = NAe3 * m_pOBBox->GetLength().z;
	D3DXVECTOR3 NBe1 = pOBBox->GetDirection(0), Be1 = NBe1 * pOBBox->GetLength().x;
	D3DXVECTOR3 NBe2 = pOBBox->GetDirection(1), Be2 = NBe2 * pOBBox->GetLength().y;
	D3DXVECTOR3 NBe3 = pOBBox->GetDirection(2), Be3 = NBe3 * pOBBox->GetLength().z;
	D3DXVECTOR3 Interval = m_pOBBox->GetPosition() - pOBBox->GetPosition();

	FLOAT rA, rB, L;

	auto isHitLength = [&](
		const D3DXVECTOR3& e, 
		D3DXVECTOR3 Ne,
		D3DXVECTOR3 e1, D3DXVECTOR3 e2, D3DXVECTOR3 e3 )
	{
		rA = D3DXVec3Length( &e );
		rB = LenSegOnSeparateAxis( &Ne, &e1, &e2, &e3 );
		L = fabs(D3DXVec3Dot( &Interval, &Ne ));
		if( L > rA + rB ){
			m_pOBBox->SetChangeColor( false );
			return false; // �Փ˂��Ă��Ȃ�.
		}
		return true;
	};

	auto isHitCross = [&]( 
		const D3DXVECTOR3& NAe, const D3DXVECTOR3& NBe, 
		D3DXVECTOR3 Ae1, D3DXVECTOR3 Ae2,
		D3DXVECTOR3 Be1, D3DXVECTOR3 Be2 )
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross( &Cross, &NAe, &NBe );
		rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
		rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
		L = fabs(D3DXVec3Dot( &Interval, &Cross ));
		if( L > rA + rB ){
			m_pOBBox->SetChangeColor( false );
			return false; // �Փ˂��Ă��Ȃ�.
		}
		return true;
	};

	// ������ : Ae.
	if( isHitLength( Ae1, NAe1, Be1, Be2, Be3 ) == false ) return false;
	if( isHitLength( Ae2, NAe2, Be1, Be2, Be3 ) == false ) return false;
	if( isHitLength( Ae3, NAe3, Be1, Be2, Be3 ) == false ) return false;
	// ������ : Be.
	if( isHitLength( Be1, NBe1, Ae1, Ae2, Ae3 ) == false ) return false;
	if( isHitLength( Be2, NBe2, Ae1, Ae2, Ae3 ) == false ) return false;
	if( isHitLength( Be3, NBe3, Ae1, Ae2, Ae3 ) == false ) return false;

	// ������ : C1.
	if( isHitCross( NAe1, NBe1, Ae2, Ae3, Be2, Be3 ) == false ) return false;
	if( isHitCross( NAe1, NBe2, Ae2, Ae3, Be1, Be3 ) == false ) return false;
	if( isHitCross( NAe1, NBe3, Ae2, Ae3, Be1, Be2 ) == false ) return false;
	// ������ : C2.
	if( isHitCross( NAe2, NBe1, Ae1, Ae3, Be2, Be3 ) == false ) return false;
	if( isHitCross( NAe2, NBe2, Ae1, Ae3, Be1, Be3 ) == false ) return false;
	if( isHitCross( NAe2, NBe3, Ae1, Ae3, Be1, Be2 ) == false ) return false;
	// ������ : C3.
	if( isHitCross( NAe3, NBe1, Ae1, Ae2, Be2, Be3 ) == false ) return false;
	if( isHitCross( NAe3, NBe2, Ae1, Ae2, Be1, Be3 ) == false ) return false;
	if( isHitCross( NAe3, NBe3, Ae1, Ae2, Be1, Be2 ) == false ) return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v.
	m_pOBBox->SetChangeColor( true );
	return true;
}

//----------------------------------.
// �� �����p ��.
//----------------------------------.
//----------------------------------.
// �X�t�B�A�̒����p�l�ݒ�֐�.
//----------------------------------.
void CCollsionManager::SetSphereAdjPosition( const D3DXVECTOR3& pos )
{
	m_pSphere->SetAdjPosition( pos );
}
//----------------------------------.
// �X�t�B�A�̒����p���a�ݒ�.
//----------------------------------.
void CCollsionManager::SetSphereAdjRadius( const float& radius )
{
	m_pSphere->SetAdjRadius( radius );
}
//----------------------------------.
// �{�b�N�X�̒����p���W�ݒ�.
//----------------------------------.
void CCollsionManager::SetBoxAdjPosition( const D3DXVECTOR3& pos )
{
	m_pOBBox->SetAdjPosition( pos );
}
//----------------------------------.
// �{�b�N�X�̒����p���a�ݒ�.
//----------------------------------.
void CCollsionManager::SetBoxAdjLength( const D3DXVECTOR3& length )
{
	m_pOBBox->SetAdjLength( length );
}