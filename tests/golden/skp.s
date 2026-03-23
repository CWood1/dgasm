	// Test: NIO with variant coverage and device boundaries
	dev low = 0
	dev high = 077

	// --- Variant sweep
	SKPBN low
	SKPBZ low
	SKPDN low
	SKPDZ low

	// --- Range check
	SKPBN low
	SKPBN high

	// --- Device number check
	SKPBN 0
	SKPBN 077
