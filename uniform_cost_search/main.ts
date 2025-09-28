import { parse } from "@std/csv";

function sleep(ms: number) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

const csvPeta = await Deno.readTextFile(
  "../data/Tugas Kelompok 1 - Peta Cilegon ke Banyuwangi.csv",
);

const data = parse(csvPeta, {
  skipFirstRow: true,
  strip: true,
  separator: ";",
});

let kotaAsal = data[0]["Kota Asal"];
const loop = true;
let total = 0;

async function main() {
  while (loop) {
    const index = data.findIndex((row) => row["Kota Asal"] === kotaAsal);
    // console.log("Index kota asal: ", index);
    console.log("Kota asal: ", data[index]["Kota Asal"]);

    const rows = data.filter((row) => row["Kota Asal"] === kotaAsal);
    console.log("Banyak Kota Tujuan: ", rows.length);

    for (let i = 0; i < rows.length; i++) {
      console.log(
        "Kota tujuan: ",
        rows[i]["Kota Tujuan"],
        "Jarak Jalan: ",
        rows[i]["Jarak Jalan"],
      );

      const jarak = Number(rows[i]["Jarak Jalan"]); // pastikan jadi number
      if (i === 0 || jarak < total) {
        total = jarak + total;
        console.log(total);
        kotaAsal = rows[i]["Kota Tujuan"]; // pindah ke kota tujuan dengan jarak terkecil
      }
    }

    console.log("");
    await sleep(1000);
  }
}

main();
