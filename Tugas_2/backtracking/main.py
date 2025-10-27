from mrv.mrv import MRV

def main():
    whichAlgorithm = input("1. MRV\n2. Degree Heuristic\npilih salah satu: ")
    if whichAlgorithm == "1":
        MRV()

if __name__ == "__main__":
    main()
