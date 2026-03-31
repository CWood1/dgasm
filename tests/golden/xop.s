	// Test: XOP instruction, with accumulator sweep
	XOP 0, 0, 0
	XOP 0, 1, 0
	XOP 0, 2, 0
	XOP 0, 3, 0

	XOP 0, 0, 0
	XOP 1, 0, 0
	XOP 2, 0, 0
	XOP 3, 0, 0

	// --- Bounds checking
	XOP 0, 0, 0
	XOP 0, 0, 037
