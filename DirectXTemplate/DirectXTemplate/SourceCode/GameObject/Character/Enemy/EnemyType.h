#ifndef ENEMY_TYPE_H
#define ENEMY_TYPE_H

// “G‚Ìí—Ş.
enum class enENEMY_TYPE
{
	None,		// ‰½‚à‚È‚µ.
	
	RUN = None,	// ‘–‚é.
	SHOOT,		// Œ‚‚Â.

	Max,		// Å‘å.
};

// “G‚ª‚Ç‚Ì•ûŒü‚ÉˆÚ“®‚·‚é‚©.
enum class enENEMY_DIRECTION
{
	None,		// ‰½‚à‚È‚µ.

	UP = None,	// ã•ûŒü.
	DOWN,		// ‰º•ûŒü.
	RIGHT,		// ‰E•ûŒü.
	LEFT,		// ¶•ûŒü.

	Max,		// Å‘å.
};

#endif	// #ifndef ENEMY_TYPE_H.