#ifndef COLLSION_MANAGER_H
#define COLLSION_MANAGER_H

#include "..\..\Global.h"

class CSphereCollision;
class COBBoxCollision;

//----------------------------------.
//	当たり判定マネージャークラス.
//	 各オブジェクトはこのクラスを使用する.
//----------------------------------.
class CCollsionManager
{
	typedef std::shared_ptr<CSphereCollision> pSphereCollision;
	typedef std::shared_ptr<COBBoxCollision> pOBBoxCollision;

public: //------ 関数 -------.
	CCollsionManager();
	~CCollsionManager();

	// 初期化.
	HRESULT Init( LPD3DXMESH pMesh, D3DXVECTOR3* pPos, D3DXVECTOR3* pRot, float* pScale );
	// デバッグ用描画.
	void DebugRender( std::shared_ptr<CCamera> camera );

	/*
	//- 当たり判定関数 -.
	*/

	// スフィア同士の当たり判定.
	bool IsShereToShere( pSphereCollision pSphere );
	// OBB同士の当たり判定.
	bool IsOBBToOBB( pOBBoxCollision pOBBox );

	/*
	//- 取得関数 -.
	*/

	// スフィア取得関数.
	pSphereCollision GetSphere() const { return m_pSphere; }
	// ボックス取得関数.
	pOBBoxCollision GetOBB() const { return m_pOBBox; }

	/*
	//- 調整用関数 -.
	*/

	// スフィアの調整用座標設定.
	void SetSphereAdjPosition( const D3DXVECTOR3& pos );
	// スフィアの調整用半径設定.
	void SetSphereAdjRadius( const float& radius );
	// ボックスの調整用座標設定.
	void SetBoxAdjPosition( const D3DXVECTOR3& pos );
	// ボックスの調整用長さ設定.
	void SetBoxAdjLength( const D3DXVECTOR3& length );

private: //------ 変数 -------.
	pSphereCollision m_pSphere;	// スフィア.
	pOBBoxCollision m_pOBBox;	// ボックス.
};

#endif	// #ifndef COLLSION_MANAGER_H.