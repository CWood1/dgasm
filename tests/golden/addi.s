	// Test: ADDI instruction, with accumulator sweep
	// --- Accumulator Sweep
	ADDI 0, 5
	ADDI 1, 5
	ADDI 2, 5
	ADDI 3, 5

	// --- Range checks
	ADDI 0, 0
	ADDI 0, 0177777
