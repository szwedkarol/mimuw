; Karol Szwed
; 19.05.2023 r.
; AKSO - Zadanie 2 - Sumowanie

section .text

global sum

sum:
	; Argumenty funkcji sum():
	; rdi - tablica "x[]"
	; rsi - "n", rozmiar tablicy "x[]"

	; rcx - "i", 1 <= i < n, indeks w tablicy "x[]"
	; r8 - wartość x[i]
	; rax - wartość przesunięcia bitowego x[i]

	; x[i] dodajemy na bitach zajmowanych przez dwie sąsiednie liczby 64-bitowe,
	; stąd dzielimy x[i] na:
	; r10 - młodsze bity x[i]
	; r11 - starsze bity x[i]

	; W i-tym kroku pętli def. y = x[0..i] (tj. liczba w U2 o 64*(i+1)-bitach)

	cmp rsi, 1
	je .exit ; tabela zawiera jeden element, więc nic nie robimy

	mov rcx, 1 ; x[0] pozostaje bez zmian
	mov r8, [rdi + 0] ; r8 = x[0]
.loop:
	test r8, r8 ; do sprawdzenia, czy x[i-1] jest dodatni, czy ujemny
	mov r8, [rdi + rcx * 8] ; r8 = x[i]
	js .negative_prevx
	mov QWORD [rdi + rcx * 8], 0 ; x[i] > 0 => y = x[0..i] > 0 => rozszerzamy
	; zakres y o kolejne 64 bity zerując je
	jmp .positive_prevx
.negative_prevx:
	mov QWORD [rdi + rcx * 8], -1 ; x[i] < 0 => y = x[0..i] < 0 => rozszerzamy
	; zakres y o kolejne 64 bity ustawiając każdy z nich na 1 (== -1 w U2)
.positive_prevx:
	; Obliczamy floor(64 * i * i / n)
	mov rax, 64
	mul rcx
	mul rcx
	div rsi
	
	mov r10, 64
	div r10 ; teraz eax zawiera indeks w tablicy, do jakiego dosuwamy x[i]
	; w rdx jest natomiast jest wartość rax mod 64

	AND eax, eax ; zerujemy starsze bity rax

	mov r10, r8 ; r10 = x[i]
	mov r11, r8 ; r11 = x[i]
	mov r8, rcx ; r8 = i, gdyż przesunięcie jako drugi argument przyjmuje cl
	mov rcx, rdx ; rcx = (rax mod 64)

	; Jeśli rax mod 64 != 0, to x[i] jest przesunięte w ten sposób, iż dodajemy
	; jego odpowiednie części (młodsze/starsze bity) do dwóch sąsiednich
	; elementów tablicy x[]

	; Młodsze bity x[i] chcemy przesunąć w lewo, aby dodawać je zgodnie z
	; wyliczonym przesunięciem - młodsze i starsze bity x[i] mają się ze sobą
	; "stykać" pomiędzy dwoma elementami tablicy x[], do których dodajemy x[i]
	shl r10, cl

	; Jeśli cl == 0, to wszystkie bity x[i] są w młodszej części => zerujemy r11
	cmp cl, 0
	jnz .nonzero_upper
	mov r11, 0

.nonzero_upper:
	; Starsze bity x[i] chcemy przesunąć w prawo, aby dodawać je zgodnie z
	; wyliczonym przesunięciem
	sub cl, 64
	neg cl ; cl = 64 - cl
	sar r11, cl

	add [rdi + rax * 8], r10 ; do niższego indeksu dodajemy młodsze bity x[i],
	; które są zawsze dodatnie
	;inc rax
	adc QWORD [rdi + rax * 8 + 8], 0 ; dodajemy CF do następnej liczby w tabeli
	inc rax

	; Jeśli starsze bity są ujemne, to zamiast je dodawać weźmiemy ich
	; uzupełnienie do 2 i je odejmiemy
	test r11, r11
	jns .positive_older_half
	neg r11
	sub [rdi + rax * 8], r11
	jmp .fi
.positive_older_half: 
	add [rdi + rax * 8], r11 ; do wyższego indeksu dodajemy starsze bity x[i]
.fi:
	mov rcx, r8 ; rcx = i
	mov r8, [rdi + rcx * 8] ; r8 = x[i]

	inc rcx ; i++
	cmp rcx, rsi ; czy i == n?
	jne .loop ; Pętla trwa, póki i < n
.exit:
	; Koniec działania programu
	xor rax, rax
	ret