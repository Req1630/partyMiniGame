#include "EnemyManager.h"
#include "..\RunEnemy\RunEnemy.h"
#include "..\..\..\..\Utility\FileManager\FileManager.h"
#include "..\EnemyType.h"

CEnemyManager::CEnemyManager()
	: m_pEnemyList		()
	, m_DirectionList	()
	, m_InitPosList		()
	, m_GameCount		( 0 )
{
	DirectionInfoReading();
	InitPositionReading();
	EnemyCreating();
}

CEnemyManager::~CEnemyManager()
{
}

//---------------------------.
// 更新関数.
//---------------------------.
void CEnemyManager::Update()
{
	m_GameCount++;	// ゲームカウントの加算.
	
	// 各敵の更新.
	for( auto& e : m_pEnemyList ){
		if( e->IsAssailable( m_GameCount ) == false ) continue;
		e->Update();
	}
}

//---------------------------.
// 当たり判定関数.
//---------------------------.
void CEnemyManager::Collision( pCollisionManager )
{
}

//---------------------------.
// 描画関数.
//---------------------------.
void CEnemyManager::Render( SCENE_INFO& info )
{
	// 各敵の描画.
	for( auto& e : m_pEnemyList ){
		if( e->IsAssailable( m_GameCount ) == false ) continue;
		e->Render( info );
	}
}

//---------------------------.
// 敵取得関数.
//---------------------------.
std::shared_ptr<CGameObject> CEnemyManager::GetEnemy( const int index ) const
{
	if( static_cast<size_t>( index ) >= m_pEnemyList.size() ) return nullptr;
	if( m_pEnemyList[index]->IsAssailable( m_GameCount ) == false ) return nullptr;

	return m_pEnemyList[index];
}

//---------------------------.
// 敵の作成.
//---------------------------.
void CEnemyManager::EnemyCreating()
{
	m_pEnemyList.emplace_back( std::make_shared<CRunEnemy>() );

	CHARACTER_INFO enemyInfo;
	CCharacter::CharacterParameterReading( enemyInfo, "GhostA" );

	// プレイヤー情報設定.
	enemyInfo.vPosition.x = 0.0f;
	enemyInfo.vPosition.z = 0.0f;
	enemyInfo.vRotation.y = static_cast<float>(D3DXToRadian(90.0f));

	m_pEnemyList[0]->SetCharacterParam( enemyInfo, "GhostA" );
	m_pEnemyList[0]->SetAttackCount( 60 );
}

//---------------------------.
// 方向情報の読み込み.
//---------------------------.
void CEnemyManager::DirectionInfoReading()
{
	std::vector<std::string> dirList;
	dirList = CFileManager::TextLoading( ENEMY_DIRECTION_TEXT_PATH );

	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::UP)]) );	// 上.
	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::DOWN)]) );	// 下.
	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::RIGHT)]) );	// 右.
	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::LEFT)]) );	// 左.
}

//---------------------------.
// 初期座標の読み込み.
//---------------------------.
void CEnemyManager::InitPositionReading()
{
	std::vector<std::string> posList;
	posList = CFileManager::TextLoading( ENEMY_INIT_POS_TEXT_PATH );

	for( const auto& l : posList ){
		m_InitPosList.emplace_back( std::stof(l) );	// 各方向をfloatに変換していれる.
	}
}