	// Test: FAMD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FAMD 0, 0
	FAMD 1, 0
	FAMD 2, 0
	FAMD 3, 0

	// --- Address boundaries (Zero-page)
	FAMD 0, 0
	FAMD 0, 077777

	FAMD 0, 0, 0
	FAMD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FAMD 0, .-037777, 1
	FAMD 0, .+040000, 1

	FAMD 0, -040000, 2
	FAMD 0, 037777, 2

	FAMD 0, -040000, 3
	FAMD 0, 037777, 3

	// --- Indirect addressing
	FAMD 0, @040, 0
