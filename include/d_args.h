#define Unpack(a, args) \
	memcpy(&a, args, sizeof(a));

#define Unpack2(a, b, args) \
	memcpy(&a, args,             sizeof(a)); \
	memcpy(&b, args + sizeof(a), sizeof(b));

#define Unpack3(a, b, c, args) \
	int offset = 0;
	memcpy(&a, args + offset, sizeof(a)); \
	offset += sizeof(a); \
\
	memcpy(&b, args + offset, sizeof(b)); \
	offset += sizeof(b);
\	
	memcpy(&c, args + offset, sizeof(c)); \
