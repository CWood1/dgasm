	// Test: ESTA with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	ESTA 0, 0
	ESTA 1, 0
	ESTA 2, 0
	ESTA 3, 0

	// --- Address boundaries (Zero-page)
	ESTA 0, 0
	ESTA 0, 077777

	ESTA 0, 0, 0
	ESTA 0, 077777, 0

	// --- Address boundaries (indexed modes)
	ESTA 0, .-037777, 1
	ESTA 0, .+040000, 1

	ESTA 0, -040000, 2
	ESTA 0, 037777, 2

	ESTA 0, -040000, 3
	ESTA 0, 037777, 3

	// --- Indirect addressing
	ESTA 0, @040, 0
