#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include <Windows.h>
#include <string>
#include <stack>
#include <memory>

#include "..\..\Global.h"

namespace scene
{
	class CSceneManager;

	class CSceneBase
	{
	public:
		// �V�[���������p���.
		struct SCENE_INIT_INFO
		{
			std::shared_ptr<CSceneManager> pSceneManager;
			std::shared_ptr<CCamera> pCamera;
			LIGHT* pLight;

			// �V�[���̒ǉ�.
			void Push( std::shared_ptr<CSceneBase> pScenebase );
			// �V�[���̎��o��.
			void Pop();
			// �V�[����2���o��.
			void TwoPop();
			// �V�[����؂�Ԃ�.
			void Change( std::shared_ptr<CSceneBase> pScenebase );

		};
	public:
		CSceneBase( SCENE_INIT_INFO sceneInitInfo )
			: m_Info	( sceneInitInfo )
		{}

		virtual ~CSceneBase(){};
	
		// �Ǎ��֐�.
		virtual void Load() = 0;
		// �X�V�֐�.
		virtual void Update() = 0;
		// �`��֐�.
		virtual void Render() = 0;

		SCENE_INIT_INFO GetInfo(){ return m_Info; };

	protected:
		SCENE_INIT_INFO m_Info;	// �V�[�����.

	private:
		// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
		CSceneBase( const CSceneBase & )				= delete;
		CSceneBase& operator = ( const CSceneBase & )	= delete;
		CSceneBase( CSceneBase && )						= delete;
		CSceneBase& operator = ( CSceneBase && )		= delete;
	};
};	// namespace scene.

#endif // #ifndef SCENE_BASE_H.