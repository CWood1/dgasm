	// Test: JSR and EJSR with variant coverage and device boundaries

	// --- Labels
label1:
	JSR label1
	JSR label2
label2:

	// --- Dot offset
	JSR .-1

	// --- Addressing modes
	JSR 5, 0
	JSR .+5, 1
	JSR 5, 2
	JSR 5, 3

	// --- Range checks
	JSR 0, 0
	JSR 255, 0
	JSR .-128, 1
	JSR .+127, 1
	JSR -128, 2
	JSR 127, 2
	JSR -128, 3
	JSR 127, 3

	// --- Indirect addressing
	JSR @0123, 0
