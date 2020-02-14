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
	const ImVec2 WINDOW_SIZE				= { 350.0f, 350.0f };	// ウィンドウサイズ.
	const ImVec2 RENDER_POSITION			= { 10.0f, 350.0f };	// 描画座標.
	const float CHANGE_VALUE				= 0.001f;				// 変更用の値.
	const char* CHARACTER_LIST_FILE_PATH	= "Data\\GameText\\CharacterData\\CharacterList.txt";

public:
	CCharacterEdit();
	~CCharacterEdit();

	void Render( scene::CSceneBase::SCENE_INIT_INFO& );

private:
	// キャラクターリストの読み込み.
	void CharacterListRead();
	// モデルの描画.
	void ModelRender( scene::CSceneBase::SCENE_INIT_INFO& );
	// リストボックスの描画.
	void ListBoxRender();
	// キャラクターの調整.
	void AdjustmentPlayer();
	// キャラクターパラメータ描画.
	void CharacterParameterRender();
	// キャラクターパラメータの書き込み.
	void CharacterParameterWriting();
	// キャラクターパラメータの読み込み.
	void CharacterParameterReading();

private:
	std::shared_ptr<CDX9StaticMesh>	m_pStaticMesh;	// スタティックメッシュ.
	std::shared_ptr<CCollsionManager> m_pCollder;	// 当たり判定.
	std::vector<std::string> m_CharacterList;		// キャラクターリスト(英語).
	std::vector<fs::path> m_CharacterNameList;		// キャラクターリスト(日本語).
	int m_NowSelectModel;							// 現在選択しているモデル番号.

	CHARACTER_INFO m_CharacterInfo;					// キャラクター情報.

};

#endif	// #ifndef CHARACTER_EDIT_H.