	// Test: FAMS with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FAMS 0, 0
	FAMS 1, 0
	FAMS 2, 0
	FAMS 3, 0

	// --- Address boundaries (Zero-page)
	FAMS 0, 0
	FAMS 0, 077777

	FAMS 0, 0, 0
	FAMS 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FAMS 0, .-037777, 1
	FAMS 0, .+040000, 1

	FAMS 0, -040000, 2
	FAMS 0, 037777, 2

	FAMS 0, -040000, 3
	FAMS 0, 037777, 3

	// --- Indirect addressing
	FAMS 0, @040, 0
