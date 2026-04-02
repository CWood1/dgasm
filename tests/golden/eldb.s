	// Test: ELDB with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	ELDB 0, 0
	ELDB 1, 0
	ELDB 2, 0
	ELDB 3, 0

	// --- Address boundaries (Zero-page)
	ELDB 0, 0
	ELDB 0, 077777

	ELDB 0, 0, 0
	ELDB 0, 077777, 0

	// --- Address boundaries (indexed modes)
	ELDB 0, .-037777, 1
	ELDB 0, .+040000, 1

	ELDB 0, -040000, 2
	ELDB 0, 037777, 2

	ELDB 0, -040000, 3
	ELDB 0, 037777, 3
