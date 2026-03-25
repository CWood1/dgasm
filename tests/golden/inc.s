	// Test: INC with variant coverage

	// --- Variant sweep - carry
	INC 0, 0
	INCZ 0, 0
	INCO 0, 0
	INCC 0, 0

	// --- Variant sweep - shift
	INC 0, 0
	INCL 0, 0
	INCR 0, 0
	INCS 0, 0

	// --- Accumulator sweep (left)
	INC 0, 0
	INC 1, 0
	INC 2, 0
	INC 3, 0

	// --- Accumulator sweep (right)
	INC 0, 0
	INC 0, 1
	INC 0, 2
	INC 0, 3

	// --- Variant sweep - shift
	INC 0, 0
	INC 0, 0, SKP
	INC 0, 0, SZC
	INC 0, 0, SNC
	INC 0, 0, SZR
	INC 0, 0, SNR
	INC 0, 0, SEZ
	INC 0, 0, SBN
	
	// --- Variant - ignore result
	INC# 0, 0
