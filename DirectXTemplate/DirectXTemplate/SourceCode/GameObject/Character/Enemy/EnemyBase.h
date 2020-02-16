#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "..\Character.h"

class CEnemyBase : public CCharacter
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();

	// 攻撃できるかどうか.
	bool IsAssailable( const int& gameCount );
	// 攻撃カウントの設定.
	void SetAttackCount( const int& attackCount ){ m_AttackCount = attackCount; }
protected:
	int m_AttackCount;		// 攻撃カウント.
	bool m_isAssailable;	// 攻撃できるか.
};

#endif	// #ifndef ENEMY_BASE_H.