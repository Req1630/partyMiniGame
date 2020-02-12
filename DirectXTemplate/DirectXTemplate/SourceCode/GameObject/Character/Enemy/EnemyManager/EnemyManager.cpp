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

//---------------------------.
// �X�V�֐�.
//---------------------------.
void CEnemyManager::Update()
{
	for( auto& e : m_pEnemyList ) e->Update();
}

//---------------------------.
// �����蔻��֐�.
//---------------------------.
void CEnemyManager::Collision( pCollisionManager )
{
}

//---------------------------.
// �`��֐�.
//---------------------------.
void CEnemyManager::Render( SCENE_INFO& info )
{
	for( auto& e : m_pEnemyList ) e->Render( info );
}

//---------------------------.
// �G�擾�֐�.
//---------------------------.
std::shared_ptr<CGameObject> CEnemyManager::GetEnemy( const int index ) const
{
	if( static_cast<size_t>( index ) >= m_pEnemyList.size() ) return nullptr;
	return m_pEnemyList[index];
}