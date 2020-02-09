#include "PlayerManager.h"
#include "..\..\..\Utility\XInput\XInput.h"
#include "..\..\..\Utility\FileManager\FileManager.h"

CPlayerManager::CPlayerManager()
	: m_PlayerList			()
	, m_oldPlayerNumber		()
	, m_InitPositionList	()
{
	// �v���C���[�̏������W�ǂݍ���.
	PlayerInitPosReading();

	// �v���C���[���쐬����.
	PlayerCreating();
}

CPlayerManager::~CPlayerManager()
{
}

//-------------------------------.
// �X�V�֐�.
//-------------------------------.
void CPlayerManager::Update()
{
	PlayerCreating();
	for( auto& p : m_PlayerList ){
		p->Control();
		p->Update();
	}
}

//-------------------------------.
// �����蔻��֐�.
//-------------------------------.
void CPlayerManager::Collision( pCollisionManager pColl )
{
	for( size_t i = 0; i < m_PlayerList.size(); i++ ){
		for( size_t j = 0; j < m_PlayerList.size(); j++ ){
			if( i == j ) continue;
			m_PlayerList[i]->Collision( m_PlayerList[j]->GetCollider() );
		}
	}
}

//-------------------------------.
// �`��֐�.
//-------------------------------.
void CPlayerManager::Render( SCENE_INFO& info )
{
	for( auto& p : m_PlayerList ){
		p->Render( info );
	}
}

//-------------------------------.
// �v���C���[�쐬.
//-------------------------------.
void CPlayerManager::PlayerCreating()
{
	// �O��擾�����v���C���[�ƈꏏ�Ȃ�I��.
	if( m_oldPlayerNumber == CXInput::GetConnectCount() ) return;

	m_PlayerList.clear();	// ���X�g���N���A����.

	int playerNumber = m_oldPlayerNumber = CXInput::GetConnectCount();

	// �v���C���[�̐l�����쐬����.
	for( int i = 0; i < playerNumber; i++ ){
		m_PlayerList.emplace_back( std::make_shared<CPlayer>() );
		// �v���C���[�l���ݒ�.
		m_PlayerList[i]->SetPlayerNumber( i );

		PLAYER_INFO playerInfo;
		// �v���C���[���̓Ǎ�.
		PlayerParameterReading( playerInfo, m_PlayModelList[i] );
		playerInfo.vPosition.x = m_InitPositionList[i].x;
		playerInfo.vPosition.z = m_InitPositionList[i].z;
		// �v���C���[���ݒ�.
		m_PlayerList[i]->SetPlayerParam( playerInfo, m_PlayModelList[i] );
	}
}

//-------------------------------.
// �v���C���[�������W�Ǎ�.
//-------------------------------.
void CPlayerManager::PlayerInitPosReading()
{
	std::vector<std::string> readList;
	readList = CFileManager::TextLoading( "Data\\GameText\\Player\\PlayerInitList.txt" );

	// �擾�������X�g�̃T�C�Y���Ȃ���ΏI��.
	if( readList.empty() == true ) return;

	for( size_t i = 0; i < readList.size(); i+=4 ){
		D3DXVECTOR3 pos = 
		{
			std::stof(readList[i]),		// x.
			std::stof(readList[i+1]),	// y.
			std::stof(readList[i+2])	// z.
		};
		m_InitPositionList.emplace_back( pos );
		// �g�p���f����.
		m_PlayModelList.emplace_back( readList[i+3] );
	}
}

//-------------------------------.
// �v���C���[�p�����[�^�̏�������.
//-------------------------------.
void CPlayerManager::PlayerParameterWriting( const PLAYER_INFO& playerInfo, std::string playerName )
{
	std::string path = CPlayerManager::PLAYER_PARAMETER_FILE_PATH;
	path += playerName + CPlayerManager::PLAYER_PARAMETER_FILE_EXE;

	CFileManager::BinaryWriting( path, playerInfo );
}

//-------------------------------.
// �v���C���[�p�����[�^�̓ǂݍ���.
//-------------------------------.
void CPlayerManager::PlayerParameterReading( PLAYER_INFO& playerInfo, std::string playerName )
{
	std::string path = CPlayerManager::PLAYER_PARAMETER_FILE_PATH;
	path += playerName + CPlayerManager::PLAYER_PARAMETER_FILE_EXE;

	CFileManager::BinaryReading( path, playerInfo );
}