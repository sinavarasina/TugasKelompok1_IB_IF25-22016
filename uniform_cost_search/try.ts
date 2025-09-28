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

// >>> ditambahkan: buat graph adjacency list
const graph: Record<string, { tujuan: string; jarak: number }[]> = {};
for (const row of data) {
  const asal = row["Kota Asal"];
  const tujuan = row["Kota Tujuan"];
  const jarak = Number(row["Jarak Jalan"]);
  if (!graph[asal]) graph[asal] = [];
  if (!graph[tujuan]) graph[tujuan] = []; // undirected
  graph[asal].push({ tujuan, jarak });
  graph[tujuan].push({ tujuan: asal, jarak });
}

// >>> ditambahkan: struktur UCS
type Node = { kota: string; cost: number; path: string[] };
let frontier: Node[] = [{ kota: "Cilegon", cost: 0, path: ["Cilegon"] }];
let visited: Record<string, number> = {}; // biaya minimum

const goal = "Banyuwangi"; // bisa diganti tujuan lain

async function main() {
  while (frontier.length > 0) {
    // >>> UCS: ambil node dengan cost terkecil
    frontier.sort((a, b) => a.cost - b.cost); // sederhana, bisa diganti priority queue
    const current = frontier.shift()!;

    console.log("Kota asal:", current.kota, "Total cost:", current.cost);

    if (current.kota === goal) {
      console.log("Sampai di goal:", goal);
      console.log("Jalur:", current.path.join(" -> "));
      console.log("Total jarak:", current.cost);
      break; // selesai
    }

    // skip jika sudah ada cost lebih kecil sebelumnya
    if (visited[current.kota] !== undefined && visited[current.kota] <= current.cost) {
      continue;
    }
    visited[current.kota] = current.cost;

    for (const tetangga of graph[current.kota]) {
      const newCost = current.cost + tetangga.jarak;
      frontier.push({
        kota: tetangga.tujuan,
        cost: newCost,
        path: [...current.path, tetangga.tujuan],
      });
    }

    console.log("");
    await sleep(500);
  }
}

main();
