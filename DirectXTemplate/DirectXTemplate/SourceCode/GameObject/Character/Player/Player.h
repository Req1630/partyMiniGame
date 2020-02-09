#ifndef PLAYER_H
#define PLAYER_H

#include "..\Character.h"
struct PLAYER_INFO;

class CPlayer : public CCharacter
{
private:
	const float MOVE_DIVISION		= 600000.0f;// 移動速度.
	const float OUTSIDE_STAGE_VALUE	= 3.5f;		// ステージ外の値.

public:
	CPlayer();
	virtual ~CPlayer();

	// 更新関数.
	virtual void Update() override;
	// 当たり判定関数.
	virtual void Collision( pCollisionManager ) override;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) override;

	// 操作関数.
	void Control();
	// プレイヤー人数の設定.
	void SetPlayerNumber( const int& playerNumber );

	// プレイヤー情報の設定.
	void SetPlayerParam( const PLAYER_INFO& playerInfo, const std::string& modelName );

private:
	// 移動関数.
	virtual void Move() override;
	// ステージ外に行かないようにする.
	void OutsideMove();

private:
	std::shared_ptr<CDX9StaticMesh> m_pStaticMesh;	// メッシュクラス.
	D3DXVECTOR2	m_MoveVector;		// 移動用ベクトル.
	D3DXVECTOR2 m_MovePower;		// 移動力.
	int m_PlayerNumber;				// プレイヤー人数.
	std::string m_ModelName;		// モデル名.
	D3DXVECTOR3 m_SphereAdjPosition;// スフィアの当たり判定座標.
	float m_SphereRadius;			// スフィアの当たり判定半径.
};

#endif	// #ifndef PLAYER_H.