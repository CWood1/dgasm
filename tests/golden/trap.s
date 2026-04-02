	// Test: TRAP instruction, with accumulator sweep
	TRAP 0, 0, 0
	TRAP 0, 1, 0
	TRAP 0, 2, 0
	TRAP 0, 3, 0

	TRAP 0, 0, 0
	TRAP 1, 0, 0
	TRAP 2, 0, 0
	TRAP 3, 0, 0

	// --- Bounds checking
	TRAP 0, 0, 0
	TRAP 0, 0, 0177
