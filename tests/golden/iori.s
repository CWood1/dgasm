	// Test: IORI instruction, with accumulator sweep
	// --- Accumulator Sweep
	IORI 0, 5
	IORI 1, 5
	IORI 2, 5
	IORI 3, 5

	// --- Range checks
	IORI 0, 0
	IORI 0, 0177777
