#include "rules.hpp"
#include <print>
#include <vector>

int main() {
  BCMobil bc;
  bc.set_verbose(true);

  bc.add_rule(1, Sym::CEK_KELISTRIKAN, Sym::MESIN_MATI_TOTAL, Priority::RENDAH);
  bc.add_rule(2, Sym::AKI_LEMAH, Sym::MESIN_BERPUTAR_LAMBAT, Priority::SEDANG);
  bc.add_rule(3, Sym::AKI_LEMAH, Sym::LAMPU_REDUP, Priority::SEDANG);
  bc.add_rule(4, Sym::GANTI_AKI, Sym::AKI_LEMAH,
              Sym::TIDAK_ADA_KARAT_PADA_TERMINAL, Logic::AND, Priority::TINGGI);
  bc.add_rule(5, Sym::AKI_LEMAH, Sym::SUARA_KLIK_SAAT_START, Priority::SEDANG);
  bc.add_rule(6, Sym::FUNGSI_KELISTRIKAN_TERPUTUS, Sym::MESIN_MATI_TOTAL,
              Sym::TIDAK_ADA_SUARA, Logic::AND, Priority::TINGGI);
  bc.add_rule(7, Sym::MESIN_SULIT_START, Sym::AKI_LEMAH, Priority::RENDAH);
  bc.add_rule(8, Sym::ISOLASI_KELISTRIKAN, Sym::CEK_KELISTRIKAN,
              Sym::TERJADI_KONSLETING, Logic::AND, Priority::TINGGI);

  bc.add_fact(Sym::MESIN_MATI_TOTAL);
  bc.add_fact(Sym::SUARA_KLIK_SAAT_START);
  bc.add_fact(Sym::TIDAK_ADA_KARAT_PADA_TERMINAL);

  auto run = [&](Sym goal) {
    std::vector<int> proof;
    bool ok = bc.prove(goal, proof);
    std::print("{} {}\n", ok ? "[TERBUKTI]" : "[GAGAL]  ",
               BCMobil::sym_name(goal));
    if (ok && !proof.empty()) {
      std::print("  Jejak rule: ");
      for (size_t i = 0; i < proof.size(); ++i)
        std::print("R{}{}", proof[i], (i + 1 < proof.size() ? " -> " : "\n"));
    }
  };

  run(Sym::GANTI_AKI);
}
