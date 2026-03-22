	// Test: NIO with accumulator coverage, address mode boundaries
	dev low = 0
	dev high = 077

	// --- Variant sweep
	NIO low
	NIOS low
	NIOC low
	NIOP low

	// --- Range check
	NIO low
	NIO high

	// --- Device number check
	NIO 0
	NIO 077
