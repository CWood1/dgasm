	// Test: ELDA with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	ELDA 0, 0
	ELDA 1, 0
	ELDA 2, 0
	ELDA 3, 0

	// --- Address boundaries (Zero-page)
	ELDA 0, 0
	ELDA 0, 077777

	ELDA 0, 0, 0
	ELDA 0, 077777, 0

	// --- Address boundaries (indexed modes)
	ELDA 0, .-037777, 1
	ELDA 0, .+040000, 1

	ELDA 0, -040000, 2
	ELDA 0, 037777, 2

	ELDA 0, -040000, 3
	ELDA 0, 037777, 3

	// --- Indirect addressing
	ELDA 0, @040, 0
