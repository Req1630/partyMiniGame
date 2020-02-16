#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "..\Character.h"

class CEnemyBase : public CCharacter
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();

	// �U���ł��邩�ǂ���.
	bool IsAssailable( const int& gameCount );
	// �U���J�E���g�̐ݒ�.
	void SetAttackCount( const int& attackCount ){ m_AttackCount = attackCount; }
protected:
	int m_AttackCount;		// �U���J�E���g.
	bool m_isAssailable;	// �U���ł��邩.
};

#endif	// #ifndef ENEMY_BASE_H.