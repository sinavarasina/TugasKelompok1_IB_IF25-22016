from mrv.mrv import MRV
from degreeHeuristic.degreeHeuristic import Degree_Heuristic
from forward_checking.forward_checking import Forward_Checking

def main():
    whichAlgorithm = input("1. MRV\n2. Degree Heuristic\n3. Forward_Checking\npilih salah satu: ")
    if whichAlgorithm == "1":
        MRV()
    elif whichAlgorithm == "2":
        Degree_Heuristic()
    elif whichAlgorithm == "3":
        Forward_Checking()
        

if __name__ == "__main__":
    main()
