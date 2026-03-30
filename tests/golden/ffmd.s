	// Test: FFMD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FFMD 0, 0
	FFMD 1, 0
	FFMD 2, 0
	FFMD 3, 0

	// --- Address boundaries (Zero-page)
	FFMD 0, 0
	FFMD 0, 077777

	FFMD 0, 0, 0
	FFMD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FFMD 0, .-037777, 1
	FFMD 0, .+040000, 1

	FFMD 0, -040000, 2
	FFMD 0, 037777, 2

	FFMD 0, -040000, 3
	FFMD 0, 037777, 3

	// --- Indirect addressing
	FFMD 0, @040, 0
