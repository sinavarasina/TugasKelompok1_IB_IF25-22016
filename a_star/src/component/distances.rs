use serde::Deserialize;

#[derive(Debug, Deserialize)]
pub struct Distances {
    #[serde(rename = "Kota Asal")]
    pub origin: String,
    #[serde(rename = "Kota Tujuan")]
    pub destination: String,
    #[serde(rename = "Jarak Jalan")]
    pub cost: i32,
}
