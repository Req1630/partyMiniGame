#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "Player.h"

#include <vector>

class CPlayerManager
{
private:
	typedef scene::CSceneBase::SCENE_INIT_INFO SCENE_INFO;
	typedef std::shared_ptr<CGameObject> pGameObject;

public:
	inline static const char* PLAYER_PARAMETER_FILE_PATH	= "Data\\GameText\\Player\\";
	inline static const char* PLAYER_PARAMETER_FILE_EXE		= ".data";

public:
	CPlayerManager();
	~CPlayerManager();

	// 更新関数.
	void Update();
	// 当たり判定関数.
	void Collision( pGameObject );
	// 描画関数.
	void Render( SCENE_INFO& );

	// プレイヤー取得関数.
	std::shared_ptr<CPlayer> GetPlayer( const int index ) const;
	// プレイヤーリストサイズ取得関数.
	int GetPlayerSize() const { return m_PlayerList.size(); }


	// プレイヤーパラメータの書き込み.
	static void PlayerParameterWriting( const CHARACTER_INFO& playerInfo, std::string playerName );
	// プレイヤーパラメータの読み込み.
	static void PlayerParameterReading( CHARACTER_INFO& playerInfo, std::string playerName );

private:
	// プレイヤー同士の当たり判定.
	void PlayerToCollision();
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