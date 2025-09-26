use csv::ReaderBuilder;
use std::collections::HashMap;

use crate::component::{distances::Distances, heuristic::Heuristic};

pub fn load_data(
    map_csv: &'static str,
    heuristic_csv: &'static str,
) -> (HashMap<String, Vec<(String, i32)>>, HashMap<String, i32>) {
    let mut graph: HashMap<String, Vec<(String, i32)>> = HashMap::new();
    let mut heuristic: HashMap<String, i32> = HashMap::new();

    let mut reader = ReaderBuilder::new()
        .delimiter(b';')
        .from_reader(map_csv.as_bytes());

    for result in reader.deserialize() {
        let edge: Distances = result.expect("invalid edges");
        graph
            .entry(edge.origin.clone())
            .or_default()
            .push((edge.destination.clone(), edge.cost));
    }

    let mut reader = ReaderBuilder::new()
        .delimiter(b';')
        .from_reader(heuristic_csv.as_bytes());

    for result in reader.deserialize() {
        let h: Heuristic = result.expect("invalid heuristic");
        heuristic.insert(h.origin, h.heuristic_value);
    }

    (graph, heuristic)
}
