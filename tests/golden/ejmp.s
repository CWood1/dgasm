	// Test: JMP and EJMP with variant coverage and device boundaries

	// --- Labels
label2:
	EJMP label2
	EJMP label3
label3:

	// --- Dot offset
	EJMP .-1

	// --- Addressing modes
	EJMP 5, 0
	EJMP .+5, 1
	EJMP 5, 2
	EJMP 5, 3

	// --- Range checks
	EJMP 0, 0
	EJMP 077777, 0
	EJMP .-037777, 1
	EJMP .+037777, 1
	EJMP -040000, 2
	EJMP 037777, 2
	EJMP -040000, 3
	EJMP 037777, 3

	// --- Indirect addressing
	EJMP @0123, 0
