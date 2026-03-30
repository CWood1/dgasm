	// Test: FLMD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FLMD 0, 0
	FLMD 1, 0
	FLMD 2, 0
	FLMD 3, 0

	// --- Address boundaries (Zero-page)
	FLMD 0, 0
	FLMD 0, 077777

	FLMD 0, 0, 0
	FLMD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FLMD 0, .-037777, 1
	FLMD 0, .+040000, 1

	FLMD 0, -040000, 2
	FLMD 0, 037777, 2

	FLMD 0, -040000, 3
	FLMD 0, 037777, 3

	// --- Indirect addressing
	FLMD 0, @040, 0
