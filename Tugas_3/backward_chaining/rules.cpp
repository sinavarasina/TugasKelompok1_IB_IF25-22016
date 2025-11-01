#include "rules.hpp"
#include <algorithm>
#include <print>

void BCMobil::add_rule(int id, Sym thenSym, Sym if1Sym,
                       std::optional<Sym> if2Sym, std::optional<Logic> logic,
                       Priority prio) {
  if (!if2Sym)
    logic.reset();
  rules.push_back(Rule{id, thenSym, if1Sym, if2Sym, logic, prio});
}

void BCMobil::add_rule(int id, Sym thenSym, Sym if1Sym, Priority prio) {
  add_rule(id, thenSym, if1Sym, std::nullopt, std::nullopt, prio);
}

u64 BCMobil::key(Sym g, int rid) {
  auto gg = static_cast<u64>(static_cast<u32>(g));
  auto rr = static_cast<u64>(static_cast<u32>(rid));
  return (gg << 32) | rr;
}

int BCMobil::specificity(const Rule &r) {
  if (!r.if2Sym)
    return 1;
  if (r.logic && *r.logic == Logic::AND)
    return 2;
  return 0;
}

int BCMobil::priority_rank(const Rule &r) {
  int base = 0;
  switch (r.prio) {
  case Priority::RENDAH:
    base = 1;
    break;
  case Priority::SEDANG:
    base = 2;
    break;
  case Priority::TINGGI:
    base = 3;
    break;
  }
  if (r.id == 8)
    base = 4;
  return base;
}

bool BCMobil::prove(Sym goal, std::vector<int> &proof_ids) {
  std::unordered_set<Sym> on_path;
  proof_ids.clear();
  tried.clear();
  memo_ok.clear();
  memo_fail.clear();
  if (verbose)
    std::print("== Mulai backward chaining untuk goal: {}\n", sym_name(goal));
  bool ok = prove_dfs(goal, proof_ids, on_path, 0);
  if (verbose)
    std::print("== Selesai: goal {} {}\n", sym_name(goal),
               ok ? "TERBUKTI" : "GAGAL");
  return ok;
}

