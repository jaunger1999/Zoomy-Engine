typedef int (*damageModFunction)(int);

struct DamageSource {
	DamageType type;
	damageModFunction *damageMods;
	int sourceObjectID;
} typedef DamageSource;
