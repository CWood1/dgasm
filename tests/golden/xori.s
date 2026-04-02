	// Test: XORI instruction, with accumulator sweep
	// --- Accumulator Sweep
	XORI 0, 5
	XORI 1, 5
	XORI 2, 5
	XORI 3, 5

	// --- Range checks
	XORI 0, 0
	XORI 0, 0177777
