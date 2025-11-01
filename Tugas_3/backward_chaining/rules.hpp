#pragma once
#include <optional>
#include <unordered_set>
#include <vector>

using u64 = unsigned long long;
using u32 = unsigned int;

enum class Sym : int {
  MESIN_MATI_TOTAL,
  MESIN_BERPUTAR_LAMBAT,
  LAMPU_REDUP,
  AKI_LEMAH,
  TIDAK_ADA_KARAT_PADA_TERMINAL,
  SUARA_KLIK_SAAT_START,
  TIDAK_ADA_SUARA,
  CEK_KELISTRIKAN,
  TERJADI_KONSLETING,
  ISOLASI_KELISTRIKAN,
  MESIN_SULIT_START,
  FUNGSI_KELISTRIKAN_TERPUTUS,
  GANTI_AKI,
};

enum class Logic : int { AND, OR };
enum class Priority : int { RENDAH, SEDANG, TINGGI };

struct Rule {
  int id;
  Sym thenSym;
  Sym if1Sym;
  std::optional<Sym> if2Sym;
  std::optional<Logic> logic;
  Priority prio;
};

class BCMobil {
public:
  void add_rule(int id, Sym thenSym, Sym if1Sym, std::optional<Sym> if2Sym,
                std::optional<Logic> logic, Priority prio);
  void add_rule(int id, Sym thenSym, Sym if1Sym, Priority prio);

  void add_fact(Sym s) { facts.insert(s); }
  void clear_facts() { facts.clear(); }

  bool prove(Sym goal, std::vector<int> &proof_ids);

  static const char *sym_name(Sym s);
  static const char *logic_name(Logic l);

  void set_verbose(bool v) { verbose = v; }

private:
  std::vector<Rule> rules;
  std::unordered_set<Sym> facts;

  std::unordered_set<Sym> memo_ok, memo_fail;
  std::unordered_set<u64> tried;
  bool verbose = false;

  bool prove_dfs(Sym goal, std::vector<int> &proof_ids,
                 std::unordered_set<Sym> &on_path, int depth);

  static u64 key(Sym g, int rid);

  static int specificity(const Rule &r);
  static int priority_rank(const Rule &r);
};
