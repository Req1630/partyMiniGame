#define _CRT_SECURE_NO_WARNINGS

#include "CharacterEdit.h"
#include "..\..\Collider\CollsionManager\CollsionManager.h"
#include "..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\Utility\FileManager\FileManager.h"

CCharacterEdit::CCharacterEdit()
	: m_pStaticMesh		( nullptr )
	, m_pCollder		( std::make_shared<CCollsionManager>() )
	, m_PlayerList		()
	, m_PlayerNameList	()
	, m_NowSelectModel	( 0 )
	, m_PlayerInfo		()
{
	PlyaerListRead();
}

CCharacterEdit::~CCharacterEdit()
{
}

void CCharacterEdit::Render( scene::CSceneBase::SCENE_INIT_INFO& info )
{
	AdjustmentPlayer();
	ModelRender( info );

	ImGui::SetNextWindowSize( WINDOW_SIZE, ImGuiCond_::ImGuiCond_Once );
	ImGui::SetNextWindowPos( RENDER_POSITION, ImGuiCond_::ImGuiCond_Once );
	ImGui::GetWindowSize();

	bool isOpen = true;
	ImGui::GetStyle().Colors[ImGuiCol_::ImGuiCol_WindowBg] = { 0.3f, 0.3f, 0.3f, 0.9f };
	ImGui::Begin( u8"キャラクター設定", &isOpen );

	ListBoxRender();
	PlayerParameterRender();
	PlayerParameterWriting();

	ImGui::End();
}

//-------------------------------.
// プレイヤーリストの読み込み.
//-------------------------------.
void CCharacterEdit::PlyaerListRead()
{
	std::vector<std::string> readList;
	readList = CFileManager::TextLoading( PLAYER_LIST_FILE_PATH );

	// テキストの情報を記憶.
	for( size_t i = 0; i < readList.size(); i+=2 ){
		m_PlayerList.emplace_back( readList[i] );
		m_PlayerNameList.emplace_back( readList[i+1] );
	}
}

//-------------------------------.
// モデルの描画.
//-------------------------------.
void CCharacterEdit::ModelRender( scene::CSceneBase::SCENE_INIT_INFO& info )
{
	// メッシュの描画.
	if( m_pStaticMesh == nullptr ) return;
	m_pStaticMesh->SetPosition( m_PlayerInfo.vPosition );
	m_pStaticMesh->SetRotation( m_PlayerInfo.vRotation );
	m_pStaticMesh->SetScale( m_PlayerInfo.ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );

	// コライダーの描画.
	m_pCollder->DebugRender( info.pCamera );
}

//-------------------------------.
// リストボックスの描画.
//-------------------------------.
void CCharacterEdit::ListBoxRender()
{
	// プレイヤーリスト分動的確保.
	char** listBox = new char*[m_PlayerNameList.size()];
	for( size_t i = 0; i < m_PlayerNameList.size(); i++ ){
		listBox[i] = (char*)new char[m_PlayerNameList[i].u8string().length()+1];
		// 文字列をコピー.
		strcpy( (char*)listBox[i], m_PlayerNameList[i].u8string().c_str() );
	}

	// リストボックスとして描画.
	if( ImGui::ListBox( u8"モデルリスト", &m_NowSelectModel, 
		listBox, m_PlayerNameList.size(), 5 ) ){
		// モデルの読み込み.
		m_pStaticMesh = CMeshResorce::GetStatic(m_PlayerList[m_NowSelectModel]);
		PlayerParameterReading();
		// コライダー作成.
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_PlayerInfo.vSphereAdjPosition );
			m_pCollder->SetSphereAdjRadius( m_PlayerInfo.SphereAdjRdius );
			m_pCollder->Init( m_pStaticMesh->GetMesh(),
				&m_PlayerInfo.vPosition,
				&m_PlayerInfo.vRotation,
				&m_PlayerInfo.ModelScale );
		}
	}

	for( size_t i = 0; i < m_PlayerNameList.size(); i++ )  delete listBox[i];
	delete listBox;
}

//-------------------------------.
// プレイヤーの調整.
//-------------------------------.
void CCharacterEdit::AdjustmentPlayer()
{
	// 座標の設定.
	if( GetAsyncKeyState('P') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.vPosition.y += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.vPosition.y -= CHANGE_VALUE;
	}
	// 回転の設定.
	if( GetAsyncKeyState('R') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.vRotation.y += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.vRotation.y -= CHANGE_VALUE;
	}
	// モデルサイズの設定.
	if( GetAsyncKeyState('S') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.ModelScale += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.ModelScale -= CHANGE_VALUE;
	}
	// スフィアの座標の設定.
	if( GetAsyncKeyState('I') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.vSphereAdjPosition.y += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.vSphereAdjPosition.y -= CHANGE_VALUE;
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_PlayerInfo.vSphereAdjPosition );
		}
	}
	// スフィアの半径の設定.
	if( GetAsyncKeyState('D') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.SphereAdjRdius += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.SphereAdjRdius -= CHANGE_VALUE;
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjRadius( m_PlayerInfo.SphereAdjRdius );
			m_pCollder->Init( m_pStaticMesh->GetMesh(),
				&m_PlayerInfo.vPosition,
				&m_PlayerInfo.vRotation,
				&m_PlayerInfo.ModelScale );
		}
	}
}

//-------------------------------.
// プレイヤーパラメータ描画.
//-------------------------------.
void CCharacterEdit::PlayerParameterRender()
{
	// ドラッグでパラメータを変更.

	ImGui::DragFloat( u8" y 座標 ", &m_PlayerInfo.vPosition.y, CHANGE_VALUE );
	ImGui::DragFloat( u8"モデルサイズ ", &m_PlayerInfo.ModelScale, CHANGE_VALUE );

	if( ImGui::DragFloat( u8"当たり判定座標 ", 
		&m_PlayerInfo.vSphereAdjPosition.y, CHANGE_VALUE )){
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_PlayerInfo.vSphereAdjPosition );
		}
	}
	if( ImGui::DragFloat( u8"当たり判定半径 ", 
		&m_PlayerInfo.SphereAdjRdius, CHANGE_VALUE )){
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjRadius( m_PlayerInfo.SphereAdjRdius );
			m_pCollder->Init( m_pStaticMesh->GetMesh(),
				&m_PlayerInfo.vPosition,
				&m_PlayerInfo.vRotation,
				&m_PlayerInfo.ModelScale );
		}
	}
}

//-------------------------------.
// プレイヤーパラメータの書き込み.
//-------------------------------.
void CCharacterEdit::PlayerParameterWriting()
{
	if( ImGui::Button( "Save" )){
		CPlayerManager::PlayerParameterWriting( m_PlayerInfo, m_PlayerList[m_NowSelectModel] );
	}
}

//-------------------------------.
// プレイヤーパラメータの読み込み.
//-------------------------------.
void CCharacterEdit::PlayerParameterReading()
{
	CPlayerManager::PlayerParameterReading( m_PlayerInfo, m_PlayerList[m_NowSelectModel] );
}