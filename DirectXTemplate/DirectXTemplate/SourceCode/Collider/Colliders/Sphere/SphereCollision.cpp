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
// モデルの半径の作成.
//----------------------------------------.
HRESULT CSphereCollision::InitModelRadius( LPD3DXMESH pMesh )
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr; // 頂点バッファ.
	void* pVertices = nullptr;	// 頂点.
	D3DXVECTOR3 vCenter;		// 中心.

	// 頂点バッファを取得.
	if( FAILED( pMesh->GetVertexBuffer( &pVB ) ) ){
		ERROR_MESSAGE("メッシュ頂点バッファの取得失敗");
		return E_FAIL;
	}
	// メッシュの頂点バッファをロックする.
	if( FAILED( pVB->Lock( 0, 0, &pVertices, 0 ) ) ){
		SAFE_RELEASE( pVB );
		ERROR_MESSAGE("メッシュ頂点バッファのロック失敗");
		return E_FAIL;
	}
	// メッシュの外接円の中心と半径を計算する.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>( pVertices ),
		pMesh->GetNumVertices(),				// 頂点の数.
		D3DXGetFVFVertexSize( pMesh->GetFVF() ),// 頂点の情報.
		&vCenter,								// (out)中心座標.
		&m_Radius );							// (out)半径.

	m_Radius = (m_Radius * (*m_pScale)) + m_AdjRadius;

	// アンロック.
	pVB->Unlock();
	SAFE_RELEASE( pVB );

#ifdef _DEBUG
	if( FAILED( m_pDebugSphere->Init( m_Radius ))){
		ERROR_MESSAGE("モデル作成失敗");
		return E_FAIL;
	}
#endif	// #ifdef _DEBUG.

	return S_OK;
}

//----------------------------------------.
// 当たり判定の表示.
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
// 色を変えるかどうか.
//----------------------------------------.
void CSphereCollision::SetChangeColor( const bool& changed )
{
#ifdef _DEBUG
	m_pDebugSphere->ChangeColor( changed );
#endif	// #ifdef _DEBUG.
}