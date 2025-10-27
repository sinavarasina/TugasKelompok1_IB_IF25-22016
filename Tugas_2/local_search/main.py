import argparse
from problem.csp_problem import CSPProblem
from hill_climb.hill_climb import HillClimbing
from simulated_annealing.simulated_annealing import SimulatedAnnealing

# ANSI colors
RESET = "\033[0m"
BOLD = "\033[1m"
GREEN = "\033[92m"
CYAN = "\033[96m"


def main():
    parser = argparse.ArgumentParser(
        description="Local Search CSP: Hill Climbing & Simulated Annealing")
    parser.add_argument(
        "algo",
        choices=["hill", "anneal", "both"],
        help="hill (Hill Climbing), anneal (Simulated Annealing), or both"
    )
    parser.add_argument("--verbose", action="store_true",
                        help="show the every step of algorithm")

    args = parser.parse_args()

    problem = CSPProblem()

    if args.algo in ("hill", "both"):
        print(f"{BOLD}{CYAN}=== Hill Climbing ==={RESET}")
        hc = HillClimbing(problem, verbose=args.verbose)
        hc_result, hc_score = hc.search()
        print(f"{GREEN}Final Solution:{RESET} {hc_result} | {
              GREEN}Score:{RESET} {hc_score}\n")

    if args.algo in ("anneal", "both"):
        print(f"{BOLD}{CYAN}=== Simulated Annealing ==={RESET}")
        sa = SimulatedAnnealing(problem, verbose=args.verbose)
        sa_result, sa_score = sa.search()
        print(f"{GREEN}Final Solution:{RESET} {
              sa_result} | {GREEN}Score:{RESET} {sa_score}")


if __name__ == "__main__":
    main()
