	// Test: JSR and EJSR with variant coverage and device boundaries

	// --- Labels
label2:
	EJSR label2
	EJSR label3
label3:

	// --- Dot offset
	EJSR .-1

	// --- Addressing modes
	EJSR 5, 0
	EJSR .+5, 1
	EJSR 5, 2
	EJSR 5, 3

	// --- Range checks
	EJSR 0, 0
	EJSR 077777, 0
	EJSR .-037777, 1
	EJSR .+037777, 1
	EJSR -040000, 2
	EJSR 037777, 2
	EJSR -040000, 3
	EJSR 037777, 3

	// --- Indirect addressing
	EJSR @0123, 0
