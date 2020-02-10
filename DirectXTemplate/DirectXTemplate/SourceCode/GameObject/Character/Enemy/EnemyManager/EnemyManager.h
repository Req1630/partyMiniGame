#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "..\EnemyBase.h"

#include <vector>

class CEnemyManager
{
	typedef scene::CSceneBase::SCENE_INIT_INFO SCENE_INFO;
	typedef std::shared_ptr<CCollsionManager> pCollisionManager;

public:
	CEnemyManager();
	~CEnemyManager();

	// �X�V�֐�.
	void Update();
	// �����蔻��֐�.
	void Collision( pCollisionManager );
	// �`��֐�.
	void Render( SCENE_INFO& );

private:
	std::vector<std::shared_ptr<CEnemyBase>> m_pEnemyList;
};

#endif	// #ifndef ENEMY_MANAGER_H.