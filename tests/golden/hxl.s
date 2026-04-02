	// Test: HXL instruction, with accumulator sweep
	// --- Accumulator Sweep
	HXL 0, 1
	HXL 1, 1
	HXL 2, 1
	HXL 3, 1

	// --- Range checks
	HXL 0, 1
	HXL 0, 2
	HXL 0, 3
	HXL 0, 4
