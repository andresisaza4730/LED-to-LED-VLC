## Results

This section presents the experimental results of simultaneous energy harvesting and communication using the red, green, and blue channels of the VLC-ID system.

---

### A. Red Channel: Energy Harvesting and Communication

**Energy Harvesting:**  
- *Green channel:* The voltage accumulation did not exceed 1 V, indicating that the green wavelength is not suitable for energy harvesting in this VLC-ID system.  
- *Blue channel:* The harvested voltage was lower than that of the green channel, confirming its inefficiency for energy storage applications.  

**Communication (Red channel):**  
- *Short distances:* Sensor saturation occurs, preventing proper data reception and decoding.  
- *At ~20 mm:* The red LED starts acting as a receiver, but data decoding is still not accurate.  
- *Conclusion:* While the red channel can receive data, improvements are required for reliable decoding at larger distances.  

![BER_Red](Figures/results/Ber_red.png)

---

### B. Green Channel: Energy Harvesting and Communication

**Energy Harvesting:**  
- *Red channel:* Generates an average voltage of ~3 V at short distances, suitable for low-cost VLC-ID applications.  
- *Blue channel:* Shows no usable voltage generation, contrary to expectations from previous studies.  

**Communication (Green channel):**  
- *Short distances:* Ineffective reception, indicating limitations.  
- *Optimal range (10–20 mm):* Achieves BER = 0%, proving reliable and precise communication.  
- *> 20 mm:* Communication deteriorates, requiring system design adjustments.  


![BER_Green](Figures/results/Ber_green.png)


---

### C. Blue Channel: Energy Harvesting and Communication

**Energy Harvesting:**  
- *Red channel:* Achieves ~3.35 V, confirming its high efficiency for VLC-ID energy harvesting.  
- *Green channel:* Reaches ~1.5 V, also suitable for storage applications.  

**Communication (Blue channel):**  
- *Up to 20 mm:* BER = 0%, ensuring accurate transmission and detection at short distances.  
- *> 20 mm:* Communication performance decreases, suggesting the need for system optimization.  

![BER_Blue](Figures/results/Ber_blue.png)

