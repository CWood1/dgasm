	// Test: JSR and EJSR with variant coverage and device boundaries

	// --- Labels
label1:
	JSR label1
	JSR label2
label2:
	EJSR label2
	EJSR label3
label3:

	// --- Dot offset
	JSR .-1
	EJSR .-1

	// --- Addressing modes
	JSR 5, 0
	JSR .+5, 1
	JSR 5, 2
	JSR 5, 3

	EJSR 5, 0
	EJSR .+5, 1
	EJSR 5, 2
	EJSR 5, 3

	// --- Range checks
	JSR 0, 0
	JSR 255, 0
	JSR .-128, 1
	JSR .+127, 1
	JSR -128, 2
	JSR 127, 2
	JSR -128, 3
	JSR 127, 3

	EJSR 0, 0
	EJSR 077777, 0
	EJSR .-037777, 1
	EJSR .+037777, 1
	EJSR -040000, 2
	EJSR 037777, 2
	EJSR -040000, 3
	EJSR 037777, 3

	// --- Indirect addressing
	JSR @0123, 0
	EJSR @0123, 0