bool BCMobil::prove_dfs(Sym goal, std::vector<int> &proof_ids,
                        std::unordered_set<Sym> &on_path, int depth) {
  if (facts.count(goal)) {
    if (verbose)
      std::print("{:{}}Fakta terpenuhi: {}\n", "", depth * 2, sym_name(goal));
    return true;
  }
  if (on_path.count(goal)) {
    if (verbose)
      std::print("{:{}}Loop terdeteksi pada {}\n", "", depth * 2,
                 sym_name(goal));
    return false;
  }
  if (memo_ok.count(goal)) {
    if (verbose)
      std::print("{:{}}Memo OK: {}\n", "", depth * 2, sym_name(goal));
    return true;
  }
  if (memo_fail.count(goal)) {
    if (verbose)
      std::print("{:{}}Memo FAIL: {}\n", "", depth * 2, sym_name(goal));
    return false;
  }

  on_path.insert(goal);
  if (verbose)
    std::print("{:{}}Buktikan goal: {}\n", "", depth * 2, sym_name(goal));

  std::vector<size_t> idx;
  idx.reserve(rules.size());
  for (size_t i = 0; i < rules.size(); ++i)
    if (rules[i].thenSym == goal)
      idx.push_back(i);

  if (verbose) {
    if (idx.empty()) {
      std::print("{:{}}Tidak ada aturan menghasilkan {}\n", "", depth * 2,
                 sym_name(goal));
    } else {
      std::print("{:{}}Conflict set (RHS == {}):\n", "", depth * 2,
                 sym_name(goal));
      for (size_t i : idx) {
        const Rule &r = rules[i];
        std::print("{:{}}  R{}: IF {}{}{} THEN {}\n", "", depth * 2, r.id,
                   sym_name(r.if1Sym),
                   (r.if2Sym
                        ? (r.logic && *r.logic == Logic::AND ? " AND " : " OR ")
                        : ""),
                   (r.if2Sym ? sym_name(*r.if2Sym) : ""), sym_name(r.thenSym));
      }
    }
  }

  std::sort(idx.begin(), idx.end(), [&](size_t a, size_t b) {
    const Rule &A = rules[a];
    const Rule &B = rules[b];
    int pa = priority_rank(A), pb = priority_rank(B);
    if (pa != pb)
      return pa > pb;
    int sa = specificity(A), sb = specificity(B);
    if (sa != sb)
      return sa > sb;
    return A.id < B.id;
  });

  if (verbose && !idx.empty()) {
    std::print("{:{}}Urutan kandidat (RuleOrder > Spesifisitas > ID):\n", "",
               depth * 2);
    for (size_t i : idx) {
      const Rule &r = rules[i];
      std::print("{:{}}  R{} [prioRank={}, spec={}]\n", "", depth * 2, r.id,
                 priority_rank(r), specificity(r));
    }
  }

  for (size_t i : idx) {
    const Rule &r = rules[i];

    auto k = key(goal, r.id);
    if (tried.count(k)) {
      if (verbose)
        std::print("{:{}}Skip R{} (refractoriness)\n", "", depth * 2, r.id);
      continue;
    }
    tried.insert(k);

    if (verbose) {
      std::print("{:{}}Coba R{} untuk mencapai {}:\n", "", depth * 2, r.id,
                 sym_name(goal));
      std::print("{:{}}Premis: {}\n", "", (depth + 1) * 2, sym_name(r.if1Sym));
      if (r.if2Sym) {
        std::print("{:{}}Premis 2: {} (operator {})\n", "", (depth + 1) * 2,
                   sym_name(*r.if2Sym),
                   (r.logic && *r.logic == Logic::AND) ? "AND" : "OR");
      }
    }

    bool ok = false;
    if (!r.if2Sym) {
      ok = prove_dfs(r.if1Sym, proof_ids, on_path, depth + 1);
      if (verbose)
        std::print("{:{}}Hasil premis: {}\n", "", (depth + 1) * 2,
                   ok ? "OK" : "FAIL");
    } else if (r.logic && *r.logic == Logic::AND) {
      bool a = prove_dfs(r.if1Sym, proof_ids, on_path, depth + 1);
      bool b = prove_dfs(*r.if2Sym, proof_ids, on_path, depth + 1);
      ok = a && b;
      if (verbose)
        std::print("{:{}}Hasil AND: {} & {} => {}\n", "", (depth + 1) * 2,
                   a ? "OK" : "FAIL", b ? "OK" : "FAIL", ok ? "OK" : "FAIL");
    } else { // OR
      std::vector<int> snapshot = proof_ids;
      bool a = prove_dfs(r.if1Sym, proof_ids, on_path, depth + 1);
      if (a) {
        ok = true;
        if (verbose)
          std::print("{:{}}Hasil OR: premis1 OK => OK\n", "", (depth + 1) * 2);
      } else {
        proof_ids = snapshot;
        bool b = prove_dfs(*r.if2Sym, proof_ids, on_path, depth + 1);
        ok = b;
        if (verbose)
          std::print("{:{}}Hasil OR: premis1 FAIL, premis2 {} => {}\n", "",
                     (depth + 1) * 2, b ? "OK" : "FAIL", ok ? "OK" : "FAIL");
      }
    }

    if (ok) {
      proof_ids.push_back(r.id);
      on_path.erase(goal);
      memo_ok.insert(goal);
      if (verbose)
        std::print("{:{}}Berhasil: goal {} dicapai via R{}\n", "", depth * 2,
                   sym_name(goal), r.id);
      return true;
    } else {
      if (verbose)
        std::print("{:{}}Gagal: R{} tidak mencukupi untuk {}\n", "", depth * 2,
                   r.id, sym_name(goal));
    }
  }

  on_path.erase(goal);
  memo_fail.insert(goal);
  if (verbose)
    std::print("{:{}}Semua kandidat gagal untuk {}\n", "", depth * 2,
               sym_name(goal));
  return false;
}

const char *BCMobil::sym_name(Sym s) {
  switch (s) {
  case Sym::MESIN_MATI_TOTAL:
    return "Mesin Mati Total";
  case Sym::MESIN_BERPUTAR_LAMBAT:
    return "Mesin Berputar Lambat";
  case Sym::LAMPU_REDUP:
    return "Lampu Redup";
  case Sym::AKI_LEMAH:
    return "Aki Lemah";
  case Sym::TIDAK_ADA_KARAT_PADA_TERMINAL:
    return "Tidak Ada Karat pada Terminal";
  case Sym::SUARA_KLIK_SAAT_START:
    return "Suara Klik saat Start";
  case Sym::TIDAK_ADA_SUARA:
    return "Tidak Ada Suara";
  case Sym::CEK_KELISTRIKAN:
    return "Cek Kelistrikan";
  case Sym::TERJADI_KONSLETING:
    return "Terjadi Konsleting";
  case Sym::ISOLASI_KELISTRIKAN:
    return "Isolasi Kelistrikan";
  case Sym::MESIN_SULIT_START:
    return "Mesin Sulit Start";
  case Sym::FUNGSI_KELISTRIKAN_TERPUTUS:
    return "Fungsi Kelistrikan Terputus";
  case Sym::GANTI_AKI:
    return "Ganti Aki";
  }
  return "?";
}

const char *BCMobil::logic_name(Logic l) {
  switch (l) {
  case Logic::AND:
    return "AND";
  case Logic::OR:
    return "OR";
  }
  return "?";
}
