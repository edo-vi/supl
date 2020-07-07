with open("ecoli.data", "r") as ec:
    with open("ecoli.csv", "w") as out:
        for line in ec.readlines():
            line = line.split()
            line = ",".join(line[1:])
            out.write(line + "\n")