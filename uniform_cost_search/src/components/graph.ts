import { Parse } from "./parse.ts";

export async function Graph() {
  const data = await Parse();
  const graph: Record<string, { tujuan: string; jarak: number }[]> = {};

  for (const row of data) {
    const asal = row["Kota Asal"];
    const tujuan = row["Kota Tujuan"];
    const jarak = Number(row["Jarak Jalan"]);
    if (!graph[asal]) graph[asal] = [];
    if (!graph[tujuan]) graph[tujuan] = [];
    graph[asal].push({ tujuan, jarak });
    graph[tujuan].push({ tujuan: asal, jarak });
  }
  return graph;
}
