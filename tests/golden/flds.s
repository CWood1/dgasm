	// Test: FLDS with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FLDS 0, 0
	FLDS 1, 0
	FLDS 2, 0
	FLDS 3, 0

	// --- Address boundaries (Zero-page)
	FLDS 0, 0
	FLDS 0, 077777

	FLDS 0, 0, 0
	FLDS 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FLDS 0, .-037777, 1
	FLDS 0, .+040000, 1

	FLDS 0, -040000, 2
	FLDS 0, 037777, 2

	FLDS 0, -040000, 3
	FLDS 0, 037777, 3

	// --- Indirect addressing
	FLDS 0, @040, 0
