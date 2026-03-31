	// Test: ISZ and EISZ with variant coverage and device boundaries

	// --- Labels

label2:
	EISZ label2
	EISZ label3
label3:

	// --- Dot offset
	EISZ .-1

	EISZ 5, 0
	EISZ .+5, 1
	EISZ 5, 2
	EISZ 5, 3

	EISZ 0, 0
	EISZ 077777, 0
	EISZ .-037777, 1
	EISZ .+037777, 1
	EISZ -040000, 2
	EISZ 037777, 2
	EISZ -040000, 3
	EISZ 037777, 3

	// --- Indirect addressing
	EISZ @0123, 0
