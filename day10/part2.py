from ortools.linear_solver import pywraplp

with open("input.txt", "r") as f:
    lines = f.readlines()

button_presses = 0

for line in lines:
    words = line.strip().split()
    targets = [int(t) for t in words[-1][1:-1].split(",")]

    buttons = []
    for button in words[1:-1]:
        buttons.append([int(l) for l in button[1:-1].split(",")])

    solver = pywraplp.Solver(
        "Minimise button presses", pywraplp.Solver.CBC_MIXED_INTEGER_PROGRAMMING
    )

    vars = []
    upper_bound = max(targets)
    for b in range(len(buttons)):
        v = solver.IntVar(0, upper_bound, f"button {b}")
        vars.append(v)

    # constraints (system of linear equations)
    for l, t in enumerate(targets):
        solver.Add(
            solver.Sum([(l in buttons[b]) * vars[b] for b in range(len(buttons))]) == t
        )

    # goal: minimise total button press
    solver.Minimize(solver.Sum(vars))

    status = solver.Solve()
    assert status == pywraplp.Solver.OPTIMAL
    button_presses += int(solver.Objective().Value())

print(button_presses)
