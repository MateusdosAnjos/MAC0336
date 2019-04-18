def main():
	exp = 256 * [0]
	log = 256 * [0]
	for i in range (256):
		valor = (45**i)%257
		if (valor == 256):
			exp[i] = 0
		else:
			exp[i] = valor	
	for i in range (256):
		log[exp[i]] = i	
	for i in range (256):
		print(exp[i], end=' ')
	print()
	for i in range (256):
		print(log[i], end=' ')
	return
main()		