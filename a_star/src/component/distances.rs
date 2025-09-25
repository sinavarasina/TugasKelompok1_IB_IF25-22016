use serde::Deserialize;

#[derive(Debug, Deserialize)]
struct Distances {
    #[serde(rename = "Kota Asal")]
    origin: String,
    #[serde(rename = "Kota Tujuan")]
    destination: String,
    #[serde(rename = "Jarak Jalan")]
    distances: i32,
}
