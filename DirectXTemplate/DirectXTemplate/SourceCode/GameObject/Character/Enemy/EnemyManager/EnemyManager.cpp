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

// XVŠÖ”.
void CEnemyManager::Update()
{
	for( auto& e : m_pEnemyList ){
		e->Update();
	}
}

// “–‚½‚è”»’èŠÖ”.
void CEnemyManager::Collision( pCollisionManager )
{
}

// •`‰æŠÖ”.
void CEnemyManager::Render( SCENE_INFO& info )
{
	for( auto& e : m_pEnemyList ){
		e->Render( info );
	}
}