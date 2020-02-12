#ifndef SHOOT_ENEMY_H
#define SHOOT_ENEMY_H

#include "..\EnemyBase.h"

class CShootEnemy : public CEnemyBase
{
public:
	CShootEnemy();
	virtual ~CShootEnemy();

	// �X�V�֐�.
	virtual void Update() override;
	// �����蔻��֐�.
	virtual void Collision( pGameObject ) override;
	// �`��֐�.
	virtual void Render( SCENE_INFO& ) override;

private:
	// �ړ��֐�.
	virtual void Move() override;
};

#endif	// #ifndef SHOOT_ENEMY_H.