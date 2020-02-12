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

	// �X�V�֐�.
	virtual void Update() = 0;
	// �����蔻��֐�.
	virtual void Collision( pGameObject ) = 0;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) = 0;

	// �����蔻��擾�֐�.
	pCollisionManager GetCollider(){ return m_pCollider; }

protected:
	D3DXVECTOR3			m_vPosition;	// �ʒu���.
	D3DXVECTOR3			m_vRotation;	// ��]���.
	pCollisionManager	m_pCollider;	// �����蔻��.
	float				m_ModelScale;	// ���f���̃T�C�Y.
};

#endif	// #ifndef GAME_OBJECT_H.