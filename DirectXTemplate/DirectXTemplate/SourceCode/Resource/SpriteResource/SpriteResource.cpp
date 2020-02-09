#include "SpriteResource.h"
#include "..\..\Utility\FileManager\FileManager.h"

CSpriteResource::CSpriteResource()
	: m_SpriteList			()
	, m_HasFinishedLoading	( false )
{
}

CSpriteResource::~CSpriteResource()
{
	m_SpriteList.clear();
}

//-------------------------------.
// �C���X�^���X�̎擾.
//-------------------------------.
CSpriteResource* CSpriteResource::GetInstance()
{
	static std::unique_ptr<CSpriteResource> pInstance = 
		std::make_unique<CSpriteResource>();
	return pInstance.get();
}

//-------------------------------.
// �X�v���C�g�̓ǂݍ���(���b�p�[).
//-------------------------------.
void CSpriteResource::Load( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	GetInstance()->SpriteLoad( pDevice11, pContext11 );
}

//-------------------------------.
// �X�v���C�g�擾�֐�.
//-------------------------------.
std::shared_ptr<CSprite> CSpriteResource::GetSprite( const std::string& spriteName )
{
	// �w�肵���X�v���C�g�����擾����.
	for( auto& s : GetInstance()->m_SpriteList ){
		if( s.first == spriteName ) return s.second;
	}

	// �X�v���C�g�̓Ǎ����I�����ĂȂ��̂� null ��Ԃ�.
	if( GetInstance()->m_HasFinishedLoading == false ) return nullptr;

	ERROR_MESSAGE( "�X�v���C�g��������܂���" );
	return nullptr;
}

//-------------------------------.
// �X�v���C�g�ǂݍ���.
//-------------------------------.
void CSpriteResource::SpriteLoad( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	auto eachLoad = [&]( const fs::directory_entry& entry )
	{
		const std::string exe		= entry.path().extension().string();	// �g���q.
		const std::string filePath	= entry.path().string();				// �t�@�C���p�X.
		const std::string fileName	= entry.path().stem().string();			// �t�@�C����.

		// �w�肵���g���q�ȊO�͓ǂݍ���.
		if( exe != ".png" && exe != ".PNG" && 
			exe != ".bmp" && exe != ".BMP" &&
			exe != ".jpg" && exe != ".JPG" ) return;

		CSprite::SPRITE_STATE ss = SpriteStateRead( filePath );
		m_SpriteList[fileName] =
			std::make_shared<CSprite>( pDevice11, pContext11, filePath.c_str(), ss );
	};

	try {
		fs::recursive_directory_iterator dir_itr(FILE_PATH), end_itr;
		std::for_each( dir_itr, end_itr, eachLoad );
	} catch ( const fs::filesystem_error& ){

	}

	// �Ǎ����I������̂� true �ɂ���.
	m_HasFinishedLoading = true;
}

//-------------------------------.
// �X�v���C�g���̓ǂݍ���.
//-------------------------------.
CSprite::SPRITE_STATE CSpriteResource::SpriteStateRead( const std::string& path )
{
	CSprite::SPRITE_STATE ss;

	std::string filePath = path;
	// �g���q��"."�̈ʒu���擾.
	size_t i = filePath.find(".");
	// �g���q��菜����".txt"�ɕύX.
	filePath.erase( i, filePath.size() ) += ".txt";

	std::vector<std::string> pramList = CFileManager::TextLoading( filePath );
	
	if( pramList.empty() == true ){
		ERROR_MESSAGE("���X�g����ł���.");
		return ss;
	}

	ss.Disp.w	= std::stof(pramList[ss.enDisp_w]);
	ss.Disp.h	= std::stof(pramList[ss.enDisp_h]);
	ss.Base.w	= std::stof(pramList[ss.enBase_w]);
	ss.Base.h	= std::stof(pramList[ss.enBase_h]);
	ss.Stride.w	= std::stof(pramList[ss.enStride_w]);
	ss.Stride.h	= std::stof(pramList[ss.enStride_h]);
	ss.vPos.x	= std::stof(pramList[ss.envPos_x]);
	ss.vPos.y	= std::stof(pramList[ss.envPos_y]);
	ss.vPos.z	= std::stof(pramList[ss.envPos_z]);
	ss.FrameNum	= std::stoi(pramList[ss.enFrameNum]);

	return ss;
}