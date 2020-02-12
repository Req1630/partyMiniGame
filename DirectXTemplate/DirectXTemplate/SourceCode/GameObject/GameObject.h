#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "..\Scene\SceneBase\SceneBase.h"

class CCollsionManager;

class CGameObject
{
protected:
	typedef scene::CSceneBase::SCENE_INIT_INFO SCENE_INFO;
	typedef std::shared_ptr<CCollsionManager> pCollisionManager;
	typedef std::shared_ptr<CGameObject> pGameObject;
	
public:
	CGameObject();
	virtual ~CGameObject();

	// 更新関数.
	virtual void Update() = 0;
	// 当たり判定関数.
	virtual void Collision( pGameObject ) = 0;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) = 0;

	// 当たり判定取得関数.
	pCollisionManager GetCollider(){ return m_pCollider; }

protected:
	D3DXVECTOR3			m_vPosition;	// 位置情報.
	D3DXVECTOR3			m_vRotation;	// 回転情報.
	pCollisionManager	m_pCollider;	// 当たり判定.
	float				m_ModelScale;	// モデルのサイズ.
};

#endif	// #ifndef GAME_OBJECT_H.