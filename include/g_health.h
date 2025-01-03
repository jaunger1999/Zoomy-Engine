typedef int (*damageModFunction)(int);

typedef enum DamageType {
	CONTACT = 0,
	BULLET  = 1,
	FIRE    = 2,
	PLASMA  = 3
} DamageType;

typedef struct DamageSource {
	DamageType type;
	damageModFunction *damageMods;
	int sourceObjectID;
} DamageSource;
