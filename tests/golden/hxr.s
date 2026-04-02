	// Test: HXR instruction, with accumulator sweep
	// --- Accumulator Sweep
	HXR 0, 1
	HXR 1, 1
	HXR 2, 1
	HXR 3, 1

	// --- Range checks
	HXR 0, 1
	HXR 0, 2
	HXR 0, 3
	HXR 0, 4
