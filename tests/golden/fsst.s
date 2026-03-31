	// Test: FSST with accumulator coverage, address mode boundaries

	// --- Address boundaries (Zero-page)
	FSST 0
	FSST 077777

	FSST 0, 0
	FSST 077777, 0

	// --- Address boundaries (indexed modes)
	FSST .-037777, 1
	FSST .+040000, 1

	FSST -040000, 2
	FSST 037777, 2

	FSST -040000, 3
	FSST 037777, 3

	// --- Indirect addressing
	FSST @040, 0
