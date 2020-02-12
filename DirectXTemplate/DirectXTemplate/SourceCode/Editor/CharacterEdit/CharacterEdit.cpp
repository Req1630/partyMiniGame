#define _CRT_SECURE_NO_WARNINGS

#include "CharacterEdit.h"
#include "..\..\Collider\CollsionManager\CollsionManager.h"
#include "..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\Utility\FileManager\FileManager.h"

CCharacterEdit::CCharacterEdit()
	: m_pStaticMesh			( nullptr )
	, m_pCollder			( std::make_shared<CCollsionManager>() )
	, m_CharacterList		()
	, m_CharacterNameList	()
	, m_NowSelectModel		( 0 )
	, m_CharacterInfo		()
{
	CharacterListRead();
}

CCharacterEdit::~CCharacterEdit()
{
}

void CCharacterEdit::Render( scene::CSceneBase::SCENE_INIT_INFO& info )
{
	ModelRender( info );
	AdjustmentPlayer();

	ImGui::SetNextWindowSize( WINDOW_SIZE, ImGuiCond_::ImGuiCond_Once );
	ImGui::SetNextWindowPos( RENDER_POSITION, ImGuiCond_::ImGuiCond_Once );
	ImGui::GetWindowSize();

	bool isOpen = true;
	ImGui::GetStyle().Colors[ImGuiCol_::ImGuiCol_WindowBg] = { 0.3f, 0.3f, 0.3f, 0.9f };
	ImGui::Begin( u8"キャラクター設定", &isOpen );

	ListBoxRender();
	CharacterParameterRender();
	CharacterParameterWriting();

	ImGui::End();
}

//-------------------------------.
// プレイヤーリストの読み込み.
//-------------------------------.
void CCharacterEdit::CharacterListRead()
{
	std::vector<std::string> readList;
	readList = CFileManager::TextLoading( CHARACTER_LIST_FILE_PATH );

	// テキストの情報を記憶.
	for( size_t i = 0; i < readList.size(); i+=2 ){
		m_CharacterList.emplace_back( readList[i] );
		m_CharacterNameList.emplace_back( readList[i+1] );
	}
}

//-------------------------------.
// モデルの描画.
//-------------------------------.
void CCharacterEdit::ModelRender( scene::CSceneBase::SCENE_INIT_INFO& info )
{
	// メッシュの描画.
	if( m_pStaticMesh == nullptr ) return;
	m_pStaticMesh->SetPosition( m_CharacterInfo.vPosition );
	m_pStaticMesh->SetRotation( m_CharacterInfo.vRotation );
	m_pStaticMesh->SetScale( m_CharacterInfo.ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );

	// コライダーの描画.
	m_pCollder->DebugRender( info.pCamera );
}

//-------------------------------.
// リストボックスの描画.
//-------------------------------.
void CCharacterEdit::ListBoxRender()
{
	// キャラクターリスト分動的確保.
	char** listBox = new char*[m_CharacterNameList.size()];
	for( size_t i = 0; i < m_CharacterNameList.size(); i++ ){
		listBox[i] = (char*)new char[m_CharacterNameList[i].u8string().length()+1];
		// 文字列をコピー.
		strcpy( (char*)listBox[i], m_CharacterNameList[i].u8string().c_str() );
	}

	// リストボックスとして描画.
	if( ImGui::ListBox( u8"モデルリスト", &m_NowSelectModel, 
		listBox, m_CharacterNameList.size(), 5 ) ){
		// モデルの読み込み.
		m_pStaticMesh = CMeshResorce::GetStatic( m_CharacterList[m_NowSelectModel] );
		CharacterParameterReading();
		// コライダー作成.
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_CharacterInfo.vSphereAdjPosition );
			m_pCollder->SetSphereAdjRadius( m_CharacterInfo.SphereAdjRdius );
			m_pCollder->Init( m_pStaticMesh->GetMesh(),
				&m_CharacterInfo.vPosition,
				&m_CharacterInfo.vRotation,
				&m_CharacterInfo.ModelScale );
		}
	}

	for( size_t i = 0; i < m_CharacterNameList.size(); i++ )  delete listBox[i];
	delete listBox;
}

//-------------------------------.
// キャラクターの調整.
//-------------------------------.
void CCharacterEdit::AdjustmentPlayer()
{
	if( GetAsyncKeyState('O') & 0x8000 ){
		// 座標の設定.
		if( GetAsyncKeyState('P') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.vPosition.y += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.vPosition.y -= CHANGE_VALUE;
		}
		// 回転の設定.
		if( GetAsyncKeyState('R') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.vRotation.y += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.vRotation.y -= CHANGE_VALUE;
		}
		// モデルサイズの設定.
		if( GetAsyncKeyState('S') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.ModelScale += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.ModelScale -= CHANGE_VALUE;
		}
		// スフィアの座標の設定.
		if( GetAsyncKeyState('I') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.vSphereAdjPosition.y += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.vSphereAdjPosition.y -= CHANGE_VALUE;
			if( m_pStaticMesh != nullptr ){
				m_pCollder->SetSphereAdjPosition( m_CharacterInfo.vSphereAdjPosition );
			}
		}
		// スフィアの半径の設定.
		if( GetAsyncKeyState('D') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.SphereAdjRdius += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.SphereAdjRdius -= CHANGE_VALUE;
			if( m_pStaticMesh != nullptr ){
				m_pCollder->SetSphereAdjRadius( m_CharacterInfo.SphereAdjRdius );
				m_pCollder->Init( m_pStaticMesh->GetMesh(),
					&m_CharacterInfo.vPosition,
					&m_CharacterInfo.vRotation,
					&m_CharacterInfo.ModelScale );
			}
		}
	}
}

//-------------------------------.
// キャラクターパラメータ描画.
//-------------------------------.
void CCharacterEdit::CharacterParameterRender()
{
	// ドラッグでパラメータを変更.
	ImGui::DragFloat( u8" y 座標 ", &m_CharacterInfo.vPosition.y, CHANGE_VALUE );
	ImGui::DragFloat( u8"モデルサイズ ", &m_CharacterInfo.ModelScale, CHANGE_VALUE );

	if( ImGui::DragFloat( u8"当たり判定座標 ", 
		&m_CharacterInfo.vSphereAdjPosition.y, CHANGE_VALUE )){
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_CharacterInfo.vSphereAdjPosition );
		}
	}
	if( ImGui::DragFloat( u8"当たり判定半径 ", 
		&m_CharacterInfo.SphereAdjRdius, CHANGE_VALUE )){
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjRadius( m_CharacterInfo.SphereAdjRdius );
			m_pCollder->Init( m_pStaticMesh->GetMesh(),
				&m_CharacterInfo.vPosition,
				&m_CharacterInfo.vRotation,
				&m_CharacterInfo.ModelScale );
		}
	}
}

//-------------------------------.
// キャラクターパラメータの書き込み.
//-------------------------------.
void CCharacterEdit::CharacterParameterWriting()
{
	if( ImGui::Button( "Save" )){
		CPlayerManager::PlayerParameterWriting( m_CharacterInfo, m_CharacterList[m_NowSelectModel] );
	}
}

//-------------------------------.
// キャラクターパラメータの読み込み.
//-------------------------------.
void CCharacterEdit::CharacterParameterReading()
{
	CPlayerManager::PlayerParameterReading( m_CharacterInfo, m_CharacterList[m_NowSelectModel] );
}