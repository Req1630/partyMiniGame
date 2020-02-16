#ifndef PLAYER_H
#define PLAYER_H

#include "..\Character.h"

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
	virtual void Collision( pGameObject ) override;
	// 描画関数.
	virtual void Render( SCENE_INFO& ) override;

	// プレイヤー同士の当たり判定.
	void PlayerToCollision( pGameObject );

	// 操作関数.
	void Control();
	// プレイヤー人数の設定.
	void SetPlayerNumber( const int& playerNumber );

private:
	// 移動関数.
	virtual void Move() override;
	// ステージ外に行かないようにする.
	void OutsideMove();

private:
	std::shared_ptr<CDX9StaticMesh> m_pStaticMesh;	// メッシュクラス.
	D3DXVECTOR2	m_MoveVector;		// 移動用ベクトル.
	D3DXVECTOR2 m_MovePower;		// 移動力.
	int			m_PlayerNumber;		// プレイヤー人数.
};

#endif	// #ifndef PLAYER_H.