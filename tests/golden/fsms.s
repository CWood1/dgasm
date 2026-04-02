	// Test: FSMS with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FSMS 0, 0
	FSMS 1, 0
	FSMS 2, 0
	FSMS 3, 0

	// --- Address boundaries (Zero-page)
	FSMS 0, 0
	FSMS 0, 077777

	FSMS 0, 0, 0
	FSMS 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FSMS 0, .-037777, 1
	FSMS 0, .+040000, 1

	FSMS 0, -040000, 2
	FSMS 0, 037777, 2

	FSMS 0, -040000, 3
	FSMS 0, 037777, 3

	// --- Indirect addressing
	FSMS 0, @040, 0
