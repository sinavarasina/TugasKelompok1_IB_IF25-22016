import random
import math
from problem.csp_problem import CSPProblem

RESET = "\033[0m"
BOLD = "\033[1m"
RED = "\033[91m"
GREEN = "\033[92m"
YELLOW = "\033[93m"
BLUE = "\033[94m"
CYAN = "\033[96m"


class SimulatedAnnealing:
    def __init__(self, problem: CSPProblem, max_iter=1000, initial_temp=100.0, cooling_rate=0.95, verbose=False):
        self.problem = problem
        self.max_iter = max_iter
        self.initial_temp = initial_temp
        self.cooling_rate = cooling_rate
        self.verbose = verbose

    def search(self):
        current = self.problem.random_state()
        current_score = self.problem.evaluate(current)
        temperature = self.initial_temp

        if self.verbose:
            print(f"{CYAN}{BOLD}Initial state:{RESET} {
                  current} | {BLUE}Score: {current_score}{RESET}")

        for step in range(1, self.max_iter + 1):
            if temperature <= 0.01:
                if self.verbose:
                    print(f"{YELLOW}Temperature too low, stopping at step {
                          step}.{RESET}")
                break

            neighbor = random.choice(self.problem.get_neighbors(current))
            neighbor_score = self.problem.evaluate(neighbor)
            delta = neighbor_score - current_score

            accepted = False
            if delta > 0:
                current, current_score = neighbor, neighbor_score
                accepted = True
            else:
                prob = math.exp(delta / temperature)
                if random.random() < prob:
                    current, current_score = neighbor, neighbor_score
                    accepted = True

            if self.verbose:
                color = GREEN if accepted else RED
                print(f"[{CYAN}Step {step}{RESET}] Temp: {BLUE}{temperature:.2f}{RESET} | "
                      f"Δ: {YELLOW}{delta:+}{RESET} | "
                      f"Status: {color}{
                          'ACCEPTED' if accepted else 'REJECTED'}{RESET} | "
                      f"Score: {BLUE}{current_score}{RESET}")

            temperature *= self.cooling_rate

            if current_score == 4:
                if self.verbose:
                    print(f"{GREEN}All constraints satisfied at step {
                          step}!{RESET}")
                break

        print(f"{BOLD}{GREEN}Simulated Annealing finished with score {
              current_score}{RESET}")
        return current, current_score
