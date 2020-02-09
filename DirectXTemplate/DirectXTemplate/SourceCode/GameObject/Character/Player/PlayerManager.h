#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "Player.h"

#include <vector>

// プレイヤー情報.
struct PLAYER_INFO
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vRotation;
	float ModelScale;
	D3DXVECTOR3 vSphereAdjPosition;
	float SphereAdjRdius;

	PLAYER_INFO()
		: vPosition				{ 0.0f, 0.0f, 0.0f }
		, vRotation				{ 0.0f, 0.0f, 0.0f }
		, ModelScale			( 1.0f )
		, vSphereAdjPosition	{ 0.0f, 0.0f, 0.0f }
		, SphereAdjRdius		( 0.0f )
	{}
};

class CPlayerManager
{
private:
	typedef scene::CSceneBase::SCENE_INIT_INFO SCENE_INFO;
	typedef std::shared_ptr<CCollsionManager> pCollisionManager;

public:
	inline static const char* PLAYER_PARAMETER_FILE_PATH	= "Data\\GameText\\Player\\";
	inline static const char* PLAYER_PARAMETER_FILE_EXE		= ".data";

public:
	CPlayerManager();
	~CPlayerManager();

	// 更新関数.
	void Update();
	// 当たり判定関数.
	void Collision( pCollisionManager );
	// 描画関数.
	void Render( SCENE_INFO& );

	// プレイヤーパラメータの書き込み.
	static void PlayerParameterWriting( const PLAYER_INFO& playerInfo, std::string playerName );
	// プレイヤーパラメータの読み込み.
	static void PlayerParameterReading( PLAYER_INFO& playerInfo, std::string playerName );
private:
	// プレイヤー作成.
	void PlayerCreating();
	// プレイヤー初期座標読込.
	void PlayerInitPosReading();

private:
	std::vector<std::shared_ptr<CPlayer>> m_PlayerList;	// プレイヤーリスト.

	int m_oldPlayerNumber;	// 前回取得したプレイヤー人数.
	std::vector<D3DXVECTOR3> m_InitPositionList;	// 初期座標リスト.
	std::vector<std::string> m_PlayModelList;		// 使用モデルリスト.
};

#endif	// #ifndef PLAYER_MANAGER_H.