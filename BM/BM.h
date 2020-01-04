void make_delta1(const char* pat, int patlen, int *delta1);


int suffix_length(const char* pat, int patlen,int pos);

void make_delta2(const char* pat, int patlen, int* delta2);

int match(const char* txt, int txtLen, const char* pat, int patLen);