def getCollisionPressure(boundingBoxList):
	out = []
	for box in boundingBoxList:
		out.append(box[4])
	return(out)

def getParticlePressure(boundingBoxList, particleStates):
	particleTally = []
	for box in boundingBoxList:
		particleTally.append(0)

	for particle in particleStates:
		for i in range(0,len(boundingBoxList)):
			if(particle[0] >= boundingBoxList[i][0] and particle[1] >= boundingBoxList[i][1] and particle[0] <= boundingBoxList[i][2] and particle[1] <= boundingBoxList[i][3]):
				particleTally[i] += 1
				break

	return(particleTally)

def main():
	boundingBoxList = [[0,0,1,1,5],[1,0,2,1,7]]
	particleStates = [[0,0],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]
	print(getCollisionPressure(boundingBoxList))
	print(getParticlePressure(boundingBoxList,particleStates))

main()

