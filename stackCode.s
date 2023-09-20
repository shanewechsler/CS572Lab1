	.data
X:	3
A:	7
B:	5
C:	4
D:	0

	.text
	push X
	push X
	mul
	push A
	mul
	push B
	push X
	mul
	add
	push C
	add
	pop D
	end
