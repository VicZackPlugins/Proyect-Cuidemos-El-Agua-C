# 🚀 GUÍA GIT INFALIBLE PARA EL EQUIPO (PROYECTOS EN C)

Esta guía está hecha a prueba de errores. Síganla paso a paso cada vez que se sienten a programar en las computadoras de la universidad o en sus laptops personales.

---

## 🛠️ SECCIÓN 1: SETUP (Primera carga / Computadoras de la U)

Ejecuta esta sección cada semana si estás en una PC de la universidad, o la primera vez que descargues el proyecto en tu laptop propia.

### 1. Configurar tu identidad (Obligatorio)
Si no haces esto, Git te rechazará los cambios. Pon tus datos en la terminal de VS Code:

```bash
git config --global user.name "Tu Nombre"
git config --global user.email "tu_correo@ejemplo.com"
```

### 2. Configurar el "Antídoto" de errores (Evita el bloqueo de rebase)
Este comando asegura que Git una los códigos de forma tradicional y no se trabe pidiendo configuraciones raras:

```bash
git config --global pull.rebase false
```

### 3. Configuración del archivo `.gitignore` (Evita subir `.exe` y temporales)
Crea un archivo llamado exactamente `.gitignore` en la raíz de tu proyecto y agrega estas líneas para que no se suban ejecutables ni archivos basura:

```text
# Ejecutables
*.exe
*.out

# Archivos objeto
*.o
*.obj

# Carpeta de configuración de VS Code
.vscode/
```

### 4. Descargar el proyecto por primera vez

#### 💡 Opción A (Clonar desde la terminal):
Ve a la carpeta de la PC donde quieras trabajar, abre la terminal y clona el repositorio:

```bash
git clone https://github.com/VicZackPlugins/Proyect-Cuidemos-El-Agua-C.git
```
Luego abre esa carpeta clonada en VS Code (`Archivo > Abrir carpeta...`).

#### 💡 Opción B (Si ya tienes la carpeta abierta en VS Code):
1. Presiona `Ctrl + Shift + G` y haz clic en **"Inicializar repositorio"** (o ejecuta `git init` en la terminal).
2. Vincula el repositorio remoto ejecutando:

```bash
git remote add origin https://github.com/VicZackPlugins/Proyect-Cuidemos-El-Agua-C.git
```

---

## 🔄 SECCIÓN 2: FLUJO DE TRABAJO A PRUEBA DE ERRORES

Sigan este circuito a rajatabla cada vez que vayan a programar para que nunca más se les borre el código ni se les dupliquen líneas.

### 🛠️ PASO A: Antes de escribir una sola línea de código
Siempre empieza tu jornada trayendo lo que tus compañeros avanzaron mientras tú dormías:

```bash
git fetch --all
git pull origin main
```

### 💻 PASO B: Escribe tu código en C
Programa tus funciones, compila y asegúrate de que el código corra bien localmente.

### 💾 PASO C: Guardar localmente (Commit)
Cuando tu código funcione y esté listo para compartir, guárdalo en tu Git local:

```bash
git add .
git commit -m "Explicacion corta de lo que agregaste"
```

### 📡 PASO D: El filtro previo al Push (¡Crucial!)
Antes de subir tu código, debes fusionarlo con lo que otros hayan subido en ese mismo instante. Ejecuta:

```bash
git pull origin main --no-rebase
```

*(Si el comando anterior da error de ramas divergentes, ejecuta en orden: `git fetch origin` y luego `git merge origin/main`)*

* **ESCENARIO 1 (Todo limpio):** La terminal dice `Already up to date` o hace un `Merge` automático sin quejas. Pasa directo al **PASO E**.
* **ESCENARIO 2 (¡Conflicto de colores!):** Si VS Code te pinta el código de verde y azul con flechas (`<<<<<<< HEAD`), ¡no cierres VS Code!. Mira las líneas en conflicto y usa los botones flotantes que aparecen arriba del código:
  * **Accept Current Change:** Deja tu línea y borra la de tu compa.
  * **Accept Incoming Change:** Borra tu línea y deja la de tu compa.
  * **Accept Both Changes:** Deja ambas líneas juntas.
  
  **Para cerrar el conflicto:** Una vez que el archivo `.c` quede limpio y sin colores raros, guarda el archivo (`Ctrl + S`) y ejecuta en la terminal:
  ```bash
  git add .
  git commit -m "Conflictos resueltos en equipo"
  ```

### 🚀 PASO E: Subir el código a la nube
Ahora que tu código está fusionado y limpio, envíalo para que tu equipo lo pueda descargar:

```bash
git push origin main
```

---

## 🚨 SECCIÓN 3: COMANDOS ÚTILES Y BOTÓN DE EMERGENCIA

* **¿El pull dio error de "divergent branches" o no te deja avanzar?**
  Fuerza la fusión tradicional sin perder tu trabajo:
  ```bash
  git fetch origin
  git merge origin/main --no-ff
  ```

* **¿Entraste en pánico por un conflicto y quieres deshacer el intento de merge?**
  ```bash
  git merge --abort
  ```

* **¿El botón de emergencia absoluto?** 
  Si editaron algo en la web y tu VS Code local quedó hecho un desastre, este comando borra lo que tienes en la PC y te deja el código exactamente igual a como está en GitHub *(salva tu código en un bloc de notas antes de usarlo)*:
  ```bash
  git fetch origin
  git reset --hard origin/main
  ```

* **¿Quieres saber qué archivos tocaste o si te falta hacer commit?**
  ```bash
  git status
  ```

* **¿Hiciste un commit local pero te diste cuenta de que te faltó una línea?**
  Escribe la línea, guarda el archivo y ejecuta esto para sumarlo al commit anterior sin crear uno nuevo:
  ```bash
  git add .
  git commit --amend --no-edit
  ```

* **¿Subieron un `.exe` por error a GitHub y quieren quitarlo?**
  ```bash
  git rm --cached *.exe
  git add .
  git commit -m "Eliminar ejecutables del repositorio"
  git push origin main
  ```
