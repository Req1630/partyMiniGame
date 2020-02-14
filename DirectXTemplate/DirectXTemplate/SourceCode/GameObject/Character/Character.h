#ifndef CHARACTER_H
#define CHARACTER_H

#include "..\GameObject.h"

// プレイヤー情報.
struct CHARACTER_INFO
{
	D3DXVECTOR3	vPosition;			// 座標.
	D3DXVECTOR3	vRotation;			// 回転.
	float		ModelScale;			// モデルスケール.
	D3DXVECTOR3	vSphereAdjPosition;	// スフィアの調整用座標.
	float		SphereAdjRdius;		// スフィアの調整用半径.

	CHARACTER_INFO()
		: vPosition				{ 0.0f, 0.0f, 0.0f }
		, vRotation				{ 0.0f, 0.0f, 0.0f }
		, ModelScale			( 1.0f )
		, vSphereAdjPosition	{ 0.0f, 0.0f, 0.0f }
		, SphereAdjRdius		( 0.0f )
	{}
};

class CCharacter : public CGameObject
{
public:
	inline static const char* CHARACTER_PARAMETER_FILE_PATH = "Data\\GameText\\CharacterData\\";
	inline static const char* CHARACTER_PARAMETER_FILE_EXE = ".data";

public:
	CCharacter();
	virtual ~CCharacter();

	// キャラクターパラメータの書き込み.
	static void CharacterParameterWriting( 
		const CHARACTER_INFO& characterInfo,
		const std::string& characterName );

	// キャラクターパラメータの読み込み.
	static void CharacterParameterReading( 
		CHARACTER_INFO& characterInfo,
		const std::string& characterName );

protected:
	// 移動関数.
	virtual void Move() = 0;
};

#endif	// #ifndef CHARACTER_H.