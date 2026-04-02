	// Test: DHXL instruction, with accumulator sweep
	// --- Accumulator Sweep
	DHXL 0, 1
	DHXL 1, 1
	DHXL 2, 1
	DHXL 3, 1

	// --- Range checks
	DHXL 0, 1
	DHXL 0, 2
	DHXL 0, 3
	DHXL 0, 4
