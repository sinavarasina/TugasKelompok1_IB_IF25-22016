import global_data as gd

# Constraint antar variabel
constraints_graph = {
    "Ani": ["Budi"],
    "Budi": ["Ani"],
    "Citra": ["Dedi"],
    "Dedi": ["Citra"],
    "Eka": []
}

def is_consistent(var, value):
    if var == "Ani" and "Budi" in gd.assignment:
        if gd.assignment["Budi"] == value:
            return False
    if var == "Budi" and "Ani" in gd.assignment:
        if gd.assignment["Ani"] == value:
            return False

    if var == "Citra" and "Dedi" in gd.assignment:
        if gd.assignment["Dedi"] != value:
            return False
    if var == "Dedi" and "Citra" in gd.assignment:
        if gd.assignment["Citra"] != value:
            return False

    return True

def is_complete_valid():
    if len(gd.assignment) != len(gd.variables):
        return False

    kelas = [[], []]
    for student, class_num in gd.assignment.items():
        kelas[class_num].append(student)

    for i in range(2):
        if "Eka" in kelas[i] and len(kelas[i]) == 1:
            return False

    for i in range(2):
        if len(kelas[i]) > 0 and len(kelas[i]) < 2:
            return False

    return True

def get_legal_values(var):
    legal = []
    for value in gd.domains[var]:
        if is_consistent(var, value):
            legal.append(value)
    return legal


def forward_check(var, value, domains_copy):
    for neighbor in constraints_graph[var]:
        if neighbor not in gd.assignment:
            for neighbor_value in list(domains_copy[neighbor]):
                if not is_consistent(neighbor, neighbor_value):
                    domains_copy[neighbor].remove(neighbor_value)
            if len(domains_copy[neighbor]) == 0:
                return False
    return True

def select_unassigned_variable():
    for v in gd.variables:
        if v not in gd.assignment:
            return v
    return None

def backtrack(domains):
    gd.steps += 1

    if len(gd.assignment) == len(gd.variables):
        return is_complete_valid()

    print(f"\nStep {gd.steps}:")
    print(f"Current assignment: {gd.assignment}")

    var = select_unassigned_variable()
    if var is None:
        return is_complete_valid()

    for value in get_legal_values(var):
        print(f"Trying {var} = Class {value}")

        if is_consistent(var, value):
            gd.assignment[var] = value

            new_domains = {v: list(domains[v]) for v in domains}

            if forward_check(var, value, new_domains):
                result = backtrack(new_domains)
                if result:
                    return True

            print(f"Backtracking from {var} = Class {value}")
            gd.backtrack_count += 1
            del gd.assignment[var]

    return False

def solve():
    domains_copy = {v: list(gd.domains[v]) for v in gd.variables}
    result = backtrack(domains_copy)

    if result:
        print("\nSolusi ditemukan:\n")
        kelas = [[], []]
        for student, class_num in gd.assignment.items():
            kelas[class_num].append(student)

        print(f"Class 0: {kelas[0]} ({len(kelas[0])} members)")
        print(f"Class 1: {kelas[1]} ({len(kelas[1])} members)")
    else:
        print("\nTidak ada solusi!")

    return result

def Forward_Checking():
    gd.assignment = {}
    gd.backtrack_count = 0
    gd.steps = 0
    solve()
