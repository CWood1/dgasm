	org 010
	const testconst = 012345

testlabel:
	dw 01234
	dw 02345, 03456
	var testvar = 04567

	org 020
	dw testlabel
	var testresv resv 3
	dw testlabel
	dw testconst, testconst, testlabel
	
