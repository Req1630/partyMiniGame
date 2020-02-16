#include "EnemyBase.h"

CEnemyBase::CEnemyBase()
	: m_AttackCount		( 0 )
	, m_isAssailable	( false )
{
}

CEnemyBase::~CEnemyBase()
{
}

//--------------------------.
// 攻撃できるかどうか.
//--------------------------.
bool CEnemyBase::IsAssailable( const int& gameCount )
{
	// ゲームカウントがアタックカウントより少なければ終了.
	if( m_AttackCount >= gameCount ) return false;

	// 多ければ true を入れて終了.
	return m_isAssailable = true;
}