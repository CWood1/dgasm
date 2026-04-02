	// Test: PSHJ with accumulator coverage, address mode boundaries

	// --- Address boundaries (Zero-page)
	PSHJ .-037777
	PSHJ .+040000

	PSHJ 0, 0
	PSHJ 077777, 0

	// --- Address boundaries (indexed modes)
	PSHJ .-037777, 1
	PSHJ .+040000, 1

	PSHJ -040000, 2
	PSHJ 037777, 2

	PSHJ -040000, 3
	PSHJ 037777, 3

	// --- Indirect addressing
	PSHJ @040, 0
