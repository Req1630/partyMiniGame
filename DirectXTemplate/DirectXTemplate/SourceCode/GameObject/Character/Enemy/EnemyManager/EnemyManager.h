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

	// 更新関数.
	void Update();
	// 当たり判定関数.
	void Collision( pCollisionManager );
	// 描画関数.
	void Render( SCENE_INFO& );

	// 敵取得関数.
	std::shared_ptr<CGameObject> GetEnemy( const int index ) const;
	// 敵リストサイズ取得関数.
	int GetEnemySize() const { return m_pEnemyList.size(); }

private:
	// 敵の作成.
	void EnemyCreating();

private:
	std::vector<std::shared_ptr<CEnemyBase>> m_pEnemyList;	// 敵リスト.
	int m_GameCount;	// ゲームカウント.
};

#endif	// #ifndef ENEMY_MANAGER_H.