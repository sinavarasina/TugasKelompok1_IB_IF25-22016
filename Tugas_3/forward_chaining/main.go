package main

import (
	"fmt"
	"sort"
)

type Rule struct {
	If       []string
	Then     string
	Priority string
}

func main() {
	facts := map[string]bool{
		"Mesin Mati Total":              true,
		"Suara Klik Saat Start":         true,
		"Tidak Ada Karat Pada Terminal": true,
	}
	_ = facts

	rules := []Rule{
		{If: []string{"Mesin Mati Total"}, Then: "Cek Kelistrikan", Priority: "1"},
		{If: []string{"Mesin Berputar Lambat"}, Then: "Aki Lemah", Priority: "2"},
		{If: []string{"Lampu Redup"}, Then: "Aki Lemah", Priority: "2"},
		{If: []string{"Aki Lemah", "Tidak Ada Karat Pada Terminal"}, Then: "Ganti Aki", Priority: "3"},
		{If: []string{"Suara Klik Saat Start"}, Then: "Aki Lemah", Priority: "2"},
		{If: []string{"Mesin Mati Total", "Tidak Ada Suara"}, Then: "Fungsi Kelistrikan Terputus", Priority: "3"},
		{If: []string{"Aki Lemah"}, Then: "Mesin Sulit Start", Priority: "2"},
		{If: []string{"Cek Kelistrikan", "Terjadi Konsleting"}, Then: "Isolasi Kelistrikan", Priority: "4"},
	}

	// sort the rules descending priority (Rule Order)
	sort.SliceStable(rules, func(i, j int) bool {
		return rules[i].Priority > rules[j].Priority
	})

	changed := true
	fmt.Println("facts : ", facts)
	for changed {
		changed = false

		for i, rule := range rules {
			satisfied := true
			fmt.Println(i)
			for _, cond := range rule.If {
				fmt.Println("====Cond", cond)
				fmt.Println("====priority", rule.Priority)
				if !facts[cond] {
					satisfied = false
					break
				}
				fmt.Println("ok")
			}
			if !satisfied {
				fmt.Println("nooooo")
			}
		}
	}

}
