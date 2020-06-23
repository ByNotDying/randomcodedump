;this is a program that takes an array

include c:\irvine\irvine32.inc


.data

string11 BYTE "Enter how many elements in your array:", 20h, 0
string12 BYTE "Enter the row size:", 20h, 0
string13 BYTE "Enter the type of your array, 1 for byte, 2 for word, 4 for dword:", 20h, 0
string14 BYTE "Enter an element in your array: ", 20h, 0
string15 BYTE "Enter array number you want to sum: ", 20h, 0

testNum dword 9

twoDtest dword 12,1,2,3,4,5,6,7,8,9
twoDb byte 40 dup (?)
twoDw word 40 dup (?)
twoDdw dword 40 dup (?)

numElements dword 0
rowSize dword 0
varType dword 0 
arrayP dword 0
rowNumber dword 0

.code

main proc

	xor eax, eax

	;get and push array and row size 
	mov edx , OFFSET string11
	call writeString
	call readint
	mov numElements , eax

	mov edx , OFFSET string12
	call writeString
	call readint
	mov rowSize , eax

	mov eax , numElements
	push eax
	mov eax , rowSize
	push eax



	;get array type, push the array type, push array of proper type

	mov edx , OFFSET string13
	call writeString
	call readint
	mov varType , eax
	mov eax , varType
	push eax
	cmp eax , 01
	je pushtwoDb
	cmp eax , 02
	je pushtwoDw
	cmp eax , 04
	je pushtwoDdw
	jne earlyexit

	pushtwoDb:
	push offset twoDb
	jmp pushbreak

	pushtwoDw:
	push offset twoDw
	jmp pushbreak

	pushtwoDdw:
	push offset twoDdw
	jmp pushbreak

	pushbreak:


	

	;we must fill the array, andthen pop and then push it for calcRowSum to use 
	pop ebx
	XOR EDI, EDI

	;loop setup
	mov ecx, numElements
	
	;Base-Index operand loop thing
	L1:
		mov edx , OFFSET string14
		call writeString
		call readint
		mov [ebx+edi], eax
		add edi, vartype
		loop L1

		;get/push row number to sum
		mov edx , OFFSET string15
		call writeString
		call readint
		mov eax, rowNumber
		mov rowNumber, eax
		push eax


	push ebx


	;list of all push operations to this point
		;get and push array and row size 
			;get array type, push the array type, push array of proper type
					;get/push row number to sum

				;we must fill the array, andthen pop and then push it for calcRowSum to use 

	;thus, the variables passed, in order of closest to ebp after call to farthest
	;&arr, rownumber, arrtype, rowsize, arraysize
	; calcRowSum(&arr, rownumber, arrtype, rowsize, arraysize){}
	call calcRowSum

	;here in case someone decides to type in an invalid number for array type
	earlyexit:

exit
main endp




calcRowSum Proc
	
	push ebp
	mov ebp, esp
	

	mov ebx, [ebp+8] ;ebp+8 = &arr
	mov ebx, [ebp+8]
	xor edi,edi

	mov edx, [ebp+12] ;ebp+12 is rownumber
	mov eax, [ebp+16] ;ebp+16 is arraytype

	mul edx ;stored in eax
	add edi, edx
	;should point to correct row now

	mov ecx, 1
	;mov ecx, [ebp+20] ;rowsize
	L2:
		mov eax, [ebx+edi]
		call writeInt
		add edi, type [ebp+8] 
	;loop L2:

	pop ebp

ret
calcRowSum endp

END main


Comment !
Enter how many elements in your array: 6
Enter the row size: 2
Enter the type of your array.
 1 for byte.
 2 for word.
 4 for doubleword.
1
Enter an element in your array, 1
Enter an element in your array, 2
Enter an element in your array, 3
Enter an element in your array, 4
Enter an element in your array, 5
Enter an element in your array, 6
Enter row number that you want me to sum: 0
The sum is: 00000003
Press any key to continue . . .
Your program must have a procedure called calcRowSum PROC that calculates the sum of one row in the two-dimensional array of bytes, words, or doublewords and returns it to main proc.

The header of the proc in C++ is as follows:

int calcRowSum ( int *array, int rowSize, int type, int rowIndex);

For the parameters and the return value use the stack.
!