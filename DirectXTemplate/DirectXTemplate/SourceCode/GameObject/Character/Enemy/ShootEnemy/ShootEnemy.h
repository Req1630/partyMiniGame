#ifndef SHOOT_ENEMY_H
#define SHOOT_ENEMY_H

#include "..\EnemyBase.h"

class CShootEnemy : public CEnemyBase
{
public:
	CShootEnemy();
	virtual ~CShootEnemy();

	// XVŠÖ”.
	virtual void Update() override;
	// “–‚½‚è”»’èŠÖ”.
	virtual void Collision( pGameObject ) override;
	// •`‰æŠÖ”.
	virtual void Render( SCENE_INFO& ) override;

private:
	// ˆÚ“®ŠÖ”.
	virtual void Move() override;
};

#endif	// #ifndef SHOOT_ENEMY_H.