- Implement systick handler 

- then test it using printf

<img src="STM32CubeWORKSPACE - MyScheduler_Src_main.c - STM32CubeIDE 5_3_2024 4_01_46 PM.png" alt="SWV" width="1647" height="507">

That output is expected as the 4 tasks share the same resource without memory protection. 

- Don't forget to include <strong><stdio.h></strong> and enable serial SWV from debug configurations.

<img src="STM32CubeWORKSPACE - MyScheduler_Src_main.c - STM32CubeIDE 5_3_2024 4_31_06 PM.png" alt="debug configurations" width="782" height="593">