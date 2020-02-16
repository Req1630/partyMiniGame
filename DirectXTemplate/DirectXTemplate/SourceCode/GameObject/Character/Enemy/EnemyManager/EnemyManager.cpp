#include "EnemyManager.h"
#include "..\RunEnemy\RunEnemy.h"

CEnemyManager::CEnemyManager()
	: m_pEnemyList	()
	, m_GameCount	( 0 )
{
	EnemyCreating();
}

CEnemyManager::~CEnemyManager()
{
}

//---------------------------.
// XVŠÖ”.
//---------------------------.
void CEnemyManager::Update()
{
	m_GameCount++;	// ƒQ[ƒ€ƒJƒEƒ“ƒg‚Ì‰ÁZ.
	
	// Še“G‚ÌXV.
	for( auto& e : m_pEnemyList ){
		if( e->IsAssailable( m_GameCount ) == false ) continue;
		e->Update();
	}
}

//---------------------------.
// “–‚½‚è”»’èŠÖ”.
//---------------------------.
void CEnemyManager::Collision( pCollisionManager )
{
}

//---------------------------.
// •`‰æŠÖ”.
//---------------------------.
void CEnemyManager::Render( SCENE_INFO& info )
{
	// Še“G‚Ì•`‰æ.
	for( auto& e : m_pEnemyList ){
		if( e->IsAssailable( m_GameCount ) == false ) continue;
		e->Render( info );
	}
}

//---------------------------.
// “Gæ“¾ŠÖ”.
//---------------------------.
std::shared_ptr<CGameObject> CEnemyManager::GetEnemy( const int index ) const
{
	if( static_cast<size_t>( index ) >= m_pEnemyList.size() ) return nullptr;
	if( m_pEnemyList[index]->IsAssailable( m_GameCount ) == false ) return nullptr;

	return m_pEnemyList[index];
}

//---------------------------.
// “G‚Ìì¬.
//---------------------------.
void CEnemyManager::EnemyCreating()
{
	m_pEnemyList.emplace_back( std::make_shared<CRunEnemy>() );

	CHARACTER_INFO enemyInfo;
	CCharacter::CharacterParameterReading( enemyInfo, "GhostA" );
	// ƒvƒŒƒCƒ„[î•ñİ’è.
	enemyInfo.vPosition.x = 13.0f;
	enemyInfo.vPosition.z = 0.0f;
	enemyInfo.vRotation.y = D3DXToRadian(90.0f);
	m_pEnemyList[0]->SetCharacterParam( enemyInfo, "GhostA" );
	m_pEnemyList[0]->SetAttackCount( 60 );
}