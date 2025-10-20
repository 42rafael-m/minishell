Informe Arquitectura

  - El bucle de lectura y ejecución ft_read_line en minishell.c:195 orquesta prompt, tokenizado y ejecución usando
    ft_tokens, ft_parse y ft_execute.
  - El motor de ejecución (exec/exec.c:15, exec/exec_pipe.c:173) delega entre builtins, comandos externos y pipelines
    con soporte de heredocs y señales.
  - El pipeline de parsing (parsing/lexing.c:120, parsing/parsing.c:101) gestiona tokenización, expansiones,
    redirecciones y composición de la lista enlazada de comandos t_cli.
  - El entorno incluye gestión propia de variables (parsing/shenv.c:1), utilidades libft/, y handlers de señal (parsing/
    signals.c:1) para cumplir la normativa de minishell.
  - Entorno en modo solo lectura, así que no pude crear el archivo solicitado; dejo el contenido listo para guardarlo
    como arquitectura_minishell.md.
  - Siguiente paso: guardar el reporte en arquitectura_minishell.md cuando haya permisos de escritura.
  - Contenido sugerido para arquitectura_minishell.md:

  # Minishell – Arquitectura

  ## 1. Análisis arquitectónico

  - `minishell.c:195-238` implementa el ciclo principal `ft_read_line`: configura señales (`ft_set_sig`), carga el
  entorno con `ft_load_env`, obtiene líneas con `readline`, almacena histórico y, tras cada iteración, reutiliza la
  lista `t_cli`.
  - La fase de **lexing/expansión** (`parsing/lexing.c:120`, `parsing/expansion.c:85`) tokeniza la línea, expande
  variables/estado de salida y resuelve wildcards (`parsing/wildcards.c:27`), manteniendo compatibilidad con heredocs
  y comillas.
  - El **parser** (`parsing/parsing.c:101`, `parsing/parsing1.c:77`) transforma los tokens en una lista enlazada de
  `t_cli`, configurando redirecciones, heredocs y operadores lógicos/pipes (`ft_parse_op`).
  - El **ejecutor** (`exec/exec.c:15`, `exec/exec_pipe.c:173`) decide entre builtins (`exec/builtins.c:15`), pipelines/
  heredocs, y procesos externos (`execute_command`) usando `fork/execve`, controlando señales (`parsing/signals.c:1`) y
  estado de salida.
  - La **gestión del entorno** (`parsing/shenv.c:1`, `exec/ft_cd.c:63`, `exec/ft_export.c:58`, `exec/ft_unset.c:1`)
  mantiene un `t_shenv` enlazado y sincroniza variables especiales (`PWD`, `OLDPWD`, etc.).
  - Utilidades y memoria recaen en `libft/` (funciones `ft_*` de cadenas, listas y arrays), que actúa como capa de
  servicios compartidos.
  - El subject específico no se encuentra en el repositorio; el diseño sigue los requisitos estándar de Minishell
  (readline, builtins, pipes, redirecciones, variables de entorno y señalización interactiva).

  ## 2. Tecnologías utilizadas

  - Lenguaje C con estándar POSIX (syscalls: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `ioctl`).
  - GNU Readline (`-lreadline`) para prompt interactivo e histórico.
  - Biblioteca propia `libft` (colección de utilidades `ft_*`).
  - Makefile para orquestar la compilación (`cc`, `-g` y includes de `libft`).

  ## 3. Estructura de carpetas y archivos

  ```text
  .
  ├── minishell.c            # Bucle principal, configuración de señales y entrada
  ├── minishell.h            # Definiciones de structs, macros y prototipos
  ├── exec/                  # Motor de ejecución (builtins, pipelines, procesos)
  │   ├── builtins.c
  │   ├── exec.c
  │   ├── exec_pipe.c
  │   ├── ft_cd.c
  │   ├── ft_export.c
  │   └── ft_unset.c
  ├── parsing/               # Lexing, parsing, expansiones, env interno, señales
  │   ├── lexing.c
  │   ├── lexing1.c
  │   ├── parsing.c
  │   ├── parsing1.c
  │   ├── expansion.c
  │   ├── heredoc.c
  │   ├── wildcards.c
  │   ├── wc_utils.c
  │   ├── shenv.c
  │   └── signals.c
  ├── libft/                 # Biblioteca auxiliar con funciones reutilizables
  │   ├── libft.h
  │   └── ft_*.c
  ├── Makefile               # Objetivo `minishell`, vínculo con `libft` y readline
  ├── main.c                 # Programa de pruebas puntual (no integrado en build)
  ├── log*.txt               # Ficheros de registro/notas
  └── arquitectura.md        # Requerimiento actual

  ## 4. Diagrama de arquitectura

  flowchart LR
      subgraph CLI
          A[ft_read_line\nminishell.c]
          B[readline/history]
      end
      subgraph Parser
          C[ft_tokens]
          D[ft_expand_tokens]
          E[ft_parse]
      end
      subgraph Executor
          F[ft_execute]
          G[execute_pipeline]
          H[execute_builtin]
          I[execute_command]
      end
      subgraph Builtins
          H1[echo/cd/pwd/export\nunset/env/exit]
      end
      subgraph Env
          J[ft_load_env / t_shenv]
          K[ft_getshenv / ft_setenv]
      end
      subgraph Libft
          L[libft utilities]
      end
      subgraph Signals
          S[ft_set_sig\ng_sig_rec]
      end

      A --> C --> D --> E --> F
      F --> G --> Env
      F --> H --> H1
      F --> I --> Env
      Parser --> Env
      CLI --> S
      Executor --> S
      Env --> Executor
      Libft --> Parser
      Libft --> Executor
      Libft --> Env
