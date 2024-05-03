- Implement systick handler 

- then test it using printf

<img src="STM32CubeWORKSPACE - MyScheduler_Src_main.c - STM32CubeIDE 5_3_2024 4_01_46 PM.png" alt="SWV" width="600" height="200">

That output is expected as the 4 tasks share the same resource without memory protection. 