	// Test: AND with variant coverage

	// --- Variant sweep - carry
	AND 0, 0
	ANDZ 0, 0
	ANDO 0, 0
	ANDC 0, 0

	// --- Variant sweep - shift
	AND 0, 0
	ANDL 0, 0
	ANDR 0, 0
	ANDS 0, 0

	// --- Accumulator sweep (left)
	AND 0, 0
	AND 1, 0
	AND 2, 0
	AND 3, 0

	// --- Accumulator sweep (right)
	AND 0, 0
	AND 0, 1
	AND 0, 2
	AND 0, 3

	// --- Variant sweep - shift
	AND 0, 0
	AND 0, 0, SKP
	AND 0, 0, SZC
	AND 0, 0, SNC
	AND 0, 0, SZR
	AND 0, 0, SNR
	AND 0, 0, SEZ
	AND 0, 0, SBN
	
	// --- Variant - ignore result
	AND# 0, 0
