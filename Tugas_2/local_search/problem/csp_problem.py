import random


class CSPProblem:
    def __init__(self):
        self.variables = ["Ani", "Budi", "Citra", "Dedi", "Eka"]
        self.domains = ["K1", "K2"]

    def random_state(self):
        return {v: random.choice(self.domains) for v in self.variables}

    def evaluate(self, state):
        score = 0

        # Constraint 1: Ani ≠ Budi
        if state["Ani"] != state["Budi"]:
            score += 1

        # Constraint 2: Citra = Dedi
        if state["Citra"] == state["Dedi"]:
            score += 1

        # Constraint 3: Eka tidak sendirian
        same_group = [p for p in self.variables if state[p] == state["Eka"]]
        if len(same_group) >= 2:
            score += 1

        # Constraint 4: Tiap kelompok minimal 2 orang
        k1 = [p for p in self.variables if state[p] == "K1"]
        k2 = [p for p in self.variables if state[p] == "K2"]
        if len(k1) >= 2 and len(k2) >= 2:
            score += 1

        return score

    def get_neighbors(self, state):
        neighbors = []
        for v in self.variables:
            new_state = state.copy()
            new_state[v] = "K1" if state[v] == "K2" else "K2"
            neighbors.append(new_state)
        return neighbors
