from mrv.mrv import MRV
from degreeHeuristic.degreeHeuristic import Degree_Heuristic

def main():
    whichAlgorithm = input("1. MRV\n2. Degree Heuristic\npilih salah satu: ")
    if whichAlgorithm == "1":
        MRV()
    elif whichAlgorithm == "2":
        Degree_Heuristic()

if __name__ == "__main__":
    main()
