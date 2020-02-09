#include "ControllerEdit.h"
#include "..\..\Utility\FileManager\FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

CControllerEdit::CControllerEdit()
{
	FileReading();
}

CControllerEdit::~CControllerEdit()
{
}

//--------------------------.
// �`��֐�.
//--------------------------.
void CControllerEdit::Render()
{
	ImGui::SetNextWindowSize( WINDOW_SIZE, ImGuiCond_::ImGuiCond_Once );
	ImGui::SetNextWindowPos( RENDER_POSITION, ImGuiCond_::ImGuiCond_Once );
	ImGui::GetWindowSize();

	bool isOpen = true;
	ImGui::GetStyle().Colors[ImGuiCol_::ImGuiCol_WindowBg] = { 0.3f, 0.3f, 0.3f, 0.9f };
	ImGui::Begin( u8"�R���g���[���[�ݒ�", &isOpen );

	ImGui::PushItemWidth( WINDOW_SIZE.x/2.0f );

	// ���x���̐ݒ� ( u8 �œ��{��\�� ).
	ImGui::LabelText( u8"�ύX�{�^��", u8"�ݒ�{�^��" );

	// �e���x���̕\��.
	for( int i = CXInput::A; i < CXInput::Max; i++ ){
		LabelRender( i );
	}

	// �{�^���ݒ�̌���.
	if( ImGui::Button( u8"����" ) ){
		ButtonSettingDetermination();
	}

	ImGui::End();
}

//--------------------------.
// ���x���̕`��.
//--------------------------.
void CControllerEdit::LabelRender( const int& index )
{
	// �ݒ�O�̃{�^�������L��.
	CXInput::enBUTTON_LIST oldNum = m_ItemList[index];

	// ���x���̕\��.
	if( ImGui::Combo( m_LabelList[index].u8string().c_str(), (int*)&m_ItemList[index], 
		BUTTON_ITEMS, IM_ARRAYSIZE(BUTTON_ITEMS) )){
		
		// �{�^�������ւ���.
		for( int i = CXInput::A; i < CXInput::Max; i++ ){
			if( i == index ) continue;
			if( m_ItemList[index] == m_ItemList[i] ){
				m_ItemList[i] = oldNum;
			}
		}
	}
}

//--------------------------.
// �{�^���ݒ�̌���.
//--------------------------.
void CControllerEdit::ButtonSettingDetermination()
{
	// �e��{�^����ݒ肷��.
	for( int i = CXInput::A; i < CXInput::Max; i++ ){
		CXInput::enBUTTON_LIST no = static_cast<CXInput::enBUTTON_LIST>(i);
		CXInput::SetButton( no, m_ItemList[no] );
	}
	// �t�@�C���ɏ�������.
	FileWriting();
}

//--------------------------.
// �t�@�C���̓ǂݍ���.
//--------------------------.
void CControllerEdit::FileReading()
{
	std::vector<std::string> readList;
	readList = CXInput::FileReading();

	// �e�L�X�g�̏����L��.
	for( size_t i = 0; i < readList.size(); i+=2 ){
		m_LabelList.emplace_back( readList[i].c_str() );
		CXInput::enBUTTON_LIST temp = static_cast<CXInput::enBUTTON_LIST>(std::stoi(readList[i+1]));
		m_ItemList.emplace_back( temp ); 
	}
}

//--------------------------.
// �t�@�C���̏�������.
//--------------------------.
void CControllerEdit::FileWriting()
{
	std::ofstream outFile;
	outFile.open( CXInput::FILE_PATH, std::ios::trunc );

	// �t�@�C�����ǂݍ��߂ĂȂ�������I��.
	if( !outFile.is_open() ) return;

	// ���X�g�̃T�C�Y���e�L�X�g�ɕۑ�.
	for( size_t i = 0; i < m_ItemList.size(); i++ ){
		outFile << m_LabelList[i].string() << ",";
		outFile << static_cast<int>(m_ItemList[i]) << std::endl;
	}

	outFile.close();
}