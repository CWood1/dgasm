	// Test: ANDI instruction, with accumulator sweep
	// --- Accumulator Sweep
	ANDI 0, 5
	ANDI 1, 5
	ANDI 2, 5
	ANDI 3, 5

	// --- Range checks
	ANDI 0, 0
	ANDI 0, 0177777
