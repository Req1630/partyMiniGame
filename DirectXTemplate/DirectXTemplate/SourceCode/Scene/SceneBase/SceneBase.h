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
		// シーン初期化用情報.
		struct SCENE_INIT_INFO
		{
			std::shared_ptr<CSceneManager> pSceneManager;
			std::shared_ptr<CCamera> pCamera;
			LIGHT* pLight;

			// シーンの追加.
			void Push( std::shared_ptr<CSceneBase> pScenebase );
			// シーンの取り出す.
			void Pop();
			// シーンを2つ取り出す.
			void TwoPop();
			// シーンを切り返る.
			void Change( std::shared_ptr<CSceneBase> pScenebase );

		};
	public:
		CSceneBase( SCENE_INIT_INFO sceneInitInfo )
			: m_Info	( sceneInitInfo )
		{}

		virtual ~CSceneBase(){};
	
		// 読込関数.
		virtual void Load() = 0;
		// 更新関数.
		virtual void Update() = 0;
		// 描画関数.
		virtual void Render() = 0;

		SCENE_INIT_INFO GetInfo(){ return m_Info; };

	protected:
		SCENE_INIT_INFO m_Info;	// シーン情報.

	private:
		// コピー・ムーブコンストラクタ, 代入演算子の削除.
		CSceneBase( const CSceneBase & )				= delete;
		CSceneBase& operator = ( const CSceneBase & )	= delete;
		CSceneBase( CSceneBase && )						= delete;
		CSceneBase& operator = ( CSceneBase && )		= delete;
	};
};	// namespace scene.

#endif // #ifndef SCENE_BASE_H.