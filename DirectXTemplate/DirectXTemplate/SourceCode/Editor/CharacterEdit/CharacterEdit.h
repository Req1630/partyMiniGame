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
	const ImVec2 WINDOW_SIZE		= { 350.0f, 350.0f };	// ウィンドウサイズ.
	const ImVec2 RENDER_POSITION	= { 10.0f, 350.0f };	// 描画座標.
	const float CHANGE_VALUE		= 0.001f;				// 変更用の値.
	const char* PLAYER_LIST_FILE_PATH		= "Data\\GameText\\Player\\PlayerList.txt";

public:
	CCharacterEdit();
	~CCharacterEdit();

	void Render( scene::CSceneBase::SCENE_INIT_INFO& );

private:
	// プレイヤーリストの読み込み.
	void PlyaerListRead();
	// モデルの描画.
	void ModelRender( scene::CSceneBase::SCENE_INIT_INFO& );
	// リストボックスの描画.
	void ListBoxRender();
	// プレイヤーの調整.
	void AdjustmentPlayer();
	// プレイヤーパラメータ描画.
	void PlayerParameterRender();
	// プレイヤーパラメータの書き込み.
	void PlayerParameterWriting();
	// プレイヤーパラメータの読み込み.
	void PlayerParameterReading();

private:
	std::shared_ptr<CDX9StaticMesh>	m_pStaticMesh;	// スタティックメッシュ.
	std::shared_ptr<CCollsionManager> m_pCollder;	// 当たり判定.
	std::vector<std::string> m_PlayerList;			// プレイヤーリスト(英語).
	std::vector<fs::path> m_PlayerNameList;			// プレイヤーリスト(日本語).
	int m_NowSelectModel;							// 現在選択しているモデル番号.

	PLAYER_INFO m_PlayerInfo;						// プレイヤー情報.

};

#endif	// #ifndef CHARACTER_EDIT_H.