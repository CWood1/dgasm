	// Test: DHXR instruction, with accumulator sweep
	// --- Accumulator Sweep
	DHXR 0, 1
	DHXR 1, 1
	DHXR 2, 1
	DHXR 3, 1

	// --- Range checks
	DHXR 0, 1
	DHXR 0, 2
	DHXR 0, 3
	DHXR 0, 4
