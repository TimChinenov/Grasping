
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
    for line in nodeResults:
        temp = line.split(';')
        pos = temp[0].strip('(')
        pos = pos.strip(')')
        pos = pos.split(',')
        pos = [float(pos[0]),float(pos[1])]
        plt.plot(pos[0],pos[1],'bo')
    plt.pause(10)
