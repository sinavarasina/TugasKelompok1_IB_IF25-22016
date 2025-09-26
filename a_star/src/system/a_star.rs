use std::collections::{HashMap, HashSet};

use crate::component::state::State;

macro_rules! log_if {
    ($enabled:expr, $($arg:tt)*) => {
        if $enabled { println!($($arg)*); }
    };
}

fn calculate_fn(g: i32, h: i32) -> i32 {
    g + h
}

fn expand_neighbors(graph: &HashMap<String, Vec<(String, i32)>>, city: &str) -> Vec<(String, i32)> {
    graph.get(city).cloned().unwrap_or_default()
}

fn reconstruct_path(states: &HashMap<String, State>, goal: &str) -> Vec<String> {
    let mut path = vec![goal.to_string()];
    let mut cur = goal.to_string();
    while let Some(state) = states.get(&cur) {
        if let Some(parent) = &state.parent {
            path.push(parent.clone());
            cur = parent.clone();
        } else {
            break;
        }
    }
    path.reverse();
    path
}

fn get_h(h_n: &HashMap<String, i32>, city: &str, debug: bool) -> i32 {
    match h_n.get(city) {
        Some(&h) => h,
        None => {
            log_if!(debug, "Heuristic not found for {}", city);
            0
        }
    }
}

fn print_open_closed_node(open_set: &HashSet<String>, closed_set: &HashSet<String>, debug: bool) {
    if !debug {
        return;
    }
    let mut o: Vec<_> = open_set.iter().cloned().collect();
    let mut c: Vec<_> = closed_set.iter().cloned().collect();
    o.sort();
    c.sort();
    println!("Open  : {}", o.join(", "));
    println!("Closed: {}", c.join(", "));
}

fn pick_lowest_f(
    open_set: &HashSet<String>,
    states: &HashMap<String, State>,
    h_n: &HashMap<String, i32>,
) -> Option<String> {
    open_set
        .iter()
        .filter_map(|c| {
            states.get(c).map(|s| {
                let h = get_h(h_n, c, false);
                let f = calculate_fn(s.g, h);
                (f, s.g, c.clone())
            })
        })
        .min_by(|a, b| a.cmp(b))
        .map(|(_, _, c)| c)
}

fn traverse_node(
    current_city: &str,
    current_g: i32,
    graph: &HashMap<String, Vec<(String, i32)>>,
    states: &mut HashMap<String, State>,
    open_set: &mut HashSet<String>,
    closed_set: &HashSet<String>,
    debug: bool,
) {
    log_if!(debug, "Expand from {}:", current_city);
    for (neighbor, step_cost) in expand_neighbors(graph, current_city) {
        if closed_set.contains(&neighbor) {
            log_if!(debug, "{} ignored (already in Closed)", neighbor);
            continue;
        }

        let new_g = current_g + step_cost;

        match states.get(&neighbor) {
            Some(prev) if new_g < prev.g => {
                log_if!(
                    debug,
                    "{}: g updated {} -> {} (via {})",
                    neighbor,
                    prev.g,
                    new_g,
                    current_city
                );
                states.insert(
                    neighbor.clone(),
                    State {
                        g: new_g,
                        parent: Some(current_city.to_string()),
                    },
                );
                let _ = open_set.insert(neighbor.clone());
            }
            Some(prev) => {
                log_if!(
                    debug,
                    "{}: previous g {} (via {}) is better, ignore g candidate {} (via {})",
                    neighbor,
                    prev.g,
                    prev.parent.as_deref().unwrap_or("START"),
                    new_g,
                    current_city
                );
            }
            None => {
                log_if!(debug, "{} first arrival, g={}", neighbor, new_g);
                states.insert(
                    neighbor.clone(),
                    State {
                        g: new_g,
                        parent: Some(current_city.to_string()),
                    },
                );
                let _ = open_set.insert(neighbor.clone());
            }
        }
    }
}

pub fn a_star(
    graph: &HashMap<String, Vec<(String, i32)>>,
    h_n: &HashMap<String, i32>,
    start: &str,
    goal: &str,
    debug: bool,
) -> Option<(Vec<String>, i32)> {
    log_if!(debug, "A* Search Algorithm");
    log_if!(debug, "Initial State: {}", start);
    log_if!(debug, "Goal State   : {}", goal);

    let mut open_set: HashSet<String> = HashSet::new();
    let mut closed_set: HashSet<String> = HashSet::new();
    let mut states: HashMap<String, State> = HashMap::new();

    states.insert(start.to_string(), State { g: 0, parent: None });
    open_set.insert(start.to_string());

    let mut step = 0usize;

    while !open_set.is_empty() {
        step += 1;
        log_if!(debug, "\nStep {}", step);
        print_open_closed_node(&open_set, &closed_set, debug);

        let Some(current) = pick_lowest_f(&open_set, &states, h_n) else {
            log_if!(debug, "No open candidates. Stopping.");
            break;
        };

        let current_g = states[&current].g;
        let h = get_h(h_n, &current, debug);
        let f = calculate_fn(current_g, h);
        log_if!(
            debug,
            "Select {} (g={}, h={}, f={})",
            current,
            current_g,
            h,
            f
        );

        if current == goal {
            let path = reconstruct_path(&states, goal);
            let total_cost = states[goal].g;

            log_if!(debug, "Goal reached\t: {}", goal);
            log_if!(debug, "Path\t\t: {}", path.join(" -> "));
            log_if!(debug, "Cost\t\t: {}", total_cost);
            log_if!(debug, "Expanded\t: {}", closed_set.len());
            log_if!(debug, "Steps\t\t: {}", step);
            log_if!(debug, "Path Lenght\t: {}", path.len());

            return Some((path, total_cost));
        }

        open_set.remove(&current);
        closed_set.insert(current.clone());

        traverse_node(
            &current,
            current_g,
            graph,
            &mut states,
            &mut open_set,
            &closed_set,
            debug,
        );
    }

    log_if!(debug, "No path from {} to {}", start, goal);
    None
}
