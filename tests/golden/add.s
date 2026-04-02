	// Test: ADD with variant coverage

	// --- Variant sweep - carry
	ADD 0, 0
	ADDZ 0, 0
	ADDO 0, 0
	ADDC 0, 0

	// --- Variant sweep - shift
	ADD 0, 0
	ADDL 0, 0
	ADDR 0, 0
	ADDS 0, 0

	// --- Accumulator sweep (left)
	ADD 0, 0
	ADD 1, 0
	ADD 2, 0
	ADD 3, 0

	// --- Accumulator sweep (right)
	ADD 0, 0
	ADD 0, 1
	ADD 0, 2
	ADD 0, 3

	// --- Variant sweep - shift
	ADD 0, 0
	ADD 0, 0, SKP
	ADD 0, 0, SZC
	ADD 0, 0, SNC
	ADD 0, 0, SZR
	ADD 0, 0, SNR
	ADD 0, 0, SEZ
	ADD 0, 0, SBN
	
	// --- Variant - ignore result
	ADD# 0, 0
