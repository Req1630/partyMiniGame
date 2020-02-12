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

	// �X�V�֐�.
	void Update();
	// �����蔻��֐�.
	void Collision( pGameObject );
	// �`��֐�.
	void Render( SCENE_INFO& );

	// �v���C���[�擾�֐�.
	std::shared_ptr<CPlayer> GetPlayer( const int index ) const;
	// �v���C���[���X�g�T�C�Y�擾�֐�.
	int GetPlayerSize() const { return m_PlayerList.size(); }


	// �v���C���[�p�����[�^�̏�������.
	static void PlayerParameterWriting( const CHARACTER_INFO& playerInfo, std::string playerName );
	// �v���C���[�p�����[�^�̓ǂݍ���.
	static void PlayerParameterReading( CHARACTER_INFO& playerInfo, std::string playerName );

private:
	// �v���C���[���m�̓����蔻��.
	void PlayerToCollision();
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