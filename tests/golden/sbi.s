	// Test: SBI instruction, with accumulator sweep
	// --- Accumulator Sweep
	SBI 0, 1
	SBI 1, 1
	SBI 2, 1
	SBI 3, 1

	// --- Range checks
	SBI 0, 1
	SBI 0, 2
	SBI 0, 3
	SBI 0, 4
