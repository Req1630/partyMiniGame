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
// 初期化.
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
// デバッグ用描画.
//-------------------------.
void CCollsionManager::DebugRender( std::shared_ptr<CCamera> camera )
{
	m_pSphere->DebugRender( camera );
	m_pOBBox->DebugRender( camera );
}

//----------------------------------.
// スフィア同士の当たり判定.
//----------------------------------.
bool CCollsionManager::IsShereToShere( pSphereCollision pSphere )
{
	// 2点間(中心点)の距離を求める.
	const D3DXVECTOR3 vLength = pSphere->GetPosition() - m_pSphere->GetPosition();
	// 長さに変換する.
	const float length = D3DXVec3Length( &vLength );
	// 2つの半径の合計.
	float twoRadiusTotal = m_pSphere->GetRadius() + pSphere->GetRadius();
	
	// 2点間の距離が2つの半径の合計より大きいので.
	// 衝突していない.
	if( length >= twoRadiusTotal ){
		m_pSphere->SetChangeColor( false );
		return false;
	}

	m_pSphere->SetChangeColor( true );

	// 衝突している.
	return true;
}

//----------------------------------.
// OBB同士の当たり判定.
//----------------------------------.
bool CCollsionManager::IsOBBToOBB( pOBBoxCollision pOBBox )
{
	auto LenSegOnSeparateAxis = []( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 )
	{
		// 3つの内積の絶対値の和で投影線分長を計算.
		// 分離軸Sepは標準化されていること.
		FLOAT r1 = fabs(D3DXVec3Dot( Sep, e1 ));
		FLOAT r2 = fabs(D3DXVec3Dot( Sep, e2 ));
		FLOAT r3 = e3 ? (fabs(D3DXVec3Dot( Sep, e3 ))) : 0;
		return r1 + r2 + r3;
	};
	// 各方向ベクトルの確保.
	// （N***:標準化方向ベクトル）.
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
			return false; // 衝突していない.
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
			return false; // 衝突していない.
		}
		return true;
	};

	// 分離軸 : Ae.
	if( isHitLength( Ae1, NAe1, Be1, Be2, Be3 ) == false ) return false;
	if( isHitLength( Ae2, NAe2, Be1, Be2, Be3 ) == false ) return false;
	if( isHitLength( Ae3, NAe3, Be1, Be2, Be3 ) == false ) return false;
	// 分離軸 : Be.
	if( isHitLength( Be1, NBe1, Ae1, Ae2, Ae3 ) == false ) return false;
	if( isHitLength( Be2, NBe2, Ae1, Ae2, Ae3 ) == false ) return false;
	if( isHitLength( Be3, NBe3, Ae1, Ae2, Ae3 ) == false ) return false;

	// 分離軸 : C1.
	if( isHitCross( NAe1, NBe1, Ae2, Ae3, Be2, Be3 ) == false ) return false;
	if( isHitCross( NAe1, NBe2, Ae2, Ae3, Be1, Be3 ) == false ) return false;
	if( isHitCross( NAe1, NBe3, Ae2, Ae3, Be1, Be2 ) == false ) return false;
	// 分離軸 : C2.
	if( isHitCross( NAe2, NBe1, Ae1, Ae3, Be2, Be3 ) == false ) return false;
	if( isHitCross( NAe2, NBe2, Ae1, Ae3, Be1, Be3 ) == false ) return false;
	if( isHitCross( NAe2, NBe3, Ae1, Ae3, Be1, Be2 ) == false ) return false;
	// 分離軸 : C3.
	if( isHitCross( NAe3, NBe1, Ae1, Ae2, Be2, Be3 ) == false ) return false;
	if( isHitCross( NAe3, NBe2, Ae1, Ae2, Be1, Be3 ) == false ) return false;
	if( isHitCross( NAe3, NBe3, Ae1, Ae2, Be1, Be2 ) == false ) return false;

	// 分離平面が存在しないので「衝突している」.
	m_pOBBox->SetChangeColor( true );
	return true;
}

//----------------------------------.
// ↓ 調整用 ↓.
//----------------------------------.
//----------------------------------.
// スフィアの調整用値設定関数.
//----------------------------------.
void CCollsionManager::SetSphereAdjPosition( const D3DXVECTOR3& pos )
{
	m_pSphere->SetAdjPosition( pos );
}
//----------------------------------.
// スフィアの調整用半径設定.
//----------------------------------.
void CCollsionManager::SetSphereAdjRadius( const float& radius )
{
	m_pSphere->SetAdjRadius( radius );
}
//----------------------------------.
// ボックスの調整用座標設定.
//----------------------------------.
void CCollsionManager::SetBoxAdjPosition( const D3DXVECTOR3& pos )
{
	m_pOBBox->SetAdjPosition( pos );
}
//----------------------------------.
// ボックスの調整用半径設定.
//----------------------------------.
void CCollsionManager::SetBoxAdjLength( const D3DXVECTOR3& length )
{
	m_pOBBox->SetAdjLength( length );
}