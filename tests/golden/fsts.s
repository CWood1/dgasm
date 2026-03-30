	// Test: FSTS with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FSTS 0, 0
	FSTS 1, 0
	FSTS 2, 0
	FSTS 3, 0

	// --- Address boundaries (Zero-page)
	FSTS 0, 0
	FSTS 0, 077777

	FSTS 0, 0, 0
	FSTS 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FSTS 0, .-037777, 1
	FSTS 0, .+040000, 1

	FSTS 0, -040000, 2
	FSTS 0, 037777, 2

	FSTS 0, -040000, 3
	FSTS 0, 037777, 3

	// --- Indirect addressing
	FSTS 0, @040, 0
