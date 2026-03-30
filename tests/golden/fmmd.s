	// Test: FMMD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FMMD 0, 0
	FMMD 1, 0
	FMMD 2, 0
	FMMD 3, 0

	// --- Address boundaries (Zero-page)
	FMMD 0, 0
	FMMD 0, 077777

	FMMD 0, 0, 0
	FMMD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FMMD 0, .-037777, 1
	FMMD 0, .+040000, 1

	FMMD 0, -040000, 2
	FMMD 0, 037777, 2

	FMMD 0, -040000, 3
	FMMD 0, 037777, 3

	// --- Indirect addressing
	FMMD 0, @040, 0
