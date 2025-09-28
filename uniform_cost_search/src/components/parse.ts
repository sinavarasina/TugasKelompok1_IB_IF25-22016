import { parse } from "@std/csv";

export async function Parse() {
  const csvPeta = await Deno.readTextFile(
    new URL("../../../data/Tugas Kelompok 1 - Peta Cilegon ke Banyuwangi.csv", import.meta.url),
  );

  const data = parse(csvPeta, {
    skipFirstRow: true,
    strip: true,
    separator: ";",
  });

  return data;
}
