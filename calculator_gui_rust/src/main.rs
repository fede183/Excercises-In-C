use eframe::{egui, epi};

struct MyApp {
    formula: String,
    error: String,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            formula: "".to_owned(),
            error: "".to_owned(),
        }
    }
}

impl epi::App for MyApp {
    fn name(&self) -> &str {
        "My egui Calulator"
    }

    fn update(&mut self, ctx: &egui::CtxRef, frame: &mut epi::Frame<'_>) {
        let Self { formula, error } = self;

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Welcome to my egui calculator");
            ui.horizontal(|ui| {
                ui.text_edit_singleline(formula);
            });

            let rows = [["1", "2", "3", "+"], ["4", "5", "6", "-"], ["7", "8", "9", "*"], ["", "0", "", "/"]];

            for row in rows {
                ui.horizontal(|ui| {
                    for row_item in row {
                        if row_item != "" && ui.button(row_item).clicked() {
                            *formula += row_item;
                        }
                    }
                });
            }

            ui.horizontal(|ui| {
                if ui.button("=").clicked() {
                    let resolved_formula : Result<f32, f32> = solve_math(&*formula);
                    if resolved_formula.is_ok() {

                        *formula = resolved_formula.unwrap().to_string();
                    }
                    if resolved_formula.is_err() {
                        *error = String::from("Formula inválida");
                        *formula = String::from("");
                    }
                }
            });
      
        });

        // Resize the native window to be just the size we need it to be:
        frame.set_window_size(ctx.used_size());
    }
}

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

fn solve_math(formula : &String) -> Result<f32, f32> {
    
    if !have_operators(formula) && !is_numeric(formula) {
        return Err(0.0);
    }

    if is_numeric(formula) {
        let number_formula : f32 = formula.parse().unwrap();
        return Ok(number_formula);
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

fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native(Box::new(MyApp::default()), options);
}