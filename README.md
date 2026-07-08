# Terminal Tic-Tac-Toe Engine

A highly interactive, multi-mode console-based Tic-Tac-Toe implementation written entirely in C. The application leverages strict structural logic blocks to process game matrix spaces, distinct multi-tier AI bot difficulties, and automated persistent file logging.

## 🚀 Architectural Features

- **Multi-Difficulty AI Automation:** Features distinct procedural tracking steps across 3 unique difficulty levels:
  - **Easy:** Randomized matrix space selection.
  - **Medium:** Proactive defensive block processing to deny immediate opponent win states.
  - **Hard:** Advanced dual-tier logical processing (checks for direct offensive paths first before executing structural defensive positioning blocks).
- **Persistent Local File Storage:** Integrates seamless file stream IO operations (`fopen`/`fprintf`) to write persistent game diagnostics (`results.txt`) tracking matchup types, dynamic scores, and chosen difficulty settings.
- **Dynamic Terminal Customization:** Leverages structural ANSI escape sequences (`\033[...]`) to dynamically inject vivid foreground colors directly into the console output.
- **Comprehensive Boundary Verification:** Employs explicit array checking structures to seamlessly invalidate out-of-bounds inputs or duplicate cell selections.

## 🛠️ Tech Stack

- **Language:** Procedural C (C99 standard or higher)
- **Standard Header Subsystems:** `<stdio.h>`, `<stdlib.h>`, `<time.h>`, `<ctype.h>`, `<string.h>`

## 📁 Repository View

```text
├── TICTAC.c           # Primary application logic, main execution pipeline, and menus
└── README.md        # Documentation and runtime configurations
