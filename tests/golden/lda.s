	// Test: LDA with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	LDA 0, 0
	LDA 1, 0
	LDA 2, 0
	LDA 3, 0

	// --- Address boundaries (Zero-page)
	LDA 0, 0
	LDA 0, 255

	LDA 0, 0, 0
	LDA 0, 255, 0

	// --- Address boundaries (indexed modes)
	LDA 0, .-128, 1
	LDA 0, .+127, 1

	LDA 0, -128, 2
	LDA 0, 127, 2

	LDA 0, -128, 3
	LDA 0, 127, 3

	// --- Indirect addressing
	LDA 0, @40, 0

	// --- Random sanity checks
	LDA 3, 255
	LDA 2, -128, 2
	LDA 1, 127, 3
	LDA 2, @127, 1
	LDA 3, @-128, 2
	LDA 2, @.+13, 1
