package mrv

import (
	"fmt"
	"slices"
)

func MRV() {
	// Variabel
	mahasiswa := []string{"Ani", "Budi", "Citra", "Dedi", "Eka"}

	// Domain
	kelas := [2][]string{{}, {}}

	// Loop
	loop := true
	for loop == true {
		if len(mahasiswa) == 0 {
			break
		}

		if mahasiswa[0] == "Ani" {
			for i := range kelas {
				if slices.Contains(kelas[i], "Budi") == false {
					kelas[i] = append(kelas[i], "Ani")
					mahasiswa = mahasiswa[1:]
					break
				}
			}

		} else if mahasiswa[0] == "Budi" {
			for i := range kelas {
				if slices.Contains(kelas[i], "Ani") == false {
					kelas[i] = append(kelas[i], "Budi")
					mahasiswa = mahasiswa[1:]
					break
				}
			}

		} else if mahasiswa[0] == "Citra" {
			kelas1 := len(kelas[0])
			kelas2 := len(kelas[1])

			lowest := 0
			if kelas2 < kelas1 {
				lowest = 1
			}
			for i := range kelas {
				if slices.Contains(kelas[i], "Dedi") == true {
					kelas[i] = append(kelas[i], "Citra")
					mahasiswa = mahasiswa[1:]
					break
				}
			}
			kelas[lowest] = append(kelas[lowest], "Citra")
			mahasiswa = mahasiswa[1:]

		} else if mahasiswa[0] == "Dedi" {
			kelas1 := len(kelas[0])
			kelas2 := len(kelas[1])

			lowest := 0
			if kelas2 < kelas1 {
				lowest = 1
			}

			for i := range kelas {
				if slices.Contains(kelas[i], "Citra") == true {
					kelas[i] = append(kelas[i], "Dedi")
					mahasiswa = mahasiswa[1:]
					break
				}
			}
			kelas[lowest] = append(kelas[lowest], "Dedi")
			mahasiswa = mahasiswa[1:]

		} else if mahasiswa[0] == "Eka" {
			for i := range kelas {
				if slices.Contains(kelas[i], "Citra") == true {
					kelas[i] = append(kelas[i], "Dedi")
					mahasiswa = mahasiswa[1:]
					break
				}
			}
			kelas[0] = append(kelas[0], "Dedi")
			mahasiswa = mahasiswa[1:]

		}

		fmt.Println(kelas)
	}

}
