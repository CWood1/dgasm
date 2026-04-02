	// Test: MOV with variant coverage

	// --- Variant sweep - carry
	MOV 0, 0
	MOVZ 0, 0
	MOVO 0, 0
	MOVC 0, 0

	// --- Variant sweep - shift
	MOV 0, 0
	MOVL 0, 0
	MOVR 0, 0
	MOVS 0, 0

	// --- Accumulator sweep (left)
	MOV 0, 0
	MOV 1, 0
	MOV 2, 0
	MOV 3, 0

	// --- Accumulator sweep (right)
	MOV 0, 0
	MOV 0, 1
	MOV 0, 2
	MOV 0, 3

	// --- Variant sweep - shift
	MOV 0, 0
	MOV 0, 0, SKP
	MOV 0, 0, SZC
	MOV 0, 0, SNC
	MOV 0, 0, SZR
	MOV 0, 0, SNR
	MOV 0, 0, SEZ
	MOV 0, 0, SBN
	
	// --- Variant - ignore result
	MOV# 0, 0
