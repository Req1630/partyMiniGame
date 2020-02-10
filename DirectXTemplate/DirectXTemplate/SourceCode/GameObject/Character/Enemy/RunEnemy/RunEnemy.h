#ifndef RUN_ENEMY_H
#define RUN_ENEMY_H

#include "..\EnemyBase.h"

class CRunEnemy : public CEnemyBase
{
	const char* MODEL_NAME = "GhostA";	// ���f����.
public:
	CRunEnemy();
	virtual ~CRunEnemy();

	// �X�V�֐�.
	virtual void Update() override;
	// �����蔻��֐�.
	virtual void Collision( pCollisionManager ) override;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) override;

private:
	// �ړ��֐�.
	virtual void Move() override;

private:
	std::shared_ptr<CDX9StaticMesh> m_pStaticMesh;	// �X�^�e�B�b�N���b�V��.
};

#endif	// #ifndef RUN_ENEMY_H.