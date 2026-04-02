	// Test: ADI instruction, with accumulator sweep
	// --- Accumulator Sweep
	ADI 0, 1
	ADI 1, 1
	ADI 2, 1
	ADI 3, 1

	// --- Range checks
	ADI 0, 1
	ADI 0, 2
	ADI 0, 3
	ADI 0, 4
