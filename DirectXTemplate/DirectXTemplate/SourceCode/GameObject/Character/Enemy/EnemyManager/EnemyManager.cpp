#include "EnemyManager.h"
#include "..\RunEnemy\RunEnemy.h"

CEnemyManager::CEnemyManager()
	: m_pEnemyList	()
{
	m_pEnemyList.emplace_back( std::make_shared<CRunEnemy>() );
}

CEnemyManager::~CEnemyManager()
{
}

// 更新関数.
void CEnemyManager::Update()
{
	for( auto& e : m_pEnemyList ){
		e->Update();
	}
}

// 当たり判定関数.
void CEnemyManager::Collision( pCollisionManager )
{
}

// 描画関数.
void CEnemyManager::Render( SCENE_INFO& info )
{
	for( auto& e : m_pEnemyList ){
		e->Render( info );
	}
}