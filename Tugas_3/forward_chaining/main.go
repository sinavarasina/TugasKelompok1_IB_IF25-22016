package main

import (
	"fmt"
	"sort"
)

type Rule struct {
	If       []string
	Then     string
	Priority int
}

func main() {
	facts := map[string]bool{
		"Mesin Mati Total":              true,
		"Suara Klik Saat Start":         true,
		"Tidak Ada Karat Pada Terminal": true,
	}
	_ = facts

	factOrder := []string{"Mesin Mati Total", "Suara Klik Saat Start", "Tidak Ada Karat Pada Terminal"}

	rules := []Rule{
		{If: []string{"Mesin Mati Total"}, Then: "Cek Kelistrikan", Priority: 1},
		{If: []string{"Mesin Berputar Lambat"}, Then: "Aki Lemah", Priority: 2},
		{If: []string{"Lampu Redup"}, Then: "Aki Lemah", Priority: 2},
		{If: []string{"Aki Lemah", "Tidak Ada Karat Pada Terminal"}, Then: "Ganti Aki", Priority: 3},
		{If: []string{"Suara Klik Saat Start"}, Then: "Aki Lemah", Priority: 2},
		{If: []string{"Mesin Mati Total", "Tidak Ada Suara"}, Then: "Fungsi Kelistrikan Terputus", Priority: 3},
		{If: []string{"Aki Lemah"}, Then: "Mesin Sulit Start", Priority: 2},
		{If: []string{"Cek Kelistrikan", "Terjadi Konsleting"}, Then: "Isolasi Kelistrikan", Priority: 4},
	}

	// sort the rules descending priority (1. Rule Order)
	sort.SliceStable(rules, func(i, j int) bool {
		// sort the rules by specificity  (2. Specificity)
		if rules[i].Priority == rules[j].Priority {
			return len(rules[i].If) > len(rules[j].If)
		}
		return rules[i].Priority > rules[j].Priority
	})

	usedRules := make(map[int]bool)

	changed := true
	loop := 0
	for changed {
		loop++
		fmt.Println(">>>>>>>>>>>>>>>>>>>>>>>>>>", loop, "<<<<<<<<<<<<<<<<<<<<<<<<<<<")
		changed = false

		for i, rule := range rules {
			// skip the rule by used rules (Refractoriness)
			if usedRules[i] {
				continue
			}

			satisfied := true
			fmt.Println("R", i)
			for _, cond := range rule.If {
				fmt.Println("Cond : ", cond)
				fmt.Println("priority : ", rule.Priority)
				fmt.Println(cond, "-------->", rule.Then)
				if !facts[cond] {
					satisfied = false
					break
				}
				fmt.Println("ok ok ok ok ok ok ok")
				fmt.Println("------------")
			}

			if !satisfied {
				fmt.Println("xxxxxxxxxxxx")
				fmt.Println("------------")
			}

			if satisfied && !facts[rule.Then] {
				fmt.Println("Rule terpenuhi:", rule.Then)
				facts[rule.Then] = true
				factOrder = append(factOrder, rule.Then)
				usedRules[i] = true
				changed = true
			}

			fmt.Printf("=====Facts=====")
			fmt.Println()

			for _, f := range factOrder {
				fmt.Printf(" - %s\n", f)
			}

			fmt.Println()
			fmt.Println()
		}
	}

}
