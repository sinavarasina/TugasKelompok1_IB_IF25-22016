from problem.csp_problem import CSPProblem

RESET = "\033[0m"
BOLD = "\033[1m"
RED = "\033[91m"
GREEN = "\033[92m"
YELLOW = "\033[93m"
BLUE = "\033[94m"
CYAN = "\033[96m"


class HillClimbing:
    def __init__(self, problem: CSPProblem, max_iter=1000, verbose=False):
        self.problem = problem
        self.max_iter = max_iter
        self.verbose = verbose

    def search(self):
        current = self.problem.random_state()
        current_score = self.problem.evaluate(current)

        if self.verbose:
            print(f"{CYAN}{BOLD}Initial state:{RESET} {
                  current} | {BLUE}Score: {current_score}{RESET}")

        for step in range(1, self.max_iter + 1):
            neighbors = self.problem.get_neighbors(current)
            scored_neighbors = [(self.problem.evaluate(n), n)
                                for n in neighbors]
            best_score, best_neighbor = max(
                scored_neighbors, key=lambda x: x[0])

            if self.verbose:
                color = GREEN if best_score > current_score else YELLOW
                print(f"[{CYAN}Step {step}{RESET}] {BLUE}Current:{RESET} {current_score} → "
                      f"{color}{best_score}{RESET} | {BLUE}Best:{RESET} {best_neighbor}")

            if best_score <= current_score:
                if self.verbose:
                    print(f"{YELLOW}No improvement at step {
                          step}, stopping.{RESET}")
                break

            current, current_score = best_neighbor, best_score

            if current_score == 4:
                if self.verbose:
                    print(f"{GREEN}All constraints satisfied at step {
                          step}!{RESET}")
                break

        print(f"{BOLD}{GREEN}Hill Climbing finished with score {
              current_score}{RESET}")
        return current, current_score
