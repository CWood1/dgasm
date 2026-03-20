	// Test: LEF with accumulator coverage, address mode boundaries
	// --- Accumulator sweep (baseline)
	LEF 0, 0
	LEF 1, 0
	LEF 2, 0
	LEF 3, 0

	// --- Address boundaries (Zero-page)
	LEF 0, 0
	LEF 0, 255

	LEF 0, 0, 0
	LEF 0, 255, 0

	// --- Address boundaries (indexed modes)
	LEF 0, .-128, 1
	LEF 0, .+127, 1

	LEF 0, -128, 2
	LEF 0, 127, 2

	LEF 0, -128, 3
	LEF 0, 127, 3

	// --- Indirect addressing
	LEF 0, @40, 0

	// --- Random sanity checks
	LEF 3, 255
	LEF 2, -128, 2
	LEF 1, 127, 3
	LEF 2, @127, 1
	LEF 3, @-128, 2
	LEF 2, @.+13, 1
