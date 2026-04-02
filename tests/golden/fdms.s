	// Test: FDMS with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	FDMS 0, 0
	FDMS 1, 0
	FDMS 2, 0
	FDMS 3, 0

	// --- Address boundaries (Zero-page)
	FDMS 0, 0
	FDMS 0, 077777

	FDMS 0, 0, 0
	FDMS 0, 077777, 0

	// --- Address boundaries (indexed modes)
	FDMS 0, .-037777, 1
	FDMS 0, .+040000, 1

	FDMS 0, -040000, 2
	FDMS 0, 037777, 2

	FDMS 0, -040000, 3
	FDMS 0, 037777, 3

	// --- Indirect addressing
	FDMS 0, @040, 0
