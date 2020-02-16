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
// �X�V�֐�.
//---------------------------.
void CEnemyManager::Update()
{
	m_GameCount++;	// �Q�[���J�E���g�̉��Z.
	
	// �e�G�̍X�V.
	for( auto& e : m_pEnemyList ){
		if( e->IsAssailable( m_GameCount ) == false ) continue;
		e->Update();
	}
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
	// �e�G�̕`��.
	for( auto& e : m_pEnemyList ){
		if( e->IsAssailable( m_GameCount ) == false ) continue;
		e->Render( info );
	}
}

//---------------------------.
// �G�擾�֐�.
//---------------------------.
std::shared_ptr<CGameObject> CEnemyManager::GetEnemy( const int index ) const
{
	if( static_cast<size_t>( index ) >= m_pEnemyList.size() ) return nullptr;
	if( m_pEnemyList[index]->IsAssailable( m_GameCount ) == false ) return nullptr;

	return m_pEnemyList[index];
}

//---------------------------.
// �G�̍쐬.
//---------------------------.
void CEnemyManager::EnemyCreating()
{
	m_pEnemyList.emplace_back( std::make_shared<CRunEnemy>() );

	CHARACTER_INFO enemyInfo;
	CCharacter::CharacterParameterReading( enemyInfo, "GhostA" );
	// �v���C���[���ݒ�.
	enemyInfo.vPosition.x = 13.0f;
	enemyInfo.vPosition.z = 0.0f;
	enemyInfo.vRotation.y = D3DXToRadian(90.0f);
	m_pEnemyList[0]->SetCharacterParam( enemyInfo, "GhostA" );
	m_pEnemyList[0]->SetAttackCount( 60 );
}