	// Test: ISZ and EISZ with variant coverage and device boundaries

	// --- Labels
label1:
	ISZ label1
	ISZ label2
label2:
	EISZ label2
	EISZ label3
label3:

	// --- Dot offset
	ISZ .-1
	EISZ .-1

	// --- Addressing modes
	ISZ 5, 0
	ISZ .+5, 1
	ISZ 5, 2
	ISZ 5, 3

	EISZ 5, 0
	EISZ .+5, 1
	EISZ 5, 2
	EISZ 5, 3

	// --- Range checks
	ISZ 0, 0
	ISZ 255, 0
	ISZ .-128, 1
	ISZ .+127, 1
	ISZ -128, 2
	ISZ 127, 2
	ISZ -128, 3
	ISZ 127, 3

	EISZ 0, 0
	EISZ 077777, 0
	EISZ .-037777, 1
	EISZ .+037777, 1
	EISZ -040000, 2
	EISZ 037777, 2
	EISZ -040000, 3
	EISZ 037777, 3

	// --- Indirect addressing
	ISZ @0123, 0
	EISZ @0123, 0
