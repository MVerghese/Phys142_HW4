def getCollisionPressure(boundingBoxList):
	out = []
	for box in boundingBoxList:
		out.append(box[4])
	return(out)

def getParticlePressure(boundingBoxList, particleStates, particleMomentums):
	particleTally = []
	particleMomentumTotal = []
	for box in boundingBoxList:
		particleTally.append(0)
		particleMomentumTotal.append(0)

	for p in range(0,len(particleStates)):
		for i in range(0,len(boundingBoxList)):
			if(particleStates[p][0] >= boundingBoxList[i][0] and particleStates[p][1] >= boundingBoxList[i][1] and particleStates[p][0] <= boundingBoxList[i][2] and particleStates[p][1] <= boundingBoxList[i][3]):
				particleTally[i] += 1
				particleMomentumTotal[i] += (particleMomentums[p][0] ** 2 + particleMomentums[p][1] ** 2)
				break

	out = []
	for i in range(0,len(particleMomentumTotal)):
		out.append(particleMomentumTotal[i]/particleTally[i])

	return(out)

def main():
	boundingBoxList = [[0,0,1,1,5],[1,0,2,1,7]]
	particleStates = [[0,0],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]
	particleMomentums = [[0,0],[.5,.5],[.7,.7],[1,.5],[1.3,.3],[1.6,.6]]
	print(getCollisionPressure(boundingBoxList))
	print(getParticlePressure(boundingBoxList,particleStates,particleMomentums))

main()

