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
		if( e->IsAppearance( m_GameCount ) == false ) continue;
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
		if( e->IsAppearance( m_GameCount ) == false ) continue;
		e->Render( info );
	}
}

//---------------------------.
// 敵取得関数.
//---------------------------.
std::shared_ptr<CGameObject> CEnemyManager::GetEnemy( const int index ) const
{
	if( static_cast<size_t>( index ) >= m_pEnemyList.size() ) return nullptr;
	if( m_pEnemyList[index]->IsAppearance( m_GameCount ) == false ) return nullptr;

	return m_pEnemyList[index];
}

//---------------------------.
// 敵の作成.
//---------------------------.
void CEnemyManager::EnemyCreating()
{
	// 敵のリストの情報.
	std::vector<std::string> enemyList;
	enemyList = CFileManager::TextLoading( ENEMY_LIST_PATH );

	// 敵のリスト.
	std::vector<std::string> enemyTypeList;
	enemyTypeList = CFileManager::TextLoading( ENEMY_TYPE_LIST_PATH );

	CHARACTER_INFO enemyInfo;

	int enemyIndex = 0;
	for( size_t i = 0;i < enemyList.size(); i+=4  ){
		m_pEnemyList.emplace_back( std::make_shared<CRunEnemy>() );

		// 敵タイプの情報.
		int type = std::stoi(enemyList[i]);
		CCharacter::CharacterParameterReading( enemyInfo, enemyTypeList[type] );


		// 移動する方向の設定.
		int direction = std::stoi(enemyList[i+1]);
		enemyInfo.vRotation.y = static_cast<float>( D3DXToRadian( m_DirectionList[direction] ) );

		// 移動する方向による初期座標の設定.
		enENEMY_DIRECTION dir = static_cast<enENEMY_DIRECTION>(direction);
		switch( dir ){
			case enENEMY_DIRECTION::UP:
				// プレイヤー情報設定.
				enemyInfo.vPosition.x = m_InitPosList[std::stoi( enemyList[i+2] )];
				enemyInfo.vPosition.z = 13.0f;
				break;
			case enENEMY_DIRECTION::DOWN:
				// プレイヤー情報設定.
				enemyInfo.vPosition.x = m_InitPosList[std::stoi( enemyList[i+2] )];
				enemyInfo.vPosition.z = -13.0f;
				break;
			case enENEMY_DIRECTION::RIGHT:
				// プレイヤー情報設定.
				enemyInfo.vPosition.x = 13.0f;
				enemyInfo.vPosition.z = m_InitPosList[std::stoi( enemyList[i+2] )];
				break;
			case enENEMY_DIRECTION::LEFT:
				// プレイヤー情報設定.
				enemyInfo.vPosition.x = -13.0f;
				enemyInfo.vPosition.z = m_InitPosList[std::stoi( enemyList[i+2] )];
				break;
			default:
				break;
		}

		// 各情報の設定.
		m_pEnemyList[enemyIndex]->SetCharacterParam( enemyInfo, enemyTypeList[type] );

		// 出現カウントの設定.
		m_pEnemyList[enemyIndex]->SetAppearanceCount( std::stoi(enemyList[i+3]) );

		enemyIndex++;
	}
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