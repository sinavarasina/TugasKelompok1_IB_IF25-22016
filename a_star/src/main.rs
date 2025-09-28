use crate::system::{a_star, deserialize_csv};

mod component;
mod system;

fn main() {
    const INITIAL_STATE: &str = "Cilegon";
    const GOAL_STATE: &str = "Banyuwangi";
    const DEBUG: bool = true;
    const MAP_CSV: &str =
        include_str!("../../data/Tugas Kelompok 1 - Peta Cilegon ke Banyuwangi.csv");
    const HEURISTIC_CSV: &str =
        include_str!("../../data/Tugas Kelompok 1 - Heuristik ke Banyuwangi - FIX.csv");

    let (graph, h_n) = deserialize_csv::load_data(MAP_CSV, HEURISTIC_CSV);

    let _ = a_star::a_star(&graph, &h_n, INITIAL_STATE, GOAL_STATE, DEBUG);
}
