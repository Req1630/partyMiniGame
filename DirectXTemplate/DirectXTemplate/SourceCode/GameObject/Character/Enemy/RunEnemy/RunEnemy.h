#ifndef RUN_ENEMY_H
#define RUN_ENEMY_H

#include "..\EnemyBase.h"

class CRunEnemy : public CEnemyBase
{
public:
	CRunEnemy();
	virtual ~CRunEnemy();

	// 更新関数.
	virtual void Update() override;
	// 当たり判定関数.
	virtual void Collision( pCollisionManager ) override;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) override;

private:
	// 移動関数.
	virtual void Move() override;
};

#endif	// #ifndef RUN_ENEMY_H.