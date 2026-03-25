	// Test: NEG with variant coverage

	// --- Variant sweep - carry
	NEG 0, 0
	NEGZ 0, 0
	NEGO 0, 0
	NEGC 0, 0

	// --- Variant sweep - shift
	NEG 0, 0
	NEGL 0, 0
	NEGR 0, 0
	NEGS 0, 0

	// --- Accumulator sweep (left)
	NEG 0, 0
	NEG 1, 0
	NEG 2, 0
	NEG 3, 0

	// --- Accumulator sweep (right)
	NEG 0, 0
	NEG 0, 1
	NEG 0, 2
	NEG 0, 3

	// --- Variant sweep - shift
	NEG 0, 0
	NEG 0, 0, SKP
	NEG 0, 0, SZC
	NEG 0, 0, SNC
	NEG 0, 0, SZR
	NEG 0, 0, SNR
	NEG 0, 0, SEZ
	NEG 0, 0, SBN
	
	// --- Variant - ignore result
	NEG# 0, 0
