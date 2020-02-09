#ifndef RUN_ENEMY_H
#define RUN_ENEMY_H

#include "..\EnemyBase.h"

class CRunEnemy : public CEnemyBase
{
public:
	CRunEnemy();
	virtual ~CRunEnemy();

	// XVŠÖ”.
	virtual void Update() override;
	// “–‚½‚è”»’èŠÖ”.
	virtual void Collision( pCollisionManager ) override;
	// •`‰æŠÖ”.
	virtual void Render( SCENE_INFO& ) override;

private:
	// ˆÚ“®ŠÖ”.
	virtual void Move() override;
};

#endif	// #ifndef RUN_ENEMY_H.