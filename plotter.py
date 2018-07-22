
if __name__ == "__main__":
    import matplotlib.pyplot as plt
    #set-up the plot
    fig, ax = plt.subplots()
    plt.xlim(-2,14)
    plt.ylim(-2,12)
    plt.pause(1)
    #plt.gca.set_aspect('equal',adjustable='box')
    #open the data file
    nodeResults = open("results.txt","r")
    nodePaths = open("path.txt","r")
    pathList = []

    counter = 0
    for line in nodeResults:
        counter += 1
        temp = line.split(';')
        pos = temp[0].strip('(')
        pos = pos.strip(')')
        pos = pos.split(',')
        pos = [float(pos[0]),float(pos[1])]
        #organize children
        if len(temp[1]) > 1:
            children = (temp[1].strip()).strip('(')
            children = children.strip(')')
            children = children.split(')(')
            for child in children:
                    cpos = child.split(',')
                    plt.plot([pos[0],float(cpos[0])],[pos[1],float(cpos[1])],'go-')
            plt.plot(pos[0],pos[1],'go')
    nodeResults.close()
    #organize path points into array
    for line in nodePaths:
        temp = line.strip()
        temp = temp.strip(")")
        temp = temp.strip("(")
        pos = temp.split(',')
        pathList.append([float(pos[0]),float(pos[1])])
    for itr in range(0,len(pathList)-1):
        xList = [pathList[itr][0],pathList[itr+1][0]]
        yList = [pathList[itr][1],pathList[itr+1][1]]
        plt.plot(xList,yList,'ro-')

    nodePaths.close()
    #plot the initial position of the shape
    plt.plot([6,4],[2.9,2.9],'r-')
    plt.plot([4,4],[2.9,2.7],'r-')
    plt.plot([4,4.2],[2.7,2.7],'r-')
    plt.plot([4.2,4.2],[2.7,0.2],'r-')
    plt.plot([4.2,4],[0.2,0.2],'r-')
    plt.plot([4,4],[0.2,0],'r-')
    plt.plot([4,6],[0,0],'r-')
    plt.plot([6,6],[0,0.2],'r-')
    plt.plot([6,5.8],[0.2,0.2],'r-')
    plt.plot([5.8,5.8],[0.2,2.7],'r-')
    plt.plot([5.8,6],[2.7,2.7],'r-')
    plt.plot([6,6],[2.7,2.9],'r-')
    plt.pause(120)
