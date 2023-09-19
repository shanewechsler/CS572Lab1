	.data
X:	3
A:	7
B:	5
C:	4
D:	0

	.text
	load X
	mul X
	mul A
	sto D
	load B
	mul X
	add C
	add D
	sto D
	end
