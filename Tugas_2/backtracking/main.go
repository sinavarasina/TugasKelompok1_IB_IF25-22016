package main

import (
	"backtracking/mrv"
	"fmt"
)

func main() {
	var whichAlgorithm string
	fmt.Println("1. MRV")
	fmt.Scanln(&whichAlgorithm)

	switch whichAlgorithm {
	case "1":
		mrv.MRV()
	}

}
