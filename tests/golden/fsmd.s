	// Test: FSMD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FSMD 0, 0
	FSMD 1, 0
	FSMD 2, 0
	FSMD 3, 0

	// --- Address boundaries (Zero-page)
	FSMD 0, 0
	FSMD 0, 077777

	FSMD 0, 0, 0
	FSMD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FSMD 0, .-037777, 1
	FSMD 0, .+040000, 1

	FSMD 0, -040000, 2
	FSMD 0, 037777, 2

	FSMD 0, -040000, 3
	FSMD 0, 037777, 3

	// --- Indirect addressing
	FSMD 0, @040, 0
