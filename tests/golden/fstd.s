	// Test: FSTD with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FSTD 0, 0
	FSTD 1, 0
	FSTD 2, 0
	FSTD 3, 0

	// --- Address boundaries (Zero-page)
	FSTD 0, 0
	FSTD 0, 077777

	FSTD 0, 0, 0
	FSTD 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FSTD 0, .-037777, 1
	FSTD 0, .+040000, 1

	FSTD 0, -040000, 2
	FSTD 0, 037777, 2

	FSTD 0, -040000, 3
	FSTD 0, 037777, 3

	// --- Indirect addressing
	FSTD 0, @040, 0
