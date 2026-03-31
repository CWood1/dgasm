	// Test: XOP1 instruction, with accumulator sweep
	XOP1 0, 0, 0
	XOP1 0, 1, 0
	XOP1 0, 2, 0
	XOP1 0, 3, 0

	XOP1 0, 0, 0
	XOP1 1, 0, 0
	XOP1 2, 0, 0
	XOP1 3, 0, 0

	// --- Bounds checking
	XOP1 0, 0, 0
	XOP1 0, 0, 017
