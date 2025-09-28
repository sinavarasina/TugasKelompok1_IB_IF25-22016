import { Graph } from "./components/graph.ts";

function sleep(ms: number) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

// Parse data dan ambil graph
const graph = await Graph();

// Deklarasi array frontier dan visited
type Node = { kota: string; cost: number; path: string[] };
const frontier: Node[] = [{ kota: "Cilegon", cost: 0, path: ["Cilegon"] }];
const visited: Record<string, number> = {};

// Daerah tujuan
const goal = "Banyuwangi";

// Main function
async function main() {
  while (frontier.length > 0) {
    frontier.sort((a, b) => a.cost - b.cost);
    const current = frontier.shift()!;

    //console.log("Kota asal:", current.kota, "Total cost:", current.cost);
    console.log("Jalur:", current.path.join(" -> "));
    console.log("Total jarak:", current.cost);

    if (current.kota === goal) {
      console.log("");
      console.log("Sampai di goal:", goal);
      console.log("Jalur:", current.path.join(" -> "));
      console.log("Total jarak:", current.cost);
      break; // selesai
    }

    //Skip jika sudah ada cost lebih kecil sebelumnya
    if (
      visited[current.kota] !== undefined &&
      visited[current.kota] <= current.cost
    ) {
      console.log("Skip!");
      console.log("");
      await sleep(1000);
      continue;
    }
    visited[current.kota] = current.cost;

    //Ambil seluruh tetangga dari kota sekarang dan masukan ke frontier
    for (const tetangga of graph[current.kota]) {
      const newCost = current.cost + tetangga.jarak;
      frontier.push({
        kota: tetangga.tujuan,
        cost: newCost,
        path: [...current.path, tetangga.tujuan],
      });
    }

    console.log("");
    await sleep(1000);
  }
}

main();
