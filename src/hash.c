// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned long hash(unsigned int const x) {
	unsigned long hash = (unsigned long)x;

	hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
	hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
	hash =  (hash >> 16) ^ hash;

	return hash;
}

// https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash_s(char const *str, unsigned int const paddedLength) {
    unsigned long hash = 5381;
    int c;
	unsigned int i = 0;

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		i++;
    }

	for(; i < paddedLength; i++) {
		hash = ((hash << 5) + hash) + (int)' '; /* hash * 33 + ' ' */
	}

    return hash;
}
