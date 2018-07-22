
if __name__ == "__main__":
    import matplotlib.pyplot as plt
    #set-up the plot
    fig, ax = plt.subplots()
    plt.xlim(0,12)
    plt.ylim(0,10)
    plt.pause(1)
    #plt.gca.set_aspect('equal',adjustable='box')
    #open the data file
    nodeResults = open("results.txt","r")
    resultsList = []
    counter = 0
    for line in nodeResults:
        counter += 1
        temp = line.split(';')
        pos = temp[0].strip('(')
        pos = pos.strip(')')
        pos = pos.split(',')
        pos = [float(pos[0]),float(pos[1])]
        #organize children
        plt.plot(pos[0],pos[1],'yo')
        if len(temp[1]) > 1:
            children = (temp[1].strip()).strip('(')
            children = children.strip(')')
            children = children.split(')(')
            for child in children:
                    cpos = child.split(',')
                    plt.plot([pos[0],float(cpos[0])],[pos[1],float(cpos[1])],'b-')
            plt.plot(pos[0],pos[1],'go')
    print "asdasdas" + str(counter)
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
