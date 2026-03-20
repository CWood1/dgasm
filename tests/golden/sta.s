	// Test: STA with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	STA 0, 0
	STA 1, 0
	STA 2, 0
	STA 3, 0

	// --- Address boundaries (Zero-page)
	STA 0, 0
	STA 0, 255

	STA 0, 0, 0
	STA 0, 255, 0

	// --- Address boundaries (indexed modes)
	STA 0, .-128, 1
	STA 0, .+127, 1

	STA 0, -128, 2
	STA 0, 127, 2

	STA 0, -128, 3
	STA 0, 127, 3

	// --- Indirect addressing
	STA 0, @40, 0

	// --- Random sanity checks
	STA 3, 255
	STA 2, -128, 2
	STA 1, 127, 3
	STA 2, @127, 1
	STA 3, @-128, 2
	STA 2, @.+13, 1
