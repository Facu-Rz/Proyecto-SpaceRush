# Configuración de VS Code – IntelliSense

Esta carpeta es utilizada por Visual Studio Code para configurar:
- IntelliSense (autocompletado y análisis de includes)
- Debug (launch.json)
- Tasks (si se agregan en el futuro)

IMPORTANTE:
- Esta carpeta NO debe renombrarse
- VS Code solo reconoce la carpeta con nombre `.vscode`
- El archivo `c_cpp_properties.json` es necesario para que
  SDL2 y otras librerías sean reconocidas por IntelliSense

Si los `#include` aparecen subrayados en rojo pero el proyecto compila,
revisar primero esta carpeta.
