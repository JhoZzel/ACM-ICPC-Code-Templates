// 3xN N
for (int mask = 0; mask < (1 << n); mask++) {
	for (int smask = mask; smask > 0; smask = (smask - 1) & mask) {
			
	}
}

// DP SOS
for(int i = 0; i < (1<<N); ++i)
    A[i] = F[i];

for(int i = 0; i < N; ++i)
    for(int mask = 0; mask < (1<<N); ++mask)
        if( mask & (1<<i) )
            F[mask] -= F[mask^(1<<i)]; 
