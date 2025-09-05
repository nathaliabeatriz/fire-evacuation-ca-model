<h2 align="center"> Scientific Research Project: Pedestrian Evacuation Simulations modeled by Cellular Automata during Forest Fires in the Cerrado Biome</h2>
<p align="center">
  <a href="#-overview">Overview</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-system-description">System Description</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-publications">Publications</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#license">License</a>
</p>
<p align="center">
  <img alt="License" src="https://img.shields.io/badge/License-Apache_2.0-orange.svg">
</p>

### 📝 Overview
- This repository contains the code and data for the Scientific Initiation project "Pedestrian Evacuation Simulations modeled by Cellular Automata during Forest Fires in the Cerrado Biome", conducted under the guidance of Danielli Araújo Lima (<a href="https://buscatextual.cnpq.br/buscatextual/visualizacv.do?id=K4472540H5&tokenCaptchar=03AFcWeA5XFZOb2jOmkWB4ZkowTw7_Xg239BvN3AVem82LsovZMWvypHo25qUOa8U-gpefj--pZWHPsCKF_iLZEopxkU3n32qQZJB6oh_8wGcGr_z543dvttK9Dtixoqh7P7iZSc3ALMWNj5YYI9aQnkloJ6Rg3ONOYp_4Yli74-ntsa4Bi6Kp67vmMq02oFtfh3mXmFJ4j_ABmMQUvmlXniBadzXRu5bn0qXSeIRcIi0Zp1ejyOToXT4S8T338MocEkmfyJv36VbXol9-27Nt-G4IBT1zBIUZ9HfREkfdpJEvetpoMV9wvNv6EU7mYjDVXqn6FRdHOyYxjB0vuUNV3zJ5CSQtjfnGVBpAoYl-oU3KfiHuoBKijek02odCPCOyMPqAPE7ZIy6qyA7N1U6jZzyXFqUVg04sHQeLjNJFv2NjUOr1ezb3xbX1qk_k5ocsjmqiuoe2NIzHrXdqPa9cOBcr_KL7LiF16ZwGVorNeqeKTGWzelvv0ChYk3aHDWiLEpOLqZzQay-sJAy7BP8yJ83T0xF3DH3E9xbAJMlqBtJ8cph9kbjdim2fXnm3QFppTQMb_kAUFWHZoddG4bqR3-6x1StQrCSRrttLc_QJ9v18oiO6IsuqlLeGT9krm65KZx12zWFq_MILSlrWG10y266rzbfUcIVG5Hg2xz62siR9v-ScbOMJBPXu0GFOJJk2vmvO87dIYMin-epJgEqN9eb7rt8A-KbeAskZn8pIWwLKEwowuZqgn0RN6IAoj3ajv8vnZcVQb5VyCMigl9_56KhwD3-bilhqufiLrQRCL_KoBC3ygGZMcjrAcXHCGNHQLUq4rqCSOvjShbMaGXzymVuiVbndtFue-ghU-fD07uqnmuD77aVx7k7HyUS3rcS-0dN_seY6AsuiS-e7gjEMJMV1wf8ZmLPvRtOIs0L0HwGcllNXV4p40bwdJtIZrlTO3u4Kj4CLX-9z_xMt2AsdoERIofq5T5hlmA">Lattes</a>) at Instituto Federal do Triângulo Mineiro.
- The project aims to develop a cellular automata-based model to simulate pedestrian evacuation dynamics in the Sete Cidades National Park (Piauí, Brazil), incorporating fire propagation scenarios to assess emergency response strategies.
- Through this project, we try to help ensure safe interactions between society and the environment.

---

### 💻 System Description  
The simulation system was implemented in C++, with some results visualized and analyzed using MATLAB for enhanced data interpretation.

### 📂 Source Structure
```plaintext
src/
├── heatmaps/                      # Heatmaps generated to analyse the evacuation dynamics
├── images/                        # Input maps of Sete Cidades NP and output simulation visualizations
├── result_files/                  # Simulations results
├── Makefile                       # Build automation and compilation configuration
├── auxiliary_functions.cpp        # Helper functions
├── floor_field.cpp                # Static and dynamic floor field implementations for pathfind
├── main.cpp                       # Runnable file, core simulation loop and scenario initialization
├── pedestrian_movement.cpp        # Pedestrian decision logic and collision avoidance functions
└── utils.cpp                      # System parameters and global constants configuration
```

---
### 📝 Publications 
- 11º Encontro de Ensino Pesquisa e Extensão (EnPE)
  - <a href="http://enpe.ptc.iftm.edu.br/index.php/enpe/article/view/411">Access Publication</a>
  - <a href="https://www.researchgate.net/publication/390795313_ANALISE_DO_DESLOCAMENTO_DE_PEDESTRES_EM_EMERGENCIAS_SIMULACAO_DE_AUTOMATOS_CELULARES_NO_PARQUE_NACIONAL_DE_SETE_CIDADES">Access Full-text </a> 
- XVI Workshop de Computação Aplicada à Gestão do Meio Ambiente e Recursos Naturais
  - <a href="https://sol.sbc.org.br/index.php/wcama/article/view/36085">Access Publication</a> 
---

### License
This project is under the Apache License, Version 2.0.
