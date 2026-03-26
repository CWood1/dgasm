	// Test: ELEF with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	ELEF 0, 0
	ELEF 1, 0
	ELEF 2, 0
	ELEF 3, 0

	// --- Address boundaries (Zero-page)
	ELEF 0, 0
	ELEF 0, 077777

	ELEF 0, 0, 0
	ELEF 0, 077777, 0

	// --- Address boundaries (indexed modes)
	ELEF 0, .-037777, 1
	ELEF 0, .+040000, 1

	ELEF 0, -040000, 2
	ELEF 0, 037777, 2

	ELEF 0, -040000, 3
	ELEF 0, 037777, 3

	// --- Indirect addressing
	ELEF 0, @040, 0
