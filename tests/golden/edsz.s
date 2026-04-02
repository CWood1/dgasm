	// Test: DSZ and EDSZ with variant coverage and device boundaries

	// --- Labels

label2:
	EDSZ label2
	EDSZ label3
label3:

	// --- Dot offset
	EDSZ .-1

	// --- Addressing modes
	EDSZ 5, 0
	EDSZ .+5, 1
	EDSZ 5, 2
	EDSZ 5, 3

	// --- Range checks
	EDSZ 0, 0
	EDSZ 077777, 0
	EDSZ .-037777, 1
	EDSZ .+037777, 1
	EDSZ -040000, 2
	EDSZ 037777, 2
	EDSZ -040000, 3
	EDSZ 037777, 3

	// --- Indirect addressing
	EDSZ @0123, 0
