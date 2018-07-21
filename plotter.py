
if __name__ == "__main__":
    import matplotlib.pyplot as plt

    #open the data file
    nodeResults = open("results.txt","r")
    resultsList = []
    for line in nodeResults:
        temp = line.split(;)
