#include "EnemyBase.h"

CEnemyBase::CEnemyBase()
	: m_AppearanceCount	( 0 )
	, m_AttackCount		( 0 )
	, m_isAssailable	( false )
{
}

CEnemyBase::~CEnemyBase()
{
}

//--------------------------.
// 出現できるかどうか.
//--------------------------.
bool CEnemyBase::IsAppearance( const int& gameCount )
{
	// ゲームカウントが出現カウントより少なければ終了.
	if( m_AppearanceCount >= gameCount ) return false;

	// 多ければ true を入れて終了.
	return m_isAssailable = true;
}