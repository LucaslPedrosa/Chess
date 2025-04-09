# ♟️ Chess Game (In Development)

A chess game written in modern **C++** using the **SFML 3.0.0** graphics library. This is a personal project to explore game logic, UI development, modular design, and modern C++ practices.

---

## 🚧 Project Status

- ✅ Board and piece rendering with SFML  
- ✅ Piece selection and basic movement system  
- ✅ Modular structure with layered design (core, game, rendering)  
- 🔜 Full chess rules implementation  
- 🔜 Main menu with game mode selection  
- 🔜 AI mode using Stockfish engine  
- 🔜 Online multiplayer mode  
- 🔜 Time control and player name display

---

## 🧩 Project Structure

```bash
src/
├── core/         # Game logic and rules
├── game/         # Game state and mode management
├── ...           # Other modules
assets/
├── textures/
│   ├── boards/   # Board textures
│   └── pieces/   # Chess piece textures
├── audio/
├── fonts/
```

---

## 🖥️ Compilation

Requirements:
- **GCC** compiler (tested with MinGW 14.2.0 via MSYS2)
- **SFML 3.0.0** installed locally

### 🔧 Build arguments (VS Code - `tasks.json`)

```bash
-fdiagnostics-color=always
-g
${workspaceFolder}/src/*.cpp
${workspaceFolder}/src/core/*.cpp
${workspaceFolder}/src/game/*.cpp
-I${workspaceFolder}/src/core
-I${workspaceFolder}/src/games
-I"C:/SFML/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/include"
-o ${workspaceFolder}/bin/chess.exe
-L"C:/SFML/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/lib"
-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

---

## 🎯 Goals

- Create a fully playable chess game with clean and interactive UI
- Support for multiple game modes (local, AI, online)
- Complete and validated chess rule logic
- Decoupled and testable design
- Visual style customization (themes for pieces and boards)

---

## 📸 Coming Soon

- GIFs and screenshots of the game in action
- Link to demo video
- Initial menu UI and mode selection

---

## 📜 License

Personal and educational project – free to use for learning purposes.