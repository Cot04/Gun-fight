# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

# Archivos fuente
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Archivos objeto
OBJ_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Librerías de SFML
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Nombre del ejecutable
EXE := $(BIN_DIR)/game

# Regla para compilar los archivos .cpp en archivos .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR) # Crear directorio de bin si no existe
	g++ -c $< -o $@ -I$(INCLUDE_DIR) $(SFML)

# Regla para enlazar los archivos .o y generar el ejecutable
$(EXE): $(OBJ_FILES)
	g++ $^ -o $@ $(SFML)

# Regla por defecto para compilar y enlazar todo
all: $(EXE)

# Regla para ejecutar el juego
run: $(EXE)
	./$(EXE)

# Regla para limpiar los archivos generados
clean:
	rm -f $(BIN_DIR)/*.o $(EXE)

# Declarar las reglas phony para evitar problemas con nombres de archivos
.PHONY: all clean run
