def getCollisionPressure(boundingBoxList):
	out = []
	for box in boundingBoxList:
		out.append(box[4])
	return(out)

def getParticlePressure(boundingBoxList, particleStates, particleMomentums, volume):
	particleTally = []
	particleMomentumTotal = []
	for box in boundingBoxList:
		particleTally.append(0)
		particleMomentumTotal.append(0)

	for p in range(0,len(particleStates)):
		for i in range(0,len(boundingBoxList)):
			if(particleStates[p][0] >= boundingBoxList[i][0] and particleStates[p][0] <= boundingBoxList[i][1] and particleStates[p][1] >= boundingBoxList[i][2] and particleStates[p][1] <= boundingBoxList[i][3]):
				particleTally[i] += 1
				particleMomentumTotal[i] += (particleMomentums[p][0] ** 2 + particleMomentums[p][1] ** 2)
				break
	out = []
	for i in range(0,len(particleMomentumTotal)):
		out.append(particleMomentumTotal[i]/volume)

	return(out)

def getTemp(boundingBoxList, particleStates, particleMomentums):
	particleTally = []
	particleMomentumTotal = []
	for box in boundingBoxList:
		particleTally.append(0)
		particleMomentumTotal.append(0)

	for p in range(0,len(particleStates)):
		for i in range(0,len(boundingBoxList)):
			if(particleStates[p][0] >= boundingBoxList[i][0] and particleStates[p][0] <= boundingBoxList[i][1] and particleStates[p][1] >= boundingBoxList[i][2] and particleStates[p][1] <= boundingBoxList[i][3]):
				particleTally[i] += 1
				particleMomentumTotal[i] += (particleMomentums[p][0] ** 2 + particleMomentums[p][1] ** 2)
				break



	return(particleMomentumTotal)

def getFlow(boundingBoxList, particleStates1, particleStates2):
	particleTally1 = []
	particleTally2 = []
	for box in boundingBoxList:
		particleTally1.append(0)
		particleTally2.append(0)

	for p in range(0,len(particleStates1)):
		for i in range(0,len(boundingBoxList)):
			if(particleStates1[p][0] >= boundingBoxList[i][0] and particleStates1[p][0] <= boundingBoxList[i][1] and particleStates1[p][1] >= boundingBoxList[i][2] and particleStates1[p][1] <= boundingBoxList[i][3]):
				particleTally1[i] += 1
				break

	for p in range(0,len(particleStates2)):
		for i in range(0,len(boundingBoxList)):
			if(particleStates2[p][0] >= boundingBoxList[i][0] and particleStates2[p][0] <= boundingBoxList[i][1] and particleStates2[p][1] >= boundingBoxList[i][2] and particleStates2[p][1] <= boundingBoxList[i][3]):
				particleTally2[i] += 1
				break

	deltaLeft = particleTally2[0]-particleTally1[0]
	deltaRight = particleTally2[1]-particleTally1[1]

	return(deltaRight-deltaLeft)




def main():
	boundingBoxList = [[0,1,0,1,5],[1,2,0,1,7]]
	particleStates = [[0,0],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]

	particleStates1 = [[0,0],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]
	particleStates2 = [[1.5,.5],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]

	particleMomentums = [[0,0],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]
	print(getCollisionPressure(boundingBoxList))
	print(getParticlePressure(boundingBoxList,particleStates,particleMomentums,1))
	print(getTemp(boundingBoxList,particleStates,particleMomentums))
	print(getFlow(boundingBoxList,particleStates1, particleStates2))

main()

