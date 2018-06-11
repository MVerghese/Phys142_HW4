import csv




def writeState(fileName, HList, VList, particleStates):
	F = open(fileName, 'w')
	HString = ""
	for barrier in HList:
		for coord in barrier:
			HString+= str(coord)+','

	HString = HString[:-1]
	HString+= '\n'
	F.write(HString)

	VString = ""
	for barrier in VList:
		for coord in barrier:
			VString+= str(coord)+','

	VString = VString[:-1]
	VString+= '\n'
	F.write(VString)

	particleStateString = ""
	for particle in particleStates:
		for coord in particle:
			particleStateString+= str(coord)+','
	particleStateString = particleStateString[:-1]
	particleStateString += '\n'
	F.write(particleStateString)

	F.close()

	return True

def readState(fileName, HList, VList, particleStates):
	with open(fileName, 'rb') as f:
		out = csv.reader(f, delimiter=',')

		parsedString = []
		for row in out:
			parsedString.append(row)	
		del HList[:]
		del VList[:]
		del particleStates[:]

		temp = []
		for i in range(0,len(parsedString[0])-1,3):
			temp.append(eval(parsedString[0][i]))
			temp.append(eval(parsedString[0][i+1]))
			temp.append(eval(parsedString[0][i+2]))
			HList.append(temp[:])
			del temp[:]

		temp = []
		for i in range(0,len(parsedString[1])-1,3):
			temp.append(eval(parsedString[1][i]))
			temp.append(eval(parsedString[1][i+1]))
			temp.append(eval(parsedString[1][i+2]))
			VList.append(temp[:])
			del temp[:]

		temp = []
		for i in range(0,len(parsedString[2])-1,2):
			temp.append(eval(parsedString[2][i]))
			temp.append(eval(parsedString[2][i+1]))
			particleStates.append(temp[:])
			del temp[:]

		f.close()

	return True


def main():
	HList = [];
	VList = [];
	particleStates = [];
	for i in range (0,5):
		temp1 = []
		temp2 = []
		temp3 = []
		for j in range(0,3):
			temp1.append(i+j)
			temp2.append(i+j+10)

		HList.append(temp1[:])
		VList.append(temp2[:])

		temp3.append(i+20)
		temp3.append(i+20+1)

		particleStates.append(temp3[:])

	#writeState("test.txt", HList, VList, particleStates)
	readState("test.txt", HList, VList, particleStates)

	print(HList)
	print(VList)
	print(particleStates)


main()
