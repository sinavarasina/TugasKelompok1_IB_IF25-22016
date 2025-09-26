use crate::system::deserialize_csv::load_data;

mod component;
mod system;

fn main() {
    const MAP_CSV: &str =
        include_str!("../../data/Tugas Kelompok 1 - Peta Cilegon ke Banyuwangi.csv");
    const HEURISTIC_CSV: &str =
        include_str!("../../data/Tugas Kelompok 1 - Heuristik ke Banyuwangi.csv");

    let (graph, h_n) = load_data(MAP_CSV, HEURISTIC_CSV);
}
