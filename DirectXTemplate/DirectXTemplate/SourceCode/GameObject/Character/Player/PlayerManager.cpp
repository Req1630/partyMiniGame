#include "PlayerManager.h"
#include "..\..\..\Utility\XInput\XInput.h"
#include "..\..\..\Utility\FileManager\FileManager.h"

CPlayerManager::CPlayerManager()
	: m_PlayerList			()
	, m_oldPlayerNumber		()
	, m_InitPositionList	()
{
	// プレイヤーの初期座標読み込み.
	PlayerInitPosReading();

	// プレイヤーを作成する.
	PlayerCreating();
}

CPlayerManager::~CPlayerManager()
{
}

//-------------------------------.
// 更新関数.
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
// 当たり判定関数.
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
// 描画関数.
//-------------------------------.
void CPlayerManager::Render( SCENE_INFO& info )
{
	for( auto& p : m_PlayerList ){
		p->Render( info );
	}
}

//-------------------------------.
// プレイヤー作成.
//-------------------------------.
void CPlayerManager::PlayerCreating()
{
	// 前回取得したプレイヤーと一緒なら終了.
	if( m_oldPlayerNumber == CXInput::GetConnectCount() ) return;

	m_PlayerList.clear();	// リストをクリアする.

	int playerNumber = m_oldPlayerNumber = CXInput::GetConnectCount();

	// プレイヤーの人数分作成する.
	for( int i = 0; i < playerNumber; i++ ){
		m_PlayerList.emplace_back( std::make_shared<CPlayer>() );
		// プレイヤー人数設定.
		m_PlayerList[i]->SetPlayerNumber( i );

		PLAYER_INFO playerInfo;
		// プレイヤー情報の読込.
		PlayerParameterReading( playerInfo, m_PlayModelList[i] );
		playerInfo.vPosition.x = m_InitPositionList[i].x;
		playerInfo.vPosition.z = m_InitPositionList[i].z;
		// プレイヤー情報設定.
		m_PlayerList[i]->SetPlayerParam( playerInfo, m_PlayModelList[i] );
	}
}

//-------------------------------.
// プレイヤー初期座標読込.
//-------------------------------.
void CPlayerManager::PlayerInitPosReading()
{
	std::vector<std::string> readList;
	readList = CFileManager::TextLoading( "Data\\GameText\\Player\\PlayerInitList.txt" );

	// 取得したリストのサイズがなければ終了.
	if( readList.empty() == true ) return;

	for( size_t i = 0; i < readList.size(); i+=4 ){
		D3DXVECTOR3 pos = 
		{
			std::stof(readList[i]),		// x.
			std::stof(readList[i+1]),	// y.
			std::stof(readList[i+2])	// z.
		};
		m_InitPositionList.emplace_back( pos );
		// 使用モデル名.
		m_PlayModelList.emplace_back( readList[i+3] );
	}
}

//-------------------------------.
// プレイヤーパラメータの書き込み.
//-------------------------------.
void CPlayerManager::PlayerParameterWriting( const PLAYER_INFO& playerInfo, std::string playerName )
{
	std::string path = CPlayerManager::PLAYER_PARAMETER_FILE_PATH;
	path += playerName + CPlayerManager::PLAYER_PARAMETER_FILE_EXE;

	CFileManager::BinaryWriting( path, playerInfo );
}

//-------------------------------.
// プレイヤーパラメータの読み込み.
//-------------------------------.
void CPlayerManager::PlayerParameterReading( PLAYER_INFO& playerInfo, std::string playerName )
{
	std::string path = CPlayerManager::PLAYER_PARAMETER_FILE_PATH;
	path += playerName + CPlayerManager::PLAYER_PARAMETER_FILE_EXE;

	CFileManager::BinaryReading( path, playerInfo );
}