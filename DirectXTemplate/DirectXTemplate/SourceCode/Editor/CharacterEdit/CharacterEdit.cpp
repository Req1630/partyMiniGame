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
	ImGui::Begin( u8"�L�����N�^�[�ݒ�", &isOpen );

	ListBoxRender();
	CharacterParameterRender();
	CharacterParameterWriting();

	ImGui::End();
}

//-------------------------------.
// �v���C���[���X�g�̓ǂݍ���.
//-------------------------------.
void CCharacterEdit::CharacterListRead()
{
	std::vector<std::string> readList;
	readList = CFileManager::TextLoading( CHARACTER_LIST_FILE_PATH );

	// �e�L�X�g�̏����L��.
	for( size_t i = 0; i < readList.size(); i+=2 ){
		m_CharacterList.emplace_back( readList[i] );
		m_CharacterNameList.emplace_back( readList[i+1] );
	}
}

//-------------------------------.
// ���f���̕`��.
//-------------------------------.
void CCharacterEdit::ModelRender( scene::CSceneBase::SCENE_INIT_INFO& info )
{
	// ���b�V���̕`��.
	if( m_pStaticMesh == nullptr ) return;
	m_pStaticMesh->SetPosition( m_CharacterInfo.vPosition );
	m_pStaticMesh->SetRotation( m_CharacterInfo.vRotation );
	m_pStaticMesh->SetScale( m_CharacterInfo.ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );

	// �R���C�_�[�̕`��.
	m_pCollder->DebugRender( info.pCamera );
}

//-------------------------------.
// ���X�g�{�b�N�X�̕`��.
//-------------------------------.
void CCharacterEdit::ListBoxRender()
{
	// �L�����N�^�[���X�g�����I�m��.
	char** listBox = new char*[m_CharacterNameList.size()];
	for( size_t i = 0; i < m_CharacterNameList.size(); i++ ){
		listBox[i] = (char*)new char[m_CharacterNameList[i].u8string().length()+1];
		// ��������R�s�[.
		strcpy( (char*)listBox[i], m_CharacterNameList[i].u8string().c_str() );
	}

	// ���X�g�{�b�N�X�Ƃ��ĕ`��.
	if( ImGui::ListBox( u8"���f�����X�g", &m_NowSelectModel, 
		listBox, m_CharacterNameList.size(), 5 ) ){
		// ���f���̓ǂݍ���.
		m_pStaticMesh = CMeshResorce::GetStatic( m_CharacterList[m_NowSelectModel] );
		CharacterParameterReading();
		// �R���C�_�[�쐬.
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
// �L�����N�^�[�̒���.
//-------------------------------.
void CCharacterEdit::AdjustmentPlayer()
{
	if( GetAsyncKeyState('O') & 0x8000 ){
		// ���W�̐ݒ�.
		if( GetAsyncKeyState('P') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.vPosition.y += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.vPosition.y -= CHANGE_VALUE;
		}
		// ��]�̐ݒ�.
		if( GetAsyncKeyState('R') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.vRotation.y += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.vRotation.y -= CHANGE_VALUE;
		}
		// ���f���T�C�Y�̐ݒ�.
		if( GetAsyncKeyState('S') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.ModelScale += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.ModelScale -= CHANGE_VALUE;
		}
		// �X�t�B�A�̍��W�̐ݒ�.
		if( GetAsyncKeyState('I') & 0x8000 ){
			if( GetAsyncKeyState(VK_UP) & 0x0001 ) m_CharacterInfo.vSphereAdjPosition.y += CHANGE_VALUE;
			if( GetAsyncKeyState(VK_DOWN) & 0x0001 ) m_CharacterInfo.vSphereAdjPosition.y -= CHANGE_VALUE;
			if( m_pStaticMesh != nullptr ){
				m_pCollder->SetSphereAdjPosition( m_CharacterInfo.vSphereAdjPosition );
			}
		}
		// �X�t�B�A�̔��a�̐ݒ�.
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
// �L�����N�^�[�p�����[�^�`��.
//-------------------------------.
void CCharacterEdit::CharacterParameterRender()
{
	// �h���b�O�Ńp�����[�^��ύX.
	ImGui::DragFloat( u8" y ���W ", &m_CharacterInfo.vPosition.y, CHANGE_VALUE );
	ImGui::DragFloat( u8"���f���T�C�Y ", &m_CharacterInfo.ModelScale, CHANGE_VALUE );

	if( ImGui::DragFloat( u8"�����蔻����W ", 
		&m_CharacterInfo.vSphereAdjPosition.y, CHANGE_VALUE )){
		if( m_pStaticMesh != nullptr ){
			m_pCollder->SetSphereAdjPosition( m_CharacterInfo.vSphereAdjPosition );
		}
	}
	if( ImGui::DragFloat( u8"�����蔻�蔼�a ", 
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
// �L�����N�^�[�p�����[�^�̏�������.
//-------------------------------.
void CCharacterEdit::CharacterParameterWriting()
{
	if( ImGui::Button( "Save" )){
		CPlayerManager::PlayerParameterWriting( m_CharacterInfo, m_CharacterList[m_NowSelectModel] );
	}
}

//-------------------------------.
// �L�����N�^�[�p�����[�^�̓ǂݍ���.
//-------------------------------.
void CCharacterEdit::CharacterParameterReading()
{
	CPlayerManager::PlayerParameterReading( m_CharacterInfo, m_CharacterList[m_NowSelectModel] );
}