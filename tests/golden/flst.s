	// Test: FLST with accumulator coverage, address mode boundaries

	// --- Address boundaries (Zero-page)
	FLST 0
	FLST 077777

	FLST 0, 0
	FLST 077777, 0

	// --- Address boundaries (indexed modes)
	FLST .-037777, 1
	FLST .+040000, 1

	FLST -040000, 2
	FLST 037777, 2

	FLST -040000, 3
	FLST 037777, 3

	// --- Indirect addressing
	FLST @040, 0
