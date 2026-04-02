	// Test: COM with variant coverage

	// --- Variant sweep - carry
	COM 0, 0
	COMZ 0, 0
	COMO 0, 0
	COMC 0, 0

	// --- Variant sweep - shift
	COM 0, 0
	COML 0, 0
	COMR 0, 0
	COMS 0, 0

	// --- Accumulator sweep (left)
	COM 0, 0
	COM 1, 0
	COM 2, 0
	COM 3, 0

	// --- Accumulator sweep (right)
	COM 0, 0
	COM 0, 1
	COM 0, 2
	COM 0, 3

	// --- Variant sweep - shift
	COM 0, 0
	COM 0, 0, SKP
	COM 0, 0, SZC
	COM 0, 0, SNC
	COM 0, 0, SZR
	COM 0, 0, SNR
	COM 0, 0, SEZ
	COM 0, 0, SBN
	
	// --- Variant - ignore result
	COM# 0, 0
