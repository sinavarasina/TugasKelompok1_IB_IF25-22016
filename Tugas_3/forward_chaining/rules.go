package main

type Rule struct {
	If       []string
	Then     string
	Priority int
}

func GetRules() []Rule {
	return []Rule{
		{If: []string{"Mesin Mati Total"}, Then: "Cek Kelistrikan", Priority: 1},
		{If: []string{"Mesin Berputar Lambat"}, Then: "Aki Lemah", Priority: 2},
		{If: []string{"Lampu Redup"}, Then: "Aki Lemah", Priority: 2},
		{If: []string{"Aki Lemah", "Tidak Ada Karat Pada Terminal"}, Then: "Ganti Aki", Priority: 3},
		{If: []string{"Suara Klik Saat Start"}, Then: "Aki Lemah", Priority: 2},
		{If: []string{"Mesin Mati Total", "Tidak Ada Suara"}, Then: "Fungsi Kelistrikan Terputus", Priority: 3},
		{If: []string{"Aki Lemah"}, Then: "Mesin Sulit Start", Priority: 2},
		{If: []string{"Cek Kelistrikan", "Terjadi Konsleting"}, Then: "Isolasi Kelistrikan", Priority: 4},
	}
}
