use serde::Deserialize;

#[derive(Debug, Deserialize)]
struct Heuristic {
    origin: String,
    heuristic_value: i32,
}
