	// Test: SUB with variant coverage

	// --- Variant sweep - carry
	SUB 0, 0
	SUBZ 0, 0
	SUBO 0, 0
	SUBC 0, 0

	// --- Variant sweep - shift
	SUB 0, 0
	SUBL 0, 0
	SUBR 0, 0
	SUBS 0, 0

	// --- Accumulator sweep (left)
	SUB 0, 0
	SUB 1, 0
	SUB 2, 0
	SUB 3, 0

	// --- Accumulator sweep (right)
	SUB 0, 0
	SUB 0, 1
	SUB 0, 2
	SUB 0, 3

	// --- Variant sweep - shift
	SUB 0, 0
	SUB 0, 0, SKP
	SUB 0, 0, SZC
	SUB 0, 0, SNC
	SUB 0, 0, SZR
	SUB 0, 0, SNR
	SUB 0, 0, SEZ
	SUB 0, 0, SBN
	
	// --- Variant - ignore result
	SUB# 0, 0
