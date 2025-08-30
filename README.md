# Visible Light Communication bidirectional LED to LED communication system and power generator for VLC-ID access system

**Manuscript ID: IEEE LATAM Submission ID: 9746**
**Authors:** Roger Alexander Martinez, Francisco Eugenio Lopez, Andrés Isaza  
**Affiliation:** Institución Universitaria ITM  

## Description
This repository contains all the scripts, data, and documentation necessary to reproduce the results of our bidirectional Visible Light Communication (VLC) system using LEDs 
as both transmitters and receivers. The system transmits data using On-Off Keying (OOK) modulation while harvesting energy at the receiver LED.

---

## Repository Structure

- **README.md** – This file  
- **LICENSE** – License of the project  
- **scripts/** – All code for the project  
  - **arduino_code/** – Arduino sketches (.ino)  
    - `Esclavo_VLC_ID_V2.ino`  
    - `Maestro_VLC_ID_V2.ino`  
    - `Texto_entre_ambos.ino`
    - `Texto_fijo_vlc.ino`    
  - **matlab_code/** – MATLAB scripts  
    - `signal_processing.m`  
- **databases/** – Experimental data  
  - `experiment_data.csv`  
- **figures/** – Images, graphs, LED setup photos  
  - `graph_experiment1.png`  
  - `graph_experiment2.png`  
  - `LED_setup.jpg`  
- **docs/** – Publications, papers, documentation  
  - `article.pdf`
