	// Test: FLDD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FLDD 0, 0
	FLDD 1, 0
	FLDD 2, 0
	FLDD 3, 0

	// --- Address boundaries (Zero-page)
	FLDD 0, 0
	FLDD 0, 077777

	FLDD 0, 0, 0
	FLDD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FLDD 0, .-037777, 1
	FLDD 0, .+040000, 1

	FLDD 0, -040000, 2
	FLDD 0, 037777, 2

	FLDD 0, -040000, 3
	FLDD 0, 037777, 3

	// --- Indirect addressing
	FLDD 0, @040, 0
