	// Test: ESTB with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	ESTB 0, 0
	ESTB 1, 0
	ESTB 2, 0
	ESTB 3, 0

	// --- Address boundaries (Zero-page)
	ESTB 0, 0
	ESTB 0, 077777

	ESTB 0, 0, 0
	ESTB 0, 077777, 0

	// --- Address boundaries (indexed modes)
	ESTB 0, .-037777, 1
	ESTB 0, .+040000, 1

	ESTB 0, -040000, 2
	ESTB 0, 037777, 2

	ESTB 0, -040000, 3
	ESTB 0, 037777, 3
