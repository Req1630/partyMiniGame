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
// �X�V�֐�.
//---------------------------.
void CEnemyManager::Update()
{
	m_GameCount++;	// �Q�[���J�E���g�̉��Z.
	
	// �e�G�̍X�V.
	for( auto& e : m_pEnemyList ){
		if( e->IsAppearance( m_GameCount ) == false ) continue;
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
		if( e->IsAppearance( m_GameCount ) == false ) continue;
		e->Render( info );
	}
}

//---------------------------.
// �G�擾�֐�.
//---------------------------.
std::shared_ptr<CGameObject> CEnemyManager::GetEnemy( const int index ) const
{
	if( static_cast<size_t>( index ) >= m_pEnemyList.size() ) return nullptr;
	if( m_pEnemyList[index]->IsAppearance( m_GameCount ) == false ) return nullptr;

	return m_pEnemyList[index];
}

//---------------------------.
// �G�̍쐬.
//---------------------------.
void CEnemyManager::EnemyCreating()
{
	// �G�̃��X�g�̏��.
	std::vector<std::string> enemyList;
	enemyList = CFileManager::TextLoading( ENEMY_LIST_PATH );

	// �G�̃��X�g.
	std::vector<std::string> enemyTypeList;
	enemyTypeList = CFileManager::TextLoading( ENEMY_TYPE_LIST_PATH );

	CHARACTER_INFO enemyInfo;

	int enemyIndex = 0;
	for( size_t i = 0;i < enemyList.size(); i+=4  ){
		m_pEnemyList.emplace_back( std::make_shared<CRunEnemy>() );

		// �G�^�C�v�̏��.
		int type = std::stoi(enemyList[i]);
		CCharacter::CharacterParameterReading( enemyInfo, enemyTypeList[type] );


		// �ړ���������̐ݒ�.
		int direction = std::stoi(enemyList[i+1]);
		enemyInfo.vRotation.y = static_cast<float>( D3DXToRadian( m_DirectionList[direction] ) );

		// �ړ���������ɂ�鏉�����W�̐ݒ�.
		enENEMY_DIRECTION dir = static_cast<enENEMY_DIRECTION>(direction);
		switch( dir ){
			case enENEMY_DIRECTION::UP:
				// �v���C���[���ݒ�.
				enemyInfo.vPosition.x = m_InitPosList[std::stoi( enemyList[i+2] )];
				enemyInfo.vPosition.z = 13.0f;
				break;
			case enENEMY_DIRECTION::DOWN:
				// �v���C���[���ݒ�.
				enemyInfo.vPosition.x = m_InitPosList[std::stoi( enemyList[i+2] )];
				enemyInfo.vPosition.z = -13.0f;
				break;
			case enENEMY_DIRECTION::RIGHT:
				// �v���C���[���ݒ�.
				enemyInfo.vPosition.x = 13.0f;
				enemyInfo.vPosition.z = m_InitPosList[std::stoi( enemyList[i+2] )];
				break;
			case enENEMY_DIRECTION::LEFT:
				// �v���C���[���ݒ�.
				enemyInfo.vPosition.x = -13.0f;
				enemyInfo.vPosition.z = m_InitPosList[std::stoi( enemyList[i+2] )];
				break;
			default:
				break;
		}

		// �e���̐ݒ�.
		m_pEnemyList[enemyIndex]->SetCharacterParam( enemyInfo, enemyTypeList[type] );

		// �o���J�E���g�̐ݒ�.
		m_pEnemyList[enemyIndex]->SetAppearanceCount( std::stoi(enemyList[i+3]) );

		enemyIndex++;
	}
}

//---------------------------.
// �������̓ǂݍ���.
//---------------------------.
void CEnemyManager::DirectionInfoReading()
{
	std::vector<std::string> dirList;
	dirList = CFileManager::TextLoading( ENEMY_DIRECTION_TEXT_PATH );

	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::UP)]) );	// ��.
	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::DOWN)]) );	// ��.
	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::RIGHT)]) );	// �E.
	m_DirectionList.emplace_back( std::stof(dirList[static_cast<int>(enENEMY_DIRECTION::LEFT)]) );	// ��.
}

//---------------------------.
// �������W�̓ǂݍ���.
//---------------------------.
void CEnemyManager::InitPositionReading()
{
	std::vector<std::string> posList;
	posList = CFileManager::TextLoading( ENEMY_INIT_POS_TEXT_PATH );

	for( const auto& l : posList ){
		m_InitPosList.emplace_back( std::stof(l) );	// �e������float�ɕϊ����Ă����.
	}
}