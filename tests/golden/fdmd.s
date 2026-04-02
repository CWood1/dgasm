	// Test: FDMD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FDMD 0, 0
	FDMD 1, 0
	FDMD 2, 0
	FDMD 3, 0

	// --- Address boundaries (Zero-page)
	FDMD 0, 0
	FDMD 0, 077777

	FDMD 0, 0, 0
	FDMD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FDMD 0, .-037777, 1
	FDMD 0, .+040000, 1

	FDMD 0, -040000, 2
	FDMD 0, 037777, 2

	FDMD 0, -040000, 3
	FDMD 0, 037777, 3

	// --- Indirect addressing
	FDMD 0, @040, 0
