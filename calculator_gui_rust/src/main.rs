use eframe::{egui, epi};
mod math;

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

            let rows = [["1", "2", "3", "+"], ["4", "5", "6", "-"], ["7", "8", "9", "*"], ["(", "0", ")", "/"]];

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
                    let resolved_formula : Result<f32, f32> = math::solve_math(&*formula);
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


fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native(Box::new(MyApp::default()), options);
}