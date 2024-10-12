	.intel_syntax noprefix
	.global main
	.text
main:
	# write message to stdout
	# write(1, message, 14)
    mov rax, 1         # Indexul apelului de sistem write este 1
	mov rdi, 1         # Primul parametru este descriptorul pentru standard output. În cazul nostru este 1
	lea rsi, message   # Al doilea parametru, adresa mesajului pe care vrem să îl afișăm
	mov rdx, 17        # Al treilea parametru, numărul de caractere pe care vrem să îl afișăm
	syscall            # Invocăm apelul de sistem
 
 
	# exit program
	# exit(0)
	# TODO 

	mov rax, 60
	mov rdi, 0
	syscall
 
.section .rodata
message:
	.asciz "Hello, Cristian!\n"