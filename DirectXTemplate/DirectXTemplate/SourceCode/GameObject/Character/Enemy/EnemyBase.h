#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "..\Character.h"

class CEnemyBase : public CCharacter
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();

	// UŒ‚‚Å‚«‚é‚©‚Ç‚¤‚©.
	bool IsAssailable( const int& gameCount );
	// UŒ‚ƒJƒEƒ“ƒg‚Ìİ’è.
	void SetAttackCount( const int& attackCount ){ m_AttackCount = attackCount; }
protected:
	int m_AttackCount;		// UŒ‚ƒJƒEƒ“ƒg.
	bool m_isAssailable;	// UŒ‚‚Å‚«‚é‚©.
};

#endif	// #ifndef ENEMY_BASE_H.