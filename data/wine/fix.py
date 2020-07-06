with open("wine.data", "r") as wine:
    with open("wine.csv", "w") as out:
        for line in wine.readlines():
            l = line[0]
            s = line[2:]
            s = s[:-1]
            out.write(s + "," + l + "\n")