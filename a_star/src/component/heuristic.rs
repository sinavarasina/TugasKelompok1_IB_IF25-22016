use serde::Deserialize;

#[derive(Debug, Deserialize)]
pub struct Heuristic {
    #[serde(rename = "Kota Asal")]
    pub origin: String,
    #[serde(rename = "Heuristik ke Banyuwangi")]
    pub heuristic_value: i32,
}
