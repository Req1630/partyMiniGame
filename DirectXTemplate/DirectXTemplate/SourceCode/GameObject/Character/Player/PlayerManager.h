#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "Player.h"

#include <vector>

// �v���C���[���.
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

	// �X�V�֐�.
	void Update();
	// �����蔻��֐�.
	void Collision( pCollisionManager );
	// �`��֐�.
	void Render( SCENE_INFO& );

	// �v���C���[�p�����[�^�̏�������.
	static void PlayerParameterWriting( const PLAYER_INFO& playerInfo, std::string playerName );
	// �v���C���[�p�����[�^�̓ǂݍ���.
	static void PlayerParameterReading( PLAYER_INFO& playerInfo, std::string playerName );
private:
	// �v���C���[�쐬.
	void PlayerCreating();
	// �v���C���[�������W�Ǎ�.
	void PlayerInitPosReading();

private:
	std::vector<std::shared_ptr<CPlayer>> m_PlayerList;	// �v���C���[���X�g.

	int m_oldPlayerNumber;	// �O��擾�����v���C���[�l��.
	std::vector<D3DXVECTOR3> m_InitPositionList;	// �������W���X�g.
	std::vector<std::string> m_PlayModelList;		// �g�p���f�����X�g.
};

#endif	// #ifndef PLAYER_MANAGER_H.