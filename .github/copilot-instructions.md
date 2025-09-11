# Copilot Instructions for Seminar-finalProject

## Project Overview
- This is a C-based command-line application for managing seminar information.
- Main logic is in `project.c`. Data is stored in CSV files (`Table.csv`, `people.csv`).
- The program provides a menu for adding, searching, updating, and deleting seminar records.

## Key Files
- `project.c`: Main application logic, menu, and all user interaction.
- `Table.csv`: Stores seminar records in CSV format.
- `people.csv`: (Purpose unclear, likely for participant or speaker data.)
- `a.exe`: Compiled output (Windows executable).

## Developer Workflows
- **Build:** Compile with a C compiler, e.g.:
  ```sh
  gcc project.c -o a.exe
  ```
- **Run:** Execute `a.exe` in the project root.
- **Test:** No automated tests are present; manual testing via the menu is required.
- **Debug:** Use standard C debugging tools (e.g., gdb, VS Code debugger).

## Project Conventions
- All data is stored in CSV files in the project root.
- Functions for user input use dynamic memory allocation and require manual `free()` calls.
- Menu-driven interface: all features are accessed via numbered menu options.
- Error handling is basic: most errors print a message and return.
- No external dependencies or libraries beyond the C standard library.

## Patterns & Examples
- Adding a seminar: prompts for name, date, speaker, and participant count, then appends to `Table.csv`.
- Data is read/written as plain text, comma-separated values.
- Example CSV row: `SeminarName,SeminarDate,Participants,Speaker`

## Integration Points
- No network or external service integration.
- All persistent data is local (CSV files).

## Recommendations for AI Agents
- Follow the menu-driven structure for new features.
- Use the same CSV format for any new data files.
- Keep all source and data files in the project root unless otherwise specified.
- When adding new features, update the menu and main switch-case in `main()`.

---
If any conventions or workflows are unclear, please ask for clarification or examples from the user.
