	// Test: DSPA with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	DSPA 0, 0
	DSPA 1, 0
	DSPA 2, 0
	DSPA 3, 0

	// --- Address boundaries (Zero-page)
	DSPA 0, 0
	DSPA 0, 077777

	DSPA 0, 0, 0
	DSPA 0, 077777, 0

	// --- Address boundaries (indexed modes)
	DSPA 0, .-037777, 1
	DSPA 0, .+040000, 1

	DSPA 0, -040000, 2
	DSPA 0, 037777, 2

	DSPA 0, -040000, 3
	DSPA 0, 037777, 3

	// --- Indirect addressing
	DSPA 0, @040, 0
