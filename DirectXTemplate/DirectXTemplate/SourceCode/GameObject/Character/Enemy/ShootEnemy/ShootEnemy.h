#ifndef SHOOT_ENEMY_H
#define SHOOT_ENEMY_H

#include "..\EnemyBase.h"

class CShootEnemy : public CEnemyBase
{
public:
	CShootEnemy();
	virtual ~CShootEnemy();

	// 更新関数.
	virtual void Update() override;
	// 当たり判定関数.
	virtual void Collision( pGameObject ) override;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) override;

private:
	// 移動関数.
	virtual void Move() override;
};

#endif	// #ifndef SHOOT_ENEMY_H.