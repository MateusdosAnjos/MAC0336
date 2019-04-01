mX = [1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0]
cX = [[0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
cXInv = [[0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
hexaTo2 = {
"0":[0, 0, 0, 0],
"1":[1, 0, 0, 0],
"2":[0, 1, 0, 0],
"3":[1, 1, 0, 0],
"4":[0, 0, 1, 0],
"5":[1, 0, 1, 0],
"6":[0, 1, 1, 0],
"7":[1, 1, 1, 0],
"8":[0, 0, 0, 1],
"9":[1, 0, 0, 1],
"A":[0, 1, 0, 1],
"B":[1, 1, 0, 1],
"C":[0, 0, 1, 1],
"D":[1, 0, 1, 1],
"E":[0, 1, 1, 1],
"F":[1, 1, 1, 1]
}

TwoTo16 = {
"0000":"0",
"1000":"1",
"0100":"2",
"1100":"3",
"0010":"4",
"1010":"5",
"0110":"6",
"1110":"7",
"0001":"8",
"1001":"9",
"0101":"A",
"1101":"B",
"0011":"C",
"1011":"D",
"0111":"E",
"1111":"F"
}
def somaBit(a, b):
	if (a == b): return 0
	else: return 1

def multiplicaByte(a, b):
	mult = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	for i in range (16):
		for j in range (16):
			if (a[i] == 1 and b[j] == 1):
				mult[i+j] = (mult[i+j] + 1)%2 
	return mult

def somaByte(a, b):
	soma = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	for i in range (16):
		soma[i] = somaBit(a[i], b[i])
	return soma	

def leHexadecimal(a):
	hexa = input()
	print("Hexa lido = ", hexa)
	byte0 = hexa[6]+hexa[7]
	byte1 = hexa[4]+hexa[5]
	byte2 = hexa[2]+hexa[3]
	byte3 = hexa[0]+hexa[1]
	a[0] = base16para2(byte0)
	a[1] = base16para2(byte1)
	a[2] = base16para2(byte2)
	a[3] = base16para2(byte3)
	for i in range (8):
		a[0].append(0)
		a[1].append(0)
		a[2].append(0)
		a[3].append(0)
	return 
		
def lePolinomio(a, b):
	k = 3
	while k >= 0:
		for i in range(8):
			a[k][i] = int(input())
		k = k - 1
	k = 3		
	while k >= 0:	
		for j in range(8):
			b[k][j] = int(input())
		k = k - 1	
	return a, b			

def calculaProduto(a, b):
	k = 6
	Cx = []
	while k > 0:
		i = 3
		while i >= 0:
			for j in range (4): 
				if ((i + j) == k):
					Cx.append((dividePolinomio((multiplicaByte(a[i], b[j])), mX)))
			i = i - 1
		k = k - 1
	Cx.append((dividePolinomio(multiplicaByte(a[0], b[0]), mX)))			
	return Cx

def dividePolinomio(dividendo, divisor):
	quociente = [0] * 16
	quoAux = [0] * 16
	i = len(divisor) - 1
	while i >= 0 and divisor[i] == 0:
		i = i - 1
	j = len(dividendo) - 1
	while j >= 0 and dividendo[j] == 0:
		j = j - 1	
	while j > i:
		quociente[int(j-i)] = 1
		quoAux[int(j-i)] = 1
		aux = multiplicaByte(quoAux, divisor)
		dividendo = somaByte(dividendo, aux)
		quoAux[int(j-i)] = 0
		j = len(dividendo) - 1
		while j >= 0 and dividendo[j] == 0:
			j = j - 1
	if j == i:
		quociente[0] = 1
		quoAux[0] = 1
		aux = multiplicaByte(quoAux, divisor)
		dividendo = somaByte(dividendo, aux)						
	return dividendo

def eleva(a, b):
	result = 1
	for i in range(b):
		result = result * a
	return result	

def base2para16(a):
	menosSig = []
	maisSig = []
	soma = 0
	resultado = []
	for i in range (4,8):
		maisSig.append(a[i])
	for i in range (4):
		soma = soma + (maisSig[i]*eleva(2, i))
	if (soma < 10):	
		resultado.append(str(soma))
	elif (soma == 10):	
		resultado.append('A')
	elif (soma == 11):	
		resultado.append('B')
	elif (soma == 12):	
		resultado.append('C')
	elif (soma == 13):	
		resultado.append('D')
	elif (soma == 14):	
		resultado.append('E')
	elif (soma == 15):	
		resultado.append('F')						
	soma = 0
	for i in range (4):
		menosSig.append(a[i])
	for i in range (4):
		soma = soma + (menosSig[i]*eleva(2, i))
	if (soma < 10):	
		resultado.append(str(soma))
	elif (soma == 10):	
		resultado.append('A')
	elif (soma == 11):	
		resultado.append('B')
	elif (soma == 12):	
		resultado.append('C')
	elif (soma == 13):	
		resultado.append('D')
	elif (soma == 14):	
		resultado.append('E')
	elif (soma == 15):	
		resultado.append('F')	

	resultado = resultado[0] + resultado[1]	
	return resultado

def base16para2(a):
	maisSig = a[0]
	menosSig = a[1]
	resultado = []
	aux = []
	aux.append(hexaTo2[menosSig])
	aux.append(hexaTo2[maisSig])
	for l in aux:
		for i in range(4):
			resultado.append(l[i])
	return resultado

def imprimePolinomio(a):
	termo = 0
	for i in range (len(a)):
		if (a[i] == 1):
			termo = termo + 1
	i = len(a) - 1
	while termo > 1:
		if (a[i] == 1):
			termo = termo - 1
			print("x^", end='')
			print(i, end='')
			print(" + ", end='')
		i = i - 1
	while termo > 0:
		if (a[i] == 1 and i > 0):
			print("x^", end='')
			print(i, end='')
			termo = termo - 1
		elif (a[i] == 1 and i == 0):
			print("1", end='')
			termo = termo - 1
		i = i - 1	
	return		

def imprimePolinomioByte(a, nome):
	
	print(nome + " = ", end='')
	print("(",end='')
	imprimePolinomio(a[3])
	print(")x^3", end=' + ')
	print("(",end='')
	imprimePolinomio(a[2])
	print(")x^2", end=' + ')
	print("(",end='')
	imprimePolinomio(a[1])
	print(")x", end=' + ')
	print("(",end='')
	imprimePolinomio(a[0])
	print(")")

	return

def imprimeGrau6(Cx):
	k = 6
	l = 0
	while k > 0:
		i = 3
		while i >= 0:
			for j in range (4): 
				if ((i + j) == k):
					print("(", end='')
					imprimePolinomio(Cx[l])
					print(")x^", end='')
					print(k)
					l = l + 1
			i = i - 1
		k = k - 1
	print("(", end='')
	imprimePolinomio(Cx[l])
	print(")")
	return

def imprimeGrau6Base16(Cx):
	k = 6
	l = 0
	while k > 0:
		i = 3
		while i >= 0:
			for j in range (4): 
				if ((i + j) == k):
					print("(", end='')
					print(base2para16(Cx[l]), end='')
					print(")x^", end='')
					print(k)
					l = l + 1
			i = i - 1
		k = k - 1
	print("(", end='')
	print(base2para16(Cx[l]), end = '')
	print(")")
	return	

def CxModMx(Ax, Bx):
	x3 = somaByte(somaByte(multiplicaByte(Ax[0], Bx[3]), multiplicaByte(Ax[1], Bx[2])), somaByte(multiplicaByte(Ax[2], Bx[1]), multiplicaByte(Ax[3], Bx[0])))
	x2 = somaByte(somaByte(multiplicaByte(Ax[0], Bx[2]), multiplicaByte(Ax[1], Bx[1])), somaByte(multiplicaByte(Ax[2], Bx[0]), multiplicaByte(Ax[3], Bx[3])))
	x1 = somaByte(somaByte(multiplicaByte(Ax[0], Bx[1]), multiplicaByte(Ax[1], Bx[0])), somaByte(multiplicaByte(Ax[2], Bx[3]), multiplicaByte(Ax[3], Bx[2])))
	x0 = somaByte(somaByte(multiplicaByte(Ax[0], Bx[0]), multiplicaByte(Ax[1], Bx[3])), somaByte(multiplicaByte(Ax[2], Bx[2]), multiplicaByte(Ax[3], Bx[1])))
	return x3, x2, x1, x0


def main():
	Ax = [0, 1, 2, 3]
	Bx = [0, 1, 2, 3]
	for i in range (4):
		Ax[i] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		Bx[i] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
###############################EXERCÍCIO 3#####################################
	
	# print("-----------------------EXERCÍCIO 3--------------------------")
	# Ax, Bx = lePolinomio(Ax, Bx)
	# imprimePolinomioByte(Ax, "Ax")
	# imprimePolinomioByte(Bx, "Bx")
	# Cx = calculaProduto(Ax, Bx)
	# imprimeGrau6(Cx)
	# imprimeGrau6Base16(Cx)
	# print("Calculo de CxModMx:")
	# x3, x2, x1, x0 = CxModMx(Ax, Bx)
	# print("(",end='')
	# #imprimePolinomio(dividePolinomio(x3, mX))
	# print(base2para16(dividePolinomio(x3, mX)),end='')
	# print(")x^3")

	# print("(",end='')
	# #imprimePolinomio(dividePolinomio(x2, mX))
	# print(base2para16(dividePolinomio(x2, mX)),end='')
	# print(")x^2")

	# print("(",end='')
	# #imprimePolinomio(dividePolinomio(x1, mX))
	# print(base2para16(dividePolinomio(x1, mX)),end='')
	# print(")x")

	# print("(",end='')
	# #imprimePolinomio(dividePolinomio(x0, mX))
	# print(base2para16(dividePolinomio(x0, mX)),end='')
	# print(")")
	
###############################################################################

##############################EXERCÍCIO 4######################################
	print("-----------------------EXERCÍCIO 4--------------------------")
	leHexadecimal(Ax)
	print("Hexa reconstruido = ", end ='')
	print(base2para16(Ax[3]), end='')
	print(base2para16(Ax[2]), end='')
	print(base2para16(Ax[1]), end='')
	print(base2para16(Ax[0]))

	imprimePolinomioByte(Ax, "Ax")
	Cx = calculaProduto(Ax, cXInv)
	print("C(x) = ")
	imprimeGrau6(Cx)
	imprimeGrau6Base16(Cx)

	#################TESTE DE QUE c(x) X cInv(x) = 1 ##########################
	#teste = calculaProduto(cX, cXInv)
	#imprimeGrau6(teste)
	#print("Calculo de CxModMx:")
	#x3, x2, x1, x0 = CxModMx(cX, cXInv)
	#print("(",end='')
	#imprimePolinomio(dividePolinomio(x3, mX))
	#print(base2para16(dividePolinomio(x3, mX)),end='')
	#print(")x^3")

	#print("(",end='')
	#imprimePolinomio(dividePolinomio(x2, mX))
	#print(base2para16(dividePolinomio(x2, mX)),end='')
	#print(")x^2")

	#print("(",end='')
	#imprimePolinomio(dividePolinomio(x1, mX))
	#print(base2para16(dividePolinomio(x1, mX)),end='')
	#print(")x")

	#print("(",end='')
	#imprimePolinomio(dividePolinomio(x0, mX))
	#print(base2para16(dividePolinomio(x0, mX)),end='')
	#print(")")
	#############################################################

	print("Calculo de BxModMx:")
	x3, x2, x1, x0 = CxModMx(Ax, cXInv)
	print("(",end='')
	#imprimePolinomio(dividePolinomio(x3, mX))
	print(base2para16(dividePolinomio(x3, mX)),end='')
	print(")x^3")

	print("(",end='')
	#imprimePolinomio(dividePolinomio(x2, mX))
	print(base2para16(dividePolinomio(x2, mX)),end='')
	print(")x^2")

	print("(",end='')
	#imprimePolinomio(dividePolinomio(x1, mX))
	print(base2para16(dividePolinomio(x1, mX)),end='')
	print(")x")

	print("(",end='')
	#imprimePolinomio(dividePolinomio(x0, mX))
	print(base2para16(dividePolinomio(x0, mX)),end='')
	print(")")

###############################################################################

main()
