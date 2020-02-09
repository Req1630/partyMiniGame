#ifndef RUN_ENEMY_H
#define RUN_ENEMY_H

#include "..\EnemyBase.h"

class CRunEnemy : public CEnemyBase
{
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
};

#endif	// #ifndef RUN_ENEMY_H.