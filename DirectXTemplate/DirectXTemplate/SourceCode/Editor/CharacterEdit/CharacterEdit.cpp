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
	ImGui::Begin( u8"�L�����N�^�[�ݒ�", &isOpen );

	ListBoxRender();
	PlayerParameterRender();
	PlayerParameterWriting();

	ImGui::End();
}

//-------------------------------.
// �v���C���[���X�g�̓ǂݍ���.
//-------------------------------.
void CCharacterEdit::PlyaerListRead()
{
	std::vector<std::string> readList;
	readList = CFileManager::TextLoading( PLAYER_LIST_FILE_PATH );

	// �e�L�X�g�̏����L��.
	for( size_t i = 0; i < readList.size(); i+=2 ){
		m_PlayerList.emplace_back( readList[i] );
		m_PlayerNameList.emplace_back( readList[i+1] );
	}
}

//-------------------------------.
// ���f���̕`��.
//-------------------------------.
void CCharacterEdit::ModelRender( scene::CSceneBase::SCENE_INIT_INFO& info )
{
	// ���b�V���̕`��.
	if( m_pStaticMesh == nullptr ) return;
	m_pStaticMesh->SetPosition( m_PlayerInfo.vPosition );
	m_pStaticMesh->SetRotation( m_PlayerInfo.vRotation );
	m_pStaticMesh->SetScale( m_PlayerInfo.ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );

	// �R���C�_�[�̕`��.
	m_pCollder->DebugRender( info.pCamera );
}

//-------------------------------.
// ���X�g�{�b�N�X�̕`��.
//-------------------------------.
void CCharacterEdit::ListBoxRender()
{
	// �v���C���[���X�g�����I�m��.
	char** listBox = new char*[m_PlayerNameList.size()];
	for( size_t i = 0; i < m_PlayerNameList.size(); i++ ){
		listBox[i] = (char*)new char[m_PlayerNameList[i].u8string().length()+1];
		// ��������R�s�[.
		strcpy( (char*)listBox[i], m_PlayerNameList[i].u8string().c_str() );
	}

	// ���X�g�{�b�N�X�Ƃ��ĕ`��.
	if( ImGui::ListBox( u8"���f�����X�g", &m_NowSelectModel, 
		listBox, m_PlayerNameList.size(), 5 ) ){
		// ���f���̓ǂݍ���.
		m_pStaticMesh = CMeshResorce::GetStatic(m_PlayerList[m_NowSelectModel]);
		PlayerParameterReading();
		// �R���C�_�[�쐬.
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
// �v���C���[�̒���.
//-------------------------------.
void CCharacterEdit::AdjustmentPlayer()
{
	// ���W�̐ݒ�.
	if( GetAsyncKeyState('P') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.vPosition.y += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.vPosition.y -= CHANGE_VALUE;
	}
	// ��]�̐ݒ�.
	if( GetAsyncKeyState('R') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.vRotation.y += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.vRotation.y -= CHANGE_VALUE;
	}
	// ���f���T�C�Y�̐ݒ�.
	if( GetAsyncKeyState('S') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.ModelScale += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.ModelScale -= CHANGE_VALUE;
	}
	// �X�t�B�A�̍��W�̐ݒ�.
	if( GetAsyncKeyState('I') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_PlayerInfo.vSphereAdjPosition.y += CHANGE_VALUE;
		if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_PlayerInfo.vSphereAdjPosition.y -= CHANGE_VALUE;
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_PlayerInfo.vSphereAdjPosition );
		}
	}
	// �X�t�B�A�̔��a�̐ݒ�.
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
// �v���C���[�p�����[�^�`��.
//-------------------------------.
void CCharacterEdit::PlayerParameterRender()
{
	// �h���b�O�Ńp�����[�^��ύX.

	ImGui::DragFloat( u8" y ���W ", &m_PlayerInfo.vPosition.y, CHANGE_VALUE );
	ImGui::DragFloat( u8"���f���T�C�Y ", &m_PlayerInfo.ModelScale, CHANGE_VALUE );

	if( ImGui::DragFloat( u8"�����蔻����W ", 
		&m_PlayerInfo.vSphereAdjPosition.y, CHANGE_VALUE )){
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_PlayerInfo.vSphereAdjPosition );
		}
	}
	if( ImGui::DragFloat( u8"�����蔻�蔼�a ", 
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
// �v���C���[�p�����[�^�̏�������.
//-------------------------------.
void CCharacterEdit::PlayerParameterWriting()
{
	if( ImGui::Button( "Save" )){
		CPlayerManager::PlayerParameterWriting( m_PlayerInfo, m_PlayerList[m_NowSelectModel] );
	}
}

//-------------------------------.
// �v���C���[�p�����[�^�̓ǂݍ���.
//-------------------------------.
void CCharacterEdit::PlayerParameterReading()
{
	CPlayerManager::PlayerParameterReading( m_PlayerInfo, m_PlayerList[m_NowSelectModel] );
}