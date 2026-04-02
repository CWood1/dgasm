	// Test: DI/DO with variant coverage and device boundaries
	dev low = 0
	dev high = 077

	// --- Variant sweep
	DIA 0, low
	DIAS 0, low
	DIAC 0, low
	DIAP 0, low

	DIB 0, low
	DIBS 0, low
	DIBC 0, low
	DIBP 0, low

	DIC 0, low
	DICS 0, low
	DICC 0, low
	DICP 0, low

	DOA 0, low
	DOAS 0, low
	DOAC 0, low
	DOAP 0, low

	DOB 0, low
	DOBS 0, low
	DOBC 0, low
	DOBP 0, low

	DOC 0, low
	DOCS 0, low
	DOCC 0, low
	DOCP 0, low

	// --- Range check
	DIA 0, low
	DIA 0, high

	// --- Accumulator sweep
	DOB 0, high
	DOB 1, high
	DOB 2, high
	DOB 3, high

	// --- Device number check
	DOCC 0, 0
	DOCC 0, 077

	
