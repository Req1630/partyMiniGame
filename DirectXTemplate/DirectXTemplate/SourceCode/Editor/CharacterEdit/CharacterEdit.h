#ifndef CHARACTER_EDIT_H
#define CHARACTER_EDIT_H

#include "..\..\GameObject\Character\Player\PlayerManager.h"

#include "..\..\Utility\ImGuiManager\ImGuiManager.h"
#include "..\..\Scene\SceneBase\SceneBase.h"

#include <filesystem>

namespace fs = std::filesystem;

class CCollsionManager;

class CCharacterEdit
{
private:
	const ImVec2 WINDOW_SIZE				= { 350.0f, 350.0f };	// �E�B���h�E�T�C�Y.
	const ImVec2 RENDER_POSITION			= { 10.0f, 350.0f };	// �`����W.
	const float CHANGE_VALUE				= 0.001f;				// �ύX�p�̒l.
	const char* CHARACTER_LIST_FILE_PATH	= "Data\\GameText\\CharacterData\\CharacterList.txt";

public:
	CCharacterEdit();
	~CCharacterEdit();

	void Render( scene::CSceneBase::SCENE_INIT_INFO& );

private:
	// �L�����N�^�[���X�g�̓ǂݍ���.
	void CharacterListRead();
	// ���f���̕`��.
	void ModelRender( scene::CSceneBase::SCENE_INIT_INFO& );
	// ���X�g�{�b�N�X�̕`��.
	void ListBoxRender();
	// �L�����N�^�[�̒���.
	void AdjustmentPlayer();
	// �L�����N�^�[�p�����[�^�`��.
	void CharacterParameterRender();
	// �L�����N�^�[�p�����[�^�̏�������.
	void CharacterParameterWriting();
	// �L�����N�^�[�p�����[�^�̓ǂݍ���.
	void CharacterParameterReading();

private:
	std::shared_ptr<CDX9StaticMesh>	m_pStaticMesh;	// �X�^�e�B�b�N���b�V��.
	std::shared_ptr<CCollsionManager> m_pCollder;	// �����蔻��.
	std::vector<std::string> m_CharacterList;		// �L�����N�^�[���X�g(�p��).
	std::vector<fs::path> m_CharacterNameList;		// �L�����N�^�[���X�g(���{��).
	int m_NowSelectModel;							// ���ݑI�����Ă��郂�f���ԍ�.

	CHARACTER_INFO m_CharacterInfo;					// �L�����N�^�[���.

};

#endif	// #ifndef CHARACTER_EDIT_H.