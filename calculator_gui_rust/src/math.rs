
fn is_numeric(possible_number : &String) -> bool {
    let test = possible_number.parse::<f64>();
    match test {
        Ok(_ok) => true,
        Err(_e) => false, 
    }  
}

fn have_operators(formula : &String) -> bool {
    let operators = String::from("+-*/");
    
    for operator in operators.chars() {
        if formula.contains(operator) {
            return true;
        }
    }

    return false;
}

pub fn solve_math(formula : &String) -> Result<f32, f32> {
    let formula_trim = String::from(formula.trim());
    return solve_math_formula(&formula_trim);
}

fn solve_math_formula(formula : &String) -> Result<f32, f32> {
    if !have_operators(formula) && !is_numeric(formula) {
        return Err(0.0);
    }

    if is_numeric(formula) {
        let number_formula : f32 = formula.parse().unwrap();
        return Ok(number_formula);
    }

    if formula.contains("(") {
        let positions_of_open_brackets : Vec<_> = formula.match_indices("(").collect();
        let positions_of_close_brackets : Vec<_> = formula.match_indices(")").collect();

        let position_open = positions_of_open_brackets[0].0;
        
        for position in positions_of_close_brackets {
            let position_close = position.0;
            let sub_formula = &formula[position_open+1..position_close];
            let sub_formula_open_brackets_count = sub_formula.matches("(").count();
            let sub_formula_close_brackets_count = sub_formula.matches(")").count();

            if sub_formula_open_brackets_count == sub_formula_close_brackets_count {
                let solved_sub_formula = solve_math_formula(&String::from(sub_formula));
                let solved_sub_formula = &solved_sub_formula.unwrap().to_string();
                
                let mut new_formula = formula.clone(); 
                
                new_formula.replace_range(position_open..position_close+1, solved_sub_formula);

                return solve_math_formula(&new_formula);
            } else {
                return Err(0.0);
            }
        }

    }


    let possible_operators = String::from("*/+-");

       
    for operator in possible_operators.chars() {
        if formula.contains(operator) {
            let formula_parts : Vec<&str> = formula.split(operator).collect();

            let solved_formula_1 : Result<f32, f32> = solve_math(&String::from(formula_parts[0]));
            let solved_formula_2 : Result<f32, f32> = solve_math(&String::from(formula_parts[1]));

            if solved_formula_1.is_err() || solved_formula_2.is_err()  {
                return Err(0.0);
            }

            let solved_formula_1 : f32 = solved_formula_1.unwrap();
            let solved_formula_2 : f32 = solved_formula_2.unwrap();
    
            return match operator {
                '+' => Ok(solved_formula_1 + solved_formula_2),
                '-' => Ok(solved_formula_1 - solved_formula_2),
                '*' => Ok(solved_formula_1 * solved_formula_2),
                '/' => Ok(solved_formula_1 / solved_formula_2),
                _ => Err(0.0),
            };
        }
    }

    return Err(0.0);
}

#[cfg(test)]
mod tests {
    use super::*;

    fn unwrap_solve_math(formula: &String) -> f32 {
        return solve_math(formula).unwrap();
    }

    #[test]
    fn test_single_number() {
        assert_eq!(unwrap_solve_math(&String::from("3")), 3.0);
    }

    #[test]
    fn test_single_sum() {
        assert_eq!(unwrap_solve_math(&String::from("3 + 4")), 7.0);
    }

    #[test]
    fn test_single_rest() {
        assert_eq!(unwrap_solve_math(&String::from("3 - 4")), -1.0);
    }

    #[test]
    fn test_single_production() {
        assert_eq!(unwrap_solve_math(&String::from("3 * 4")), 12.0);
    }

    #[test]
    fn test_single_divition() {
        assert_eq!(unwrap_solve_math(&String::from("4 / 2")), 2.0);
    }

    #[test]
    fn test_single_bracket_sum() {
        assert_eq!(unwrap_solve_math(&String::from("(3 + 4)")), 7.0);
    }

    #[test]
    fn test_single_bracket_rest() {
        assert_eq!(unwrap_solve_math(&String::from("(3 - 4)")), -1.0);
    }

    #[test]
    fn test_single_bracket_production() {
        assert_eq!(unwrap_solve_math(&String::from("(3 * 4)")), 12.0);
    }

    #[test]
    fn test_single_bracket_divition() {
        assert_eq!(unwrap_solve_math(&String::from("(4 / 2)")), 2.0);
    }
}